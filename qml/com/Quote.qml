import QtQuick 2.13
import QtQuick.Controls 2.12
import "ui.js" as UI

Item {
    id: root
    property alias text: txt.text
    property alias textColor: txt.color
    property alias color: e_rect.color
    height: e_rect.height + 2
    Rectangle {
        id: e_rect
        color: Qt.rgba(0.1,0.1,0.1,0.9)
        width: parent.width
        height: txt.height + 8
        radius: 8
        x: 10
        y: 2
        Txt {
            id: txt
            width: parent.width
            y: 4
            onPressed: function(mouse) {
                if(root.parent && root.parent.pressed) {
                    root.parent.pressed(mouse);
                }
            }
            onReleased: function(mouse) {
                if(root.parent && root.parent.released) {
                    root.parent.released(mouse);
                }
            }
            Keys.onPressed:function(event) {
                if(root.parent && root.parent.onKeyPressed) {
                    root.parent.onKeyPressed(event);
                }
            }
        }
    }
    function getTxt() {
        return txt;
    }
}
