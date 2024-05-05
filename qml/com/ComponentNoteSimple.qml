import QtQuick 2.0
import QtQuick.Controls 2.12
import "../com/com.js" as Com
import "../book/Book.js" as Book
import "ui.js" as UI

Rectangle {
    id: root_com_note_simple
    width: note_list.width
    height: cols.height
    color: "transparent"
    MouseArea {
        anchors.fill: parent
        Column {
            id: cols
            x: 10
            width: parent.width - 60
            spacing: 5
            property var qmlArr: qmls
            onQmlArrChanged: {
                cols.data = [];
                if(qmlArr) {
                    let i = 0;
                    for(let k in qmlArr) {
                        let qml = qmlArr[k];
                        let o = Qt.createQmlObject(qml, cols, "dy_"+i);
                        i++;
                    }
                }
            }
            function pressed(mouse) {
                note_list_view.currentIndex = index;
            }
            function released(mouse) {
                if (mouse.button === Qt.RightButton) {
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
        Rectangle {
            x:0
            y:0
            visible: index === note_list_view.currentIndex
            width: 10
            height: Com.max(Com.min(root_com_note_simple.height, 50), e_num.height)
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
    }
}

