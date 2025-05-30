﻿import QtQuick
import QtQuick.Controls.Fusion
import Qt.labs.platform

import "../com"
import "../com/com.js" as Com
import "../com/tag.js" as Tag
import "XM.js" as XM
import "../com/ui.js" as UI

Rectangle {
    id: root_xm
    anchors.fill: parent
    signal st(int type, string tip)
    signal key(var e)
    signal tipsInfo(string txt)
    property var tagCom: Qt.createComponent("qrc:/qml/com/Tag.qml")
//    property var lineItemCom: Qt.createComponent("qrc:/com/LineItem.qml")
    property var tagManager: new Tag.TagManager(tagCom, Com.type_pk, search_bar, tag_view, category_list_view, new XM.PKTagDelegate(root_xm))
    property int sorting_col_index: 0
    property int pre_cid: 0
    property int pre_xmid: 0
    property int wallpaper_cid: 0
    property bool preNotEmptyKeySearch:false

    ListModel {
        id: list_model_category
    }
    TextField {
        id: search_bar
        anchors.top: parent.top
        width: category_list.width
        height: 40
        placeholderText: $a.tr("Search...")
        placeholderTextColor: "#a9a9a9"
        font.pointSize: UI.font_size_title2
        font.family: "Arial"
        color: "white"
        selectByMouse: true
        background: Rectangle {
            anchors.fill: parent
            color:"#222"
        }
        onTextChanged: {
            let txt = text;
            text = txt.replace("  ", " ");
        }
        Keys.onPressed: function(event) {
            if(event.key === Qt.Key_Escape || event.key === Qt.Key_Tab) {
                event.accepted = true;
                category_list_view.forceActiveFocus();
            } else if(event.key === Qt.Key_Return) {
                let notEmptyKey = search_bar.text.trim().length > 0;
                if(preNotEmptyKeySearch || notEmptyKey) {
                    refreshData();
                }
                preNotEmptyKeySearch = notEmptyKey;
                category_list_view.forceActiveFocus();
            }
        }
        onFocusChanged: {
            if(focus) {
                $a.regMenuReceiver(this);
            }
        }
    }
    Menu {
        id: colRightMenu
        MenuItem {
            text: $a.tr("Edit")
            onTriggered: {
                XM.openColEditPopup();
            }
        }
        MenuSeparator {}
        MenuItem {
            text: $a.tr("Delete")
            onTriggered: {
                XM.delCol();
            }
        }
        // MenuSeparator {}
        // MenuItem {
        //     text: $a.tr("Generate PDF")
        //     onTriggered: {
        //        let cid = XM.getCurrentCategoryId();
        //        $a.genFile(Com.file_type_pdf, Com.type_pk, cid, 0);
        //     }
        // }
        MenuSeparator {}
        MenuItem {
            text: $a.tr("Generate HTML")
            onTriggered: {
               let cid = XM.getCurrentCategoryId();
               $a.genFile(Com.file_type_html, Com.type_pk, cid, 0);
            }
        }
        // MenuSeparator {}
        // MenuItem {
        //     text: $a.tr("Export Single XM")
        //     onTriggered: {
        //         let cid = XM.getCurrentCategoryId();
        //         $a.genFile(Com.file_type_xm, Com.type_pk, cid, 0, 0);
        //     }
        // }
        // MenuSeparator {
        // }
        // MenuItem {
        //     text: $a.tr("Export Batch XM")
        //     onTriggered: {
        //         let col = XM.getCurrentCategory();
        //         if(col){
        //             $a.genFile(Com.file_type_xm, Com.type_pk, col.id, 0, 1);
        //         }
        //     }
        // }
        MenuSeparator {}
        MenuItem {
            id: mi_set_pwd
            onTriggered: {
                let c = XM.getCurrentCategory();
                if(c.jm) {
                    popup_input.delegate = {
                        onSubmit:function(v) {
                            $xm.validateCategoryPWD(c.id, v, Com.putFunc(function(y){
                                if(y) {
                                    $xm.deleteEncryption(c.id, Com.putFunc(function(){
                                        c.jm = false;
                                        alert('取消成功');
                                        popup_input.close();
                                    }));
                                } else {
                                    alert("密码错误");
                                }
                            }));
                        }
                    };
                    popup_input.op();
                } else {
                    popup_input.delegate = {
                        onSubmit:function(v) {
                            $xm.encrypt(c.id, v, Com.putFunc(function(){
                                c.jm = true;
                                alert('设置成功');
                                popup_input.close();
                            }));
                        }
                    };
                    popup_input.op(1);
                }
            }
        }
        MenuSeparator {}
        MenuItem {
            id: mi_set_done
            onTriggered: {
                let c = XM.getCurrentCategory();
                if(c.ty === 1) {
                    $xm.setCategoryType(c.id, 0, Com.putFunc(function(){
                        c.ty = 0;
                        alert("取消成功");
                    }));
                } else {
                    $xm.setCategoryType(c.id, 1, Com.putFunc(function(){
                        c.ty = 1;
                        alert("设置成功");
                    }));
                }
            }
        }
        onAboutToShow: {
            let c = XM.getCurrentCategory();
            if(c.jm) {
                mi_set_pwd.text = "取消密码";
            } else {
                mi_set_pwd.text = "设置密码";
            }
            if(c.ty === 1) {
                mi_set_done.text = "取消此分类为[已完成]";
            } else {
                mi_set_done.text = "设置此分类为[已完成]";
            }
        }
    }
    Menu {
        id: menu_right_xm
        MenuItem {
            text: $a.tr("Detail")
            shortcut: "Space"
            onTriggered: {
                XM.detail();
            }
        }
        MenuSeparator {
        }
        MenuItem {
            id: mi_pic_model
            text: $a.tr("Picture Model")
            shortcut: "Enter"
            onTriggered: {
                XM.openImgView();
            }
        }
        MenuSeparator {
            visible: mi_pic_model.visible
        }
        MenuItem {
            text: $a.tr("Edit")
            shortcut: ctrlName+"+Enter"
            onTriggered: {
                XM.openEditPopup();
            }
        }
        MenuSeparator {
        }
        MenuItem {
            text: $a.tr("Out Edit")
            shortcut: ctrlName+"+Alt+Enter"
            onTriggered: {
                XM.openOutEdit();
            }
        }
        MenuSeparator {
        }
        MenuItem {
            id: mi_sticky
            text: $a.tr("Sticky")
            shortcut: ctrlName+"+Home"
            onTriggered: {
                let xm = XM.getCurrentXM();
                if(xm.sticky) {
                    XM.cancelSticky(xm.id);
                } else {
                    XM.sticky(xm.id);
                }
            }
        }
        MenuSeparator {
        }
        MenuItem {
            id: mi_cp_main_img
            text: $a.tr("Copy main image")
            shortcut: "Alt+Shift+C"
            onTriggered: {
                XM.copyPK(0);
            }
        }
        MenuSeparator {
            visible: mi_cp_main_img.visible
        }
        MenuItem {
            id: mi_cp_link
            visible: mi_cp_main_img.visible
            text: $a.tr("Copy main image link")
            shortcut: ctrlName+"+Alt+C"
            onTriggered: {
                XM.copyPK(1);
            }
        }
        MenuSeparator {
            visible: mi_cp_main_img.visible
        }
        MenuItem {
            id: mi_cont
            text: $a.tr("Copy content")
            shortcut: ctrlName+"+Shift+C"
            onTriggered: {
                XM.copyPK(2);
            }
        }
        MenuSeparator {
            visible: mi_cont.visible
        }
        MenuItem {
            id: mi_en_de
            text: $a.tr("Encrypt | Decrypt")
            shortcut: ctrlName+"+E"
            onTriggered: {
                XM.openEncryptPopup();
            }
        }
        MenuSeparator {
            visible: mi_en_de.visible
        }
        Menu {
            title: $a.tr("Export")
            MenuItem {
                id: mi_exp_pdf
                text: $a.tr("Export PDF")
                onTriggered: {
                    let pk = XM.getCurrentXM();
                    if(pk) {
                        $a.genFile(Com.file_type_pdf, Com.type_pk, 0, pk.id);
                    }
                }
            }
            MenuSeparator {
                visible: mi_exp_pdf.visible
            }
            MenuItem {
                id: mi_exp_html
                text: $a.tr("Export HTML")
                onTriggered: {
                    let pk = XM.getCurrentXM();
                    if(pk){
                        $a.genFile(Com.file_type_html, Com.type_pk, 0, pk.id);
                    }
                }
            }
            MenuSeparator {
                visible: mi_exp_html.visible
            }
            MenuItem {
                id: mi_exp_xm
                text: $a.tr("Export XM")
                onTriggered: {
                    let pk = XM.getCurrentXM();
                    if(pk){
                        $a.genFile(Com.file_type_xm, Com.type_pk, 0, pk.id);
                    }
                }
            }
            MenuSeparator {
                visible: mi_exp_xm.visible
            }
            MenuItem {
                id: mi_exp_site
                text: $a.tr("Export Site")
                onTriggered: {
                    let pk = XM.getCurrentXM();
                    if(pk){
                        $a.genFile(Com.file_type_site, Com.type_pk, 0, pk.id);
                    }
                }
            }
        }
        MenuSeparator {
            visible: mi_exp_site.visible
        }
        MenuItem {
            id: mi_del_site
            text: $a.tr("Delete from Site")
            onTriggered: {
                let pk = XM.getCurrentXM();
                if(pk){
                    $a.deleteFromSite(pk.id);
                }
            }
        }
        MenuSeparator {
            visible: mi_del_site.visible
        }
        MenuItem {
            id: mi_clear_stime
            text: $a.tr("Clear Solved Time")
            onTriggered: {
                let pk = XM.getCurrentXM();
                if(pk){
                    $xm.clearSolvedTime(pk.id, Com.putFunc(function(r) {
                        pk.stime = 0;
                        tipsInfo($a.tr("Success"));
                    }));
                }
            }
        }
        // MenuSeparator {
        //     visible: mi_del_site.visible
        // }
        // MenuItem {
        //     id: mi_send_phone
        //     text: $a.tr("Send To Phone")
        //     onTriggered: {
        //         let pk = XM.getCurrentXM();
        //         if(pk){
        //             $a.sendToPhone(Com.type_pk, pk.id, Com.putFunc(function(r) {
        //                 tipsInfo($a.tr("Success"));
        //             }));
        //         }
        //     }
        // }
        MenuSeparator {
            visible: mi_clear_stime.visible
        }
        MenuItem {
            id: mi_del
            text: $a.tr("Delete")
            shortcut: "Backspace"
            onTriggered: {
                ensure_popup.open();
            }
        }
        onAboutToShow: {
            let xm = XM.getCurrentXM();
            if(xm.sticky) {
                mi_sticky.text = $a.tr("Cancel Sticky");
            } else {
                mi_sticky.text = $a.tr("Sticky");
            }
        }
    }
    Rectangle {
        id: category_list
        width: 160
        anchors {
            left: parent.left
            top: search_bar.bottom
            bottom: parent.bottom
        }
        color: "#282828"
        clip: true
        Rectangle {
            id: e_col_header
            width: parent.width
            height: btn_add_col.height
            color:"#000"
            Btn {
                id: btn_add_col
                width: parent.width
                text: "+"
                text_size: UI.btn_font_smybol_size
                text_color: "#EAEAEA"
                hover_color: "#191919"
                radius: 1
                function click() {
                    XM.onBtnClick_addCol();
                }
            }
        }
        MyList {
            id: category_list_view
            showHighligh:true
            anchors.topMargin: e_col_header.height
            anchors.fill: category_list
            model: list_model_category
            clip:true
            delegate: ComponentCategory{}
            onCurrentIndexChanged: {
                let c = XM.getCurrentCategory();
                list_model_xm.clear();
                if(c&&c.jm) {
                    popup_input.delegate = {
                        onSubmit:function(v) {
                            $xm.validateCategoryPWD(c.id, v, Com.putFunc(function(y){
                                if(y) {
                                    XM.loadXM(true, function(){
                                        xm_list_view.currentIndex = 0;
                                    });
                                    popup_input.close();
                                } else {
                                    alert("密码错误");
                                }
                            }));
                        }
                    };
                    popup_input.op();
                } else {
                    XM.loadXM(true, function() {
                        xm_list_view.currentIndex = 0;
                    });
                }
            }
            focus: true
            highColor: "#000"
            Keys.onPressed:function(event) {
                XM.onKeysPressed(event);
            }
        }
        MouseArea {
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 10
            hoverEnabled: true
            property int startX:0

            onPressed:function(mouse){
                startX = mouse.x
            }
            onReleased: {
                startX = 0
                $a.setLocal($a.ENV_K_LAST_CATEGORY_LEFT_WIDTH, Math.floor(category_list.width));
            }
            onPositionChanged:{
                if(startX > 0){
                    let left = mouse.x < startX;
                    if(left){
                        let delta = startX - mouse.x
                        category_list.width = Com.max(100,category_list.width - delta);
                    } else {
                        let delta = mouse.x - startX
                        category_list.width = Com.min(root_xm.width/3*2,category_list.width + delta);
                    }
                    $a.setUIVal(0, xm_list.width);
                }
            }
            onEntered: {
                cursorShape = Qt.SizeHorCursor
            }
            onExited: {
                cursorShape = Qt.ArrowCursor
            }
        }
    }

    ///
    Finder {
        id: finder
        property string contCache: ""
        function find() {
            if(edit_pk_popup.visible) {
                let i = finder.find0(edit_pk_popup.text);
                edit_pk_popup.select(i, finder.txt());
            } else if(detailView.visible) {
                detailView.select(finder.txt());
            }
        }
        function clear() {
            if(edit_pk_popup.visible) {
                edit_pk_popup.clearSelect();
            } else if(detailView.visible) {
                detailView.clearSelect();
            }
            contCache = "";
        }
    }

    ///
    ListModel {
        id: list_model_xm
    }
    Component {
        id: pkNoMoreBtn
        Rectangle{}
    }
    Rectangle {
        id: xm_list
        anchors {
            left: category_list.right
            top: parent.top
            bottom: parent.bottom
            right: parent.right
        }
        color: "white"
        MyList {
            id: xm_list_view
            Component {
                id: xm_list_footer
                Column {
                    width: xm_list_view.width
                    Text {
                        text: $a.tr("Loading") + "..."
                        width: parent.width
                        height: 40
                        font.pointSize: UI.font_size_normal
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: "#191919"
                        visible: xm_list_view.loading
                    }
                    MoreBtn {
                        visible: !xm_list_view.loading && list_model_xm.count > 0
                        function click() {
                            if(xm_list_view.footer) {
                                XM.loadXM();
                            }
                        }
                    }
                    Text {
                        text: $a.tr("No Record")
                        font.pointSize: UI.font_size_normal
                        width: parent.width
                        height: 40
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: "#191919"
                        visible: !xm_list_view.loading && list_model_xm.count === 0
                    }
                }
            }
            onCurrentIndexChanged: {
                if(!search_bar.focus) {
                    if(!popup_input.visible) {
                        category_list_view.forceActiveFocus();
                    }
                }
            }
            anchors.fill: xm_list
            model: list_model_xm
            delegate: ComponentXM {}
        }
        function next() {
            if(xm_list_view.currentIndex+1>=xm_list_view.count) {
                XM.loadXM();
            }
            let i = xm_list_view.currentIndex+1;
            if(i > xm_list_view.count-1) {
                xm_list_view.currentIndex = xm_list_view.count-1;
                return null;
            } else {
                xm_list_view.currentIndex = i;
                return list_model_xm.get(i);
            }
        }
        function previous() {
            let i = xm_list_view.currentIndex-1;
            if(i < 0){
                xm_list_view.currentIndex = 0;
                return null;
            } else {
                xm_list_view.currentIndex = i;
                return list_model_xm.get(i);
            }
        }
        function onClose() {
            XM.img_view_delegate.onClose();
        }
        function getTagManager() {
            return tag_view.tagManager;
        }
        function openEditPopup(add, pk) {
            XM.openEditPopup(add, pk);
        }
        function getData(id, w, cb) {
            $xm.getXM(id, w, Com.putFunc(function(pk){
                pk = Com.convXM(1, 1, pk);
                if(cb){
                    cb(pk);
                }
            }));
        }
        function openFinder() {
            finder.open();
        }
    }
    TagView {
        id:tag_view
        tagManager: root_xm.tagManager

        function onTagList(all, list) {
            root_xm.tagManager.loadTagList(all, list);
            //等标签加载完再加载主页数据
            if(list_model_category.count === 0) {
                Com.info("loadCategory on init tags");
                XM.loadCategory();
            }
        }
        function onAddTag(st, tag) {
            tag_view.clearInput();
        }
        function onDelete(tid, ref) {
            root_xm.tagManager.delTagInView(tid, ref);
        }
    }
    MyEditorPopup {
        id: edit_pk_popup
        function submit(upeditor=0) {
            XM.submitXM(function(xm) {
                if(xm) {
                    edit_pk_popup.bid = xm.id;
                }
                if($l.isDebug()) {
                    Com.debug('submitXM cb', JSON.stringify(xm));
                }
            }, upeditor);
        }
        function cancel() {
            if($l.isDebug()) {
                Com.debug('cancelEditXM');
            }
            XM.submitXM(function(xm) {
                if($l.isDebug()) {
                    Com.debug('submitXM cb', JSON.stringify(xm));
                }
                if(add && xm) {
                    let xm0 = list_model_xm.get(0);
                    if(!xm0 || xm0.id !== xm.id) {
                        list_model_xm.insert(0, xm);
                        xm_list_view.currentIndex = 0;
                    }
                }
                XM.closeEditPK();
            });
        }
    }
    MyFieldPopup {
        id: col_edit_popup
        placeholder: $a.tr("Category Name")
        property bool add: false

        function submit() {
            XM.submitCol(add);
        }
        function cancel() {
            col_edit_popup.close();
            category_list_view.forceActiveFocus();
            add = false;
        }
        function onUpdated() {
            let i = category_list_view.currentIndex;
            let c = list_model_category.get(i);
            c.name = col_edit_popup.text.trim();
            col_edit_popup.clear();
            col_edit_popup.close();
            category_list_view.forceActiveFocus();
            add = false;
        }
        function onAdded(err, c) {
            if(err) {
                Com.error(err);
                tipsInfo(err);
                return;
            }
            list_model_category.append(c);
            category_list_view.forceActiveFocus();
            col_edit_popup.clear();
            col_edit_popup.close();
            add = false;
        }
    }
    EnsurePopup {
        id: ensure_popup
        function onSure(y) {
            category_list_view.forceActiveFocus();
            if(y) {
                XM.deletePK(ensure_popup);
            }
        }
        function onDeleted(ref) {
            ensure_popup.close();
            if(ref>0){
                tipsInfo($a.tr("Can not delete! found")+ " "+ ref + " " + $a.tr("referenced."));
            } else {
                XM.colTotalDecrement();
                list_model_xm.remove(xm_list_view.currentIndex);
            }
        }
    }
    Component.onCompleted: {
        category_list_view.forceActiveFocus();
    }
    function init(data) {
        Com.info("XM init data");
        if(data) {
            let lw = data[$a.ENV_K_LAST_CATEGORY_LEFT_WIDTH];
            if(lw) {
                category_list.width = lw;
            }
            if(list_model_category.count === 0) {
                category_list_view.forceActiveFocus();
                tagManager.initData();
            }
        }
    }
    function onGetCategories(list) {
//        console.log("--------------->>>>>>>>>>>", search_bar.text.trim(), list.length, list_model_xm.count);
        if($l.isDebug()) {
            Com.trace("onGetCategories", JSON.stringify(list));
        }
        list_model_category.clear();
        for(let i = 0; i < list.length; i++) {
            list_model_category.append(list[i]);
        }
        if(list_model_xm.count === 0) {
            XM.loadXM();
        }
    }
    function hasNewPK(col) {
        let c = list_model_category.get(0);
        if(category_list_view.currentIndex === 0) {
            let row0 = list_model_xm.get(0);
            if(row0) {
                $xm.getNewXMList(c.id, row0.id, xm_list.width, root_xm);
            } else {
                XM.loadXM(false);
            }
        }
        if(col) {
            XM.addOrUpdateCol(col);
        }
        //更新默认文件夹total
        $xm.countCategory(c.id, Com.putFunc(function(n) {
            c.total = n;
        }));
    }
    function onGetNewPKList(list) {
        for(let i = 0; i < list.length; i++) {
            let pk = list[i];
            let nextDateStr = 1;
            let nextTimeStr = 1;
            if(i < list.length -1) {
                let nextPK = list[i+1];
                let arr = Com.parseTime(nextPK.time, 1);
                nextDateStr = arr[0];
                nextTimeStr = arr[1];
            }
            pk = Com.convXM(nextDateStr, nextTimeStr, list[i]);
            list_model_xm.insert(0, pk);
        }
    }
    function onMoved(colIndex) {
        let oldC = list_model_category.get(category_list_view.currentIndex);
        oldC.total = Com.max(0, oldC.total - 1);
        let c = list_model_category.get(colIndex);
        c.total = c.total + 1;
        list_model_xm.remove(xm_list_view.currentIndex);
    }
    function onUpdateXM(xm, upeditor=1) {
        let arr = XM.getPKByIdInCurrentList(xm.id);
        if(arr) {
            // console.log("onUpdateXM", JSON.stringify(xm));
            arr[1].simple_cont = xm.simple_cont;
            arr[1].cont = xm.cont;
            arr[1].simple_qmls = xm.simple_qmls;
            arr[1].qmls = xm.qmls;
            arr[1].lst = xm.lst;
            if(edit_pk_popup.visible) {
                if(upeditor) {
                   if(edit_pk_popup.bid === xm.id){
                       edit_pk_popup.updateText(xm.cont);
                   }
                }
            } else if(detailView.visible) {
                if(detailView.pk.id === xm.id) {
                    detailView.update(xm);
                }
            }
        }
    }
    function fuckFocus() {
        category_list_view.forceActiveFocus();
    }
    function getListWidth() {
        return xm_list.width;
    }
    function onPush(ty, data) {
        if(ty === Com.PUSH_UP_TAGS) {
            let pk = XM.getCurrentXM();
            if(pk) {
                pk.tags = data.tags;
                xm_list_view.currentItem.updateTags(data.tags);
                if(detailView.visible) {
                    detailView.updateTags(data.tags);
                }
            }
        }
    }

    function navBtnClick(ty) {
        if(ty === 'add') {
            XM.openEditPopup(1);
        } else if(ty === 'tag') {
            tagManager.openTagView();
        }
    }
    function refreshData() {
        XM.refreshAll(true);
        category_list_view.forceActiveFocus();
    }
}
