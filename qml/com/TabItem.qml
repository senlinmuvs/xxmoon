import QtQuick 2.0

Text {
    id: root
    y: 14
    width: 80
    height: 50
    text: ""
    color: "gray"
    font {
        pixelSize: 14
    }

    MouseArea {
        anchors.fill: parent;
        onClicked: {
            click();
        }
   }
   function click(){
   }
}
