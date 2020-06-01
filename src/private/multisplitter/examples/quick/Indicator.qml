import QtQuick 2.6
import com.kdab.kddockwidgets.multisplitter 1.0;

Image {
    id: root
    property int location: KDMultiSplitter.Location_None;
    property QtObject relativeTo: null

    width: 48
    height: 48

    function locationToStr() {
        switch (root.location) {
        case KDMultiSplitter.Location_OnLeft:
            return "left";
        case KDMultiSplitter.Location_OnRight:
            return "right";
        case KDMultiSplitter.Location_OnTop:
            return "top";
        case KDMultiSplitter.Location_OnBottom:
            return "bottom";
        }
    }

    function imageFileName() {
        if (relativeTo)
            return "inner_%1.png".arg(locationToStr())
        return "outter_%1.png".arg(locationToStr())
    }

    source:  "qrc:///img/classic_indicators/" + imageFileName()

    MouseArea {
        anchors.fill: parent
        onClicked: {
            _controller.addItem(root.location, root.relativeTo);
        }
    }
}
