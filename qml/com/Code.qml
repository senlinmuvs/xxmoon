import QtQuick 2.13
import QtQuick.Controls 2.12
import "ui.js" as UI

Rectangle {
    id: root
    property alias text: txt.text
    property alias textColor: txt.color
    color: Qt.rgba(0.1,0.1,0.1,0.9)
    height: flickable.height
    radius: 8
    x: 10
    Flickable {
        id: flickable
        width: parent.width
        height: txt.height
        flickableDirection: Flickable.HorizontalFlick
        TextArea.flickable: Txt {
            id: txt
            width: parent.width
            x: -5
        }
        ScrollBar.horizontal: ScrollBar {}
    }
    function getTxt() {
        return txt;
    }
}
