import QtQuick 2.0
import "com.js" as Com

Flow {
    id: root
    spacing: 8
    property string tag_ids:""
    property var delegate:null

    onTag_idsChanged: {
        if($l.isDebug()){
            Com.trace("TagLine.qml tagIdsChanged delegate", delegate!==null, tag_ids);
        }
        update(tag_ids);
    }

    function update(ids) {
        if($l.isDebug()){
            Com.trace("TagLine.qml update", ids);
        }
        data = [];
        if(ids) {
            let tags = ids.split("#");
            for(let i = 0; i < tags.length; i++) {
                let id = tags[i].trim();
                if(id) {
                    if(delegate) {
                        if($l.isDebug()) {
                            Com.debug("delegate.createTag", id, 'simple', tags.length, JSON.stringify(tags));
                        }
                        delegate.createTag(Number(id), root, "simple", 1);
                    }
                }
            }
        }
        tag_ids = ids;
//        console.log('>>>>>>>>>', tag_ids);
    }
}
