.import "qrc:/qml/com/com.js" as Com
.import "qrc:/qml/com/tag.js" as Tag

/// col
function refreshAll(key_changed) {
    if($l.isDebug()) {
        Com.debug("refreshAll", key_changed);
    }
    let k = search_bar.text.trim();
    if(key_changed && k.length === 0 && col_list_model.count > 0) {
        pre_cid = getCurrentColId();
        pre_pkid = getCurrentPkId();
    }
    col_list_view.currentIndex = 0;
    col_list_model.clear();
    pk_list_model.clear();
    loadCategory();
}
function loadCategory() {
    $cg.getCategories(search_bar.text.trim(), root);
}
function submitCol(add) {
    if(add) {
        addCol();
    } else {
        let i = col_list_view.currentIndex;
        let c = col_list_model.get(i);
        if(c) {
            editCol(c.id);
        }
    }
}
function addCol() {
    let name = col_edit_popup.text.trim();
    if(name === '') {
        return;
    }

    let n = col_list_model.count;
    for(let x = 0; x < n; x++) {
        let m = col_list_model.get(x);
        if(m.name === name) {
            tipsInfo(qsTr("Exists Already"));
            return;
        }
    }
    $cg.addCategory(name, col_edit_popup);
}
function editCol(id) {
    let name = col_edit_popup.text.trim();
    if(name.length > 30) {
        tipsInfo(qsTr("too long"));
    } else {
        $cg.editCategory(id, name, col_edit_popup);
    }
}
function delCol() {
    let i = col_list_view.currentIndex;
    if(i > 0) {
        let c = col_list_model.get(i);
        if(c.total>0) {
            tipsInfo(qsTr("Can not delete, it not empty."));
        } else {
            $cg.delCategory(c.id, Com.putFunc(function(){
                let i = col_list_view.currentIndex;
                col_list_model.remove(i);
                loadXM();
            }));
        }
    } else {
        tipsInfo(qsTr("Can not delete the default folder."));
    }
}
function moveToCategory(i) {
    let currentPKIndex = pk_list_view.currentIndex;
    let pk = pk_list_model.get(currentPKIndex);
    if(pk) {
        let c = col_list_model.get(i);
        if(c.id !== pk.cid) {
            $cg.updateXMCid(i, pk.id, c.id, root);
        }
    }
}
function colTotalIncrement() {
    let i = col_list_view.currentIndex;
    let c = col_list_model.get(i);
    c.total = c.total + 1;
}
function colTotalDecrement() {
    let i = col_list_view.currentIndex;
    let c = col_list_model.get(i);
    c.total = Com.max(0, c.total - 1);
}

function addOrUpdateCol(col) {
    let n = col_list_model.count;
    let add = true;
    for(let i = 0; i < n; i++) {
        let m = col_list_model.get(i);
        if(m.id === col.id) {
            m.total = col.total;
            add = false;
        }
    }
    if(add) {
        col_list_model.append(col);
    }
}

/// pk
function loadXM(clear, cb) {
    let index = col_list_view.currentIndex;
    pk_list_view.footer = pk_list_more_btn;
    if(clear) {
        pk_list_model.clear();
    }
    let c = col_list_model.get(index);
    if(c){
        let cid = c.id;
        let k = search_bar.text.trim();
        let lsId = getPKLastId();
        $cg.getXMList(k, cid, lsId, pk_list.width, Com.putFunc(function(list){
            loadPk0(list);
            if(cb) {
                cb();
            }
        }));
    }
}
function loadPk0(list) {
    if($l.isDebug()) {
        Com.debug("pushPK list", list.length);
    }
    let ar = Com.parseTime(getPKLastTime(), 1);
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
        let i = getColIndexByCid(pre_cid);
        if(i >= 0) {
            col_list_view.currentIndex = i;
            pre_cid = 0;
        }
    }
    if(pre_pkid > 0) {
        let arr = getPKByIdInCurrentList(pre_pkid);
        if(arr) {
            let i = arr[0];
            pk_list_view.currentIndex = i;
            pre_pkid = 0;
        }
    }
    $app.setUIVal(0, pk_list.width);
}

