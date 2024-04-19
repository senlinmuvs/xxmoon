import QtQuick
import QtQuick.Controls.Fusion
import QtQuick.Dialogs
import Qt.labs.platform

import "../com"
import "../com/com.js" as Com
import "../com/tag.js" as Tag
import "../com/ui.js" as UI
import "Book.js" as Book

Rectangle {
    id: root
    anchors.fill: parent
    signal st(int type, string tip)
    signal key(var e)
    signal tipsInfo(string txt)

    property var tagCom: Qt.createComponent("qrc:/qml/com/Tag.qml")
    property var tagManager: new Tag.TagManager(tagCom, 1, search_bar, tag_view, work_list_view, new Book.NoteTagDelegate())
    property int view_type: 0

    ListModel {
        id: work_list_model
    }
    ListModel {
        id: model_work_cat
    }
    TextField {
        id: search_bar
        property var keys: []
        anchors.top: parent.top
        anchors.left:parent.left
        anchors.right: parent.right
        height: 40
        placeholderText: $a.tr("Search...")
        font.family: "Arial"
        font.pointSize: UI.btn_font_size
        color: "white"
        selectByMouse: true
        background: Rectangle {
            anchors.fill: parent
            color:"#222"
        }
        onTextChanged: {
            keys = Book.filterKey(text);
            clearData();
            loadWork();
        }
        Keys.onPressed: function(event) {
            if(event.key === Qt.Key_Escape || event.key === Qt.Key_Return || event.key === Qt.Key_Tab) {
                event.accepted = true;
                work_list_view.forceActiveFocus();
            }
        }
        onFocusChanged: {
            if(focus) {
                $a.regMenuReceiver(this);
            }
        }
    }
    Component {
        id: com_work_cat
        Rectangle {
            color: "transparent"
            width: e_name.width + e_n.width + 20
            height: 30
            Row {
                anchors.centerIn: parent
                spacing: 1
                Text {
                    id: e_name
                    height: 30
                    text: name
                    color: "white"
                    verticalAlignment: Text.AlignVCenter
                }
                Text {
                    id: e_n
                    text: n>0?n:''
                    height: 30
                    color: "white"
                    font.pointSize: 10
                    verticalAlignment: Text.AlignVCenter
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: function(mouse){
                    list_work_cat.currentIndex = index;
                }
            }
        }
    }
    Rectangle {
        id: work_list
        width: parent.width/3
        anchors {
            left: parent.left
            top: search_bar.bottom
            bottom: parent.bottom
        }
        color: "#282828"
        clip: true
        Rectangle {
            id: e_work_header
            width: parent.width
            height: e_wlh_col.height
            color:"#393939"
            Column {
                id: e_wlh_col
                width: parent.width
                Btn {
                    width: parent.width
                    text: "+"
                    text_size: UI.btn_font_smybol_size
                    text_color: "#EAEAEA"
                    hover_color: "#191919"
                    radius: 1
                    function click() {
                        Book.onBtnClick_addBook();
                    }
                }
                MyList {
                    id: list_work_cat
                    width: parent.width
                    height: 30
                    showHighligh: true
                    highColor: "#292929"
                    clip: true
                    orientation: ListView.Horizontal
                    model: model_work_cat
                    delegate: com_work_cat
                    onCurrentIndexChanged: {
                        clearData();
                        loadWork();
                    }
                }
            }
        }
        MyList {
            id: work_list_view
            showHighligh: true
            clip: true
            Component {
                id: workMoreBtn
                MoreBtn {
                    function click() {
                        if(work_list_view.footer) {
                            loadWork();
                        }
                    }
                }
            }
            Component {
                id: workNoMoreBtn
                Rectangle{}
            }
            anchors.top: e_work_header.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            model: work_list_model
            delegate: ComponentWork{}
            onCurrentIndexChanged: {
                note_list_view.page = 0;
                note_list_view.currentIndex = 0;
                Book.loadNote(true);
            }
//            interactive: false
            focus: true
            highColor: "#000"
            Keys.onPressed: function(event) {
                Book.onKeyPressed(event);
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
                $a.setLocal($a.ENV_K_LAST_BOOK_LEFT_WIDTH, Math.floor(work_list.width));
            }
            onPositionChanged:function(mouse){
                if(startX > 0){
                    let left = mouse.x < startX;
                    if(left){
                        let delta = startX - mouse.x
                        work_list.width = Com.max(100,work_list.width - delta);
                    } else {
                        let delta = mouse.x - startX
                        work_list.width = Com.min(root.width/3*2,work_list.width + delta);
                    }
                    $a.setUIVal(1, note_list.width);
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
    Menu {
        id: menu_work_right
        MenuItem {
            text: $a.tr("Edit")
            onTriggered: {
                let i = work_list_view.currentIndex;
                let w = work_list_model.get(i);
                if(w) {
                    work_edit_popup.op(w.name, w.author, Com.parseTime(w.time,1)[0], w.tag, w.extra, w.id);
                }
            }
        }
        MenuSeparator {}
        MenuItem {
            text: $a.tr("Delete")
            onTriggered: {
                Book.delWork();
            }
        }
        MenuSeparator {}
        MenuItem {
            text: $a.tr("Generate PDF")
            onTriggered: {
               let w = Book.getCurrentWork();
               if(w) {
                   $a.genFile(Com.file_type_pdf, Com.type_book, w.id, 0);
               }
            }
        }
        MenuSeparator {}
        MenuItem {
            text: $a.tr("Generate HTML")
            onTriggered: {
               let w = Book.getCurrentWork();
               if(w) {
                   $a.genFile(Com.file_type_html, Com.type_book, w.id, 0);
               }
            }
        }
        MenuSeparator {
        }
        MenuItem {
            text: $a.tr("Generate XM")
            onTriggered: {
                let w = Book.getCurrentWork();
                if(w){
                    $a.genFile(Com.file_type_xm, Com.type_book, w.id, 0);
                }
            }
        }
        MenuSeparator {
        }
        MenuItem {
            id: mi_exp_site
            text: $a.tr("Export Site")
            onTriggered: {
                let w = Book.getCurrentWork();
                if(w){
                    $a.genFile(Com.file_type_site, Com.type_book, w.id, 0);
                }
            }
        }
        MenuSeparator {
        }
        MenuItem {
            id: mi_del_site
            text: $a.tr("Delete from Site")
            onTriggered: {
                let w = Book.getCurrentWork();
                if(w) {
                    $a.deleteFromSite(w.id, Com.type_book);
                }
            }
        }
    }
    Menu {
        id: menu_right_note
        MenuItem {
            text: $a.tr("Detail")
            shortcut: "Space"
            onTriggered: {
                Book.detail();
            }
        }
        MenuSeparator {
        }
        MenuItem {
            id: mi_pic_model
            text: $a.tr("Picture Model")
            shortcut: "Enter"
            onTriggered: {
                Book.openImgView();
            }
        }
        MenuSeparator {
            visible: mi_pic_model.visible
        }
        MenuItem {
            id: mi_cont
            text: $a.tr("Copy content")
            shortcut: ctrlName+"+Shift+C"
            onTriggered: {
                Book.copyCont();
            }
        }
        MenuSeparator {
            visible: mi_cont.visible
        }
        MenuItem {
            text: $a.tr("Edit")
            shortcut: ctrlName+"+Enter"
            onTriggered: {
                Book.openEditPopup();
            }
        }
        MenuSeparator {
        }
        MenuItem {
            text: $a.tr("Out Edit")
            shortcut: ctrlName+"+Alt+Enter"
            onTriggered: {
                Book.outEdit();
            }
        }
        MenuSeparator {
        }
        MenuItem {
            text: $a.tr("Delete")
            shortcut: "Backspace"
            onTriggered: {
                ensure_popup.open();
            }
        }
        // MenuSeparator {
        // }
        // MenuItem {
        //     id: mi_send_phone
        //     text: $a.tr("Send To Phone")
        //     onTriggered: {
        //         let n = Book.getCurrentNote();
        //         if(n){
        //             $a.sendToPhone(Com.type_book, n.id, Com.putFunc(function(r) {
        //                 tipsInfo($a.tr("Success"));
        //             }));
        //         }
        //     }
        // }
    }

    ///
    Finder {
        id: finder
        property string contCache: ""
        function find() {
            if(edit_note_popup.visible) {
                let i = finder.find0(edit_note_popup.text);
                edit_note_popup.select(i, finder.txt());
            } else if(detailView.visible) {
                detailView.select(finder.txt());
            }
        }
        function clear() {
            if(edit_note_popup.visible) {
                edit_note_popup.clearSelect();
            } else if(detailView.visible) {
                detailView.clearSelect();
            }
            contCache = "";
        }
    }
    ///
    BookEditPopup {
        id: work_edit_popup
        x:(root.width-width)/2
        y:(root.height-height)/2

        function submit() {
            Book.submitBook();
        }
        function cancel() {
            work_edit_popup.cl();
            work_list_view.forceActiveFocus();
        }
    }
    ListModel {
        id: note_list_model
    }
    Component {
        id: note_delegate_list
        ComponentNote{}
    }
    Component {
        id: note_delegate_simple
        ComponentNoteSimple{}
    }
    Rectangle {
        id: note_list
        anchors {
            left: work_list.right
            top: parent.top
            bottom: parent.bottom
            right: parent.right
        }
        color: "white"
        MyList {
            id: note_list_view
            property int page: 0
            vt: view_type
            Component {
                id: note_list_more_btn
                MoreBtn {
                    function click() {
                        if(note_list_view.footer) {
                            Book.loadNote();
                        }
                    }
                }
            }
            anchors.fill: note_list
            anchors.topMargin: 10
            model: note_list_model
            delegate: view_type === 0 ? note_delegate_list : note_delegate_simple
//            footer: note_list_more_btn
//            focus: true
        }
        function pushNote(list) {
            if($l.isTrace()) {
                console.log(JSON.stringify(list));
            }
            let ar = Com.parseTime(Book.getNoteLastTime(), 1);
            let preDateStr = ar[0];
            let preTimeStr = ar[1];
            for(let i in list) {
                let e = list[i];
                let n = Book.note(e, preDateStr, preTimeStr);
                note_list_model.append(n);
                preDateStr = n.date_str;
                preTimeStr = n.time_str;
            }
            if(list.length > 0) {
                note_list_view.page++;
            }
            if(list.length < $a.pageSize) {
                note_list_view.footer = workNoMoreBtn;
            } else {
                note_list_view.footer = note_list_more_btn;
            }
            $a.setUIVal(1, note_list.width);
        }
        function onDeletedNote() {
            note_list_model.remove(note_list_view.currentIndex);
            let i = work_list_view.currentIndex;
            let total = work_list_model.get(i).total;
            work_list_model.setProperty(i, 'total', Com.max(0,total-1));
        }
    }
    TagView {
        id:tag_view
        tagManager: root.tagManager
        function onTagList(all, list) {
            root.tagManager.loadTagList(all, list);
            //等标签加载完再加载主页数据
            if(work_list_model.count === 0) {
                loadWork();
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
        id: edit_note_popup
        first_field_enable:true
        function submit() {
            Book.submitNote();
        }
        function cancel() {
            Book.cancelEditNote();
        }
    }
    EnsurePopup {
        id: ensure_popup
        function onSure(y) {
            work_list_view.forceActiveFocus();
            if(y) {
                Book.deleteNote();
            }
        }
    }
    Column {
        anchors {
            top: parent.top
            topMargin: 2
            right: parent.right
            rightMargin: 2
        }
        spacing: 4
        Btn {
            id: sort_btn
            width: 20
            height: 20
            text: "p"
            text_size: UI.book_btn_view_font_size
            color: Qt.rgba(0/255, 0/255, 0/255, 0.9)
            function click() {
                if(text === 'p') {
                    text = 't';
                } else {
                    text = 'p';
                }

                note_list_view.page = 0;
                Book.loadNote(true);
                $a.set($a.ENV_K_LAST_SORT, text);
            }
        }
        Btn {
            id: view_btn
            width: 20
            height: 20
            text: view_type === 0 ? "≡" : '■'
            text_size: UI.book_btn_view_font_size
            color: Qt.rgba(0/255, 0/255, 0/255, 0.9)
            function click() {
                if(view_type === 0) {
                    text = "■";
                    view_type = 1;
                } else {
                    text = "≡";
                    view_type = 0;
                }
                $a.set($a.ENV_K_LAST_VIEW_TYPE, view_type);
            }
        }
    }
    Component.onCompleted: {
        work_list_view.forceActiveFocus();

        $bk.getWorkTagList(Com.putFunc(function(list){
            let tagMap = {};
            for(let i = 0; i < list.length; i++) {
                let arr = list[i].split("#");
                for(let j = 0; j < arr.length; j++) {
                    let tag = arr[j];
                    if(tag) {
                        let n = tagMap[tag];
                        if(!n) {
                            n = 0;
                        }
                        tagMap[tag] = n+1;
                    }
                }
            }
            let tagMapCopy = Object.assign({},tagMap);
            let tags = [];
            let count = 0;
            let x = 0;
            while(true) {
                let maxTag = '';
                let maxN = 0;
                for(let k in tagMap) {
                    // console.log(k, tagMap[k]);
                    let n = Number(tagMap[k]);
                    if(n > maxN) {
                        maxTag = k;
                        maxN = n;
                    }
                    count++;
                }
                if(maxTag) {
                    tags[tags.length] = maxTag;
                    delete tagMap[maxTag];
                }
                if(x++ >= count) {
                    break;
                }
            }
            $bk.countWork(Com.putFunc(function(c){
                model_work_cat.append({name:"全部", n:c});

                for(let i = 0; i < tags.length; i++) {
                    let name = tags[i];
                    model_work_cat.append({name:name, n:tagMapCopy[name]});
                }
            }));
        }));
    }
    function init(data) {
        if(data) {
            root.view_type = data[$a.ENV_K_LAST_VIEW_TYPE];
            sort_btn.text = data[$a.ENV_K_LAST_SORT];
            let lw = data[$a.ENV_K_LAST_BOOK_LEFT_WIDTH];
            if(lw){
                work_list.width = lw;
            }
            if(work_list_model.count === 0) {
                work_list_view.forceActiveFocus();
                tagManager.initData();
            }
        }
    }
    function loadWork() {
        let k = search_bar.text.trim();
        let tag = '';
        let wtag = model_work_cat.get(list_work_cat.currentIndex);
        if(wtag) {
            tag = wtag.name;
            if(tag==='全部') {
                tag = '';
            }
        }
        $bk.getWorkList(k, tag, Book.getWorkLastTime(), root);
    }
    function pushWork(list) {
        Com.info('pushWork', list.length);
        let preTimeStr = Com.parseTime(Book.getWorkLastTime())[0];
        for(let i in list) {
            let e = list[i];
            if($l.isTrace()) {
                Com.trace('work', JSON.stringify(e));
            }
            let w = {
                id: e.id,
                name: e.name,
                author: e.author,
                time: e.time,
                total: e.total,
                t: e.t,
                from_str: '',
                tag: e.tag,
                extra: e.extra
            };
            let arr = Com.parseTime(w.time);
            w.time_str = arr[0];
            w.visible_time = preTimeStr !== w.time_str;
            if(e.fro === 0) {
                w.from_str = 'K';
            } else if(e.fro === 1) {
                w.from_str = '豆';
            } else if(e.fro === 2) {
                w.from_str = '微';
            }
            if($l.isTrace()) {
                console.log(JSON.stringify(w));
            }
            work_list_model.append(w);
            preTimeStr = w.time_str;
        }
        if(list.length > 0) {
            Book.loadNote();
        }
        if(list.length < $a.pageSize) {
            work_list_view.footer = workNoMoreBtn;
        } else {
            work_list_view.footer = workMoreBtn;
        }
    }
    ///
    function onUpdateWork(work) {
        let arr = work_edit_popup.getData();
        if(arr) {
            let w_ = Book.getWorkById(work_edit_popup.bid);
            if(w_) {
                let diffMonth = Com.getMonth(w_[1].time) !== Com.getMonth(work.time);
                if(diffMonth) {
                    work_list_model.remove(w_[0]);
                    onAddWork(work);
                } else {
                    w_[1].name = work.name;
                    w_[1].author = work.author;
                    w_[1].time = work.time;
                    w_[1].tag = work.tag;
                    w_[1].extra = work.extra;
                }
            }
        }
        work_edit_popup.cl();
        work_list_view.forceActiveFocus();
    }
    function onAddWork(work) {
        let insertIndex = 0;
        for(let i = 0; i < work_list_model.count; i++) {
            let w = work_list_model.get(i);
            if(w) {
//                Com.log(i, w.time, work.time);
                if(w.time <= work.time) {
                    insertIndex = i;
                    break;
                }
            }
        }
        let arr = Com.parseTime(work.time);
        work.time_str = arr[0];
        work.visible_time = true;
        if(insertIndex>0) {
            let prew = work_list_model.get(insertIndex-1);
            if(prew) {
                work.visible_time = prew.time_str !== work.time_str;
            }
        }
        work_list_model.insert(insertIndex, work);
        //
        work_list_view.forceActiveFocus();
        work_edit_popup.cl();
    }
    function fuckFocus(){
        work_list_view.forceActiveFocus();
    }
    function onUpdateNote(n) {
        let arr = Book.getNoteByIdInCurrentList(n.id);
        if(arr) {
            arr[1].cont = n.cont;
            arr[1].qmls = JSON.stringify(n.qmls);
            if(detailView.visible) {
                if(detailView.pk.id === n.id) {
                    detailView.update(Book.convNoteToPK(n));
                }
            }
            if(edit_note_popup.visible) {
               if(edit_note_popup.bid === n.id){
                   edit_note_popup.updateText(n.cont);
               }
            }
        }
    }
    function getListWidth() {
        return xm_list.width;
    }
    function clearData() {
        note_list_view.page = 0;
        work_list_model.clear();
        note_list_model.clear();
    }
    function navBtnClick(ty) {
        if(ty === 'add') {
            Book.openEditPopup(1);
        } else if(ty === 'tag') {
            tagManager.openTagView();
        }
    }
}
