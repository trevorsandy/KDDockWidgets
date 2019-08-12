/*
  This file is part of KDDockWidgets.

  Copyright (C) 2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file
 * @brief A class that is QWidget when building for QtWidgets, and QObject when building for QtQuick.
 *
 * Allows to have the same code base supporting both stacks.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KDDOCKWIDGETS_QWIDGETADAPTERQUICK_H
#define KDDOCKWIDGETS_QWIDGETADAPTERQUICK_H

#include "docks_export.h"

#include <QQuickItem>
#include <QObject>
#include <QCloseEvent>

class QWindow;

namespace KDDockWidgets {

class FloatingWindow;
/*
class QuickItem : public QQuickItem
{
public:
    explicit QuickItem(QQuickItem *parent)
        : QQuickItem(parent)
    {
    }
    ~QuickItem() override;

    QRect geometry() const { return {}; }
    void setGeometry(QRect) {}

    void releaseMouse()
    {
        ungrabMouse();
    }
};
QuickItem::~QuickItem() {}
*/

class DOCKS_EXPORT QWidgetAdapter : public QObject
{
    Q_OBJECT
public:
    explicit QWidgetAdapter(QObject *parent = nullptr, Qt::WindowFlags f = {});
    ~QWidgetAdapter() override;

    ///@brief returns the FloatingWindow this widget is in, otherwise nullptr
    FloatingWindow *floatingWindow() const;

    void setFlag(Qt::WindowType, bool on = true);

    void setGeometry(QRect);
    QRect geometry() const;
    QRect rect() const;
    void show();
    bool isVisible() const { return true; }
    void setVisible(bool);
    void setEnabled(bool) {}
    int width() const { return 0; }
    int height() const { return 0; }
    void setFixedHeight(int) {}
    void setFixedWidth(int) {}
    void raise();
    void update() {}
    QSize size() const {return {}; }
    QSize minimumSizeHint() const {return {}; }
    QSize minimumSize() const {return {}; }
    int minimumHeight() const {return {};}
    int minimumWidth() const {return {};}
    int x() const { return 0; }
    int y() const { return 0; }

    void grabMouse();
    void releaseMouse();
    void setMinimumSize(QSize);
    void resize(QSize);
    bool isWindow() const { return false; }

    QWindow *windowHandle() const;
    QWidgetAdapter *window() const { return nullptr; }
    QWidgetAdapter *parentWidget() const { return nullptr; }
    QPoint mapToGlobal(QPoint) const { return {}; }
    QPoint mapFromGlobal(QPoint) const { return {}; }
    bool testAttribute(Qt::WidgetAttribute) { return false; }

    void setWindowTitle(const QString &) {}
    void setWindowIcon(const QIcon &) {}
    void close() {}
    QWidgetAdapter* childAt(QPoint) { return nullptr; }

protected:
    void raiseAndActivate();

    virtual bool onResize(QSize oldSize, QSize newSize);
    virtual void onLayoutRequest();
    virtual void onMousePress();
    virtual void onMouseMove(QPoint globalPos);
    virtual void onMouseRelease();
    virtual void onCloseEvent(QCloseEvent *);
};

}

#endif