import QtQuick
import QtQuick.Controls
import "../com/com.js" as Com
import "../xm/XM.js" as XM
import "ui.js" as UI

Rectangle {
    id: xm_list_rect
    width: xm_list_view.width
    height: wrap.height + row_time.height + 15
    color: sticky ? "#ececec" : "transparent"
//    clip: true
    property alias btn_no: btn_no

    MouseArea {
        anchors.fill: parent
        Rectangle {
            id: wrap
            anchors.top: parent.top
            width: parent.width
            height:Com.min(xm_list_col.height+10, 400)
            clip: true
            color: "transparent"
    //        color: "gray"
            Column {
                id: xm_list_col
                spacing: UI.ui_pk_cont_space
                anchors {
                    top:parent.top
                    topMargin: UI.ui_xm_list_margin
                    left: parent.left
                    leftMargin: UI.ui_xm_list_margin
                    right: parent.right
                    rightMargin: UI.ui_xm_list_margin
                }
                Row {
                    spacing: 8
                    visible: jm_ensure
                    width: parent.width
                    layoutDirection: Qt.RightToLeft
                    Btn {
                        id: btn_no
                        text: $a.tr("no")
                        color: Qt.rgba(0/255, 0/255, 0/255, 0.9)
                        function click() {
                            if(btn_no.visible) {
                                $xm.getXM(XM.getCurrentXMId(), xm_list.width, Com.putFunc(function(pk) {
                                    simple_cont = pk.simple_cont;
                                    cont = pk.cont;
                                    simple_qmls = pk.simple_qmls;
                                    cols.qmls = pk.simple_qmls;
                                    qmls = pk.qmls;
                                    jm_ensure = false;
                                    jm = jm ? 0 : 1;
                                    category_list_view.forceActiveFocus();
                                }));
                            }
                        }
                    }
                    Btn {
                        text: $a.tr("yes")
                        color: Qt.rgba(0/255, 0/255, 0/255, 0.9)
                        function click() {
                            $a.ensureEncryptOrDecrypt(id, cont, Com.putFunc(function(st) {
                                if(st === 0) {
                                    let pk = XM.getCurrentXM();
                                    if(pk){
                                        pk.jm_ensure = false;
                                        pk.img_path = Com.file_pre + $a.getCfgVal("img_dir") + "/" + img;
                                    }
                                }
                            }));
                        }
                    }
                }
                MyImage {
                    id: e_img
                    visible: img
                    source: jm? Com.img_logo : img_path
                    img_radius: 5
                    width: jm ? 48 : Com.calImgSizeByWidth(src_w,src_h,xm_list.width-100)[0]
                    height: jm ? 48 : Com.calImgSizeByWidth(src_w,src_h,xm_list.width-100)[1]
                    anchors.horizontalCenter: parent.horizontalCenter
                    function pressed(mouse) {
                        xm_list_view.currentIndex = index;
                    }
                    function released(mouse) {
                        if (mouse.button === Qt.RightButton) {
                            openRightClickMenu(mouse);
                        }
                    }
                    function onClickImg(src, mouse) {
                        if (mouse.button === Qt.RightButton) {
                            openRightClickMenu(mouse);
                        } else {
                            XM.openImgView(src);
                        }
                    }
                }
                Column {
                    id: cols
                    width: parent.width - 10
                    spacing: 2
                    property var qmls: simple_qmls
                    onQmlsChanged: {
                        // console.log("simple_qmls changed", qmls, JSON.stringify(qmls));
                        cols.data = [];
                        if(qmls) {
                            let i = 0;
                            for(let k in qmls) {
                                let qml = qmls[k];
                                Qt.createQmlObject(qml, cols, "dy_"+i);
                                i++;
                            }
                        }
                    }
                    function pressed(mouse) {
                        xm_list_view.currentIndex = index;
                    }
                    function released(mouse) {
                        if (mouse.button === Qt.RightButton) {
                            openRightClickMenu(mouse);
                        }
                    }
                    function onClickImg(src, mouse) {
                        if (mouse.button === Qt.RightButton) {
                            openRightClickMenu(mouse);
                        } else {
                            XM.openImgView(src);
                        }
                    }
                    function onKeyPressed(event) {
                        XM.onKeysPressed(event);
                    }
                }
            }
        }
        Row {
            id: row_time
            anchors.top: wrap.bottom
            anchors.topMargin: 8
            x: 10
            width: parent.width - 20
            height: 25
            layoutDirection: Qt.RightToLeft
            spacing: 20
            Text {
                text: (date_str + " " + time_str)
                visible: visible_time
                font.pointSize: UI.ui_font_pk_time
                color:"#898989"
                height: parent.height
                verticalAlignment: Text.AlignVCenter
            }
            TagLine {
                id: tag_line
                tag_ids: tags
                delegate: tag_view.tagManager
            }
        }
        Rectangle {
            x: 0
            y: xm_list_rect.height - 2
            width: xm_list.width
            height: UI.ui_separate_height
            color: UI.ui_separate_color
        }
        Rectangle {
            x:0
            y:0
            visible: index === xm_list_view.currentIndex
            width: 10
            height: Com.max(Com.min(xm_list_rect.height, 50), e_num.height)
            color: UI.ui_highlight_color
            Text {
                id: e_num
                text:Com.verText(index+1)
                font.pointSize: 10
                width: parent.width
                x: parent.width/2-width/2
                y: parent.height/2-height/2
                color: "white"
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
            }
        }
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onPressed:function(mouse) {
            xm_list_view.currentIndex = index;
        }
        onDoubleClicked:function(mouse) {
            XM.openEditPopup();
        }
        onMouseXChanged:function(mouse) {
            if(tags) {
                if(mouseY>parent.height-30) {
                    mouse.accepted = false;
                }
            }
            if(jm_ensure) {
                mouse.accepted = false;
            }
        }
    }
    function updateTags(tags) {
        tag_line.tag_ids = tags;
        if($l.isDebug()) {
            Com.debug("ComponentXM updateTags", tags);
        }
    }
    function updateImage() {
        let tmp = img.source;
        img.soucre = "";
        img.source = tmp;
    }
    function openRightClickMenu() {
        mi_cp_main_img.visible = !jm && img.length > 0;
        mi_pic_model.visible = !jm && (img.length > 0 || imgs.length > 0);
        mi_cont.visible = !jm && simple_cont.length > 0;
        mi_en_de.visible = simple_cont.length > 0 || img.length > 0;
        mi_exp_pdf.visible = !jm;
        mi_exp_html.visible = !jm;
        mi_exp_xm.visible = !jm;
        menu_right_xm.open();
    }
    function refresh(xm) {
        console.log("refresh xm");
        cols.qmls = xm.simple_qmls;
    }
}
