import QtQuick 2.0

MyBtn {
    color: "transparent"
    property alias imgRadius: img.img_radius
    property alias src: img.source
    property alias imgWidth: img.width
    property alias imgHeight: img.height
    xx: dp(10)
    width: img.width + xx
    height: img.height + xx

    MyImage {
        id: img
        anchors.centerIn: parent
        img_radius: 1
        border.width: 0
        // enableMask: false
        width: parent.width - xx
        height: parent.height - xx
    }
}
