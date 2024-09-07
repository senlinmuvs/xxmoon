import QtQuick 2.0

Rectangle {
    id: root
    property string src
    property double scale:1
    anchors.horizontalCenterOffset: 5
    MyImage {
        id: img
        source: src
        anchors.fill: parent
    }
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onEntered: {
            if(root.parent && root.parent.onEnterImg) {
                root.parent.onEnterImg();
            }
            cursorShape = Qt.OpenHandCursor;
        }
        onExited: {
            if(root.parent && root.parent.onExitImg) {
                root.parent.onExitImg();
            }
            cursorShape = Qt.ArrowCursor;
        }
        onPressed: function(mouse) {
            if(root.parent && root.parent.pressed) {
                root.parent.pressed(mouse);
            }
        }
        onClicked: function(mouse) {
            if(root.parent && root.parent.onClickImg) {
                root.parent.onClickImg(src, mouse);
            }
        }
    }
    Component.onCompleted: {
        if(parent) {
            anchors.horizontalCenter = parent.horizontalCenter;
        }
    }
}
