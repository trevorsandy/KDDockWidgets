/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.9

/**
 * @brief Base component for title bars.
 *
 * You need to derive from it to give it a GUI appearance you desire.
 * See TitleBar.qml for an example.
 * Basically you should:
 *  - Show the title
 *  - Show float and close buttons. Bind them to floatButtonVisible, closeButtonEnabled etc.
 *  - emit closeButtonClicked(), floatButtonClicked() as needed
 */
Rectangle {
    id: root

    readonly property QtObject titleBarCpp: parent.titleBarCpp // It's set in the loader
    readonly property string title: titleBarCpp ? titleBarCpp.title : ""
    readonly property bool floatButtonVisible: titleBarCpp && titleBarCpp.floatButtonVisible
    readonly property bool closeButtonEnabled: titleBarCpp && titleBarCpp.closeButtonEnabled

    // So the tests can send mouse events programatically
    readonly property QtObject mouseAreaForTests: dragMouseArea

    /// The hight the title bar should have when visible. Override in your component with another value
    /// Don't set 'hight' directly in the overridden component
    property int heightWhenVisible: 30

    /// @brief Signal emitted by a TitleBar.qml component when the close button is clicked
    signal closeButtonClicked();

    /// @brief Signal emitted by a TitleBar.qml component when the float button is clicked
    signal floatButtonClicked();

    visible: titleBarCpp && titleBarCpp.visible
    height: visible ? heightWhenVisible : 0
    implicitHeight: heightWhenVisible

    MouseArea {
        id: dragMouseArea
        objectName: "draggableMouseArea"
        anchors.fill: parent
        onDoubleClicked: {
            if (titleBarCpp)
                titleBarCpp.onDoubleClicked();
        }
    }

    onTitleBarCppChanged: {
        if (titleBarCpp) {
            titleBarCpp.filterEvents(dragMouseArea)

            // Setting just so the unit-tests can access the buttons
            titleBarCpp.titleBarQmlItem = this;
        }
    }

    onCloseButtonClicked: {
        titleBarCpp.onCloseClicked();
    }

    onFloatButtonClicked: {
        titleBarCpp.onFloatClicked();
    }
}
