import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    id: root
    property alias img: image.source
    property int st: 0
    signal clicked
    signal entered_
    signal exited_

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
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton| Qt.RightButton;
        onClicked: {
            click()
        }
        onEntered: {
            entered_()
        }
        onExited: {
            exited_()
        }
   }
   function reset() {}
   function click() {}
}
