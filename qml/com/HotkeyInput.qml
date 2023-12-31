import QtQuick 2.0
import QtQuick.Controls 2.12
import "../com/ui.js" as UI

TextField {
    height: 23
    font.family: "Arial"
    font.pointSize: UI.my_feild_font_size
    color: "#696969"
    horizontalAlignment: Text.AlignLeft
    background: Rectangle {
        anchors.fill: parent
        color:"#222"
    }
    Keys.onPressed: {
        let k = $app.getKeyName(event.key, event.modifiers);
        if(k.indexOf("+") < 0 && !/^F\d+$/.test(k)) {
            k = "Ctrl+Alt+" + k;
        }
        text = k;
    }
    onTextChanged: {
        if(text){
            if(text.length > 1){
                let a = text[text.length-2].toUpperCase();
                let b = text[text.length-1].toUpperCase();
                if(a === b){
                    text = text.substring(0, text.length-1);
                }
            }
        }
    }
    onFocusChanged: {
        if(focus){
            color = "white";
        } else {
            color = "#696969";
            submit();
        }
    }
    function submit(){
    }
}
