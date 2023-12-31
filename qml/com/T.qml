import QtQuick 2.0
import "qrc:/com/ui.js" as UI

TextEdit {
    font.pointSize: UI.font_size_normal
    selectByMouse: true
    readOnly: true
    persistentSelection: true
}
