import QtQuick 2.0
import "com.js" as Com

Rectangle {
    id: root
    property string src
    anchors.horizontalCenterOffset: 15
    MyImage {
        id: img
        source: src
        anchors.fill: parent
    }
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            if(root.parent.onEnterImg) {
                root.parent.onEnterImg();
            }
        }
        onExited: {
            if(root.parent.onExitImg) {
                root.parent.onExitImg();
            }
        }
        onClicked: {
            if(root.parent.onClickImg) {
                root.parent.onClickImg(src);
            }
        }
    }
    Component.onCompleted: {
        if(parent) {
            anchors.horizontalCenter = parent.horizontalCenter;
        }
    }
}
