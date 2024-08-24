import QtQuick 2.0
import "ui.js" as UI
MyBtn {
    width: parent?parent.width:50
    height: 30
    text: $a.tr("More") + "..."
    text_size: UI.font_size_btn
    text_color: "#808080"
    radius: 1
    color:"transparent"
    hover_color: "#e9e9e9"
}
