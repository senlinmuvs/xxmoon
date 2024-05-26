.import "qrc:/qml/com/com.js" as Com
.import "qrc:/qml/com/tag.js" as Tag

///Work
function filterKey(k) {
    if(k.startsWith("#")) {
        let arr = tagManager.parseKey(k);
        return [false, false, '', arr[0]];
    } else {
        let k1 = "", k2 = k.trim();
        let searchAuthor = k.startsWith("a ");
        let searchBook = k.startsWith("b ");
        if(searchAuthor || searchBook) {
            let tmp = k.substring(2, k.length).trim();
            let i = tmp.indexOf(" ");
            if(i >= 0) {
                k1 = tmp.substring(0, i);
                k2 = tmp.substring(i+1, tmp.length);
            } else {
                k1 = tmp;
            }
        }
        return [searchAuthor, searchBook, k1, k2];
    }
}

function getWorkLastTime() {
    if(work_list_model.count > 0) {
        let lastW = work_list_model.get(work_list_model.count - 1);
        return lastW.time;
    } else {
        return 0;
    }
}
function workTotalIncrement() {
    let i = work_list_view.currentIndex;
    let w = work_list_model.get(i);
    w.total = w.total + 1;
}
function workTotalDecrement() {
    let i = work_list_view.currentIndex;
    let w = work_list_model.get(i);
    w.total = Com.max(0, w.total - 1);
}
function getCurrentWork() {
    let i = work_list_view.currentIndex;
    let w = work_list_model.get(i);
    return w;
}

function onKeyPressed(event) {
    event.accepted = true;
    let jump = false;
    if(event.modifiers === Qt.ShiftModifier && event.key === Qt.Key_J) {
        if(work_list_view.currentIndex+1 >= work_list_view.count) {
            loadWork();
        }
        work_list_view.currentIndex = (work_list_view.currentIndex+1) % work_list_view.count;
    } else if(event.modifiers === Qt.ShiftModifier && event.key === Qt.Key_K) {
        let i = work_list_view.currentIndex - 1;
        if(i < 0){
            i = work_list_view.count - 1;
        }
        work_list_view.currentIndex = i;
    } else if(event.key === Qt.Key_J || event.key === Qt.Key_Down) {
        if(note_list_view.currentIndex+1>=note_list_view.count) {
            loadNote();
        }
        note_list_view.currentIndex = Com.min(note_list_view.count-1, note_list_view.currentIndex+1);
        jump = true;
    } else if(event.key === Qt.Key_K || event.key === Qt.Key_Up) {
        note_list_view.currentIndex = Com.max(0, note_list_view.currentIndex-1);
        jump = true;
    } else if(event.modifiers === ctrlVal && event.key === Qt.Key_Return) {
        openEditPopup();
    } else if(event.modifiers === ctrlVal && event.key === Qt.Key_N) {
        openEditPopup(1);
    } else if(event.modifiers === (ctrlVal|Qt.ShiftModifier) && event.key === Qt.Key_N) {
        onBtnClick_addBook();
    } else if(event.modifiers === (ctrlVal|Qt.ShiftModifier) && event.key === Qt.Key_C) {
        copyCont();
    } else if(event.modifiers === (ctrlVal|Qt.AltModifier) && event.key === Qt.Key_Return) {
        outEdit();
    } else if(event.key === Qt.Key_Delete || event.key === Qt.Key_Backspace) {
        if(note_list_model.count > 0) {
            ensure_popup.open();
        }
    } else if(event.modifiers === ctrlVal && event.key === Qt.Key_F) {
        search_bar.forceActiveFocus();
    } else if(event.modifiers === ctrlVal && event.key === Qt.Key_T) {
        navBtnClick('tag');
    } else if(event.key === Qt.Key_Home) {
        note_list_view.currentIndex = 0;
    } else if(event.key === Qt.Key_End) {
        note_list_view.currentIndex = note_list_view.count - 1;
    } else if(event.key === Qt.Key_Space) {
        detail();
    } else if(event.key === Qt.Key_Return){
        openImgView();
    } else {
        jump = true;
    }

    if(jump) {
        Com.jump(event, work_list_model, work_list_view);
    }
    root.key(event);
}
function outEdit() {
    let n = getCurrentNote();
    if(n) {
        $a.openInExternal(1, n.id, 1);
    }
}

function copyCont() {
    let n = getCurrentNote();
    if(n){
        $a.copy(n.cont);
    }
}

function next() {
    if(note_list_view.currentIndex+1>=note_list_view.count) {
        loadNote();
    }
    let i = note_list_view.currentIndex+1;
    if(i > note_list_view.count-1) {
        note_list_view.currentIndex = note_list_view.count-1;
        return null;
    } else {
        note_list_view.currentIndex = i;
        return note_list_model.get(i);
    }
}
function previous() {
    let i = note_list_view.currentIndex-1;
    if(i < 0){
        note_list_view.currentIndex = 0;
        return null;
    } else {
        note_list_view.currentIndex = i;
        return note_list_model.get(i);
    }
}

