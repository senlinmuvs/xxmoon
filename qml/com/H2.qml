import QtQuick 2.0
import "qrc:/com/ui.js" as UI

TextEdit {
    font.pointSize: UI.font_size_h2
    selectByMouse: true
    readOnly: true
    persistentSelection: true
}
