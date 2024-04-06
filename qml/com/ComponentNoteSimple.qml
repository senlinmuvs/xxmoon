import QtQuick 2.0
import QtQuick.Controls 2.12
import "../com/com.js" as Com
import "../book/Book.js" as Book
import "ui.js" as UI

Rectangle {
    id: root
    width: note_list.width
    height: cols.height
    color: "transparent"
    Column {
        id: cols
        x: 10
        width: parent.width - 60
        spacing: 5
        property string qmlStr: qmls
        onQmlStrChanged: {
            if(qmls) {
//                console.log(qmlStr);
                cols.data = [];
                let arr = JSON.parse(qmlStr);
                for(let i = 0; i < arr.length; i++) {
                    let qml = arr[i];
                    let o = Qt.createQmlObject(qml, cols, "dy_"+i);
                }
            }
        }
    }
    Rectangle {
        x:0
        y:0
        visible: index === note_list_view.currentIndex
        width: 10
        height: Com.min(root.height, 50)
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
            if(mouse.button === Qt.RightButton){
                menu_right_note.open();
            }
        }
        onDoubleClicked: {
            Book.openEditPopup();
        }
    }
}

