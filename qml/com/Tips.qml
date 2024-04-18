import QtQuick 2.0
import QtQuick.Controls 2.12

Popup {
    id: root
    width: 300
    height: 150
    x: parent.width/2-width/2
    y: parent.height/2-height/2
    modal: true
    focus: true
    clip: true

    ListModel {
        id: model
        ListElement {
            cont: ""
        }
    }
    Component {
        id: delegate
        Rectangle {
            width: text.width + 20
            height: text.height
            color:"transparent"
            Text {
                id:text
                y: -15
                font.pointSize: 15
                text: cont
                wrapMode: Text.WrapAnywhere
                onLinkActivated: Qt.openUrlExternally(link);
            }
        }
    }

    ListView {
        anchors.fill: parent
        model: model
        delegate: delegate
    }

    function alert(txt) {
        model.clear();
        appendText(txt);
        open();
    }

    function appendText(txt) {
        model.append({cont:txt});
    }
}
