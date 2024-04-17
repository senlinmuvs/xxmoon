import QtQuick
import QtQuick.Controls.Fusion
import Qt.labs.platform
import "com.js" as Com
import "ui.js" as UI

Popup {
    id: root
    property alias text: text.text
    width: parent.width+UI.nav_width
    height: parent.height
    x: parent.width-width
    y: 0

//    modal: true
    closePolicy: Popup.NoAutoClose
    topPadding: 0
    rightPadding: 0
    leftPadding: 0
    bottomPadding: 0
    focus: true

//    ListModel {
//        id:row_model
//    }

    property int gid: 0 // group id
    property int bid: 0 // business id
    property bool pending_close: false

    property alias first_field_enable: first_field.visible
    property var delegate

    Rectangle {
        id: editor
        anchors.fill: parent
        clip: true
        Rectangle {
            id: tool_bar
            color: UI.color_tool_bar
            width: parent.width
            height: 25
            Rectangle {
                x: 0
                y: tool_bar.height + 4
                width: parent.width
                height: 1
                color: "#565656"
            }
            Row {
                anchors.fill: parent
                anchors.leftMargin: 2
                anchors.topMargin: 2
                spacing: 8
                Btn {
                    id: btn_h1
                    height: 24
                    text:'H1'
                    text_size: UI.font_size_btn
                    function click() {
                        h1();
                    }
                }
                Btn {
                    id: btn_h2
                    height: 24
                    text:'H2'
                    text_size: UI.font_size_btn
                    function click() {
                        h2();
                    }
                }
                Btn {
                    id: btn_h3
                    height: 24
                    text:'H3'
                    text_size: UI.font_size_btn
                    function click() {
                        h3();
                    }
                }
                Btn {
                    id: btn_b
                    height: 24
                    text:'B'
                    text_size: 12
                    function click() {
                        b();
                    }
                }
                Btn {
                    id: btn_quote
                    height: 24
                    text:'<>'
                    text_size: UI.font_size_btn
                    function click() {
                        quote();
                    }
                }
                Btn {
                    id: btn_img
                    height: 24
                    text:'Img'
                    text_size: UI.font_size_btn
                    function click() {
                        img();
                    }
                }
                Btn {
                    id: btn_link
                    height: 24
                    text:'Link'
                    text_size: UI.font_size_btn
                    function click() {
                        link();
                    }
                }
                Btn {
                    id: btn_annotate
                    height: 24
                    text:'An'
                    text_size: UI.font_size_btn
                    function click() {
                        annotate();
                    }
                }
                Rectangle {
                    width: parent.width-530
                    height: 1
                }
                Btn {
                    id: btn_done
                    height: 24
                    color: "#000000"
                    font_family: "Arail"
                    text_color: "white"
                    text: qsTr("Done")
                    text_size: UI.font_size_btn
                    function click() {
                        cl();
                    }
                }
            }
        }
        TextField {
            id: first_field
            x: 0
            y: tool_bar.height + 4
            visible: false
            width: 200
            height: 30
            selectByMouse: true
            placeholderText: '位置:123-456'
            placeholderTextColor: "#808080"
            validator: RegularExpressionValidator {
                regularExpression: /[0-9]{1,9}-[0-9]{1,9}/
            }
            color: "#000"
            background: Rectangle {
                color: "transparent"
                Rectangle {
                    width: parent.width
                    height: 1
                    y: parent.height - height
                    color: "#181818"
                }
            }
            Keys.onPressed: function(event) {
                onKeys(event);
            }
            onFocusChanged: {
                if(focus) {
                    $app.regMenuReceiver(this);
                }
            }
        }
        ScrollView {
            id: scroll
            anchors.fill: parent
            anchors.bottomMargin: rect_status.height
            anchors.topMargin: first_field.visible?first_field.height+tool_bar.height:tool_bar.height
//            Row{
//                ListView {
//                    id:row
//                    width: 30;
//                    model: row_model
//                    delegate: Text {
//                        text:n
//                        font.pointSize: 12;
//                        lineHeight: 1.2
//                    }
//                }
                TextArea {
                    id: text
                    font.pointSize: UI.ui_font_pk
                    text: ""
                    color: "#080808"
                    wrapMode: Text.Wrap
                    selectByMouse: true
                    focus: true
                    selectionColor: "#7887FF"
                    selectedTextColor: "#FFF"
                    tabStopDistance: 4*fontMetrics.advanceWidth(" ")
                    FontMetrics {
                        id: fontMetrics
                        font.family: text.font
                    }
                    Keys.onPressed: function(event) {
                        onKeys(event);
                    }
                    onTextChanged: {
                        setCounter();
                    }
                    onFocusChanged: {
                        if(focus) {
                            $app.regMenuReceiver(text);
                        }
                    }
                }
        }
        Rectangle {
            id: rect_status
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: 18
            color:"transparent"
            BtnImg {
                id: btn_tip
                anchors.right: counter.left
                anchors.rightMargin: 5
                anchors.verticalCenter: parent.verticalCenter
                xx: 5
                imgWidth: 13
                imgHeight: width
                src: "qrc:/assets/tips.png"
                function click() {
                    //如果要在编辑与预览不断切换，请先进入详情再进入编辑，然后 C+W -> C+Enter -> C+W ...
                    alert(qsTr("If you want to constantly switch between editing and preview, please enter the details first and then enter the editing, then C+W -> C+Enter -> C+W ..."), false);
                }
            }
            Text {
                id: counter
                anchors.right: parent.right
                anchors.rightMargin: 5
                height: parent.height
                verticalAlignment: Text.AlignVCenter
                color:"#969696"
                font.pointSize: 10
            }
        }
    }
    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.RightButton
        onClicked:function(mouse) {
            if (mouse.button === Qt.RightButton) {
                menu_right.open();
            }
        }
    }
    Menu {
        id: menu_right
        MenuItem {
            id: mi_copy
            text: qsTr("Copy")
            onTriggered: {
                $app.triggerMenu(3);
            }
        }
        MenuSeparator {
            visible: mi_copy.visible
        }
        MenuItem {
            id: mi_paste
            text: qsTr("Paste")
            onTriggered: {
                $app.triggerMenu(4);
            }
        }
        MenuSeparator {
            visible: mi_paste.visible
        }
        MenuItem {
            id: mi_cut
            text: qsTr("Cut")
            onTriggered: {
                $app.triggerMenu(5);
            }
        }
        MenuSeparator {
            visible: mi_cut.visible
        }
        MenuItem {
            text: qsTr("Close") + " ("+ctrlName+"+W)"
            onTriggered: {
                timer.stop();
                cancel();
            }
        }
    }

    Timer {
        id: timer
        repeat: true
        interval: 5000
        onTriggered: {
            submit();
        }
    }
    Component.onCompleted: {
        text.forceActiveFocus();
    }
    onVisibleChanged: {
        if(visible) {
            timer.start();
        } else {
            timer.stop();
        }
    }

    function setCounter() {
        let chars = text.length;
        counter.text = chars;
    }
    function setPosition() {
        if(first_field.visible) {
            let arr_ = $app.getUIVal(3);
            let arr = arr_.split(',');
            let id = arr[0];
            if(id > 0 && Number(id) === root.bid) {
                let pos = arr[1];
                text.cursorPosition = pos;
            }
        } else {
            let arr_ = $app.getUIVal(2);
            let arr = arr_.split(',');
            let id = arr[0];
            if(id > 0 && Number(id) === root.bid) {
                let pos = arr[1];
                text.cursorPosition = pos;
            }
        }

    }
    function submit() {
    }
    function cancel() {
    }
    function editorAddTab(event) {
        event.accepted = true;
        let start = text.selectionStart;
        let end = text.selectionEnd;
        let tab = '\t';
        if(start === end){
            text.text = text.text.insert(start, tab);
            text.cursorPosition = start+1;
        } else {
            let s = text.text;
            for(let i = start; i >= 0; i--) {
                if(i===0) {
                    s = s.insert(i, tab);
                    start++;
                    end++;
                } else {
                    if(s[i]==='\n') {
                        s = s.insert(i+1, tab);
                        start++;
                        end++;
                        break;
                    }
                }
            }
            for(let i = start; i < end; i++) {
                if(s[i]==='\n') {
                    end++;
                    s = s.insert(i+1, tab);
                }
            }
            text.text = s;
            text.cursorPosition = start;
            text.moveCursorSelection(end, TextEdit.SelectCharacters);
        }
//        let x = text.text.replace(/\n/g, 'n').replace(/\t/g, 't');
//        Com.log(text.selectionStart, text.selectionEnd, text.lineCount, text.length, x);
    }

    function editorDelTab(event) {
        event.accepted = true;
        let start = text.selectionStart;
        let end = text.selectionEnd;
        let tab = '\t';
        let space = ' ';
        if(start === end) {
            text.text = text.text.insert(start, tab);
            text.cursorPosition = start+1;
        } else {
            let s = text.text;
            for(let i = start; i >= 0; i--) {
                if(i === 0) {
                    if(Com.eq(s[i],tab,space)) {
                        s = s.del(i, 1);
                        start--;
                        end--;
                        break;
                    }
                } else {
                    if(s[i]==='\n'){
                        if(Com.eq(s[i+1],tab,space)) {
                            s = s.del(i+1, 1);
                            start--;
                            end--;
                        }
                        break;
                    }
                }
            }
            for(let i = start; i < end; i++) {
                if(s[i] === '\n') {
                    if(i+1 < s.length && Com.eq(s[i+1],tab,space)) {
                        s = s.del(i+1, 1);
                        end--;
                    }
                }
            }
            text.text = s;
            text.cursorPosition = start;
            text.moveCursorSelection(end, TextEdit.SelectCharacters);
        }
//        let x = text.text.replace(/\n/g, 'n').replace(/\t/g, 't');
//        Com.log(text.cursorPosition, text.selectionStart, text.selectionEnd, text.lineCount, text.length, x);
    }

    function setData(gid=0, bid=0, cont='', pos0=0, pos1=0, bj=0, pc = false) {
        root.gid = gid;
        root.bid = bid;
        text.text = cont;
        if((pos1 >= pos0 || pos1 === 0) && pos0>=0 && (pos0+pos1)>0) {
            first_field.text = pos0 + '-' + pos1;
        } else {
            first_field.text = '';
        }
        pending_close = pc;
    }
    function getData() {
        if(first_field.visible) {
            let pos0 = 0;
            let pos1 = 0;
            let p = first_field.text;
            let arr = p.split('-');
            if(arr.length > 0) {
                pos0 = Number(arr[0].trim());
            }
            if(arr.length > 1) {
                pos1 = Number(arr[1].trim());
            }
            return {pos0:pos0, pos1:pos1, cont:text.text};
        } else {
            return text.text;
        }
    }
    function op(gid, bid, cont, pos0, pos1) {
        setData(gid, bid, cont, pos0, pos1);
        open();
        setCounter();
        setPosition();
        $app.regMenuReceiver(text);
    }
    function cl() {
//        console.log("---->>>>>> edit clo", gid, bid, delegate);
        if(first_field.visible) {
            $app.setUIVal(3, root.bid+","+text.cursorPosition);
        } else {
            $app.setUIVal(2, root.bid+","+text.cursorPosition);
        }
        //
        if(delegate) {
            delegate.onClose(gid, bid);
        }
        setData();
        close();
    }
    function hasChanged(n) {
        if(n.cont !== text.text) {
            return true;
        }
        if(first_field.visible) {
            let pos0 = 0;
            let pos1 = 0;
            let p = first_field.text;
            let arr = p.split('-');
            if(arr.length > 1) {
                pos0 = Number(arr[0].trim());
                pos1 = Number(arr[1].trim());
            }
            if(pos0 !== n.pos0) {
                return true;
            }
            if(pos1 !== n.pos1) {
                return true;
            }
        }
        return false;
    }
    function updateText(cont) {
        text.text = cont;
    }
    function select(i,k) {
        if(i>=0 && k.length > 0){
            text.cursorPosition = i;
            text.moveCursorSelection(i+k.length, TextEdit.SelectCharacters);
        }
    }
    function clearSelect() {
//        text.cursorPosition = 0;
//        text.moveCursorSelection(0, TextEdit.SelectCharacters);
    }
    function onKeys(event) {
        if(event.modifiers === ctrlVal && event.key === Qt.Key_W) {
            event.accepted = true;
            timer.stop();
            cancel();
        } else if(event.modifiers === ctrlVal && event.key === Qt.Key_S) {
            submit();
        } else if(event.key === Qt.Key_Backtab) {
            if(first_field.focus) {
                text.forceActiveFocus();
            } else if(text.focus) {
                if(text.selectedText) {
                    editorDelTab(event);
                } else {
                    first_field.forceActiveFocus();
                }
            }
        } else if(event.key === Qt.Key_Tab) {
            if(first_field.focus) {
                text.forceActiveFocus();
            } else if(text.focus) {
                editorAddTab(event);
            }
        } else if(event.modifiers === ctrlVal && event.key === Qt.Key_F) {
            finder.open();
        }
    }
    function insertFlagToLineHead(fromPos, flag) {
        let oldI = fromPos;
        let i = fromPos;
        while(i-- > 0) {
            if(text.text[i] === '\n') {
                i = i + 1;
                break
            }
        }
        text.text = text.text.substring(0, i) + flag +    text.text.substring(i);
        text.cursorPosition = oldI + flag.length;
    }
    function insertFlagToLineEnd(fromPos, flag) {
        let oldI = fromPos;
        let i = fromPos;
        while(i < text.text.length) {
            if(text.text[i] === '\n') {
                break
            }
            i++;
        }
        text.text = text.text.substring(0, i) + flag +    text.text.substring(i);
        text.cursorPosition = oldI;
    }
    function insertFlag(i, flag) {
        text.text = text.text.substring(0, i) + flag +    text.text.substring(i);
    }

    function h1() {
        insertFlagToLineHead(text.cursorPosition, '# ');
    }

    function h2() {
        insertFlagToLineHead(text.cursorPosition, '## ');
    }
    function h3() {
        insertFlagToLineHead(text.cursorPosition, '### ');
    }
    function b() {
        insertFlagToLineHead(text.cursorPosition, "**");
        insertFlagToLineEnd(text.cursorPosition, "**");
    }
    function img() {
        let index = text.cursorPosition;
        let dataDir = $app.dataDir;
        normalFileDialog.nameFilters = ["Image(*.png *.jpg *.jpeg *.bmp *.gif)"];
        normalFileDialog.folder = "file://" + dataDir + "/xxmoon/imgs";
        normalFileDialog.fileMode = FileDialog.OpenFiles;
        normalFileDialog.open();

        let fuck = function(img) {
            let flag = "\n!("+img+")";
            insertFlag(index, flag);
            text.cursorPosition = index + flag.length;
            index += flag.length;
        }

        normalFileDialog.onFinished = function() {
            let files = normalFileDialog.files;
            for (let i = 0; i < files.length; i++) {
                let f = files[i];
                let pre = 'file://' + dataDir + "/xxmoon/imgs/"
                let img = f.trim();
                if(f.startsWith(pre)) {
                    img = f.substring(pre.length).trim();
                } else {
                    import_total += 1;
                    $cg.xm(f, Com.putFunc(function(pkimg){
                        fuck(pkimg);
                    }));
                    return;
                }
                fuck(img);
            }
        }
    }
    function quote() {
        let s = text.selectionStart;
        let e = text.selectionEnd;
        insertFlagToLineHead(s, "```\n");
        insertFlagToLineEnd(e, "\n```");
    }
    function link() {
        let s = text.selectionStart;
        let e = text.selectionEnd;
        let flag1 = "![地址或ID:";
        if(text.selectedText.length > 0) {
            let flag2 = "]";
            insertFlag(s, flag1);
            insertFlag(e + flag1.length, text.selectedText + flag2);
        } else {
            let flag2 = "显示名称]";
            insertFlag(s, flag1);
            insertFlag(e + flag1.length, flag2);
        }
        let from = s;
        text.cursorPosition = s + 2;
        text.moveCursorSelection(from + flag1.length - 1, TextEdit.SelectCharacters);
    }
    function annotate() {
        let s = text.selectionStart;
        let e = text.selectionEnd;
        insertFlagToLineHead(s, ":[");
        insertFlagToLineEnd(e, "]");
    }
}
