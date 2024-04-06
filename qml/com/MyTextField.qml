import QtQuick
import QtQuick.Controls.Fusion
import "../com/ui.js" as UI

TextField {
    height: 23
    font.family: "Arial"
    font.pointSize: UI.my_feild_font_size
    color: "white"
    selectByMouse: true
    horizontalAlignment: Text.AlignLeft
    property var range

    onTextChanged: {
        text = val(text);
    }
    onFocusChanged: {
        if(!focus){
            submit();
        }
    }
    function val(text){
        if(range) {
            let reg = /^\d+$/;
            let min = Number(range[0]);
            let max = Number(range[1]);
            let v = Number(text);
            if(reg.test(text) && v >= min && v <= max) {
                return text;
            }
            return text.substring(0, text.length-1);
        }
        return text;
    }
    function submit(){
    }
}
