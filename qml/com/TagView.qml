import QtQuick
import QtQuick.Controls.Fusion
import "com.js" as Com
import "../category/Category.js" as Category

Popup {
    id: root
    x:parent.width-width
    y: 0
    width: parent.width/4 + 20
    height: parent.height
    topPadding: 0
    rightPadding: 0
    leftPadding: 0
    bottomPadding: 0
    focus: true
    background: Rectangle {
        color: Qt.rgba(100/255,100/255,100/255, 0.6)
    }

    property alias flows: flows
    property var tagManager

    Rectangle {
        anchors.fill: parent
        clip: true
        color: "transparent"
        anchors.topMargin: 8
        anchors.leftMargin: 8
        anchors.rightMargin: 0
        anchors.bottomMargin: 43
        ScrollView {
            id: scroll
            anchors.fill: parent
            width: parent.width
            Flow {
                id: flows
                width: parent.width - 8
                spacing: 8
            }
        }
    }
    TextField {
        id: input
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 40
        placeholderText: qsTr("input tag")
        font.pointSize: 16
        font.family: "Arial"
        color: "white"
        selectByMouse: true
        focus: true
        background: Rectangle {
            anchors.fill: parent
            color: Qt.rgba(100/255,100/255,100/255, 0.6)
        }
        onTextChanged: {
            tagManager.searchTags(input.text);
        }
        Keys.onPressed:function(event) {
            if(event.modifiers === ctrlVal && event.key === Qt.Key_Return) {
                tagManager.setTagForItem(input.text);
            } else if(event.modifiers === Qt.AltModifier && event.key === Qt.Key_Return) {
                tagManager.addTag(input.text);
            } else if(event.key === Qt.Key_Return) {
                tagManager.selectTag(input.text);
            }
        }
        onFocusChanged: {
            if(focus) {
                $app.regMenuReceiver(this);
            }
        }
    }
    onClosed: {
//        Com.log('close tag v');
//        work_list_view.forceActiveFocus();
        tagManager.onTagViewClosed();
    }

    function clearFlows() {
        flows.data = null;
        flows.width = tag_view.width - 8;
    }

    function clearInput() {
        input.clear();
    }
    function op() {
        open();
        if(input.focus) {
            $app.regMenuReceiver(input);
        }
    }
}
