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
            width: parent.width
            Rectangle {
                color: "transparent"
                x:3
                width: parent.width-3
                height: UI.nav_tab_height
                property var btn: colBtn

                NavBtn {
                    id: colBtn
                    img: Com.img_logo
                    anchors.centerIn: parent
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
                            pageLoader.source = "qrc:/qml/xm/XM.qml";
                            st = 1;
                            curIndex = 0;
                            parent.color = "transparent";
                        }
                    }
                    onEntered_: {
                        if(curIndex !== 0) {
                            parent.color = "#414141";
                        }
                    }
                    onExited_: {
                        if(curIndex !== 0) {
                            parent.color = "transparent";
                        }
                    }
                }
            }
            Rectangle {
                color: "transparent"
                x:3
                width: parent.width-3
                height: UI.nav_tab_height
                property var btn: bookBtn
                NavBtn {
                    id: bookBtn
                    img: Com.img_kindle
                    anchors.centerIn: parent
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
                            parent.color = "transparent";
                        }
                    }
                    onEntered_: {
                        if(curIndex !== 1) {
                            parent.color = "#414141";
                        }
                    }
                    onExited_: {
                        if(curIndex !== 1) {
                            parent.color = "transparent";
                        }
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
                id: btn_add
                text: "+"
                text_size: UI.book_btn_add_font_size
                color:"transparent"
                function click() {
                    navBtnClick('add');
                }
            }
            Btn {
                id: btn_tag
                text: "#"
                text_size: UI.book_btn_tag_font_size
                color:"transparent"
                function click() {
                    navBtnClick('tag');
                }
            }
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
            // BtnImg {
            //     id: btn_recycle
            //     src: "qrc:/assets/icon_recycle.png"
            //     xx: 20
            //     imgWidth: 20
            //     imgHeight: imgWidth
            //     anchors.horizontalCenter: parent.horizontalCenter
            //     function click() {
            //         pageLoader.source = "qrc:/qml/Recycle.qml";
            //     }
            // }
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
        width: parent.width
        height: UI.nav_tab_height
        color: "#484848"

        Rectangle {
            x: 0
            width: 3
            height: parent.height
            color: "#FFFFFF"
        }
    }
    function go(i) {
        navCol.children[i].btn.click();
    }
    function onKeysPressed(event) {
        if(event.key === Qt.Key_Tab) {
            let i = (curIndex+1) % navCol.children.length;
            go(i);
        }
    }
}
