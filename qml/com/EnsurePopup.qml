import QtQuick 2.0
import QtQuick.Controls 2.12
import "ui.js" as UI

Popup {
    id: root
    width: 230
    height: 120
    x: parent.width/2-width/2
    y: parent.height/2-height/2
    modal: true
    focus: true
    background: Rectangle{color: Qt.rgba(0.2, 0.2, 0.2, 0.9);radius: 10}

    property alias text: popup_text.text
    property var onSure2
    function onSure(y) {
    }

    Rectangle {
        anchors.centerIn: parent
        focus: true
        radius: 5
        Column {
            anchors.centerIn: parent
            spacing: 20
            Text {
                id: popup_text
                font.family: "Arail"
                font.bold: true
                color: "white"
                font.pointSize: UI.font_size_title1
                text: qsTr("Ensure delete?")
            }
            Row {
                spacing: 30
                Btn {
                    z:10
                    color: "white"
                    text_color: "#191919"
                    text_size: UI.font_size_btn
                    radius: height/2
                    text: qsTr("OK")

                    function click() {
                        onSure(true);
                        if(onSure2) {
                            onSure2(true);
                        }
                        root.close();
                    }
                }
                Btn {
                    z:10
                    color: "white"
                    text_color: "#191919"
                    text_size: UI.font_size_btn
                    radius: height/2
                    text: qsTr("Cancel")

                    function click() {
                        onSure(false);
                        if(onSure2) {
                            onSure2(false);
                        }
                        root.close();
                    }
                }
            }
        }
        Keys.onReturnPressed: {
            onSure(true);
            if(onSure2) {
                onSure2(true);
            }
            root.close();
        }
    }
    onVisibleChanged: {
        if(visible){
            root.forceActiveFocus();
        } else {
            onSure(false);
            if(onSure2) {
                onSure2(false);
            }
            root.close();
        }
    }
}
