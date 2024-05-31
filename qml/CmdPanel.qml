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
    width: 300
    height: 300
    background: Rectangle {
        color: Qt.rgba(0.2, 0.2, 0.2, 0.8)
        radius: 10
    }
    x: screen.width/2 - width/2
    y: screen.height/2 - height/2

    property string key: ''

    ListModel {
        id: m
    }
    Component {
        id: com_list
        Rectangle {
            width: root.width
            height: e_col.height
            color:"transparent"
            clip: true
            Column {
                id: e_col
                width: parent.width - 40
                x: 20
                Text {
                    id: e_text
                    font.bold: true
                    font.pointSize: 16
                    color: "white"
                    text: n + " " + tip
                    wrapMode: Text.WrapAnywhere
                    verticalAlignment: Text.AlignVCenter
                    width: parent.width
                    height: 40
                    onContentHeightChanged: function(contentHeight) {
                        height = Math.max(contentHeight + 20, height);
                    }
                }
                Rectangle {
                    color: "#696969"
                    width: parent.width
                    height: 1
                }
            }
        }
    }
    MyList {
        id: e_list
        anchors.fill: parent
        delegate: com_list
        model: m
        showHighligh: true
        highColor: "#191919"
        currentIndex: -1
        focus: true
        header: Rectangle {
            color: "transparent"
            width: e_list.width
            height: e_txt.height
            Text {
                id: e_txt
                x: 10
                width: parent.width-20
                height: key?30:10
                color: "white"
                text: key.length+': '+key
                visible: key
                font.pointSize: 12
                verticalAlignment: Text.AlignVCenter
                maximumLineCount: 1
                clip: true
            }
        }
        Keys.onPressed: function(e) {
            if(e.key === Qt.Key_Escape) {
                close();
            } else if(e.key === Qt.Key_Home) {
                e_list.currentIndex = 0;
            } else if(e.key === Qt.Key_End) {
                e_list.currentIndex = m.count-1;
            } else if(e.key === Qt.Key_J) {
                e_list.currentIndex = Math.min(e_list.currentIndex+1, m.count-1);
            } else if(e.key === Qt.Key_K) {
                e_list.currentIndex = Math.max(e_list.currentIndex-1, 0);
            } else if(e.key === Qt.Key_Return) {
                let row = m.get(e_list.currentIndex);
                exe(row, 0);
                return;
            }

            let k = Number(e.key);
            if(k && k >= 49 && k <= 85) {
                let i = k-49;
                if(i >= 0 && i < m.count) {
                    let row = m.get(i);
                    // console.log(JSON.stringify(row));
                    if(row && row.script) {
                        exe(row);
                    }
                    e_list.currentIndex = i;
                }
            }
        }
    }
    Timer {
        id: e_close_timer
        repeat: false
        interval: 300
        onTriggered: {
            close();
        }
    }
    Component.onCompleted: {
        e_list.forceActiveFocus();
    }
    function exe(row, delayClose=1) {
        $a.exePanelCmd(root.key, row.script, row.ty);
        if(delayClose) {
            e_close_timer.start();
        } else {
            close();
        }
    }

    function open(k, datas) {
        m.clear();
        root.key = k.replace("\n", " ");
        for(let i in datas) {
            // console.log(JSON.stringify(datas[i]));
            m.append(datas[i]);
        }
        e_list.currentIndex = -1;
        root.show();
        root.raise();
        root.requestActivate();
    }
    function close() {
        root.hide();
    }
}
