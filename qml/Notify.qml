import QtQuick
import QtQuick.Controls
import Qt.labs.platform
import "com"
import "com/com.js" as Com
import "com/ui.js" as UI

ApplicationWindow {
    id: root
    visible: true
    color: "transparent"
    flags: Qt.FramelessWindowHint|Qt.WindowSystemMenuHint|Qt.WindowMinimizeButtonHint|Qt.Window
    width: text.width + 40
    height: text.height + 40
    background: Rectangle {
        color: Qt.rgba(0.2, 0.2, 0.2, 0.8)
        radius: 10
    }
    x: screen.width - width - 2
    Text {
        id: text
        anchors.centerIn: parent
        font.bold: true
        font.pixelSize: 20
        color: "white"
        textFormat: Text.RichText
        renderType: Text.NativeRendering
        wrapMode: Text.WrapAnywhere
        onContentWidthChanged: {
            if(contentWidth >= 520) {
                width = 520;
            }
            if(contentWidth <= 200) {
                width = 200;
            }
        }
        onContentHeightChanged: {
            if(contentHeight >= 1000) {
                height = 1000;
            }
        }
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        focus: true
        Keys.onPressed: function(e) {
            if(e.key === Qt.Key_Escape) {
                close();
            }
        }
    }
    Timer {
        id: timer
        interval: 3000
        repeat: false
        onTriggered: {
            close();
        }
    }
    function open(msg, ty=0) {
        if(text.text) {
            if(text.text.substring(text.text.lastIndexOf("\n")+1) !== msg) {
                text.text += "\n" + msg;
            }
        } else {
            text.text = msg;
        }
        root.show();
        root.raise();
        root.requestActivate();
        if(ty === 0) {
            timer.start();
        }
        text.forceActiveFocus();
    }
    function close() {
        text.text = "";
        root.destroy();
    }
    MouseArea {
        anchors.fill: parent;
        onClicked: {
            close();
        }
    }
}
