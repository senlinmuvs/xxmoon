import QtQuick
import QtQuick.Controls
import Qt.labs.platform
import "com.js" as Com
import "ui.js" as UI

Window {
    id: root
    x: screen.width/2 - width/2
    y: screen.height/2 - height/2
    property string name
    flags: Qt.Window
    width: Com.min(800, screen.width/3*2)
    height: Com.min(900, screen.height/5*4)

    Detail {
        id: e_detail
        anchors.fill: parent
    }

    function open(pk, delegate) {
        name = 'dw_'+(window.win_detail_index++);
        if(!window.win_detail_refs) {
            window.win_detail_refs = {};
        }
        window.win_detail_refs[name] = 1;
        center();
        show();
        raise();
        requestActivate();

        let detail_delegate = {
            getTagManager: function() {
                delegate.getTagManager();
            },
            next: function() {
                delegate.next();
            },
            previous: function() {
                delegate.previous();
            },
            openFinder: function() {
                delegate.openFinder();
            },
            openEditPopup: function(b,pk) {
                delegate.openEditPopup(b,pk);
            },
            onClose: function() {
                delegate.onClose();
            },
            getData: function(id,w,cb) {
                delegate.getData(id,w,cb);
            },
            importFile: function() {
                delegate.importFile();
            },
            isSeparateWindow: function() {
                return true;
            },
            close:function() {
                delete window.win_detail_refs[root.name];
                root.close();
            }
        };
        window.openDetail(pk, detail_delegate, e_detail);
    }
    function center() {
        x = screen.width/2 - width/2;
        y = screen.height/2 - height/2 - 30;
    }
}
