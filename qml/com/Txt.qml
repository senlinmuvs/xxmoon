import QtQuick
import QtQuick.Controls.Fusion
import "ui.js" as UI
import "../com/com.js" as Com

TextArea {
    id: root

    readOnly: true
    textFormat: Text.RichText
    renderType: Text.NativeRendering
    selectByMouse: true
    selectionColor: "#7887FF"
    selectedTextColor: "#FFF"
    font.pointSize: UI.ui_font_pk
    color: "#404040"
    background: Rectangle {
        color: "transparent"
    }
    wrapMode: Text.WrapAnywhere

    onLinkActivated: function(link) {
        if(link) {
            if(Com.isNumber(link)) {
                if(pk.id !== link) {
                    push(pk.id);
                    reloadData(link);
                }
            } else if(Com.isVideo(link)) {
                $a.openVideo(link.substring(7));
            } else if(Com.isFile(link)) {
                $a.openDir(link.substring(7));
            } else {
                Qt.openUrlExternally(link);
            }
        }
    }
    onSelectionEndChanged: {
        $a.regMenuReceiver(root);
    }
    function getTxt() {
        return root;
    }
    onPressed: function(mouse) {
        if(parent && parent.pressed) {
            parent.pressed(mouse);
        }
    }
    onReleased: function(mouse) {
        if(parent && parent.released) {
            parent.released(mouse);
        }
    }
    Keys.onPressed:function(event) {
        if(parent && parent.onKeyPressed) {
            parent.onKeyPressed(event);
        }
        //复制列表上不起作用自己实现，详情中又起作用
        if (event.modifiers & Qt.ControlModifier && event.key === Qt.Key_C) {
            if(selectedText) {
                $a.cp(selectedText);
            }
        }
    }
}
