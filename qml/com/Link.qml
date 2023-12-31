import QtQuick 2.0
import "ui.js" as UI

TextEdit {
    color: UI.color_link
    wrapMode: Text.WordWrap
    horizontalAlignment: Text.AlignLeft
    verticalAlignment: Text.AlignHCenter
    font.pointSize: UI.font_size_normal
    property string url: ''
    selectByMouse: true
    readOnly: true

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            onClick();
        }
    }
    function onClick() {
        if(url) {
            Qt.openUrlExternally(url);
        }
    }
}
