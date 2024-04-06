import QtQuick 2.0
import QtQuick.Controls 2.12
import "../com/com.js" as Com
import "../book/Book.js" as Book
import "ui.js" as UI

Rectangle {
    id: note_list_rect
    width: note_list_col.width
    height: note_list_col.height + 20
    color: "transparent"
    Column {
        id: note_list_col
        anchors {
            top:parent.top
            topMargin: 10
            left: parent.left
            leftMargin: 8
        }
        spacing: 10
//        Rectangle {
//            color: "transparent"
//            height: 6
//            width: parent.width
//            visible: visible_date
//        }
//        Rectangle {
//            height: 20
//            width: 100
//            radius: 10
//            visible: visible_date
//            anchors.left: parent.left
//            anchors.leftMargin: note_list.width/2 - width/2
//            color:"black"
//            Text {
//                anchors.centerIn: parent
//                text: date_str
//                font {
//                    pointSize: UI.date_font_size
//                    bold:true
//                }
//                color: "white"
//            }
//        }
//        Rectangle {
//            color: "transparent"
//            height: 6
//            width: parent.width
//            visible: visible_date
//        }
        Row {
            width: note_list.width
            height: cols.height
            Column {
                id: cols
                width: parent.width - 40
                spacing: 5
                property string qmlStr: qmls
                onQmlStrChanged: {
//                    console.log("qmlStr changed", qmlStr);
                    if(qmls) {
                        cols.data = [];
                        let arr = JSON.parse(qmlStr);
                        for(let i = 0; i < arr.length; i++) {
                            let qml = arr[i];
                            let o = Qt.createQmlObject(qml, cols, "dy_"+i);
                        }
                    }
                }
            }
        }

        Row {
            spacing: 15
            width: parent.width - 15
            layoutDirection: Qt.RightToLeft
            Text {
                width: 80
                font.pointSize: UI.ui_font_pk_time
                color:"#898989"
                text: (date_str + " " + time_str)
                horizontalAlignment: Text.AlignRight
            }
            Text {
                font.pointSize: UI.ui_font_pk_time
                color:"#898989"
                text: Com.getPos(pos0, pos1)
                horizontalAlignment: Text.AlignRight
            }
//            Circle {
//                visible: bj
//            }
            TagLine {
                id:tag_line
                tag_ids: tags
                delegate: tag_view.tagManager
            }
        }
    }
    Rectangle {
        x:0
        y:note_list_rect.height;
        width: note_list.width
        height: 1
        color: "#E8E8E8"
    }
    Rectangle {
        x:0
        y:0
        visible: index === note_list_view.currentIndex
        width: 10
        height: Com.min(note_list_rect.height, 50)
        color: UI.ui_highlight_color
        Text {
            text:Com.verText(index+1)
            font.pointSize: 10
            width: parent.width
            x: parent.width/2-width/2+1
            y: parent.height/2-height/2+7
            color: "white"
            verticalAlignment: Text.AlignVCenter
        }
    }
    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: function(mouse){
            note_list_view.currentIndex = index;
            work_list_view.forceActiveFocus();
            if(mouse.button === Qt.RightButton) {
                mi_pic_model.visible = imgs.length > 0;
                menu_right_note.open();
            }
        }
        onDoubleClicked: {
            Book.openEditPopup();
        }
        onMouseXChanged: {
            if(tags) {
                if(mouseY>parent.height-30){
                    mouse.accepted = false;
                }
            }
        }
    }
    function updateTags(tags) {
        tag_line.tag_ids = tags;
    }
}
