import QtQuick
import QtQuick.Controls
import "../com/com.js" as Com
import "../collect/Collect.js" as Collect
import "ui.js" as UI

Rectangle {
    id: pk_list_rect
    width: pk_list_view.width
    height: wrap.height + row_time.height + 15
    color: "transparent"
//    clip: true
    property alias btn_no: btn_no

    Rectangle {
        id: wrap
        anchors.top: parent.top
        width: parent.width
        height:Com.min(pk_list_col.height+10, 400)
        clip: true
        color: "transparent"
//        color: "gray"
        Column {
            id: pk_list_col
            spacing: UI.ui_pk_cont_space
            anchors {
                top:parent.top
                topMargin: UI.ui_pk_list_margin
                left: parent.left
                leftMargin: UI.ui_pk_list_margin
                right: parent.right
                rightMargin: UI.ui_pk_list_margin
            }
//            Rectangle {
//                height: UI.ui_date_height
//                width: 100
//                radius: 10
//                visible: visible_date
//                anchors.topMargin: UI.ui_pk_list_margin
//                anchors.left: parent.left
//                anchors.leftMargin: pk_list.width/2 - width/2
//                color:"black"
//                Text {
//                    anchors.centerIn: parent
//                    text: date_str
//                    font {
//                        pointSize: UI.date_font_size
//                        bold:true
//                    }
//                    color: "white"
//                }
//            }
            Row {
                spacing: 8
                visible: jm_ensure
                width: parent.width
                layoutDirection: Qt.RightToLeft
                Btn {
                    id: btn_no
                    text: "no"
                    color: Qt.rgba(0/255, 0/255, 0/255, 0.9)
                    function click() {
                        if(btn_no.visible) {
                            $col.getPK(Collect.getCurrentPkId(), pk_list.width, Com.putFunc(function(pk) {
                                simple_cont = pk.simple_cont;
                                cont = pk.cont;
//                                simple_html = pk.simple_html;
//                                html = pk.html;
                                simple_qmls = JSON.stringify(pk.simple_qmls);
                                qmls = pk.qmls;
                                jm_ensure = false;
                                jm = jm ? 0 : 1;
                            }));
                        }
                    }
                }
                Btn {
                    text: "yes"
                    color: Qt.rgba(0/255, 0/255, 0/255, 0.9)
                    function click() {
                        $app.ensureEncryptOrDecrypt(id, cont, Com.putFunc(function(st) {
                            if(st === 0) {
                                let pk = Collect.getCurrentPK();
                                if(pk){
                                    pk.jm_ensure = false;
                                    pk.img_path = Com.file_pre + $app.getCfgVal("img_dir") + "/" + img;
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
                width: jm ? 48 : Com.calImgSizeByWidth(src_w,src_h,pk_list.width-100)[0]
                height: jm ? 48 : Com.calImgSizeByWidth(src_w,src_h,pk_list.width-100)[1]
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Column {
                id: cols
                width: parent.width - 30
                spacing: 2
                property string qmls: simple_qmls
                onQmlsChanged: {
    //                console.log("simple_qmls changed", qmls);
                    if(qmls) {
                        cols.data = [];
                        let arr = JSON.parse(qmls);
    //                    console.log("updateSimpleQmls", qmls);
                        for(let i = 0; i < arr.length; i++) {
                            let qml = arr[i];
    //                        console.log(">>>>", qml);
                            Qt.createQmlObject(qml, cols, "dy_"+i);
                        }
                    }
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
        y: pk_list_rect.height - 2
        width: pk_list.width
        height: UI.ui_separate_height
        color: UI.ui_separate_color
    }
    Rectangle {
        x:0
        y:0
        visible: index === pk_list_view.currentIndex
        width: 10
        height: Com.max(Com.min(pk_list_rect.height, 50), e_num.height)
        color: UI.ui_highlight_color
        Text {
            id: e_num
            text:Com.verText(index+1)
            font.pointSize: 10
            width: parent.width
            x: parent.width/2-width/2+1
            y: parent.height/2-height/2+7
            color: "white"
            anchors.verticalCenter: parent.verticalCenter
        }
    }
    MouseArea {
        anchors.fill: parent
        // propagateComposedEvents:
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onPressed: {
            pk_list_view.currentIndex = index;
//            col_list.forceActiveFocus();
        }
        onDoubleClicked: {
            Collect.openEditPopup();
        }
        onClicked:function(mouse){
            if (mouse.button === Qt.RightButton) {
                pk_list_view.currentIndex = index;
                mi_cp_main_img.visible = !jm && img.length > 0;
                mi_pic_model.visible = !jm && (img.length > 0 || imgs.length > 0);
                mi_cont.visible = !jm && simple_cont.length > 0;
                mi_en_de.visible = simple_cont.length > 0 || img.length > 0;
                mi_exp_pdf.visible = !jm;
                mi_exp_html.visible = !jm;
                mi_exp_xm.visible = !jm;
                menu_right_pk.open();
            }
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
            Com.debug("ComponentPK updateTags", tags);
        }
    }
    function updateImage() {
        let tmp = img.source;
        img.soucre = "";
        img.source = tmp;
    }
}
