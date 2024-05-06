import QtQuick
import QtQuick.Controls
import Qt.labs.platform
import "com"
import "com/com.js" as Com
import "com/ui.js" as UI

ApplicationWindow {
    id: window
    visible: true
    color: "transparent"
//    flags: $a.getPlatform() === Com.platform_win ? Qt.FramelessWindowHint|Qt.WindowSystemMenuHint|Qt.WindowMinimizeButtonHint|Qt.Window : 0
    width: Com.min(800, screen.width/3*2)
    height: Com.min(900, screen.height/5*4)
    minimumWidth: Com.min(width, 100)
    minimumHeight: Com.min(height, 100)
    x: screen.width/2 - width/2
    y: screen.height/2 - height/2
    property bool winIsMax: false
    property var w_notify: null

    property int st: 0
    property int st_height: UI.main_st_height
    property var mini_win
    property int cbid: 0
    // property var cbs: {0:null} // all call back
    property var cbs
    property bool inited: false
    property string xmfile: ''
    property bool widthChanged
    property bool heightChanged

    property int ctrlVal:Qt.ControlModifier;
    property string ctrlName:$a.getPlatform() === Com.platform_mac ? "Cmd" : "Ctrl";

    property var win_detail_refs//{detail_win_name:1}保持详情分离窗口引用避免加载数据多了窗口消失
    property int win_detail_index: 0//详情分离窗口的索引计数,即窗口名后缀

    Menu {
        id: trayMenu
        MenuItem {
          text: $a.tr("Quit")
          onTriggered: {
              Com.info("Tray Menu close");
              tray.hide();
              Qt.quit();
          }
        }
    }
    SystemTrayIcon {
        id: tray
        visible: true
        icon.source: "qrc:/assets/tray32.png"
        tooltip: $a.tr("xxmoon")
        menu: $a.getPlatform() === Com.platform_mac ? null : trayMenu
        onActivated: function(reason) {
            if($a.getPlatform() === Com.platform_mac) {
                if(reason === SystemTrayIcon.Trigger) {
                    $a.xm();
                } else if(reason === SystemTrayIcon.DoubleClick) {
                    open();
                }
            } else {
                open();
            }
        }
        function open() {
            if(window.width === screen.width) {
                window.showMaximized();
            } else {
                window.show();
            }
            window.raise();
            window.requestActivate();
        }
    }
    onWindowStateChanged: function(windowState) {
       if(windowState === 2) {
           $a.setLocal("maxWindow",1);
           winIsMax = true;
       } else {
           $a.setLocal("maxWindow",0);
           winIsMax = false;
       }
    }
    onWidthChanged: {
        if(window.width === screen.width) {
            return;
        }
            if(widthChanged) {
                saveWindowSize();
        }
        widthChanged = true;
    }
    onHeightChanged: {
        if(window.width === screen.width) {
            return;
        }
            if(heightChanged) {
                saveWindowSize();
        }
        heightChanged = true;
    }
    Detail {
        id: detailView
        z: 10
    }
    ImgViewer {
        id: imgViewer
    }
    MyFieldPopup {
        id: encrypt_cont_popup
        pwd: true
        z: 11
        placeholder: $a.tr("Password")
    }
//    Server {
//        id: serv
//    }
    Rectangle {
        id: rect
        anchors.fill: parent
//        layer.enabled: true
        Rectangle {
            id: e_top_sep
            color: UI.ui_separate_color
            width: parent.width
            height: $a.getPlatform() === Com.platform_win ? 1 : 0
        }
        Navigation {
            id: navigation
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.topMargin: e_top_sep.height
            width: 70
            height: parent.height-e_top_sep.height
        }
        Loader {
            id: pageLoader
            z:1
            width: parent.width - navigation.width
            height: parent.height-e_top_sep.height
            anchors.left: navigation.right
            anchors.top: parent.top
            anchors.topMargin: e_top_sep.height
            source: "qrc:/qml/xm/XM.qml"
            focus: true
            onLoaded: {
                if(pageLoader.item.init) {
                    pageLoader.item.init($a.getUIData());
                }
            }
            Keys.onPressed: function(event) {
                navigation.onKeysPressed(event);
            }
        }
    }
    About {
        id: about
    }
    Connections {
        target: pageLoader.item
        function onSt(type, tip) {
            Com.st(type, tip);
        }
        function onTipsInfo(txt) {
            tips_info.popup(txt);
        }
        function onKey(e) {
            navigation.onKeysPressed(e);
        }
    }
    Timer {
        id: global_timer
        property int round_st: 3
        property int round_check_import: 6

        repeat: true
        interval: 1000
        triggeredOnStart: true
        onTriggered: {
            if(window.st) {
                if(round_st-- <= 0) {
                    Com.st(0, "");
                    round_st = 3;
                }
            }
            if(round_check_import-- <= 0) {
                $a.checkImport();
                round_check_import = 6;
            }
        }
    }
    Timer {
        id: global_timer2
        repeat: true
        interval: 1000
        triggeredOnStart: true
        onTriggered: {
            $a.checkTmpFile();
        }
    }
    Tips {
        id: tips_new_v
        onActiveFocusChanged: {
            pageLoader.forceActiveFocus();
        }
    }
    TipsInfo {
        id: tips_info
    }
    EnsurePopup {
        id: e_ensure
    }
    DropArea {
        anchors.fill: parent
        onDropped: {
            let files = [];
            if(Com.isDir(drop.text)) {
                files = $a.getFilesInDir(drop.text);
            } else {
                files = [drop.text];
            }
            doFile(0, files);
        }
    }
    FileDialog {
        id: fileDialog
        fileMode: FileDialog.OpenFiles
        acceptLabel: $a.tr('Import')
        title: ""
        nameFilters: ["Kindle TXT(*.txt)", "xxmoon(*.xm)", "Image(*.png *.jpg *.jpeg *.bmp *.gif *.webp)"]
//        folder: shortcuts.home
        onAccepted: {
//            Com.log(fileDialog.currentFiles);
            doFile(1, fileDialog.currentFiles);
        }
    }
    FolderDialog {
        id: folderDialog
        property var onFinished
        onAccepted: {
            if(onFinished){
                onFinished();
            }
        }
    }
    FileDialog {
        id: normalFileDialog
        property var onFinished
        onAccepted: {
            if(onFinished){
                onFinished();
            }
        }
    }
    Component {
        id: com_notify
        Notify{}
    }

    property int import_total: 0
    property int import_n: 0
    function startXM() {
        if(import_total === 0) {
            import_total = 1;
            return true;
        } else {
            return false;
        }
    }
    function onFinished(type, i, total, param) {
//        console.log("onFinished >>>>>>>>>>>>>>", type, i, total, param);
        import_n += 1;

        if(i!==-1 && total!==-1) {
            import_n = i;
            import_total = total;
        }

        if(import_n === import_total) {
            Com.st(1, $a.tr("Imported") + (import_n+"/"+import_total));
//            Com.log('imported', (import_n+"/"+import_total));
            if(type === Com.type_book) {
                if(pageLoader.item.loadWork){
                    pageLoader.item.loadWork(param);
                }
            } else if(type === Com.type_pk) {
                if(pageLoader.item.hasNewPK){
                    pageLoader.item.hasNewPK(param);
                }
            }
            import_n = 0;
            import_total = 0;
        } else {
//            Com.log('Import', (import_n+"/"+import_total));
            Com.st(0, $a.tr("Import") + (import_n+"/"+import_total));
        }
    }
    function doFile(t, files) {
        if(files && files.length === 1) {
            files = files[0].split("\n");
        }
        files = Com.removeEmpty(files);
        if(files.length === 0){
            return;
        }

        let type = Com.getFileType(files[0]);
        if(type === Com.file_type_xm && t === 0) {
            //only open
        } else {
            import_total = files.length;
        }
        for(let i = 0; i < files.length; i++) {
            let file = files[i].trim();
            if(file) {
                if($l.isDebug()) {
                    Com.debug("doFile t", t, i, "type", type, "file", file, "progress", import_n+"/"+import_total);
                }
                if(type > 0) {
                    if(type === Com.file_type_img) {
                        Com.st(0, $a.tr("Import") + (import_n+"/"+import_total));
                        $xm.xm(file);
                    } else if(type === Com.file_type_txt) {
                        Com.st(0, $a.tr("Import"));
                        $a.import(file, window);
                    } else if(type === Com.file_type_xm) {
                        if(type === Com.file_type_xm && t === 0) {
                            //only open
                        } else {
                            Com.st(0, $a.tr("Import") + (import_n+"/"+import_total));
                        }
                        $a.openXMFile(file, "", Com.putFunc(function(pk) {
                            if(t === 0) {
                                openXM(pk);
                            } else if(t === 1) {
                                importXM(pk);
                            }
                        }));
                    }
                }
            }
        }
    }

    function init(data) {
        let wh = data[$a.ENV_K_LAST_WH];
        if(wh && wh.length > 1) {
            window.width = wh[0];
            window.height = wh[1];
        }
        if(!inited){
            x = screen.width/2 - window.width/2;
            y = screen.height/2 - window.height/2;
            inited = true;
        }

        if(data["maxWindow"]) {
            winIsMax = true;
            window.showMaximized();
        } else {
            winIsMax = false;
        }
    }
    Component.onCompleted: {
        global_timer.start();
        global_timer2.start();
        init($a.getUIData());
//        while(true) {
//            if($a.existsAllowedURL()) {
//                $a.init();
//                break;
//            } else {
//                $a.alertMacTip($a.tr("First, please select a data storage directory!"),
//                           $a.tr("A xxmoon directory will be created in the directory you selected to store the data of this app."));
//                $a.selectDataDir();
//            }
//        }

        ////////////////////////////////
        let ctrl = $a.getCtrl();
        if(ctrl.toLowerCase() === "ctrl" || ctrl.toLowerCase() === "cmd") {
            ctrlVal = Qt.ControlModifier;
        } else if(ctrl.toLowerCase() === "meta") {
            ctrlVal = Qt.MetaModifier;
            //qt中的meta对应mac的ctrl
            ctrlName = $a.getPlatform() === Com.platform_mac ? "Ctrl" : "Meta";
        }
        ////////////////////////////////
    }
    function onGenFile(file) {
        if(file) {
            Com.st(1, $a.tr('generated success.'));
            if(file === "") {
                file = $a.fileDir;
            }
            if($a.getPlatform() === Com.platform_win && /.+[.](pdf|html|xm)/.test(file)) {
                file = file.substring(0, file.lastIndexOf("/"));
            }
            $a.openDir(file);
        } else {
            Com.st(1, $a.tr('generated failure.'));
        }
    }
    function onUpdatedXM(xm) {
        if($l.isDebug()) {
            Com.trace("onUpdatedXM", JSON.stringify(xm));
        }
        if(pageLoader.item.onUpdateXM) {
            pageLoader.item.onUpdateXM(xm);
        }
    }
    function onUpdatedNote(n) {
        if($l.isDebug()) {
            Com.trace("onUpdatedNote", JSON.stringify(n));
        }
        if(pageLoader.item.onUpdateNote) {
            pageLoader.item.onUpdateNote(n);
        }
    }
    function onCallback(k, param) {
        let t1 = new Date().getTime();
        let func = cbs[k];
        if(func) {
            func(param);
            delete cbs[k];
        }
        let t2 = new Date().getTime();
        if($l.isDebug()) {
            let len = Object.keys(cbs).length;
            if($l.isDebug()) {
                Com.trace("open detail cost", t2 - t1, "mills.", "callback queue len", len);
            }
        }
    }
    function onPush(ty, data) {
        if(ty === 0) {
            if(serv.visible) {
                serv.onPush(ty, data);
            }
        } else if(ty === 1) {
            fileDialog.open();
        } else if(ty === 2) {
            about.op();
        }
        if(pageLoader.item.onPush) {
            pageLoader.item.onPush(ty, data);
        }
    }
    function onCall(ty, data) {
        console.log("onCall", ty, data);
        if(ty === 0) {
            return ""+pageLoader.item.getListWidth();
        }
        return "";
    }
    function saveWindowSize() {
        let whxy = window.width+","+window.height+","+window.x+","+window.y;
        if($l.isDebug()) {
            Com.debug("saveWindowSize", whxy, screen.width, screen.height);
        }
        $a.setLocal($a.ENV_K_LAST_WH, whxy);
    }
    function openDetail(pk, delegate, win=detailView) {
        if($l.isDebug()) {
            Com.debug("openDetail xm", JSON.stringify(pk), "delegate", (delegate!==null));
        }
        if(pk) {
            if(delegate) {
                win.delegate = delegate;
                win.tagLine.delegate = delegate.getTagManager();
            }
            win.cl();
            win.updateTags(pk.tags);
//          console.log("jm_ensure", pk.jm_ensure, "pk.id", pk.id);
            if(pk.jm_ensure || pk.id === 0) {
                win.op(pk);
            } else {
                win.reloadData(pk.id);
            }
            if(pk.id === 0) {
                title_bar.showImportBtn = true;
            }
        }
    }
    function openXM(pk) {
        pk = Com.convXM(1, 1, pk);
        xmfile = pk.file;
        let delegate = {
            onClose:function() {
                pageLoader.item.fuckFocus();
                title_bar.showImportBtn = false;
                xmfile = '';
            },
            getTagManager:function() {
                return null;
            },
            openEditPopup:function(add, pk) {
            },
            importFile:function() {
                import_total = 1;
                importXM();
            }
        }
        openDetail(pk, delegate);
        if(pk.jm) {
            let delegate = {
                onSubmit:function() {
                    let pwd = encrypt_cont_popup.text;
                    $a.openXMFile(xmfile, pwd, Com.putFunc(function(pk2) {
                        encrypt_cont_popup.cancel();
                        openXM(pk2);
                    }));
                },
                onCancel:function() {
                    pageLoader.item.fuckFocus();
                }
            }
            encrypt_cont_popup.delegate = delegate;
            encrypt_cont_popup.closePolicy = Popup.NoAutoClose;
            encrypt_cont_popup.op();
        }
    }
    function importXM(p) {
        if(!p) {
            p = detailView.pk;
        }
        if($l.isDebug()) {
            Com.trace("importXM", JSON.stringify(p));
        }
        let pkdata = {
            uuid: p.uuid,
            img: p.img,
            cont: p.cont,
            jm: p.jm ? 1 : 0
        }
        $a.importXM(pkdata);
    }
    function setStat(st, msg) {
        if(msg){
            Com.st(1, msg);
        } else {
            Com.st(1, Com.msgs[st]);
        }
    }
    function dp(n) {
        return n;
    }
    function sp(n) {
        return n;
    }
    function hasNew(type) {
        if(type === Com.type_book) {
            if(pageLoader.item.loadWork){
                pageLoader.item.loadWork();
            }
        } else if(type === Com.type_pk) {
            if(pageLoader.item.hasNewPK){
                pageLoader.item.hasNewPK();
            }
        }
    }
    function _alert(msg, autoclose=1) {
        alert(msg, autoclose, 0);
    }
    function alert(msg, autoclose=1, cb) {
        if(msg) {
            tips_info.popup(msg, autoclose, cb);
        }
    }
    function ensure(msg) {
        e_ensure.text = msg;
        e_ensure.open();
    }
    function showOrHide() {
        if(window.active) {
            window.hide();
        } else {
            if(winIsMax) {
                window.showMaximized();
            } else {
                window.show();
            }
            window.raise();
            window.requestActivate();
        }
    }
    function notify(msg) {
        if(!w_notify) {
            w_notify = com_notify.createObject(null, {});
        }
        w_notify.open(msg);
    }
    function navBtnClick(ty) {
        if(pageLoader.item.navBtnClick){
            pageLoader.item.navBtnClick(ty);
        }
    }
}
