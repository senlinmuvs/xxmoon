import QtQuick
// import QtQuick.Effects
import "com.js" as Com

Rectangle {
    id: root
    width: 50
    height: 50
    color:"transparent"
    clip: true
    radius: 10
    property alias img_radius: root.radius
    property string source
    property alias fillMode: img.fillMode

    Image {
        id: img
        anchors.fill: parent
        smooth: true
        antialiasing: true
        source: root.source
        fillMode: Image.PreserveAspectFit
        cache: false
    }
    AnimatedImage {
        visible: Com.isAnimation(root.source)
        anchors.fill: parent
        source: root.source
        onStatusChanged: playing = (status == AnimatedImage.Ready)
    }
    // Rectangle {
    //     id: mask
    //     color: "#FFFFFF"
    //     anchors.fill: parent
    //     radius: 5
    //     visible: !Com.isAnimation(root.source)
    //     antialiasing: true
    //     smooth: true
    // }
    // OpacityMask {
    //     id:mask_image
    //     anchors.fill: parent
    //     source: img
    //     maskSource: mask
    //     visible: !Com.isAnimation(root.source)
    //     antialiasing: true
    // }
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onEntered: {
            if(root && root.onEnterImg) {
                root.onEnterImg();
            }
            cursorShape = Qt.OpenHandCursor;
        }
        onExited: {
            if(root && root.onExitImg) {
                root.onExitImg();
            }
            cursorShape = Qt.ArrowCursor;
        }
        onPressed: function(mouse) {
            if(root && root.pressed) {
                root.pressed(mouse);
            }
        }
        onClicked: function(mouse) {
            if(root && root.onClickImg) {
                root.onClickImg(source, mouse);
            }
        }
    }
    Component.onCompleted: {
        if(parent) {
            anchors.horizontalCenter = parent.horizontalCenter;
        }
    }
}
