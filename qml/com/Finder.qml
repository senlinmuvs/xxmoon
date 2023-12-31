import QtQuick 2.13
import QtQuick.Controls 2.12
import "com.js" as Com
import "ui.js" as UI

Popup {
    id:root
    width: parent.width + UI.nav_width
    height: 30
    x:parent.width-width
    y: 0
    z: 100
    topPadding: 0
    rightPadding: 0
    leftPadding: 0
    bottomPadding: 0
    focus: true
    background: null

    property alias text: text
    property int lastIndex: -1
    property int direction: 0

    Rectangle {
        anchors.fill: parent
        color:"transparent"
        TextField {
            id: text
            anchors.fill: parent
            font.pointSize: UI.font_size_normal
            color: "white"
            focus: true
            selectByMouse: true
            background: Rectangle {
                anchors.fill: parent
                color: Qt.rgba(0,0,0,0.5)
            }
            onTextChanged: {
                lastIndex = -1;
            }
            Keys.onPressed: {
                onKeysPressed(event);
            }
        }
    }
    onClosed: {
        lastIndex = -1;
        clear();
    }

    function onKeysPressed(event) {
        if(event.modifiers === Qt.ShiftModifier && event.key === Qt.Key_Return) {
            direction = 1;
            find();
        } else if(event.key === Qt.Key_Return) {
            direction = 0;
            find();
        }
    }
    function find() {
    }
    function clear() {
    }
    function find0(txt) {
        let k = text.text;
        let i = -1;
        if(direction === 0) {
            let from = lastIndex >= 0 ? lastIndex+k.length : 0;
            let remainText = txt.substring(from);
            i = remainText.toLowerCase().indexOf(k.toLowerCase());
            if(i >= 0) {
                i = from + i;
            }
        } else {
            let from = lastIndex >= 0 ? lastIndex-k.length : txt.length;
            let remainText = txt.substring(0, from);
            i = remainText.toLowerCase().reverse().indexOf(k.toLowerCase().reverse());
            if(i >= 0) {
                i = from - i - k.length;
            }
        }
        if(i >= 0) {
            lastIndex = i;
        }
        return i;
    }
    function txt() {
        return text.text;
    }
}
