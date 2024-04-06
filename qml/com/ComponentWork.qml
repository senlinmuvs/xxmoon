import QtQuick 2.0
import "com.js" as Com
import "../book/Book.js" as Book
import "ui.js" as UI

Rectangle {
    id: work_list_rect
    width: work_list.width
    height: work_list_col.height + 20
    color: "transparent"

    Column {
        id: work_list_col
        width: parent.width
        x: 10
        y: 10
        spacing: 10
        Rectangle {
            color: "transparent"
            height: 10
            width: parent.width
            visible: visible_time
        }
        Rectangle {
            height: 20
            width: 80
            radius: 10
            visible: visible_time
            anchors.horizontalCenter: parent.horizontalCenter
            Text {
                anchors.centerIn: parent
                text: time_str
                font {
                    pointSize: UI.date_font_size
                    bold:true
                }
                color: "black"
            }
        }
        Rectangle {
            color: "transparent"
            height: 10
            width: parent.width
            visible: visible_time
        }
        Row {
            spacing: 10
            Text {
                textFormat: Text.RichText
                width: work_list.width - 50
                text: search_bar.keys[1] ? Book.viewCont(name, search_bar.keys[2]) : name
                font {
                    pointSize: 16
                    bold: true
                }
                color: "white"
                wrapMode: Text.Wrap
            }
            Text {
                id: work_note_total
                text: total
                width: 25
                horizontalAlignment: Text.AlignRight
                font {
                    pointSize: UI.total_font_size
                }
                color:"#989898"
            }
        }
        Row {
            spacing: 10
            Text {
                width: work_list.width - e_extra.width - 25
                text: search_bar.keys[0] ? Book.viewCont(author, search_bar.keys[2]) : author
                font {
                    pointSize: 12
                }
                color:"#989898"
                wrapMode: Text.Wrap
            }
            Text {
                id: e_extra
                text: Com.parseTime(time, 1)[0] + " " + from_str
                width: 70
                horizontalAlignment: Text.AlignRight
                font {
                    pointSize: UI.total_font_size
                }
                color:"#989898"
            }
        }
    }
    Rectangle {
        x:0
        y:work_list_rect.height
        width: work_list.width
        height: 1
        color: "#686868"
    }
    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: function(mouse){
            work_list_view.forceActiveFocus();
            work_list_view.currentIndex = index;
            if (mouse.button === Qt.RightButton) {
                menu_work_right.open();
            }
        }
    }
}
