import QtQuick 2.0

Rectangle {
    id: root
    color: "transparent"
    Column {
        id: col
        MyImage {
            id: img
            width: parent.width
            height: parent.height - summary.height
        }
        Text {
            id: summary
            width: parent.width
            height: 40
            visible: simple_cont
        }
    }
}
