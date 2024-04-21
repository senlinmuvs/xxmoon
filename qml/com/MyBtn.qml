import QtQuick

Rectangle {
    id:root
    width: 12
    height: 12
    radius: width/2
    color: Qt.rgba(10/255, 10/255, 10/255, 0.8)

    property alias text: lap.text
    property alias text_visible: lap.visible
    property alias text_color: lap.color
    property alias text_bold: lap.font.bold
    property alias text_size: lap.font.pointSize
    property alias font_family: lap.font.family
    property int xoff
    property int yoff
    property var mask_color: Qt.rgba(100/255, 100/255, 100/255, 0.6)
    property alias mask_visible: mask.visible
    property string hover_color:"#494949"
    property alias t: lap
    property bool enable_click: true
    property bool enable_drag: false
    property string old_color
    property int xx: 0
    property alias tip: e_tip_txt.text

    Rectangle {
        id: mask
        anchors.fill: parent
        color: mask_color
        visible: false
        radius: parent.radius
    }
    Text {
        id: lap
        color: "white"
        visible: true
        font {
            pointSize: 14
            bold: false
            family: "Arial"
        }
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.horizontalCenter: root.horizontalCenter
        anchors.horizontalCenterOffset: xoff
        anchors.verticalCenter: root.verticalCenter
        anchors.verticalCenterOffset: yoff
    }
    Rectangle {
        id: e_tip
        visible: false
        width: e_tip_txt.width + 20
        height: e_tip_txt.height + 10
        anchors.right: root.left
        anchors.rightMargin: 2
        anchors.verticalCenter: root.verticalCenter
        color: "transparent"
        border.color: "#191919"
        border.width: 1
        radius: 20
        Text {
            id: e_tip_txt
            color: "#191919"
            anchors.centerIn: parent
        }
    }
    MouseArea {
        id: area
        x: xx
        y: xx
        width: parent.width + xx
        height: parent.height + xx
//        drag.target: parent
        drag.axis: Drag.XAxis
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        propagateComposedEvents: true
        property bool moving: false
        property bool enter: false
        hoverEnabled: true

        onPositionChanged: {
            if(!hoverEnabled || !enter){
                mask.visible = false;
            }
        }
        onClicked:function(mouse) {
            if(enable_click) {
                mouse.accepted = true;
                if(mouse.button === Qt.LeftButton) {
                    click();
                } else {
                    rightClick();
                }
            }
        }
        onDoubleClicked: function(mouse){
            mouse.accepted = true;
        }
        onPressed: {
            old_color = root.color;
            if(enable_click) {
                mask.color = mask_color
                mask.visible = true
            }
        }
        onPressAndHold: {
            if(enable_drag) {
                moving = true;
                color = '#d50023';
                mask.visible = false;
            }
        }
        onReleased:function(mouse) {
            root.color = old_color;
            mask.visible = false;
            if(enable_drag) {
                area.drag.target = null;
            }
            if(moving){
                moved(mouse);
                moving = false;
            }
        }
        onMouseXChanged: function(mouse) {
            mouse.accepted = true;
            if(moving) {
                if(!area.drag.target){
                    area.drag.target = parent;
                }
            }
        }
        onEntered: {
            // console.log(mouseX, mouseY);
            e_tip.visible = e_tip_txt.text ? true : false;
            enter = true
            if(hover_color) {
                mask.color = hover_color
                mask.visible = true
            }
            fkEntered();
        }
        onExited: {
            e_tip.visible = false;
            enter = false
            mask.visible = false;
            fkExited();
        }
    }
    function click(){}
    function rightClick() {
    }
    function moved(mouse) {
    }
    function showOverlap(){
        lap.visible = true
    }
    function hideOverlap() {
        lap.visible = false
    }
    function fkEntered() {
    }
    function fkExited() {
    }
}
