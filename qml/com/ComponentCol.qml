import QtQuick
import "com.js" as Com
import "../collect/Collect.js" as Collect
import "ui.js" as UI

Rectangle {
    id: col_list_rect
    width: col_list.width
    height: e_col_name.height + 20
    color: "transparent"

    Text {
        id: e_col_name
        x: 10
        y: 10
        textFormat: Text.RichText
        width: parent.width - 30
        text: name
        font.pointSize: UI.col_font_size
        font.bold: true
        color: "white"
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.WrapAnywhere
    }
    Text {
        id: work_note_total
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        text: total
        width: 40
        height: UI.ui_col_row_height
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.pointSize: UI.total_font_size
        color:"#989898"
    }
    Text {
        id: flag_moving
        x: (parent.width-width)/2
        y: col_list_rect.height - 15
        color:"#C9C9C9"
        text:qsTr("Sorting...")
        font.pointSize: 10
        visible: index > 0 && index === sorting_col_index
    }
    Rectangle {
        x:0
        y:col_list_rect.height
        width: col_list.width
        height: 1
        color: "#686868"
    }
    CanvasLine {
        id: canvasLine
        x: parent.width - 60
        y: 0
        width: 60
        height: parent.height
        function onFinished() {
            if(isLeft) {
                if(index > 0 && (stopX > 0 && Com.abs(startX-stopX) > 20)) {
                    if(sorting_col_index > 0) {
                        if(sorting_col_index !== index) {
                            let c = col_list_model.get(sorting_col_index);
                            let dstIndex = index;
                            $col.sortingCol(c.id, sorting_col_index, dstIndex, Com.putFunc(function() {
                                let c = col_list_model.get(sorting_col_index);
                                let cloneCol = {id: c.id, name: c.name, total: c.total};
                                if(c) {
                                    col_list_model.remove(sorting_col_index);
                                    col_list_model.insert(dstIndex, cloneCol);
                                    if(sorting_col_index === col_list_view.currentIndex || dstIndex === col_list_view.currentIndex) {
                                        Collect.loadPk(true);
                                    }
                                    sorting_col_index = 0;
                                }
                            }));
                        } else {
                            sorting_col_index = 0;
                        }
                    } else {
                        sorting_col_index = index;
                    }
                }
            } else {
                if(stopX > 0 && Com.abs(startX-stopX) > 20) {
                    Collect.moveToCollect(index);
                }
            }
        }
        function onDoubleClicked0() {
            Collect.moveToCollect(index);
        }
    }
    MouseArea {
        anchors.fill: parent
        anchors.rightMargin: 60
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: function(mouse){
            col_list_view.forceActiveFocus();
            col_list_view.currentIndex = index;
            if (mouse.button === Qt.RightButton) {
                colRightMenu.open();
            }
        }
    }
}
