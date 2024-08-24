import QtQuick 2.13
import QtQuick.Controls 2.12
import "ui.js" as UI

Rectangle {
    id: root
    property alias text: txt.text
    property alias textColor: txt.color
    color: Qt.rgba(0.1,0.1,0.1,0.9)
    height: scroll.height
    radius: 8
    x: 10
    ScrollView {
        id: scroll
        width: parent.width
        height: txt.height
        contentWidth:  txt.width - 5
        contentHeight: height
        clip: true
        Txt {
            id: txt
            width: root.width
            x: -5
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
        ScrollBar.vertical.policy: ScrollBar.AlwaysOff
        ScrollBar.horizontal.policy: ScrollBar.AsNeeded
        // ScrollBar.horizontal: ScrollBar {
        //     id: scrollBar
            // parent: scroll.parent
            // anchors.left: scroll.left
            // anchors.right: scroll.right
            // anchors.bottom: scroll.bottom
            // height: 10
        // }
    }
    // Flickable {
    //     id: flickable
    //     width: parent.width
    //     height: txt.height
    //     flickableDirection: Flickable.HorizontalFlick
    //     TextArea.flickable: Txt {
    //         id: txt
    //         width: parent.width
    //         x: -5
    //         onPressed: function(mouse) {
    //             if(root.parent && root.parent.pressed) {
    //                 root.parent.pressed(mouse);
    //             }
    //         }
    //         onReleased: function(mouse) {
    //             if(root.parent && root.parent.released) {
    //                 root.parent.released(mouse);
    //             }
    //         }
    //         Keys.onPressed:function(event) {
    //             if(root.parent && root.parent.onKeyPressed) {
    //                 root.parent.onKeyPressed(event);
    //             }
    //         }
    //     }
    //     ScrollBar.horizontal: ScrollBar {
    //     }
    // }
    function getTxt() {
        return txt;
    }
}
