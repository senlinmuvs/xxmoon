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
    width: 600
    height: 50
    background: Rectangle {
        color: Qt.rgba(0.2, 0.2, 0.2, 0.8)
        radius: 10
    }
    x: screen.width/2 - width/2
    y: screen.height/2 - height/2

    property var delegate: null
    property string holder: ''

    TextField {
        id: e_tf
        anchors.fill: parent
        font.pointSize: 14
        placeholderText: holder
        placeholderTextColor: "#a9a9a9"
        verticalAlignment: Text.AlignVCenter
        background: Rectangle{color:"transparent"}
        color: "white"
        focus: true
        Keys.onPressed: function(event) {
            if(event.key === Qt.Key_Return) {
                if(delegate && delegate.onSubmit) {
                    delegate.onSubmit(text);
                    close();
                }
            } else if(event.key === Qt.Key_Escape) {
                close();
            }
        }
    }
    function open() {
        root.show();
        root.raise();
        root.requestActivate();
    }
    function close() {
        e_tf.text = '';
        root.hide();
    }
}
