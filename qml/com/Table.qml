import QtQuick 2.15
import QtQuick.Controls 2.12
import Qt.labs.qmlmodels 1.0
import "ui.js" as UI
Item {
    id: root
    TableModel {
        id: m
//        TableModelColumn{display:'a'}
//        TableModelColumn{display:'b'}
        rows: [
            {"a":1, "b":2},
            {"a":3, "b":4},
        ]
    }
    TableView {
        width: 300
        height: 200
        columnSpacing: 0
        rowSpacing: 0
        clip: true
        property var columnWidths: [100, 50]
        property var rowHeights: [50, 20, 10]
        property alias datas: m.rows
        model: m
        columnWidthProvider: function(i) {
            return columnWidths[i];
        }
        rowHeightProvider: function(i) {
            return rowHeights[i];
        }
        delegate: Rectangle {
            implicitWidth: 100
            implicitHeight: 50
            border.width: 1
            Text {
                text: display
                anchors.fill: parent
                wrapMode: Text.WrapAnywhere
            }
        }
        Component.onCompleted: {
//            let qml =
//                "import QtQuick 2.15;import QtQuick.Controls 2.12;import Qt.labs.qmlmodels 1.0;"
//                "TableModelColumn{display:'a'}TableModelColumn{display:'b'}";
//            Qt.createQmlObject(qml, m, "dytmc");
//            console.log("created cols", o);
            for(let i in datas) {
                m.appendRow(datas[i]);
            }
        }
    }
}