let img_view_delegate = {
    setIndex:function(i) {
        work_list_view.currentIndex = i;
    },
    getCurrentIndex:function() {
        return work_list_view.currentIndex;
    },
    previous:function(){
        return previous();
    },
    next:function(){
        return next();
    },
    onClose:function() {
        work_list_view.forceActiveFocus();
        let note = getCurrentNote();
        if(note) {
            let tmp_q = note.qmls;
            note.qmls = "";
            note.qmls = tmp_q;
        }
    }
}

function openImgView(img) {
    let pk = getCurrentNote();
    if(pk) {
        imgViewer.delegate = img_view_delegate;
        let n = imgViewer.append(pk);
        if(n>0) {
            if(img) {
                imgViewer.setCurIndexByImg(img);
            }
            imgViewer.open();
        }
    }
}

let detail_delegate = {
    next:function() {
        if(note_list_view.currentIndex+1>=note_list_view.count) {
            loadNote();
        }
        let i = note_list_view.currentIndex + 1;
        if(i > note_list_view.count - 1) {
            note_list_view.currentIndex = note_list_view.count - 1;
            return null;
        } else {
            note_list_view.currentIndex = i;
            return note_list_model.get(i);
        }
    },
    previous:function() {
        let i = note_list_view.currentIndex-1;
        if(i < 0){
            note_list_view.currentIndex = 0;
            return null;
        } else {
            note_list_view.currentIndex = i;
            return note_list_model.get(i);
        }
    },
    onClose:function() {
        img_view_delegate.onClose();
    },
    getTagManager:function() {
        return tag_view.tagManager;
    },
    openEditPopup:function(add, pk) {
        edit_note_popup.delegate = editor_delegate;
        openEditPopup(add, pk);
    },
    getData:function(id, w, cb) {
        $bk.getNote(id, Com.putFunc(function(n){
            cb(convNoteToPK(n));
        }));
    },
    openFinder:function() {
        finder.open();
    }
}

let editor_delegate = {
    onClose:function(wid, id) {
//        if(detailView.visible) {
//            detailView.reloadData(id);
//        }
    }
}

///Note
function convNoteToPK(e) {
    let extra = "";
    let w = getCurrentWork();
    if(w) {
        extra = w.name + " / " + w.author + " / ["+ e.pos0 + "-" + e.pos1 + "]";
    }
    return {
        id: e.id,
        cont: e.cont,
//        html: e.html,
        qmls: e.qmls,
        time: e.time,
        tags: e.tags,
        imgs: e.imgs,
        bj: e.bj,
        wid: e.wid,
        img_path:'',
        extra: extra,
        bk:1,
        lst:e.lst
    }
}

