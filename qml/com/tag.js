.import "com.js" as Com

class TagManager {
    constructor(tagCom, type, search_bar, tag_view, focus_view, tagDelegate) {
        this.tagCom = tagCom;
        this.type = type;
        this.search_bar = search_bar;
        this.tag_view = tag_view;
        this.focus_view = focus_view;
        this.tag_list = [];
        this.tagDelegate = tagDelegate;
    }
    parseKey(s) {
        let k = '';
        let tags = [];
        s = s.trim();
        if(s.startsWith("#")){
          let arr = s.split("#");
          for(let i = 0; i < arr.length; i++) {
            let it = arr[i].trim();
            if(i===arr.length-1) {
              let lastArr = it.split(' ');
              tags[tags.length] = lastArr[0];
              if(lastArr.length>1){
                k = lastArr[1];
              }
            } else {
              if(it) {
                tags[tags.length] = it;
              }
            }
          }
        }
        if(tags.length===0){
          k = s;
        }
        return [k, tags];
    }
    getTagsFromSerachKey() {
        let s = this.search_bar.text.trim();
        let arr = this.parseKey(s);
        return arr[1];
    }
    addTagFromSearchKey(tag) {
        let s = this.search_bar.text.trim();
        let k = "#"+tag;
        let i = s.indexOf(k);
        if(i<0) {
            if(s.length > 0){
                this.search_bar.text = k +" " + s;
            } else {
                this.search_bar.text = s + k +" ";
            }
        }
    }
    delTagFromSearchKey(tag) {
        let s = this.search_bar.text.trim();
        let k = "#"+tag;
        let i = s.indexOf(k);
        if(i>=0){
            this.search_bar.text = s.del(i, k.length);
        }
    }
    //
    initData() {
        this.searchTags();
    }
    openTagView() {
        this.tag_view.op();
    //    searchTags();
    }
    searchTags(k="") {
        $app.tagList(k, this.type, this.tag_view);
        if($l.isDebug()) {
            Com.debug("tag.js searchTags", "k", k, "type", this.type, "tag_view", this.tag_view!==null);
        }
    }
    loadTagList(all, list) {
        for(let i = 0; i < list.length; i++) {
            for(let j = 0; j < list.length-i-1; j++) {
                if(list[j].n < list[j+1].n) {
                    let tmp = list[j];
                    list[j] = list[j+1];
                    list[j+1] = tmp;
                } else if (list[j].n === list[j+1].n) {
                    if(list[j].tag > list[j+1].tag) {
                        let tmp = list[j];
                        list[j] = list[j+1];
                        list[j+1] = tmp;
                    }
                }
            }
        }
        this.tag_list = list;
        this.refreshTagView();
    //    Com.log('tags', JSON.stringify(tags), tag_view.flows.data.length);
    }
    refreshTagView() {
        this.tag_view.clearFlows();
        let selectedTags = this.getTagsFromSerachKey();
//        Com.log('init tag view', JSON.stringify(selectedTags));
//        Com.log(JSON.stringify(this.tag_list));
        for(let i = 0; i < this.tag_list.length; i++) {
            let t = this.tag_list[i];
            let ta = this.tagCom.createObject(this.tag_view.flows);
            this.tagDelegate.tagManager = this;
            ta.delegate = this.tagDelegate;
            ta.setData(t);
            if(Com.contains(selectedTags, t.tag)) {
                ta.selected();
            }
//            Com.log(i, this.tag_list.length, ta, JSON.stringify(t));
        }
        this.tag_view.flows.forceLayout();
    }
    createTag(id, parent, state, flag) {
        let t = this;
        $app.getTagById(id, Com.putFunc(function(r) {
            if(r) {
                t.createTag0(r, parent, state, flag);
            } else {
                Com.error('create tag not found', id, state, flag);
            }
        }));
    }
    createTag0(tagData, parent, state, flag) {
        let tag = this.tagCom.createObject(parent);
        tag.state = state;
        tag.delegate = this.tagDelegate;
        tag.flag = flag;
        tag.setData(tagData);
        if($l.isDebug()) {
            Com.debug("createTag", "tagData", JSON.stringify(tagData), "state", state, "flag", flag);
        }
    }
    delTagInView(tid, ref) {
        if(ref === 0){
            let t = this.getTagByIdFromCurrentTagList(tid);
            if(t) {
                this.tag_list.remove(t[0]);
                this.refreshTagView();
                this.delTagFromSearchKey(t[1].tag);
            }
        } else {
            this.refreshTagView();
        }
    }
    getTagByIdFromCurrentTagList(id) {
//        Com.log('getTagById', id, JSON.stringify(this.tag_list));
        for(let i = 0; i < this.tag_list.length; i++) {
            if(Number(this.tag_list[i].id) === Number(id)) {
                return [i, this.tag_list[i]];
            }
        }
        return 0;
    }
    findTag(tag) {
        for(let i = 0; i < this.tag_list.length; i++) {
            if(this.tag_list[i].tag === tag) {
                return [i, this.tag_list[i]];
            }
        }
        return 0;
    }
    addTag(tag) {
        tag = tag.trim();
        if(tag==="") {
            return;
        }
        let t = this.findTag(tag);
        if(t) {
            let tagItem = this.tag_view.flows.data[t[0]];
            tagItem.click();
        } else {
            $app.addTag(tag, this.tag_view);
        }
    }
    selectTag(tag) {
        tag = tag.trim();
        if(tag==="") {
            return;
        }
        let t = this.findTag(tag);
        if(t) {
            let tagItem = this.tag_view.flows.data[t[0]];
            tagItem.click();
        } else {
            if(this.tag_view.flows.data.length > 0) {
                let first = this.tag_view.flows.data[0];
                first.click();
            }
        }
    }
    setTagForItem(tag) {
        if(this.tag_list.length > 0) {
            let curFirstTag = this.tag_list[0];
            if(curFirstTag.tag.toLowerCase().indexOf(tag.toLowerCase()) >= 0) {
                let tagItem = this.tag_view.flows.data[0];
                tagItem.rightClick();
            }
        }
    }
    onTagViewClosed() {
        this.focus_view.forceActiveFocus();
    }
}
class TagDelegate {
    constructor() {
        this.tagManager = 0;
    }
    click(tag, st) {
        if(st) {
            this.tagManager.addTagFromSearchKey(tag.tag);
        } else {
            this.tagManager.delTagFromSearchKey(tag.tag);
        }
    }
    getCurrentItem() {
        return 0;
    }
    updateTags(id,tags){
        if($l.isDebug()) {
            Com.debug("warn: updateTags default impl");
        }
    }
    rightClick(tag) {
        let addTagId = tag.id;
        let it = this.getCurrentItem();
        if(it) {
            let dstTags = it.tags;
            if(it.tags) {
                let k = "#" + addTagId+"#";
                let i = it.tags.indexOf(k);
                if(i<0){
                    dstTags = it.tags + addTagId+'#';
                }
            } else {
                dstTags = "#"+addTagId+'#';
            }
            if(it.tags !== dstTags) {
                let newTagIds = dstTags.toArr('#');
//                Com.log(JSON.stringify(newTagIds));
                if(newTagIds.length <= Com.MAX_TAG) {
//                    $app.updatePKTags(it.id, dstTags, pk_list);
                    this.updateTags(it.id,dstTags);
                } else {
                    tipsInfo(qsTr("Cant more than") + Com.MAX_TAG + qsTr("tags"));
                }
            }
        }
    }
    onMoved(flag, mouse, btn, tag) {
        if(flag === 0) {
            if(btn.x < -btn.width/2 || btn.x > this.tagManager.tag_view.width - btn.width/2) {
                $app.delTag(tag.id, this.tagManager.tag_view);
            }
        } else {
            if(Com.abs(btn.x) >= btn.width*2) {
                let delTagId = tag.id;
                let it = this.getCurrentItem();
                if(it) {
                    let k = '#'+delTagId;
                    let i = it.tags.indexOf(k);
                    let dstTags = it.tags.del(i, k.length);
                    if(dstTags==='#') {
                        dstTags = '';
                    }
//                    Com.log('del tag', it.id, dstTags);
                    this.updateTags(it.id,dstTags);
                }
            }
        }
    }
}
