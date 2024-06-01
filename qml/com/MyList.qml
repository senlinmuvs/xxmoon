import QtQuick
import "ui.js" as UI

ListView {
    id: root
    property string highColor: "#FBFBFB"
    property int vt : 0
    property bool showHighligh: false
    property int hightighRadius: 0

    spacing: 1
    currentIndex: 0
    boundsBehavior: Flickable.StopAtBounds
    highlightMoveDuration: 100
    highlightMoveVelocity: -1
    highlightResizeDuration: 100
    highlightResizeVelocity: -1
    highlight: Rectangle {
        visible: showHighligh
        color: highColor
        radius: hightighRadius
    }
}