function deletePK(target) {
    let i = pk_list_view.currentIndex;
    if(i>=0){
        let p = pk_list_model.get(i);
        p.img_path = "";
        $cg.deleteXM(p.id, target);
    }
}
function openEditPopup(add, pk) {
    if(add) {
        let cid = getCurrentColId();
        edit_pk_popup.op(cid);
    } else {
        if(!pk) {
            pk = getCurrentPK();
        }
        if(pk) {
            $cg.getXM(pk.id, pk_list.width, Com.putFunc(function(pk2) {
                edit_pk_popup.op(pk.cid, pk.id, pk2.cont);
            }));
        }
    }
}
function openOutEdit() {
    let pk = getCurrentPK();
    if(pk && !pk.jm) {
        $app.openInExternal(1, pk.id);
    }
}

function submitPK() {
//    console.log("submitPK .........");
    let txt = edit_pk_popup.text;
    let send = false;
    if(edit_pk_popup.bid <= 0) {
        if(txt!=='') {
            $cg.addXM(getCurrentColId(), txt, pk_list.width, edit_pk_popup);
            send = true;
        }
    } else {
        let k = search_bar.text.trim();
        if($l.isDebug()) {
            $l.debug("updatePK "+ edit_pk_popup.bid + " " + txt + " " + k);
        }
        $cg.updateXM(edit_pk_popup.bid, txt, k, pk_list.width, Com.putFunc(function(r) {
            if(r.st === 0) {
                let arr = getPKByIdInCurrentList(edit_pk_popup.bid);
                if(arr) {
                    let pk = pk_list_model.get(arr[0]);
                    arr[1].simple_cont = r.simple_cont;
                    arr[1].cont = r.cont;
                    arr[1].simple_qmls = JSON.stringify(r.simple_qmls);
                    arr[1].qmls = r.qmls;
                    pk.imgs = r.imgs;
                }
            } else if(r.st === 1) {
                tipsInfo(qsTr("Failure.Not found the doc!"));
            } else if(r.st === 3) {
                tipsInfo(qsTr("Can not edit encrypted content."));
            }
            if(edit_pk_popup.pending_close) {
                closeEditPK();
            }
        }));
        send = true;
    }
    if(!send && edit_pk_popup.pending_close) {
        closeEditPK();
    }
}
function cancelEditPK() {
    edit_pk_popup.pending_close = true;
    submitPK();
}
function closeEditPK() {
    edit_pk_popup.cl();
    col_list_view.forceActiveFocus();
    if(detailView.visible) {
       let suc = detailView.reopen();
       if(!suc) {
           openDetail(getCurrentPK(), pk_list);
       }
    }
}

function onKeysPressed(event) {
    event.accepted = true;
    let jump = false;
    if(event.modifiers === Qt.ShiftModifier && event.key === Qt.Key_J) {
        col_list_view.currentIndex = (col_list_view.currentIndex+1) % col_list_view.count;
    } else if(event.modifiers === ctrlVal && event.key === Qt.Key_E) {
        openEncryptPopup();
    } else if(event.modifiers === Qt.ShiftModifier && event.key === Qt.Key_K) {
        let i = col_list_view.currentIndex - 1;
        if(i < 0){
            i = col_list_view.count - 1;
        }
        col_list_view.currentIndex = i;
    } else if(event.key === Qt.Key_J || event.key === Qt.Key_Down) {
        pk_list.next();
        jump = true;
    } else if(event.key === Qt.Key_K || event.key === Qt.Key_Up) {
        pk_list.previous();
        jump = true;
    } else if(event.modifiers === (ctrlVal | Qt.ShiftModifier) && event.key === Qt.Key_E) {
        openColEditPopup();
    } else if(event.modifiers === ctrlVal && event.key === Qt.Key_Return) {
        openEditPopup();
    } else if(event.modifiers === (ctrlVal | Qt.AltModifier) && event.key === Qt.Key_Return) {
        openOutEdit();
    } else if(event.key === Qt.Key_Delete || event.key === Qt.Key_Backspace) {
        if(pk_list_model.count > 0){
            ensure_popup.open();
        }
    } else if(event.modifiers === ctrlVal && event.key === Qt.Key_F) {
        search_bar.forceActiveFocus();
    } else if(event.key === Qt.Key_Return) {
        openImgView();
    } else if(event.modifiers === Qt.ShiftModifier && event.key === Qt.Key_Space) {
        detailWin();
    } else if(event.key === Qt.Key_Space) {
        detail();
    } else if(event.modifiers === ctrlVal && event.key === Qt.Key_N) {
        navBtnClick('add');
    } else if(event.modifiers === (ctrlVal | Qt.ShiftModifier) && event.key === Qt.Key_N) {
        onBtnClick_addCol();
    } else if(event.modifiers === (Qt.AltModifier|Qt.ShiftModifier) && event.key === Qt.Key_C) {
        copyPK(0);
    } else if(event.modifiers === (ctrlVal|Qt.AltModifier) && event.key === Qt.Key_C) {
        copyPK(1);
    } else if(event.modifiers === (ctrlVal|Qt.ShiftModifier) && event.key === Qt.Key_C) {
        copyPK(2);
    } else if(event.modifiers === ctrlVal && event.key === Qt.Key_T) {
        navBtnClick('tag');
    } else if(event.key === Qt.Key_Home) {
        pk_list_view.currentIndex = 0;
    } else if(event.key === Qt.Key_End) {
        pk_list_view.currentIndex = pk_list_view.count - 1;
    } else if(event.key === Qt.Key_Escape) {
        if(pk_list_model.count > 0 && pk_list_view.currentItem.btn_no) {
            pk_list_view.currentItem.btn_no.click();
        }
        jump = true;
    } else {
        jump = true;
    }

    if(jump) {
        Com.jump(event, col_list_model, col_list_view);
    }
    root.key(event);
}

