import QtQuick 2.14
import QtQuick.Controls 2.14
import Qt.labs.platform 1.1
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
    x: screen.width - width - 5
    y: 20
    Text {
        id: text
        anchors.centerIn: parent
        font.bold: true
        font.pixelSize: 20
        color: "white"
        wrapMode: Text.WrapAnywhere
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        onContentWidthChanged: {
            if(contentWidth > 500) {
                width = 520;
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
            text.text += "\n" + msg;
        } else {
            text.text = msg;
        }
        root.show();
        root.raise();
        root.requestActivate();
        if(ty === 0) {
            timer.start();
        }
    }
    function close() {
        text.text = "";
        root.hide();
    }
    MouseArea {
        anchors.fill: parent;
        onClicked: {
            close();
        }
    }
}
