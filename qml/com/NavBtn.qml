import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    id: root
    property alias img: image.source
    property int st: 0
    signal clicked

    color: "transparent"
    width: 32
    height: 32
    anchors.horizontalCenter: parent.horizontalCenter
    Image {
        id: image
        anchors.fill: parent
        source: ""
    }
    MouseArea {
        anchors.fill: parent;
        acceptedButtons: Qt.LeftButton| Qt.RightButton;
        onClicked: {
            click()
        }
   }
   function reset() {}
   function click() {}
}