function detail() {
    openDetail(getCurrentPK(), pk_list);
}
function detailWin() {
    let com = Qt.createComponent("qrc:/qml/com/DetailWin.qml");
    let win = com.createObject();
    win.open(getCurrentPK(), pk_list);
    win_detail_refs[win_detail_refs.length] = win;
}
function openColEditPopup() {
    let i = col_list_view.currentIndex;
    let c = col_list_model.get(i);
    if(c) {
        col_edit_popup.text = c.name;
        col_edit_popup.open();
    }
}

function openEncryptPopup() {
    if(pk_list_model.count > 0) {
        let pk = getCurrentPK();
        if(pk) {
            let twiceCheck = !pk.jm;
            encrypt_cont_popup.delegate = {
                onSubmit:function() {
                    enOrDecrypt();
                    col_list_view.forceActiveFocus();
                },
                onCancel:function() {
                    col_list_view.forceActiveFocus();
                }
            };
            encrypt_cont_popup.op(twiceCheck);
        }
    }
}

let img_view_delegate = {
    setIndex:function(i) {
        pk_list_view.currentIndex = i;
    },
    getCurrentIndex:function() {
        return pk_list_view.currentIndex;
    },
    previous:function(){
        return pk_list.previous();
    },
    next:function(){
        return pk_list.next();
    },
    onClose:function() {
        col_list_view.forceActiveFocus();
        let pk = getCurrentPK();
        if(pk) {
            let tmp = pk.img_path;
            pk.img_path = "";
            pk.img_path = tmp;
            let tmp_qmls = pk.simple_qmls;
            pk.simple_qmls = "";
            pk.simple_qmls = tmp_qmls;
        }
    }
}

function openImgView() {
    let pk = getCurrentPK();
    if(pk && !pk.jm) {
        imgViewer.delegate = img_view_delegate;
        let n = imgViewer.append(pk);
        if(n>0) {
            imgViewer.open();
        }
    }
}
function copyPK(type) {
    let pk = getCurrentPK();
    if(pk) {
        $cg.copyXM(type, pk.id);
    }
}
function getPKByIdInCurrentList(id) {
    let ct = pk_list_model.count;
    for(let i = 0; i < ct; i++) {
        let pk = pk_list_model.get(i);
        if(pk.id === id) {
            return [i,pk];
        }
    }
    return null;
}
function getCurrentColId() {
    let ci = col_list_view.currentIndex;
    let c = col_list_model.get(ci);
    if(c) {
        return c.id;
    }
    return 0;
}
function getCurrentCol() {
    let i = col_list_view.currentIndex;
    return col_list_model.get(i);
}
function getCurrentPK() {
    let i = pk_list_view.currentIndex;
    let pk = pk_list_model.get(i);
    return pk;
}
function getCurrentPkId() {
    let pk = getCurrentPK();
    if(pk){
        return pk.id;
    }
    return 0;
}

