import QtQuick
import QtQuick.Controls.Fusion
import Qt.labs.platform

import "../com"
import "../com/com.js" as Com
import "../com/tag.js" as Tag
import "Collect.js" as Collect
import "../com/ui.js" as UI

Rectangle {
    id: root
    anchors.fill: parent
    signal st(int type, string tip)
    signal key(var e)
    signal tipsInfo(string txt)
    property var tagCom: Qt.createComponent("qrc:/qml/com/Tag.qml")
//    property var lineItemCom: Qt.createComponent("qrc:/com/LineItem.qml")
    property var tagManager: new Tag.TagManager(tagCom, Com.type_pk, search_bar, tag_view, col_list_view, new Collect.PKTagDelegate())
    property int sorting_col_index: 0
    property int pre_cid: 0
    property int pre_pkid: 0
    property int wallpaper_cid: 0

    ListModel {
        id: col_list_model
    }
    TextField {
        id: search_bar
        anchors.top: parent.top
        anchors.left:parent.left
        anchors.right: parent.right
        height: 40
        placeholderText: qsTr("Search...")
        font.pointSize: UI.btn_font_size
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
            if(txt === text) {
                Collect.refreshAll(true);
            }
        }
        Keys.onPressed: function(event) {
            if(event.key === Qt.Key_Escape || event.key === Qt.Key_Return || event.key === Qt.Key_Tab) {
                event.accepted = true;
                col_list_view.forceActiveFocus();
            }
        }
        onFocusChanged: {
            if(focus) {
                $app.regMenuReceiver(this);
            }
        }
    }
    Menu {
        id: colRightMenu
        MenuItem {
            text: qsTr("Edit") + " ("+ctrlName+"+Shift+E)"
            onTriggered: {
                Collect.openColEditPopup();
            }
        }
        MenuSeparator {}
        MenuItem {
            text: qsTr("Delete")
            onTriggered: {
                Collect.delCol();
            }
        }
        MenuSeparator {}
        MenuItem {
            text: qsTr("Generate PDF")
            onTriggered: {
               let cid = Collect.getCurrentColId();
               $app.genFile(Com.file_type_pdf, Com.type_pk, cid, 0);
            }
        }
        MenuSeparator {}
        MenuItem {
            text: qsTr("Generate HTML")
            onTriggered: {
               let cid = Collect.getCurrentColId();
               $app.genFile(Com.file_type_html, Com.type_pk, cid, 0);
            }
        }
        MenuSeparator {}
        MenuItem {
            text: qsTr("Export Single XM")
            onTriggered: {
                let cid = Collect.getCurrentColId();
                $app.genFile(Com.file_type_xm, Com.type_pk, cid, 0, 0);
            }
        }
        MenuSeparator {
        }
        MenuItem {
            text: qsTr("Export Batch XM")
            onTriggered: {
                let col = Collect.getCurrentCol();
                if(col){
                    $app.genFile(Com.file_type_xm, Com.type_pk, col.id, 0, 1);
                }
            }
        }
//        MenuSeparator {
//            visible: $app.getPlatform() === Com.platform_win
//        }
//        MenuItem {
//            visible: $app.getPlatform() === Com.platform_win
//            text: wallpaper_cid === Collect.getCurrentColId() ? qsTr("Cancel Wallpaper Folder") : qsTr("As Wallpaper Folder")
//            onTriggered: {
//                let cid = Collect.getCurrentColId();
//                if(wallpaper_cid === cid) {
//                    $app.set($app.ENV_K_WALLPAPER_CID, 0);
//                } else {
//                    $app.set($app.ENV_K_WALLPAPER_CID, cid);
//                }
//            }
//        }
    }
    Menu {
        id: menu_right_pk
        MenuItem {
            text: qsTr("Detail") + " (Space)"
            onTriggered: {
                Collect.detail();
            }
        }
        MenuSeparator {
        }
        MenuItem {
            id: mi_pic_model
            text: qsTr("Picture Model") + " (Enter)"
            onTriggered: {
                Collect.openImgView();
            }
        }
        MenuSeparator {
            visible: mi_pic_model.visible
        }
        MenuItem {
            text: qsTr("Edit") + " ("+ctrlName+"+Enter)"
            onTriggered: {
                Collect.openEditPopup();
            }
        }
        MenuSeparator {
        }
        MenuItem {
            text: qsTr("Out Edit") + " ("+ctrlName+"+Alt+Enter)"
            onTriggered: {
                Collect.openOutEdit();
            }
        }
        MenuSeparator {
        }
        MenuItem {
            id: mi_cp_main_img
            text: qsTr("Copy main image") + " (Alt+Shift+C)"
            onTriggered: {
                Collect.copyPK(0);
            }
        }
        MenuSeparator {
            visible: mi_cp_main_img.visible
        }
        MenuItem {
            id: mi_cp_link
            visible: mi_cp_main_img.visible
            text: qsTr("Copy main image link") + " ("+ctrlName+"+Alt+C)"
            onTriggered: {
                Collect.copyPK(1);
            }
        }
        MenuSeparator {
            visible: mi_cp_main_img.visible
        }
        MenuItem {
            id: mi_cont
            text: qsTr("Copy content") + " ("+ctrlName+"+Shift+C)"
            onTriggered: {
                Collect.copyPK(2);
            }
        }
        MenuSeparator {
            visible: mi_cont.visible
        }
        MenuItem {
            id: mi_del
            text: qsTr("Delete") + " (Backspace/Del)"
            onTriggered: {
                ensure_popup.open();
            }
        }
        MenuSeparator {
            visible: mi_del.visible
        }
        MenuItem {
            id: mi_en_de
            text: qsTr("Encrypt | Decrypt") + " ("+ctrlName+"+E)"
            onTriggered: {
                Collect.openEncryptPopup();
            }
        }
        MenuSeparator {
            visible: mi_en_de.visible
        }
        MenuItem {
            id: mi_exp_pdf
            text: qsTr("Export PDF")
            onTriggered: {
                let pk = Collect.getCurrentPK();
                if(pk) {
                    $app.genFile(Com.file_type_pdf, Com.type_pk, 0, pk.id);
                }
            }
        }
        MenuSeparator {
            visible: mi_exp_pdf.visible
        }
        MenuItem {
            id: mi_exp_html
            text: qsTr("Export HTML")
            onTriggered: {
                let pk = Collect.getCurrentPK();
                if(pk){
                    $app.genFile(Com.file_type_html, Com.type_pk, 0, pk.id);
                }
            }
        }
        MenuSeparator {
            visible: mi_exp_html.visible
        }
        MenuItem {
            id: mi_exp_xm
            text: qsTr("Export XM")
            onTriggered: {
                let pk = Collect.getCurrentPK();
                if(pk){
                    $app.genFile(Com.file_type_xm, Com.type_pk, 0, pk.id);
                }
            }
        }
        MenuSeparator {
            visible: mi_exp_xm.visible
        }
        MenuItem {
            id: mi_exp_site
            text: qsTr("Export Site")
            onTriggered: {
                let pk = Collect.getCurrentPK();
                if(pk){
                    $app.genFile(Com.file_type_site, Com.type_pk, 0, pk.id);
                }
            }
        }
        MenuSeparator {
            visible: mi_exp_site.visible
        }
        MenuItem {
            id: mi_del_site
            text: qsTr("Delete from Site")
            onTriggered: {
                let pk = Collect.getCurrentPK();
                if(pk){
                    $app.deleteFromSite(pk.id);
                }
            }
        }
        MenuSeparator {
            visible: mi_del_site.visible
        }
        MenuItem {
            id: mi_send_phone
            text: qsTr("Send To Phone")
            onTriggered: {
                let pk = Collect.getCurrentPK();
                if(pk){
                    $app.sendToPhone(Com.type_pk, pk.id, Com.putFunc(function(r) {
                        tipsInfo(qsTr("Success"));
                    }));
                }
            }
        }
        MenuSeparator {
            visible: mi_send_phone.visible
        }
        MenuItem {
            id: mi_clear_stime
            text: qsTr("Clear Solved Time")
            onTriggered: {
                let pk = Collect.getCurrentPK();
                if(pk){
                    $col.clearSolvedTime(pk.id, Com.putFunc(function(r) {
                        pk.stime = 0;
                        tipsInfo(qsTr("Success"));
                    }));
                }
            }
        }
    }
    Rectangle {
        id: col_list
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
                    Collect.onBtnClick_addCol();
                }
            }
        }
        MyList {
            id: col_list_view
            showHighligh:true
            anchors.topMargin: e_col_header.height
            anchors.fill: col_list
            model: col_list_model
            clip:true
            delegate: ComponentCol{}
            onCurrentIndexChanged: {
                Collect.loadPk(true);
                pk_list_view.currentIndex = 0;
            }
            focus: true
            highColor: "#000"
            Keys.onPressed:function(event){
                Collect.onKeysPressed(event);
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
                $app.setLocal($app.ENV_K_LAST_COLLECT_LEFT_WIDTH, Math.floor(col_list.width));
            }
            onPositionChanged:{
                if(startX > 0){
                    let left = mouse.x < startX;
                    if(left){
                        let delta = startX - mouse.x
                        col_list.width = Com.max(100,col_list.width - delta);
                    } else {
                        let delta = mouse.x - startX
                        col_list.width = Com.min(root.width/3*2,col_list.width + delta);
                    }
                    $app.setUIVal(0, pk_list.width);
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
        id: pk_list_model
    }
    Component {
        id: pkNoMoreBtn
        Rectangle{}
    }
    Rectangle {
        id: pk_list
        anchors {
            left: col_list.right
            top: parent.top
            bottom: parent.bottom
            right: parent.right
        }
        color: "white"
        MyList {
            id: pk_list_view
            Component {
                id: pk_list_more_btn
                MoreBtn {
                    function click() {
                        if(pk_list_view.footer) {
                            Collect.loadPk();
                        }
                    }
                }
            }
            anchors.fill: pk_list
            model: pk_list_model
            delegate: ComponentPK {}
//            function click(){
//                col_list_view.forceActiveFocus();
//            }
        }
        GridView {
            id: grid
            cellWidth: 100
            cellHeight: cellWidth
            delegate: ComponentGridPK{}
        }
        Column {
            anchors {
                bottom: parent.bottom
                bottomMargin: 4
                right: parent.right
                rightMargin: 4
            }
            spacing: 10
            Btn {
                id: btn_tag
                width: 35
                height: 35
                text: "#"
                text_size: UI.book_btn_tag_font_size
                color: Qt.rgba(0/255, 0/255, 0/255, 0.9)
                radius: width/2
                function click() {
                    tagManager.openTagView();
                }
            }
            Btn {
                id: btn_add
                width: 35
                height: 35
                text: "+"
                text_size: UI.book_btn_add_font_size
                color: Qt.rgba(0/255, 0/255, 0/255, 0.9)
                radius: width/2
                function click() {
                    Collect.openEditPopup(1);
                }
            }
        }
        function next() {
            if(pk_list_view.currentIndex+1>=pk_list_view.count) {
                Collect.loadPk();
            }
            let i = pk_list_view.currentIndex+1;
            if(i > pk_list_view.count-1) {
                pk_list_view.currentIndex = pk_list_view.count-1;
                return null;
            } else {
                pk_list_view.currentIndex = i;
                return pk_list_model.get(i);
            }
        }
        function previous() {
            let i = pk_list_view.currentIndex-1;
            if(i < 0){
                pk_list_view.currentIndex = 0;
                return null;
            } else {
                pk_list_view.currentIndex = i;
                return pk_list_model.get(i);
            }
        }
        function pushPK(list) {
            if($l.isDebug()) {
                Com.debug("pushPK list", list.length);
            }
            let ar = Com.parseTime(Collect.getPKLastTime(), 1);
            let preDateStr = ar[0];
            let preTimeStr = ar[1];
            for(let i in list) {
                let e = list[i];
                if($l.isDebug()) {
                    Com.debug("pk", JSON.stringify(e));
                }
                let pk = Com.convPK(preDateStr, preTimeStr, e);
                pk_list_model.append(pk);
                preDateStr = pk.date_str;
                preTimeStr = pk.time_str;
            }
            if(list.length < $app.pageSize) {
                pk_list_view.footer = pkNoMoreBtn;
            } else {
                pk_list_view.footer = pk_list_more_btn;
            }

            //定位当前选中项
            if(pre_cid > 0) {
                let i = Collect.getColIndexByCid(pre_cid);
                if(i >= 0) {
                    col_list_view.currentIndex = i;
                    pre_cid = 0;
                }
            }
            if(pre_pkid > 0) {
                let arr = Collect.getPKByIdInCurrentList(pre_pkid);
                if(arr) {
                    let i = arr[0];
                    pk_list_view.currentIndex = i;
                    pre_pkid = 0;
                }
            }
            $app.setUIVal(0, pk_list.width);
        }
        function onClose() {
            Collect.img_view_delegate.onClose();
        }
        function getTagManager() {
            return tag_view.tagManager;
        }
        function openEditPopup(add, pk) {
            Collect.openEditPopup(add, pk);
        }
        function getData(id, w, cb) {
            $col.getPK(id, w, Com.putFunc(function(pk){
                pk = Com.convPK(1, 1, pk);
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
        tagManager: root.tagManager

        function onTagList(all, list) {
            root.tagManager.loadTagList(all, list);
            //等标签加载完再加载主页数据
            if(col_list_model.count === 0) {
                Com.info("loadCollects on init tags");
                Collect.loadCollects();
            }
        }
        function onAddTag(st, tag) {
            tag_view.clearInput();
        }
        function onDelete(tid, ref) {
            root.tagManager.delTagInView(tid, ref);
        }
    }
    MyEditorPopup {
        id: edit_pk_popup
        function submit() {
            Collect.submitPK();
        }
        function cancel() {
            Collect.cancelEditPK();
        }
        function onAdded(pk) {
            pk = Com.convPK(1, 1, pk);
            Collect.colTotalIncrement();
            if(pk_list_model.count > 0) {
                let p = pk_list_model.get(0);
                if(p.date_str === pk.date_str) {
                    p.visible_date = false;
                    if(p.time_str === pk.time_str) {
                        p.visible_time = false;
                    }
                }
            }
            pk_list_model.insert(0, pk);
            pk_list_view.currentIndex = 0;
            edit_pk_popup.bid = pk.id;
//                root.st(1, qsTr("Saved"));
            if(pending_close) {
                Collect.closeEditPK();
            }
        }
    }
    MyFieldPopup {
        id: col_edit_popup
        placeholder: qsTr("Category Name")
        property bool add: false

        function submit() {
            Collect.submitCol(add);
        }
        function cancel() {
            col_edit_popup.close();
            col_list_view.forceActiveFocus();
            add = false;
        }
        function onUpdated() {
            let i = col_list_view.currentIndex;
            let c = col_list_model.get(i);
            c.name = col_edit_popup.text.trim();
            col_edit_popup.clear();
            col_edit_popup.close();
            col_list_view.forceActiveFocus();
            add = false;
        }
        function onAdded(err, c) {
            if(err) {
                Com.error(err);
                tipsInfo(err);
                return;
            }
            col_list_model.append(c);
            col_list_view.forceActiveFocus();
            col_edit_popup.clear();
            col_edit_popup.close();
            add = false;
        }
    }

    EnsurePopup {
        id: ensure_popup
        function onSure(y) {
            col_list_view.forceActiveFocus();
            if(y) {
                Collect.deletePK(ensure_popup);
            }
        }
        function onDeleted(ref) {
            ensure_popup.close();
            if(ref>0){
                tipsInfo(qsTr("Can not delete! found")+ " "+ ref + " " + qsTr("referenced."));
            } else {
                Collect.colTotalDecrement();
                pk_list_model.remove(pk_list_view.currentIndex);
            }
        }
    }
    Component.onCompleted: {
        col_list_view.forceActiveFocus();
    }
    function init(data) {
        Com.info("Collect init data");
        if(data) {
            let lw = data[$app.ENV_K_LAST_COLLECT_LEFT_WIDTH];
            if(lw) {
                col_list.width = lw;
            }
            if(col_list_model.count === 0) {
                col_list_view.forceActiveFocus();
                tagManager.initData();
            }
        }
    }
    function onGetCollects(list) {
//        console.log("--------------->>>>>>>>>>>", search_bar.text.trim(), list.length, pk_list_model.count);
        if($l.isDebug()) {
            Com.trace("onGetCollects", JSON.stringify(list));
        }
        col_list_model.clear();
        for(let i = 0; i < list.length; i++) {
            col_list_model.append(list[i]);
        }
        if(pk_list_model.count === 0) {
            Collect.loadPk();
        }
    }
    function hasNewPK(col) {
        let c = col_list_model.get(0);
        if(col_list_view.currentIndex === 0) {
            let row0 = pk_list_model.get(0);
            if(row0) {
                $col.getNewPKList(c.id, row0.id, pk_list.width, root);
            } else {
                Collect.loadPk(false);
            }
        }
        if(col) {
            Collect.addOrUpdateCol(col);
        }
        //更新默认文件夹total
        $col.countCol(c.id, Com.putFunc(function(n) {
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
            pk = Com.convPK(nextDateStr, nextTimeStr, list[i]);
            pk_list_model.insert(0, pk);
        }
    }
    function onMoved(colIndex) {
        let oldC = col_list_model.get(col_list_view.currentIndex);
        oldC.total = Com.max(0, oldC.total - 1);
        let c = col_list_model.get(colIndex);
        c.total = c.total + 1;
        pk_list_model.remove(pk_list_view.currentIndex);
    }
    function onUpdatePK(pk) {
        let arr = Collect.getPKByIdInCurrentList(pk.id);
        if(arr) {
//            console.log("onUpdatePK", JSON.stringify(pk));
            arr[1].simple_cont = pk.simple_cont;
            arr[1].cont = pk.cont;
            arr[1].simple_qmls = JSON.stringify(pk.simple_qmls);
            arr[1].qmls = pk.qmls;
            arr[1].lst = pk.lst;
            if(detailView.visible) {
                if(detailView.pk.id === pk.id) {
                    detailView.update(pk);
                }
            }
            if(edit_pk_popup.visible){
               if(edit_pk_popup.bid === pk.id){
                   edit_pk_popup.updateText(pk.cont);
               }
            }
        }
    }
    function fuckFocus() {
        col_list_view.forceActiveFocus();
    }
    function getListWidth() {
        return pk_list.width;
    }
    function onPush(ty, data) {
        if(ty === Com.PUSH_UP_TAGS) {
            let pk = Collect.getCurrentPK();
            if(pk) {
                pk.tags = data.tags;
                pk_list_view.currentItem.updateTags(data.tags);
                if(detailView.visible) {
                    detailView.updateTags(data.tags);
                }
            }
        }
    }
}
