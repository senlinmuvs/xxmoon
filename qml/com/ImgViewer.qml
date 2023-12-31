import QtQuick 2.13
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import Qt.labs.platform 1.1
import "com.js" as Com

Window {
    id:root
    x: screen.width/2 - width/2
    y: screen.height/2 - height/2
    flags: Qt.FramelessWindowHint | Qt.Window
    color: "transparent"

    property alias src: img.source
    property int curIndex: 0
    property var list:[]
    property int imgBottom: 82
    property bool lock:false
    property var delegate

    MyImage {
        id: img
        anchors.fill:parent
        img_radius: 1
        focus: true
        Keys.onPressed: {
            onKeysPressed(event);
        }
        states: [
          State {
              name: "no_bottom"
              PropertyChanges { target: img; anchors.bottomMargin: 0 }
          },
          State {
              name: "has_bottom"
              PropertyChanges { target: img; anchors.bottomMargin: imgBottom }
          }
        ]
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            onClicked: {
                menu.open();
            }
        }
    }

    MouseArea {
        id: mouseRegion
        anchors.fill: parent
        property variant clickPos: "1,1"
        onPressed: {
            clickPos  = Qt.point(mouse.x,mouse.y)
        }
        onPositionChanged: {
            var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
            root.x += delta.x;
            root.y += delta.y;
        }
        onDoubleClicked: {
            openInExternal();
        }
    }

    Menu {
        id:menu
//        MenuItem {
//            id: mi_set_wallpaper
//            visible: $app.getPlatform() === Com.platform_win
//            text: qsTr("As Wallpaper") + " (Ctrl+Enter)"
//            onTriggered: {
//                setWallpaper();
//            }
//        }
//        MenuSeparator {
//            visible: mi_set_wallpaper.visible
//        }
        MenuItem {
            text: qsTr("Copy") + " (" + ctrlName + "+C)"
            onTriggered: {
                copyImg();
            }
        }
        MenuSeparator {}
        MenuItem {
            text: qsTr("Copy Link") + " (" + ctrlName + "+Alt+C)"
            onTriggered: {
                copyLink();
            }
        }
        MenuSeparator {}
        MenuItem {
            text: qsTr("Out Edit") + " (Enter)"
            onTriggered: {
                openInExternal();
            }
        }
        MenuSeparator {}
        MenuItem {
            text: qsTr("Reveal in File Manager") + " (" + ctrlName + "+Enter)"
            onTriggered: {
                revealInFinder();
            }
        }
        MenuSeparator {}
        MenuItem {
            text: qsTr("Close") + " (Esc)"
            onTriggered: {
                close();
            }
        }
    }
    Timer {
        id: e_iv_timer
        repeat: true
        interval: 1000
        triggeredOnStart: false
        onTriggered: {
            let cur = list[curIndex];
            img.source = "";
            img.source = cur.img;
        }
    }

    function onKeysPressed(event) {
        if(event.key === Qt.Key_Escape) {
            close();
        } else if(event.key === Qt.Key_J) {
            next();
        } else if(event.key === Qt.Key_K) {
            previous();
        } else if(event.key === Qt.Key_Equal) {
            enlarge();
        } else if(event.key === Qt.Key_0) {
            original();
        } else if(event.key === Qt.Key_Minus) {
            lessen();
        } else if(event.key === Qt.Key_Home) {
            setToTop();
        } else if(event.key === Qt.Key_End) {
            setToBottom();
        } else if(event.key === Qt.Key_Down) {
            setToDown();
        } else if(event.key === Qt.Key_Up) {
            setToUp();
        } else if(event.modifiers === ctrlVal && event.key === Qt.Key_C) {
            copyImg();
        } else if(event.modifiers === (ctrlVal|Qt.AltModifier) && event.key === Qt.Key_C) {
            copyLink();
        } else if(event.modifiers === ctrlVal && event.key === Qt.Key_Return) {
            revealInFinder();
        } else if(event.key === Qt.Key_Return) {
            openInExternal();
        } else if(event.key === Qt.Key_Space) {
            let file = img.source.substring(7);
            let name = file.substring(0, file.lastIndexOf("."));
            let postfix = file.substring(file.lastIndexOf("."));
            let isOriginal = file.lastIndexOf("_original"+postfix) > 0;
            if(isOriginal) {
                name = name.replace("_original", "");
                let ok0 = $app.existFile(name+postfix);
                if(ok0) {
                    img.source = "";
                    img.source = "file://" + name + postfix;
                }
                console.log("切换为缩略图", img.source);
            } else {
                let ok1 = $app.existFile(name+"_original"+postfix);
                if(ok1) {
                    img.source = "";
                    img.source = "file://" + name + "_original"+postfix;
                }
                console.log("切换为原图", img.source);
            }
        }
    }

    function close() {
        list = [];
        curIndex = 0;
        root.hide();
        if(delegate.onClose) {
            delegate.onClose();
        }
        e_iv_timer.stop();
    }

    function next() {
        if(lock) {
            return;
        }
        lock = true;
        let cur = curIndex + 1;
        if(cur > list.length-1) {
            while(true) {
                let pk = delegate.next();
                if(pk) {
                    let n = append(pk);
                    if(n) {
                        curIndex = cur;
                        break;
                    }
                } else {
                    break;
                }
            }
        } else {
            curIndex = cur;
        }
        open();
        lock = false;
    }
    function previous() {
        if(lock) {
            return;
        }
        lock = true;
        let cur = curIndex - 1;
        if(cur < 0) {
            while(true) {
                let pk = delegate.previous();
                if(pk) {
                    let n = prepend(pk);
                    if(n) {
                        curIndex = n - 1;
                        break;
                    }
                } else {
                    break;
                }
            }
        } else {
            curIndex = cur;
        }
        open();
        lock = false;
    }

    function append(pk) {
        let n = 0;
        if(pk){
            let curPKListViewIndex = delegate.getCurrentIndex();
            if(pk.img_path) {
                list[list.length] = {i:curPKListViewIndex,img:pk.img_path, w:pk.src_w, h: pk.src_h};
                n++;
            }
            let arr = pk.imgs.split(",");
            for(let i = 0; i < arr.length; i++) {
                if(arr[i]) {
                    let wh = Com.parseWithHeightInImgName(arr[i]);
                    list[list.length] = {i:curPKListViewIndex,img:Com.file_pre+$app.imgDir+'/'+arr[i], w:wh[0], h:wh[1]};
                    n++;
                }
            }
        }
        return n;
    }

    function prepend(pk) {
        let n = 0;
        if(pk){
            let curPKListViewIndex = delegate.getCurrentIndex();
            if(pk.img_path) {
                list.unshift({i:curPKListViewIndex,img:pk.img_path, w:pk.src_w, h: pk.src_h});
                n++;
            }
            let arr = pk.imgs.split(",");
            for(let i = 0; i < arr.length; i++) {
                if(arr[i]) {
                    let wh = Com.parseWithHeightInImgName(arr[i]);
                    list.unshift({i:curPKListViewIndex,img:Com.file_pre+$app.imgDir+'/'+arr[i], w:wh[0], h:wh[1]});
                    n++;
                }
            }
        }
        return n;
    }

    function checkIndex() {
        if(curIndex < 0 || curIndex > list.length-1) {
            return false;
        }
        return true;
    }

    function setCurIndexByImg(img) {
        for(let i = 0; i < list.length; i++) {
//            console.log("setCurIndexByImg", list[i].img, img);
            if(list[i].img === img) {
                curIndex = i;
                return;
            }
        }
    }

    function open() {
        if(!checkIndex()){
            return;
        }
        let it = list[curIndex];
        src = it.img;
        let wh = Com.calImgSizeByHeight(it.w, it.h);
        width = wh[0];
        height = wh[1];
        setBottom();
        center();
        show();
        raise();
        requestActivate();
        if(delegate){
            delegate.setIndex(it.i);
        }
    }
    function setBottom() {
        if($app.getPlatform() === Com.platform_mac){
            if(root.height > screen.height - imgBottom){
                img.state = "has_bottom";
            } else {
                img.state = "no_bottom";
            }
        }
    }

    function enlarge() {
        if(!checkIndex()){
            return;
        }
        let ar = Com.zoom(img.width, img.height);
        let curImg = list[curIndex];
        let maxW = curImg.w * 2;
        if(ar[0] > maxW){
            root.width = maxW;
            root.height = curImg.h * 2;
        } else {
            root.width = ar[0];
            root.height = ar[1];
        }
        setBottom();
        center();
    }
    function lessen() {
        if(!checkIndex()){
            return;
        }
        let ar = Com.zoom(img.width, img.height, 0.8);
        let curImg = list[curIndex];
        let minW = curImg.w * 0.5;
        if(ar[0] < minW) {
            root.width = minW;
            root.height = curImg.h * 0.5;
        } else {
            root.width = ar[0];
            root.height = ar[1];
        }
        setBottom();
        center();
    }
    function original() {
        if(!checkIndex()){
            return;
        }
        let curImg = list[curIndex];
        root.width = curImg.w;
        root.height = curImg.h;
        setBottom();
        center();
    }
    function setToTop() {
        root.y = 0;
    }
    function setToBottom() {
        root.y = screen.height-root.height;
    }
    function setToUp() {
        if(screen.height-root.height > 0) {
            root.y = Com.max(root.y - 100, 25);
        } else {
            root.y = Com.min(root.y + 100, 25);
        }
    }
    function setToDown() {
        let max = screen.height-root.height;
        if(max > 0){
            root.y = Com.min(root.y+50,max);
        } else {
            root.y = Com.max(root.y-50,max);
        }
    }
    function center() {
        x = screen.width/2 - width/2;
        y = screen.height/2 - height/2 - 30;
    }
    function openInExternal() {
        let img = list[curIndex];
        $app.openInExternal(0, img.img);
        e_iv_timer.start();
    }
    function revealInFinder() {
        let img = list[curIndex];
        $app.openDir(img.img);
    }
    function setWallpaper() {
        if(list.length > 0 && curIndex>=0){
            let path = list[curIndex].img;
            path = path.replace(Com.file_pre, "")
                     .replace("//", "\\")
                     .replace("/", "\\");
            $app.setWallpaper(path);
        }
    }
    function copyImg() {
        if(list.length > 0 && curIndex>=0) {
            let path = list[curIndex].img;
            $app.copyImg(path);
        }
    }
    function copyLink() {
        if(list.length > 0 && curIndex>=0){
            let path = list[curIndex].img;
            let imglink = "!("+Com.extraImgname(path)+")";
            $app.copy(imglink);
        }
    }
}
