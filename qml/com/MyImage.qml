import QtQuick 2.0
import QtGraphicalEffects 1.0
import "com.js" as Com

Rectangle {
    id: root
    width: 50
    height: 50
    color:"transparent"

    property alias img_radius: mask.radius
    property string source
    property alias clip: img.clip
    property alias enableMask: mask.visible
    property alias fillMode: img.fillMode

    Image {
        id: img
        anchors.fill: parent
        smooth: true
        visible: false
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
    Rectangle {
        id: mask
        color: "#FFFFFF"
        anchors.fill: parent
        radius: 5
        visible: !Com.isAnimation(root.source)
        antialiasing: true
        smooth: true
    }
    OpacityMask {
        id:mask_image
        anchors.fill: parent
        source: img
        maskSource: mask
        visible: !Com.isAnimation(root.source)
        antialiasing: true
    }
}
