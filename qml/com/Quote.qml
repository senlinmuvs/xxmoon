import QtQuick 2.13
import QtQuick.Controls 2.12
import "ui.js" as UI

Rectangle {
    id: root
    property alias text: txt.text
    property alias textColor: txt.color
    color: Qt.rgba(0.1,0.1,0.1,0.9)
    height: txt.height + 8
    radius: 8
    x: 10

    Txt {
        id: txt
        width: parent.width
        y: 4
    }
    function getTxt() {
        return txt;
    }
}
