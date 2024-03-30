import QtQuick 2.9
import QtQuick.Controls 2.2
import "com"
import "com/com.js" as Com
import "com/ui.js" as UI

Rectangle {
    id:root;
    width: UI.nav_width
    height: parent.height
    color: "#383838"
    property NavBtn currentNavBtn: colBtn
    property int initYOffset: 0
    property int curIndex: 0

    Rectangle {
        width: parent.width
        height: parent.height
        color: "transparent"
        z: 1;

        Column {
            id: navCol
            spacing: 20
            y: 10
            width: parent.width
            NavBtn {
                id: colBtn
                img: Com.img_logo
                function reset() {
                    img = Com.img_logo;
                    st = 0;
                }
                function click() {
                    if(st == 0) {
                        currentNavBtn.reset();
                        img = Com.img_logo;
                        currentNavBtn = colBtn;
                        curTabLabel.y = initYOffset;
                        pageLoader.source = "qrc:/qml/collect/Collect.qml";
                        st = 1;
                        curIndex = 0;
                    }
                }
            }
            NavBtn {
                id: bookBtn
                img: Com.img_kindle
                function reset() {
                    img = Com.img_kindle;
                    st = 0;
                }
                function click() {
                    if(st == 0) {
                        currentNavBtn.reset();
                        img = Com.img_kindle;
                        currentNavBtn = bookBtn;
                        curTabLabel.y = curTabLabel.height + initYOffset;
                        pageLoader.source = "qrc:/qml/book/Book.qml";
                        st = 1;
                        curIndex = 1;
                    }
                }
            }
        }
        Column {
            anchors {
                bottom: parent.bottom
                bottomMargin: 10
                right: parent.right
                rightMargin: 10
            }
            spacing: 8
//            Btn {
//                id: btn_serv
//                text: "S"
//                color:"transparent"
//                text_size: UI.nav_btn_serv_font_size
//                function click() {
//                    serv.op();
//                }
//                function fkEntered() {
//                    Com.st(0, qsTr('Mobile connect to computer'));
//                }
//                function fkExited() {
//                    Com.st(0, '');
//                }
//            }
            Btn {
                id: btn_imp
                text: "●"
                color:"transparent"
                text_size: UI.nav_btn_imp_font_size
                function click() {
                    if(!$app.importDouban()) {
                        if(!$app.importWechatRead()) {
                            fileDialog.open();
                        }
                    }
                }
                function fkEntered() {
                    $app.getLastPath(btn_imp);
                }
                function fkExited() {
                    Com.st(0, '');
                }
                function onGetLastPath(arr) {
                    Com.st(0, qsTr("Last imported path:") + arr[0]);
                }
            }
            Btn {
                id: btn_more
                text: "≡"
                color:"transparent"
                text_color: "white"
                text_size: UI.nav_btn_more_font_size
                function click() {
                    about.op();
                }
            }
        }
    }
    Rectangle {
        id: curTabLabel
        x: 0
        y: initYOffset
        z: 0
        width: 70
        height: 52
        color: "#484848"

        Rectangle {
            x: 0
            width: 3
            height: parent.height
            color: "#FFFFFF"
        }
    }
    function go(i) {
        navCol.children[i].click();
    }
    function onKeysPressed(event) {
        if(event.key === Qt.Key_Tab) {
            let i = (curIndex+1) % navCol.children.length;
            go(i);
        }
    }
}
