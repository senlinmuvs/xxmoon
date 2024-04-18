import QtQuick 2.0
import QtQuick.Controls 2.12

Popup {
    id: root
    width: rect_cont.width + 50
    height: rect_cont.height
    x: parent.width/2-width/2
    y: parent.height/2-height/2
    z: 11
    modal: true
    focus: true
    clip: true
    topInset: 0
    leftInset: 0
    bottomInset: 0
    rightInset: 0
    padding: 0
    background: Rectangle{color: Qt.rgba(0.2, 0.2, 0.2, 0.9);radius: 10}

    property var cb: null

    Rectangle {
        id: rect_cont
        color:"transparent"
        anchors.left: parent.left
        anchors.right: parent.right
        height: text.height + 20
        radius: 5
        width: text.width + 20
        Text {
            id: text
            y: 10
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            color:"white"
            font.pixelSize: 16
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
    Timer {
        id: timer
        interval: 1500
        onTriggered: {
            text.text = '';
            close();
            if(cb) {
                cb();
                cb = null;
            }
        }
    }
    function popup(txt,autoclose=true,cb) {
        text.text = txt;
        open();
        if(autoclose) {
            timer.start();
        }
        root.cb = cb;
    }
}
