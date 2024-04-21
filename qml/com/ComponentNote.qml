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

    MouseArea {
        anchors.fill: parent
        Column {
            id: note_list_col
            anchors {
                top:parent.top
                topMargin: 10
                left: parent.left
                leftMargin: 8
            }
            spacing: 10
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
                    function pressed(mouse) {
                        note_list_view.currentIndex = index;
                    }
                    function released(mouse) {
                        if (mouse.button === Qt.RightButton) {
                            mi_pic_model.visible = imgs.length > 0;
                            menu_right_note.open();
                        }
                    }
                    function onClickImg(src, mouse) {
                        if (mouse.button === Qt.RightButton) {
                            menu_right_note.open();
                        } else {
                            Book.openImgView(src);
                        }
                    }
                    function onKeyPressed(event) {
                        Book.onKeyPressed(event);
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
            height: Com.max(Com.min(note_list_rect.height, 50), e_num.height)
            color: UI.ui_highlight_color
            Text {
                id: e_num
                text:Com.verText(index+1)
                font.pointSize: 10
                width: parent.width
                x: parent.width/2-width/2
                y: parent.height/2-height/2
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                anchors.centerIn: parent
            }
        }
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onPressed:function(mouse) {
            note_list_view.currentIndex = index;
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
