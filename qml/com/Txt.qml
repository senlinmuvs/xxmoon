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

    onLinkActivated: {
        if(link) {
            if(Com.isNumber(link)) {
                if(pk.id !== link) {
                    push(pk.id);
                    reloadData(link);
                }
            } else if(Com.isFile(link)) {
                $app.openDir(link);
            } else {
                Qt.openUrlExternally(link);
            }
        }
    }
    onSelectionEndChanged: {
        $app.regMenuReceiver(root);
    }
    function getTxt() {
        return root;
    }
}