function loadNote(clear, cb) {
    note_list_view.footer = note_list_more_btn;
    if(clear) {
        note_list_model.clear();
    }
    let w = getCurrentWork();
    if(w){
        let k = search_bar.text.trim();
        let sort = sort_btn.text.trim();
        // console.log('load note', k, w.id, note_list_view.page, sort, JSON.stringify(w));
        $bk.getNoteList(k, w.id, note_list_view.page, sort, note_list_view.width, Com.putFunc(function(list){
            if($l.isDebug()) {
                Com.debug("pushNote len", list.length);
            }
            let ar = Com.parseTime(getNoteLastTime(), 1);
            let preDateStr = ar[0];
            let preTimeStr = ar[1];
            for(let i in list) {
                if($l.isTrace()) {
                    Com.trace("note", JSON.stringify(list[i]));
                }
                let e = list[i];
                let n = note(e, preDateStr, preTimeStr);
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
            if(cb) {
                cb();
            }
        }));
    }
}
function detail() {
    openDetail(convNoteToPK(getCurrentNote()), detail_delegate);
}
// book
function onBtnClick_addBook() {
    if(!work_edit_popup.visible) {
        work_edit_popup.op();
    }
}
function submitBook() {
    let arr = work_edit_popup.getData();
    let name = arr[0];
    let author = arr[1];
    let date = arr[2];
    let tag = arr[3];
    let extra = arr[4];
    if(!name || !date) {
        return;
    }
    let time = Com.convStrToTime(date)/1000;
    if(work_edit_popup.bid) {
        $bk.updateWork(work_edit_popup.bid, name, author, time, tag, extra, root);
    } else {
        let n = work_list_model.count;
        for(let x = 0; x < n; x++) {
            let m = work_list_model.get(x);
            if(m.name === name && m.author === author) {
                tipsInfo($a.tr("Exists Already"));
                return;
            }
        }
        $bk.addWork(name, author, time, tag, extra, root);
    }
}
function getWorkById(bid) {
    for(let i = 0; i < work_list_model.count; i++) {
        let w = work_list_model.get(i);
        if(w) {
            if(w.id === bid) {
                return [i, w];
            }
        }
    }
    return 0;
}
function delWork() {
    let i = work_list_view.currentIndex;
    let w = work_list_model.get(i);
    if(w.total > 0) {
        tipsInfo($a.tr("Can not delete, it not empty."));
    } else {
        $bk.delWork(w.id, Com.putFunc(function(){
            work_list_model.remove(i);
            loadNote();
        }));
    }
}
///edit popup
function getCurrentNote() {
    let i = note_list_view.currentIndex;
    let n = note_list_model.get(i);
    return n;
}
function getCurrentNoteId() {
    let n = getCurrentNote();
    return n?n.id:0;
}
function getNoteByIdInCurrentList(id) {
    let ct = note_list_model.count;
    for(let i = 0; i < ct; i++) {
        let n = note_list_model.get(i);
        if(n.id === id) {
            return [i, n];
        }
    }
    return null;
}
function openEditPopup(add, n) {
    if(add) {
        let w = getCurrentWork();
        if(w) {
            edit_note_popup.op(w.id);
        }
    } else {
        if(!n) {
            let i = note_list_view.currentIndex;
            n = note_list_model.get(i);
        }
        if(n) {
//            Com.log(n.wid, n.id, n.cont, n.pos0, n.pos1);
            edit_note_popup.op(n.wid, n.id, n.cont, n.pos0, n.pos1, n.bj);
        }
    }
}
function submitNote(cb, upeditor=0) {
    if(edit_note_popup.bid) {
        updateNote(edit_note_popup.bid, cb, upeditor);
    } else {
        addNote(edit_note_popup.gid, cb);
    }
}
function updateNote(id, cb, upeditor=0) {
    let d = edit_note_popup.getData();
    if($l.isDebug()) {
        $l.debug("updateNote id "+id+" " + d);
    }
    $bk.updateNote(id, d.cont, d.pos0, d.pos1, note_list.width, Com.putFunc(function(n) {
        if($l.isDebug()) {
            $l.debug("updateNote finished note " + JSON.stringify(n));
        }
        n = note(n);
        onUpdateNote(n, upeditor);
        if(cb) {
            cb(n);
        }
    }));
}

function addNote(id, cb) {
    let d = edit_note_popup.getData();
    if(d.cont.trim() === '') {
        if(cb) {
            cb();
        }
        return;
    }
    $bk.addNote(id, d.cont, d.pos0, d.pos1, note_list.width, Com.putFunc(function(n){
        n = note(n);
        workTotalIncrement();
        edit_note_popup.bid = n.id;
        if(cb) {
            cb(n);
        }
    }));
}
function closeEditNote() {
    edit_note_popup.cl();
    work_list_view.forceActiveFocus();
    if(detailView.visible){
       let suc = detailView.reopen();
       if(!suc) {
           openDetail(getCurrentNote(), detail_delegate);
       }
    }
}
function deleteNote() {
    $bk.deleteNote(getCurrentNoteId(), note_list);
}
function getNoteLastTime() {
    if(note_list_model.count > 0) {
        let lastN = note_list_model.get(note_list_model.count - 1);
        return lastN.time;
    } else {
        return 0;
    }
}
function getNoteById(id) {
    for(let i = 0; i < note_list_model.count; i++) {
        let n = note_list_model.get(i);
        if(n) {
            if(n.id === id) {
                return [i, n];
            }
        }
    }
    return 0;
}
function note(e, preDateStr = '', preTimeStr='') {
    let n = {
        id: e.id,
        wid: e.wid,
        pos0: e.pos0,
        pos1: e.pos1,
        time: e.time,
        cont: e.cont,
//        html: e.html,
        qmls: e.qmls,
        tags: e.tags,
        bj: e.bj,
        date_str:'',
        time_str:'',
        visible_date: false,
        visible_time: false,
        imgs: e.imgs,
        lst_str: ''
    };
    let arr = Com.parseTime(n.time, 1);
    n.date_str = arr[0];
    n.time_str = arr[1];
    arr = Com.parseTime(e.lst, 1);
    n.lst_str = arr[0] + " " + arr[1];
    n.visible_date = preDateStr !== n.date_str;
    n.visible_time = preTimeStr !== n.time_str;
    return n;
}
///
class NoteTagDelegate extends Tag.TagDelegate {
    getCurrentItem() {
        return getCurrentNote();
    }
    updateTags(id,tags){
        $bk.updateNoteTags(id, tags, Com.putFunc(function(r){
            if($l.isDebug()){
                Com.debug("Book.js cb updateNoteTags", JSON.stringify(r));
            }
            let n = getCurrentNote();
            if(n) {
                n.tags = r.tags;
                note_list_view.currentItem.updateTags(r.tags);
                if(detailView.visible) {
                    detailView.updateTags(r.tags);
                }
                tagManager.searchTags();
            }
        }));
    }
}
function viewCont(cont, k) {
    if(!cont) {
        return "";
    }
    if(!k) {
        k = search_bar.keys[3];
    }
    if(k) {
        return Com.wrapKey(cont, k);
    } else {
        return cont;
    }
}