function getColIndexByCid(cid) {
    let len = col_list_model.count;
    for(let i = 0; i < len; i++){
        let c = col_list_model.get(i);
        if(c && c.id === cid) {
            return i;
        }
    }
    return -1;
}

function onBtnClick_addCol() {
    if(!col_edit_popup.visible) {
        col_edit_popup.text = '';
        col_edit_popup.add = true;
        col_edit_popup.open();
    }
}

function getPKLastTime() {
    if(pk_list_model.count > 0) {
        let last = pk_list_model.get(pk_list_model.count - 1);
        return last.time;
    } else {
        return 0;
    }
}
function getPKLastId() {
    if(pk_list_model.count > 0) {
        let last = pk_list_model.get(pk_list_model.count - 1);
        return last.id;
    } else {
        return 0;
    }
}

function test() {
//    let col = "fuck";
//    for(let i = 0; i < 1000; i++) {
//        $app.addCol(col+i, col_edit_popup);
//    }
    let pk = "fuck";
    for(let i = 0; i < 10000; i++) {
        $cg.addXM(8, pk+i, edit_pk_popup);
    }
}
//test();

///
class PKTagDelegate extends Tag.TagDelegate {
    getCurrentItem() {
        return getCurrentPK();
    }
    updateTags(id,tags) {
        $cg.updateXMTags(id, tags, Com.putFunc(function(r) {
            let pk = getCurrentPK();
            if(pk) {
                pk.tags = r.tags;
                pk.stime = r.stime;
                pk_list_view.currentItem.updateTags(r.tags);
                if(detailView.visible) {
                    detailView.updateTags(r.tags, r.stime);
                }
                if($l.isDebug()) {
                    Com.debug("updateTags id", id, "tags", r.tags);
                }
            }
        }));
    }
}

function enOrDecrypt() {
    let pk = getCurrentPK();
    if(pk) {
        let pwd = encrypt_cont_popup.text.trim();
        if(pk.jm) {
            Com.st(0, qsTr("decrypting..."));
            $app.decrypt(pk.id, pwd, pk_list.width, Com.putFunc(function(pk2) {
                if($l.isDebug()) {
                    $l.debug("decrypt pk " + JSON.stringify(pk2));
                }
                if(getCurrentColId() === pk2.cid) {
                    let pk = getCurrentPK();
                    if(pk) {
                        pk.jm = 0;
                        pk.jm_ensure = true;
                        pk.simple_cont = pk2.simple_cont;
                        pk.cont = pk2.cont;
//                        pk.simple_html = pk2.simple_html;
//                        pk.html = pk2.html;
                        pk.simple_qmls = JSON.stringify(pk2.simple_qmls);
                        pk.img_path = Com.file_pre + $app.getCfgVal("tmp_dir") + "/" + pk2.img;
                        pk.qmls_ = JSON.stringify(pk2.qmls);
                        pk.forceMaxWidth = true;
                        if($l.isDebug()) {
                            console.log("set pk" + JSON.stringify(pk));
                        }
                    }
                }
                encrypt_cont_popup.cancel();
                Com.st(1, qsTr("Finished"));
            }));
        } else {
            Com.st(0, qsTr("encrypting..."));
            $app.encrypt(pk.id, pwd, pk_list.width, Com.putFunc(function(pk2) {
                if($l.isDebug()) {
                    $l.trace("encrypt pk " + JSON.stringify(pk2));
                }
                if(getCurrentColId() === pk2.cid) {
                    let pk = getCurrentPK();
                    if(pk) {
                        pk.jm = 1;
                        pk.jm_ensure = true;
                        pk.cont = pk2.cont;
                        pk.simple_qmls = JSON.stringify(pk2.simple_qmls);
                        if($l.isDebug()){
                            $l.trace("set pk " + JSON.stringify(pk));
                        }
                    }
                }
                encrypt_cont_popup.cancel();
                Com.st(1, qsTr("Finished"));
            }));
        }
        encrypt_cont_popup.clear();
    }
}
