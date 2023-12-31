import QtQuick 2.0

Rectangle {
    id:root
    width: 400;
    height: 30;
    color: "transparent";
    property alias title: text.text

    anchors.horizontalCenter: parent.horizontalCenter

    Rectangle {
        id: mark
        width: 8
        height: 8
        color: "red"
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        radius: width/2
    }
    Text {
        id: text
        anchors {
            top: mark.bottom
            topMargin: 3
            horizontalCenter: parent.horizontalCenter
        }
        text:""
        font {
            pointSize: 15
            bold: true
        }
        color:"#FFFFFF"
    }
}
