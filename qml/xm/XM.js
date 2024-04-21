.import "qrc:/qml/com/com.js" as Com
.import "qrc:/qml/com/tag.js" as Tag

/// col
function refreshAll(key_changed) {
    if($l.isDebug()) {
        Com.debug("refreshAll", key_changed);
    }
    let k = search_bar.text.trim();
    if(key_changed && k.length === 0 && list_model_category.count > 0) {
        pre_cid = getCurrentCategoryId();
        pre_xmid = getCurrentXMId();
    }
    category_list_view.currentIndex = 0;
    list_model_category.clear();
    list_model_xm.clear();
    loadCategory();
}
function loadCategory() {
    $xm.getCategories(search_bar.text.trim(), root);
}
function submitCol(add) {
    if(add) {
        addCol();
    } else {
        let i = category_list_view.currentIndex;
        let c = list_model_category.get(i);
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

    let n = list_model_category.count;
    for(let x = 0; x < n; x++) {
        let m = list_model_category.get(x);
        if(m.name === name) {
            tipsInfo($a.tr("Exists Already"));
            return;
        }
    }
    $xm.addCategory(name, col_edit_popup);
}
function editCol(id) {
    let name = col_edit_popup.text.trim();
    if(name.length > 30) {
        tipsInfo($a.tr("too long"));
    } else {
        $xm.editCategory(id, name, col_edit_popup);
    }
}
function delCol() {
    let i = category_list_view.currentIndex;
    if(i > 0) {
        let c = list_model_category.get(i);
        if(c.total>0) {
            tipsInfo($a.tr("Can not delete, it not empty."));
        } else {
            $xm.delCategory(c.id, Com.putFunc(function(){
                let i = category_list_view.currentIndex;
                list_model_category.remove(i);
                loadXM();
            }));
        }
    } else {
        tipsInfo($a.tr("Can not delete the default folder."));
    }
}
function moveToCategory(i) {
    let currentPKIndex = xm_list_view.currentIndex;
    let pk = list_model_xm.get(currentPKIndex);
    if(pk) {
        let c = list_model_category.get(i);
        if(c.id !== pk.cid) {
            $xm.updateXMCid(i, pk.id, c.id, root);
        }
    }
}
function colTotalIncrement() {
    let i = category_list_view.currentIndex;
    let c = list_model_category.get(i);
    c.total = c.total + 1;
}
function colTotalDecrement() {
    let i = category_list_view.currentIndex;
    let c = list_model_category.get(i);
    c.total = Com.max(0, c.total - 1);
}

function addOrUpdateCol(col) {
    let n = list_model_category.count;
    let add = true;
    for(let i = 0; i < n; i++) {
        let m = list_model_category.get(i);
        if(m.id === col.id) {
            m.total = col.total;
            add = false;
        }
    }
    if(add) {
        list_model_category.append(col);
    }
}

/// pk
function loadXM(clear, cb) {
    let index = category_list_view.currentIndex;
    xm_list_view.footer = xm_list_more_btn;
    if(clear) {
        list_model_xm.clear();
    }
    let c = list_model_category.get(index);
    if(c){
        let cid = c.id;
        let k = search_bar.text.trim();
        let lsId = getPKLastId();
        $xm.getXMList(k, cid, lsId, xm_list.width, Com.putFunc(function(list){
            loadXM0(list);
            if(cb) {
                cb();
            }
        }));
    }
}
function loadXM0(list) {
    if($l.isDebug()) {
        Com.debug("pushXM list", list.length);
    }
    let ar = Com.parseTime(getPKLastTime(), 1);
    let preDateStr = ar[0];
    let preTimeStr = ar[1];
    for(let i in list) {
        let e = list[i];
        if($l.isDebug()) {
            Com.debug("xm", JSON.stringify(e));
        }
        let xm = Com.convXM(preDateStr, preTimeStr, e);
        list_model_xm.append(xm);
        preDateStr = xm.date_str;
        preTimeStr = xm.time_str;
    }
    if(list.length < $a.pageSize) {
        xm_list_view.footer = pkNoMoreBtn;
    } else {
        xm_list_view.footer = xm_list_more_btn;
    }

    //定位当前选中项
    if(pre_cid > 0) {
        let i = getColIndexByCid(pre_cid);
        if(i >= 0) {
            category_list_view.currentIndex = i;
            pre_cid = 0;
        }
    }
    if(pre_xmid > 0) {
        let arr = getPKByIdInCurrentList(pre_xmid);
        if(arr) {
            let i = arr[0];
            xm_list_view.currentIndex = i;
            pre_xmid = 0;
        }
    }
    $a.setUIVal(0, xm_list.width);
}

function deletePK(target) {
    let i = xm_list_view.currentIndex;
    if(i>=0){
        let p = list_model_xm.get(i);
        p.img_path = "";
        $xm.deleteXM(p.id, target);
    }
}
function openEditPopup(add, pk) {
    if(add) {
        let cid = getCurrentCategoryId();
        edit_pk_popup.op(cid);
    } else {
        if(!pk) {
            pk = getCurrentXM();
        }
        if(pk) {
            $xm.getXM(pk.id, xm_list.width, Com.putFunc(function(pk2) {
                edit_pk_popup.op(pk.cid, pk.id, pk2.cont);
            }));
        }
    }
}
function openOutEdit() {
    let pk = getCurrentXM();
    if(pk && !pk.jm) {
        $a.openInExternal(1, pk.id);
    }
}

function submitPK() {
//    console.log("submitPK .........");
    let txt = edit_pk_popup.text;
    let send = false;
    if(edit_pk_popup.bid <= 0) {
        if(txt!=='') {
            $xm.addXM(getCurrentCategoryId(), txt, xm_list.width, edit_pk_popup);
            send = true;
        }
    } else {
        let k = search_bar.text.trim();
        if($l.isDebug()) {
            $l.debug("updateXM "+ edit_pk_popup.bid + " " + txt + " " + k);
        }
        $xm.updateXM(edit_pk_popup.bid, txt, k, xm_list.width, Com.putFunc(function(r) {
            if(r.st === 0) {
                let arr = getPKByIdInCurrentList(edit_pk_popup.bid);
                if(arr) {
                    let pk = list_model_xm.get(arr[0]);
                    arr[1].simple_cont = r.simple_cont;
                    arr[1].cont = r.cont;
                    arr[1].simple_qmls = JSON.stringify(r.simple_qmls);
                    arr[1].qmls = r.qmls;
                    pk.imgs = r.imgs;
                }
            } else if(r.st === 1) {
                tipsInfo($a.tr("Failure.Not found the doc!"));
            } else if(r.st === 3) {
                tipsInfo($a.tr("Can not edit encrypted content."));
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
    category_list_view.forceActiveFocus();
    if(detailView.visible) {
       let suc = detailView.reopen();
       if(!suc) {
           openDetail(getCurrentXM(), xm_list);
       }
    }
}

function onKeysPressed(event) {
    event.accepted = true;
    let jump = false;
    if(event.modifiers === Qt.ShiftModifier && event.key === Qt.Key_J) {
        category_list_view.currentIndex = (category_list_view.currentIndex+1) % category_list_view.count;
    } else if(event.modifiers === ctrlVal && event.key === Qt.Key_E) {
        openEncryptPopup();
    } else if(event.modifiers === ctrlVal && event.key === Qt.Key_Home) {
        let xm = getCurrentXM();
        if(xm.sticky) {
            cancelSticky(xm.id);
        } else {
            sticky(xm.id);
        }
    } else if(event.modifiers === Qt.ShiftModifier && event.key === Qt.Key_K) {
        let i = category_list_view.currentIndex - 1;
        if(i < 0){
            i = category_list_view.count - 1;
        }
        category_list_view.currentIndex = i;
    } else if(event.key === Qt.Key_J || event.key === Qt.Key_Down) {
        xm_list.next();
        jump = true;
    } else if(event.key === Qt.Key_K || event.key === Qt.Key_Up) {
        xm_list.previous();
        jump = true;
    } else if(event.modifiers === (ctrlVal | Qt.ShiftModifier) && event.key === Qt.Key_E) {
        openColEditPopup();
    } else if(event.modifiers === ctrlVal && event.key === Qt.Key_Return) {
        openEditPopup();
    } else if(event.modifiers === (ctrlVal | Qt.AltModifier) && event.key === Qt.Key_Return) {
        openOutEdit();
    } else if(event.key === Qt.Key_Delete || event.key === Qt.Key_Backspace) {
        if(list_model_xm.count > 0){
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
        xm_list_view.currentIndex = 0;
    } else if(event.key === Qt.Key_End) {
        xm_list_view.currentIndex = xm_list_view.count - 1;
    } else if(event.key === Qt.Key_Escape) {
        if(list_model_xm.count > 0 && xm_list_view.currentItem.btn_no) {
            xm_list_view.currentItem.btn_no.click();
        }
        jump = true;
    } else {
        jump = true;
    }

    if(jump) {
        Com.jump(event, list_model_category, category_list_view);
    }
    root.key(event);
}

function detail() {
    openDetail(getCurrentXM(), xm_list);
}
function detailWin() {
    let com = Qt.createComponent("qrc:/qml/com/DetailWin.qml");
    let win = com.createObject();
    win.open(getCurrentXM(), xm_list);
    win_detail_refs[win_detail_refs.length] = win;
}
function openColEditPopup() {
    let i = category_list_view.currentIndex;
    let c = list_model_category.get(i);
    if(c) {
        col_edit_popup.text = c.name;
        col_edit_popup.open();
    }
}

function openEncryptPopup() {
    if(list_model_xm.count > 0) {
        let pk = getCurrentXM();
        if(pk) {
            let twiceCheck = !pk.jm;
            encrypt_cont_popup.delegate = {
                onSubmit:function() {
                    enOrDecrypt();
                    category_list_view.forceActiveFocus();
                },
                onCancel:function() {
                    category_list_view.forceActiveFocus();
                }
            };
            encrypt_cont_popup.op(twiceCheck);
        }
    }
}

let img_view_delegate = {
    setIndex:function(i) {
        xm_list_view.currentIndex = i;
    },
    getCurrentIndex:function() {
        return xm_list_view.currentIndex;
    },
    previous:function(){
        return xm_list.previous();
    },
    next:function(){
        return xm_list.next();
    },
    onClose:function() {
        category_list_view.forceActiveFocus();
        let pk = getCurrentXM();
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

function openImgView(img) {
    let pk = getCurrentXM();
    if(pk && !pk.jm) {
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
function copyPK(type) {
    let pk = getCurrentXM();
    if(pk) {
        $xm.copyXM(type, pk.id);
    }
}
function getPKByIdInCurrentList(id) {
    let ct = list_model_xm.count;
    for(let i = 0; i < ct; i++) {
        let pk = list_model_xm.get(i);
        if(pk.id === id) {
            return [i,pk];
        }
    }
    return null;
}
function getCurrentCategoryId() {
    let ci = category_list_view.currentIndex;
    let c = list_model_category.get(ci);
    if(c) {
        return c.id;
    }
    return 0;
}
function getCurrentCategory() {
    let i = category_list_view.currentIndex;
    return list_model_category.get(i);
}
function getCurrentXM() {
    let i = xm_list_view.currentIndex;
    let pk = list_model_xm.get(i);
    return pk;
}
function getCurrentXMId() {
    let pk = getCurrentXM();
    if(pk){
        return pk.id;
    }
    return 0;
}

function getColIndexByCid(cid) {
    let len = list_model_category.count;
    for(let i = 0; i < len; i++){
        let c = list_model_category.get(i);
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
    if(list_model_xm.count > 0) {
        let last = list_model_xm.get(list_model_xm.count - 1);
        return last.time;
    } else {
        return 0;
    }
}
function getPKLastId() {
    if(list_model_xm.count > 0) {
        let last = list_model_xm.get(list_model_xm.count - 1);
        return last.id;
    } else {
        return 0;
    }
}

function test() {
//    let col = "fuck";
//    for(let i = 0; i < 1000; i++) {
//        $a.addCol(col+i, col_edit_popup);
//    }
    // let pk = "fuck";
    // for(let i = 0; i < 10000; i++) {
    //     $xm.addXM(8, pk+i, edit_pk_popup);
    // }
}
//test();

///
class PKTagDelegate extends Tag.TagDelegate {
    getCurrentItem() {
        return getCurrentXM();
    }
    updateTags(id,tags) {
        $xm.updateXMTags(id, tags, Com.putFunc(function(r) {
            let pk = getCurrentXM();
            if(pk) {
                pk.tags = r.tags;
                pk.stime = r.stime;
                xm_list_view.currentItem.updateTags(r.tags);
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
    let pk = getCurrentXM();
    if(pk) {
        let pwd = encrypt_cont_popup.text.trim();
        if(pk.jm) {
            Com.st(0, $a.tr("decrypting..."));
            $a.decrypt(pk.id, pwd, xm_list.width, Com.putFunc(function(pk2) {
                if($l.isDebug()) {
                    $l.debug("decrypt pk " + JSON.stringify(pk2));
                }
                if(getCurrentCategoryId() === pk2.cid) {
                    let pk = getCurrentXM();
                    if(pk) {
                        pk.jm = 0;
                        pk.jm_ensure = true;
                        pk.simple_cont = pk2.simple_cont;
                        pk.cont = pk2.cont;
//                        pk.simple_html = pk2.simple_html;
//                        pk.html = pk2.html;
                        pk.simple_qmls = JSON.stringify(pk2.simple_qmls);
                        pk.img_path = Com.file_pre + $a.getCfgVal("tmp_dir") + "/" + pk2.img;
                        pk.qmls_ = JSON.stringify(pk2.qmls);
                        pk.forceMaxWidth = true;
                        if($l.isDebug()) {
                            console.log("set pk" + JSON.stringify(pk));
                        }
                    }
                }
                encrypt_cont_popup.cancel();
                Com.st(1, $a.tr("Finished"));
            }));
        } else {
            Com.st(0, $a.tr("encrypting..."));
            $a.encrypt(pk.id, pwd, xm_list.width, Com.putFunc(function(pk2) {
                if($l.isDebug()) {
                    $l.trace("encrypt pk " + JSON.stringify(pk2));
                }
                if(getCurrentCategoryId() === pk2.cid) {
                    let pk = getCurrentXM();
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
                Com.st(1, $a.tr("Finished"));
            }));
        }
        encrypt_cont_popup.clear();
    }
}
function sticky(id) {
    let xm = getCurrentXM();
    $xm.sticky(id, Com.putFunc(function(){
        xm.sticky = 1;
        alert("置顶成功");
        loadXM(true, function(){
            xm_list_view.currentIndex = 0;
        });
    }));
}
function cancelSticky(id) {
    let xm = getCurrentXM();
    $xm.cancelSticky(id, Com.putFunc(function(){
        xm.sticky = 0;
        alert("取消置顶成功");
        loadXM(true, function(){
            xm_list_view.currentIndex = 0;
        });
    }));
}
