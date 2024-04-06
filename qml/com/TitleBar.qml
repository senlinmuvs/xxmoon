import QtQuick 2.0
import "com.js" as Com
import "ui.js" as UI

Rectangle {
    id:root
    width: parent.width
    height: 30
    color:"#181818"
    property var win
    property alias title: title.text
    property alias showImportBtn: importBtn.visible
    property int lastX: 0
    property int lastY: 0
    property int lastW: 0
    property int lastH: 0

    Row {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: parent.height
        Rectangle {
            width: 10
            height: root.height
            color: "transparent"
        }
        Text {
            id: logo
            y: 4
            text:qsTr("xxmoon")
            color: "white"
            font.pointSize: 10
            width: 80
            horizontalAlignment: Text.AlignLeft
        }
        Text {
            id: title
            y: 4
            color: "white"
            font.pointSize: 10
            horizontalAlignment: Text.AlignHCenter
            width: parent.width - logo.width - minBtn.width*3 - (importBtn.visible?importBtn.width:0) - 10
        }
        Row {
            MyBtn {
                id: importBtn
                radius: 1
                width: 38
                height: 26
                text: "●"
                text_size: 15
                text_color: "#9F9F9F"
                mask_color: "#393939"
                hover_color: "#6f6f6f"
                visible: false
                function click() {
                    window.import_total = 1;
                    window.importXM();
                }
            }
            MyBtn {
                id: minBtn
                y: -2
                radius: 1
                width: 38
                height: 26
                text: "-"
                text_size: 20
                text_color: "#9F9F9F"
                mask_color: "#393939"
                hover_color: "#6f6f6f"
                function click() {
                    window.showMinimized();
                }
            }
            MyBtn {
                id: maxBtn
                y: -2
                radius: 1
                width: 38
                height: 26
                text: "□"
                text_bold: true
                text_size: 14
                text_color: "#9F9F9F"
                mask_color: "#393939"
                hover_color: "#6f6f6f"
                function click() {
                    maxWin();
                }
            }
            MyBtn {
                id: xBtn
                y: -2
                radius: 1
                width: 38
                height: 26
                text: "x"
                text_size: 12
                text_color: "#9F9F9F"
                mask_color: "#552233"
                hover_color: "#d50023"
                function click() {
                    window.hide();
                }
            }
        }
    }

    function maxWin() {
        if(window.width === screen.width) {
            window.showNormal();
            console.log("maxWin 0", lastW, lastH);
            if(lastW > 0 && lastH > 0) {
                window.width = lastW;
                window.height = lastH;
            }
            window.x = lastX;
            window.y = lastY;
            $app.setLocal("maxWindow", 0);
        } else {
            console.log("maxWin 1", lastW, lastH);
            lastW = window.width;
            lastH = window.height;
            lastX = window.x;
            lastY = window.y;
            window.setMaxWindow();
            $app.setLocal("maxWindow", 1);
        }
    }

    MouseArea {
        id: dragRegion
        anchors.fill: parent
        anchors.rightMargin: minBtn.width*3 + (importBtn.visible?importBtn.width:0)
        property point clickPos:"0,0"

        onPressed:function(mouse) {
            clickPos =Qt.point(mouse.x,mouse.y)
        }
        onPositionChanged: {
            var delta =Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
            win.setX(win.x + delta.x)
            win.setY(win.y + delta.y)
        }
    }
}
