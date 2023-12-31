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
    width: 140
    height: 70
    background: Rectangle {
        color: Qt.rgba(0.2, 0.2, 0.2, 0.8)
        radius: 10
    }
    x: screen.width - 160
    y: 20
    Text {
        id: text
        anchors.centerIn: parent
        font.bold: true
        font.pixelSize: 20
        color: "white"
    }
    Timer {
        id: timer
        interval: 3000
        repeat: false
        onTriggered: {
            root.hide();
        }
    }
    function open(msg) {
        text.text = msg;
        root.show();
        root.raise();
        root.requestActivate();
        timer.start();
    }
}
