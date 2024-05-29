import QtQuick 2.13
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import Qt.labs.platform 1.1
import '../com'
import "../com/com.js" as Com
import "../xm/XM.js" as XM
import "ui.js" as UI

Rectangle {
    id: root
    width: parent.width
    height: parent.height
    x: parent.width-width
    visible: false

    property var pk: null
    property double scrollStep: 0.025
    property var stack: []
    property alias tagLine: tag_line
    property var delegate:null
    property var items: []

    MouseArea {
        id: ma_root
        anchors.fill: parent

        ScrollView {
            id: scroll
            width: parent.width
            height: parent.height
            contentWidth:  width - 5
            contentHeight: col.height + 30
            clip: true
            Column {
                id: col
                width: parent.width
                spacing: UI.ui_pk_cont_space
                anchors {
                    top:parent.top
                    topMargin: 5
                    left: parent.left
                    right: parent.right
                    rightMargin: 5
                }
                MyImage {
                    id: img
                    z:1
                    source: pk ? (pk.jm ? Com.img_logo : pk.img_path) : ''
                    img_radius: 5
                    width: pk?Com.calImgSizeByWidth(pk.src_w,pk.src_h,root.width-100)[0]:0
                    height: pk?Com.calImgSizeByWidth(pk.src_w,pk.src_h,root.width-100)[1]:0
                    anchors.horizontalCenter: parent.horizontalCenter
                    function onClickImg(src, mouse) {
                        if (mouse.button === Qt.LeftButton) {
                            openImgView(src);
                        } else {
                            openRightClickMenu(mouse);
                        }
                    }
                    function released(mouse) {
                        if(root.delegate && root.delegate.isSeparateWindow && root.delegate.isSeparateWindow()) {
                            return;
                        }
                        if (mouse.button === Qt.RightButton) {
                            openRightClickMenu(mouse);
                        }
                    }
                }
                Column {
                    id: cols
                    width: parent.width - 10
                    function onClickImg(src, mouse) {
                        if (mouse.button === Qt.LeftButton) {
                            openImgView(src);
                        } else {
                            openRightClickMenu(mouse);
                        }
                    }
                    function released(mouse) {
                        if(root.delegate && root.delegate.isSeparateWindow && root.delegate.isSeparateWindow()) {
                            return;
                        }
                        if (mouse.button === Qt.RightButton) {
                            openRightClickMenu(mouse);
                        }
                    }
                }
                Row {
                    width: parent.width
                    layoutDirection: Qt.RightToLeft
                    TagLine {
                        id: tag_line
                        tag_ids: pk?pk.tags:""
                        delegate: root.delegate?root.delegate.getTagManager():null
                    }
                }
                Text {
                    width: parent.width
                    visible: pk && pk.extra
                    text: pk && pk.extra ? pk.extra : ""
                    color: "#898989"
                    font.pointSize: UI.detail_time_font_size
                    horizontalAlignment: Text.AlignHCenter
                }
                Row {
                    width: parent.width
                    layoutDirection: Qt.RightToLeft
                    spacing: 10
                    Text {
                        text: pk&&pk.id>0 ? "["+pk.id+"]" : ''
                        font.pointSize: UI.detail_time_font_size
                        color:"#898989"
                        height: 25
                        lineHeight: height
                    }
                    Text {
                        id: e_dtime
                        text: pk&&pk.dtime?Com.viewTime(pk.dtime) + " " + $a.tr('done') : ''
                        font.pointSize: UI.detail_time_font_size
                        color:"#898989"
                        height: 25
                        lineHeight: height
                    }
                    Text {
                        id: e_stime
                        text: pk&&pk.stime?Com.viewTime(pk.stime) + " " + $a.tr('solved ') : ''
                        font.pointSize: UI.detail_time_font_size
                        color:"#898989"
                        height: 25
                        lineHeight: height
                    }
                    Text {
                        text: pk&&pk.lst?Com.viewTime(pk.lst) + " " + $a.tr('up ') : ''
                        font.pointSize: UI.detail_time_font_size
                        color:"#898989"
                        height: 25
                        lineHeight: height
                    }
                    Text {
                        id: time
                        text: pk && pk.time ? Com.viewTime(pk.time) + " " + $a.tr('created ') : ''
                        font.pointSize: UI.detail_time_font_size
                        color:"#898989"
                        height: 25
                        lineHeight: height
                    }
                }
            }
            Keys.onUpPressed: scrollBar.decrease()
            Keys.onDownPressed: scrollBar.increase()
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ScrollBar.vertical: ScrollBar {
                id: scrollBar
                parent: scroll.parent
                anchors.top: scroll.top
                anchors.right: scroll.right
                anchors.bottom: scroll.bottom
                stepSize: scrollStep
            }
            Keys.onPressed: function(event) {
                onKeysPressed(event);
            }
        }

        acceptedButtons: Qt.RightButton
    }
    Menu {
        id: menu_right
        MenuItem {
            id: mi_copy
            text: $a.tr("Copy")
            onTriggered: {
                $a.triggerMenu(3);
            }
        }
        MenuSeparator {
            visible: mi_copy.visible
        }
        MenuItem {
            id: mi_paste
            text: $a.tr("Paste")
            onTriggered: {
                $a.triggerMenu(4);
            }
        }
        MenuSeparator {
            visible: mi_copy.visible
        }
        MenuItem {
            id: mi_import
            visible: pk!=null&&pk.file!==''
            text: $a.tr("Import")
            onTriggered: {
                importFile();
            }
        }
        MenuSeparator {
            visible: mi_import.visible
        }
        MenuItem {
            id: mi_edit
            visible: pk&&!pk.file
            text: $a.tr("Edit")
            shortcut: ctrlName+"+Enter"
            onTriggered: {
                edit();
            }
        }
        MenuSeparator {
            visible: mi_edit.visible
        }
        MenuItem {
            visible: mi_edit.visible
            text: $a.tr("Out Edit")
            shortcut: ctrlName+"+Alt+Enter"
            onTriggered: {
                outEdit();
            }
        }
        MenuSeparator {
            visible: mi_edit.visible
        }
        MenuItem {
            id:mi_picture_model
            text: $a.tr("Picture Model")
            shortcut: "Enter"
            onTriggered: {
                openImgView();
            }
        }
        MenuSeparator {
            visible: mi_picture_model.visible
        }
        MenuItem {
            text: $a.tr("Close")
            shortcut: "Esc"
            onTriggered: {
                close();
            }
        }
    }

    function onKeysPressed(event) {
        if(event.modifiers === ctrlVal && event.key === Qt.Key_J) {
            if(root.delegate && root.delegate.isSeparateWindow && root.delegate.isSeparateWindow()) {
                return;
            }
            if(delegate){
                let pk = delegate.next();
                openDetail(pk);
            }
        } else if(event.modifiers === ctrlVal && event.key === Qt.Key_K) {
            if(root.delegate && root.delegate.isSeparateWindow && root.delegate.isSeparateWindow()) {
                return;
            }
            if(delegate){
                let pk = delegate.previous();
                openDetail(pk);
            }
        } else if(event.key === Qt.Key_Home) {
            setToTop();
        } else if(event.key === Qt.Key_End) {
            setToBottom();
        } else if(event.key === Qt.Key_J) {
            setToDown();
        } else if(event.key === Qt.Key_K) {
            setToUp();
        } else if(event.modifiers === ctrlVal && event.key === Qt.Key_Return) {
            if(root.delegate && root.delegate.isSeparateWindow && root.delegate.isSeparateWindow()) {
                return;
            }
            edit();
        } else if(event.modifiers === (ctrlVal | Qt.AltModifier) && event.key === Qt.Key_Return) {
            if(root.delegate && root.delegate.isSeparateWindow && root.delegate.isSeparateWindow()) {
                return;
            }
            outEdit();
        } else if(event.key === Qt.Key_Left) {
            if(stack.length > 0) {
                let id = stack[stack.length-1];
                reloadData(id);
                pop();
            }
        } else if(event.modifiers === ctrlVal && event.key === Qt.Key_F) {
            if(delegate) {
                delegate.openFinder();
            }
        } else if((event.modifiers === ctrlVal && event.key === Qt.Key_W) || event.key === Qt.Key_Escape) {
            if(root.delegate && root.delegate.isSeparateWindow && root.delegate.isSeparateWindow()) {
                if(event.modifiers === ctrlVal && event.key === Qt.Key_W) {
                    root.delegate.close();
                }
                return;
            }
            close();
        } else if(event.key === Qt.Key_Return) {
            openImgView();
        }
    }
    function edit() {
        if(!pk.jm){
            push(pk.id);
            if(delegate) {
                delegate.openEditPopup(false, pk);
            }
            $a.setUIVal(4, scrollBar.position);
        }
    }
    function outEdit() {
        if(pk){
            if(pk.bk){
                $a.openInExternal(1, pk.id, 1);
            } else {
                if(!pk.jm){
                    $a.openInExternal(1, pk.id);
                }
            }
        }
    }
    function open() {
        visible = true;
        scroll.forceActiveFocus();
    }
    function close() {
        if(root.delegate && root.delegate.isSeparateWindow && root.delegate.isSeparateWindow()) {
            return;
        }
        visible = false;
        for(let i = 0; i < items.length; i++) {
            items[i].destroy();
        }
        items = [];
        if(delegate) {
            delegate.onClose();
        }
    }
    function scrollTo(pos) {
        console.log("scrollTo", pos);
        scrollBar.position = pos;
    }
    function setToTop() {
        scrollTo(0);
    }
    function setToBottom() {
        scrollBar.stepSize = 1;
        setToDown();
        scrollBar.stepSize = scrollStep;
    }
    function setToUp() {
        scrollBar.decrease();
    }
    function setToDown() {
        scrollBar.increase();
    }
    function updateTags(tags, stime) {
        if($l.isDebug()){
            Com.trace("Detail.qml updateTags", JSON.stringify(tags));
        }
        if(stime && pk) {
            pk.stime = stime;
            refreshStime();
        }
        tag_line.update(tags);
    }
    function refreshStime() {
        e_stime.text = pk&&pk.stime?Com.viewTime(pk.stime) + " " + $a.tr('solved ') : ''
    }
    function cl() {
        pk = null;
        stack = [];
    }
    function op(pk) {
        root.pk = pk;
        // console.log("openDetail>>>>>>>>>", JSON.stringify(pk));
        let qmls;
        if(pk.qmls_) {
            qmls = JSON.parse(pk.qmls_);
        } else {
            qmls = pk.qmls;
        }
        if(qmls) {
            cols.data = [];
        //            console.log("---------------------------------------------");
            for(let i = 0; i < qmls.length; i++) {
                let qml = qmls[i];
                if(pk.forceMaxWidth) {
                    if(qml.startsWith("Txt{")) {
                        let ind = qml.indexOf("width:");
                        if(ind >= 0) {
                            qml = qml.substring(0, ind)+"width:"+(root.width-30)+"}";
                        }
                    }
                }
        //                console.log(i, qml);
                let t1 = new Date().getTime();
                let o = Qt.createQmlObject(qml, cols, "dy_"+i);
                let t2 = new Date().getTime();
        //                console.log(">>>>>>>>>>>>>", t2-t1, qml);
            }
        //            console.log("---------------------------------------------");
        }
        scroll.forceActiveFocus();
        refreshStime();
        open();
    }
    function reopen() {
        if(stack.length > 0) {
            let lastId = stack[stack.length-1];
            reloadData(lastId);
            pop();

            let pos = Number($a.getUIVal(4));
            if(pos) {
                scrollTo(pos);
            }
            return true;
        }
        return false;
    }
    function reloadData(id, cb) {
        if($l.isDebug()) {
            Com.debug('reloadData', id);
        }
        if(id > 0) {
            delegate.getData(id, root.width, function(pk) {
                if($l.isDebug()) {
                    Com.debug('reloadData suc pk', JSON.stringify(pk));
                }
                updateTags(pk.tags);
//                console.log(JSON.stringify(pk.qmls));
                op(pk);
                if(cb) {
                    cb(pk);
                }
            });
        }
    }
    function push(id) {
        stack[stack.length] = id;
    }
    function pop(){
        stack.length = stack.length-1;
    }
    function update(pk) {
        root.pk = pk;
        op(pk);
    }
    function select(k) {
        if(k.length > 0) {
            let first = false;
            if(k !== preFindKey) {
                clearFind();
                first = true;
            }
            if(cols.data) {
                clearSelect();
                let found = false;
                for(let i = 0; i < cols.data.length; i++) {
                    let it = cols.data[i];
                    if(it instanceof Txt || it instanceof Quote || it instanceof Code) {
                        let e_txt = it.getTxt();
                        let txt = e_txt.getText(0, it.text.length);
                        let ok = select0(i, e_txt, txt, k, first);
                        if(ok) {
                            found = true;
                            break;
                        }
                    }
                }
                if(!found) {
                    let jumpToFirst = false;
                    if(firstQmlIndex >= 0 && firstSelectStart >= 0 && firstSelectEnd >= 0) {
                        let it = cols.data[firstQmlIndex];
                        if(it) {
//                            console.log(firstQmlIndex, firstSelectStart, firstSelectEnd);
                            qmlIndex = firstQmlIndex;
                            selectStart = firstSelectEnd;
                            it.getTxt().select(firstSelectStart, firstSelectEnd);
                            jumpToFirst = true;
                        }
                    }
                    if(!jumpToFirst) {
                        clearFind();
                    }
                }
            }
            preFindKey = k;
        }
    }

    property int firstQmlIndex: -1
    property int firstSelectStart: -1
    property int firstSelectEnd: -1
    property string preFindKey: ''
    property int qmlIndex: 0
    property int selectStart: 0
    function clearFind() {
        qmlIndex = 0;
        selectStart = 0;
        firstQmlIndex = -1;
        firstSelectStart = -1;
        firstSelectEnd = -1;
    }
    function select0(qmlI, it, text, k, first) {
        if(qmlI < qmlIndex) {
            return false;
        }
//        console.log("----------------select0 start--------------------");
//        console.log("select0", qmlIndex, it, text.length, text, k, selectStart);
        let len = text.length;
        let i = text.indexOf(k, selectStart);
        if(i < 0) {
            if(qmlI===qmlIndex) {
                selectStart = 0;
            }
            return false;
        }
        let j = i+k.length;
        it.select(i,j);
        qmlIndex = qmlI;
        selectStart = j;
        if(first) {
            firstQmlIndex = qmlIndex;
            firstSelectStart = i;
            firstSelectEnd = j;
        }

        let line = $a.calLine(text,i);
        let bl = Com.max(0,Com.min(1,(it.y+(line/it.lineCount*it.height))/(cols.height+root.height/2) - 0.05));
        scrollTo(bl);
//        console.log("select0", i, j, selectStart, line, it.lineCount, bl);
//        console.log("----------------select0 end--------------------");
        return true;
    }
    function clearSelect() {
        for(let i = 0; i < cols.data.length; i++) {
            let it = cols.data[i];
            if(it instanceof Txt || it instanceof Quote || it instanceof Code) {
                let e_txt = it.getTxt();
                e_txt.select(0, 0);
            }
        }
    }
    function importFile() {
        if(delegate) {
            delegate.importFile();
        }
    }
    function openImgView(img) {
        let img_view_delegate = {
            setIndex:function(i) {
            },
            getCurrentIndex:function() {
                return 0;
            },
            previous:function() {
                return null;
            },
            next:function() {
                return null;
            },
            onClose:function() {
                let tmp = root.pk;
                cl();
                op(tmp);
            }
        }
        imgViewer.delegate = img_view_delegate;
        let n = imgViewer.append(pk);
        if(n>0) {
            if(img) {
                imgViewer.setCurIndexByImg(img);
            }
            imgViewer.open();
        }
    }
    function openRightClickMenu(mouse) {
        mi_picture_model.visible = pk&&pk.imgs.length > 0;
        menu_right.open();
    }
}
