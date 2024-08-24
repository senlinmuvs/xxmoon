import QtQuick
import "com.js" as Com
import "../xm/XM.js" as XM
import "ui.js" as UI

Rectangle {
    id: root_com_col
    width: category_list.width
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
        font.italic: ty||jm
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
        y: root_com_col.height - 15
        color:"#C9C9C9"
        text:$a.tr("Sorting...")
        font.pointSize: 10
        visible: index > 0 && index === sorting_col_index
    }
    Rectangle {
        x:0
        y:root_com_col.height
        width: category_list.width
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
                            let c = list_model_category.get(sorting_col_index);
                            let dstIndex = index;
                            $xm.sorting(c.id, sorting_col_index, dstIndex, Com.putFunc(function() {
                                let c = list_model_category.get(sorting_col_index);
                                let cloneCol = {id: c.id, name: c.name, total: c.total};
                                if(c) {
                                    list_model_category.remove(sorting_col_index);
                                    list_model_category.insert(dstIndex, cloneCol);
                                    if(sorting_col_index === category_list_view.currentIndex || dstIndex === category_list_view.currentIndex) {
                                        XM.loadXM(true);
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
                    XM.moveToCategory(index);
                }
            }
        }
        function onDoubleClicked0() {
            XM.moveToCategory(index);
        }
    }
    MouseArea {
        anchors.fill: parent
        anchors.rightMargin: 60
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        hoverEnabled: true
        onClicked: function(mouse){
            category_list_view.forceActiveFocus();
            category_list_view.currentIndex = index;
            if (mouse.button === Qt.RightButton) {
                colRightMenu.open();
            }
            root_com_col.color = "transparent";
        }
        onEntered: {
            root_com_col.color = "#393939";
        }
        onExited: {
            root_com_col.color = "transparent";
        }
    }
}
