import QtQuick 2.0
import "ui.js" as UI

ListView {
    id: root
    property string highColor: "#FBFBFB"
    property int vt : 0
    property bool showHighligh: false

    spacing: 1
    currentIndex: 0
//    interactive: false
//    flicking: false
    boundsBehavior: Flickable.StopAtBounds
    highlightMoveDuration: 100
    highlightMoveVelocity: -1
    highlightResizeDuration: 100
    highlightResizeVelocity: -1
    highlight: Rectangle {
        visible: showHighligh
        color: highColor
    }
//    MouseArea {
//        anchors.fill: parent
//        acceptedButtons: Qt.LeftButton | Qt.RightButton
//        onWheel: root.flick(0, wheel.angleDelta.y * 10)
//        onClicked: {
//            click();
//        }
//    }
//    function click(){

//    }
}
