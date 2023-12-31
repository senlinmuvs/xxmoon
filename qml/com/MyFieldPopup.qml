﻿import QtQuick 2.0
import QtQuick.Controls 2.12

import "com.js" as Com

Popup {
    id: root
    property alias text: popup_text.text
    property var placeholder: ""
    property bool pwd: false
    property bool enablePwdTwiceCheck: false

    property var delegate: null

    property string tmpPwd: ''
    property bool tmpClose: false

    width: 250
    height: 40
    x:(parent.width-width)/2
    y:(parent.height-height)/2
    modal: true
//    closePolicy: Popup.NoAutoClose
    topPadding: 0
    rightPadding: 0
    leftPadding: 0
    bottomPadding: 0
    focus: true
    TextField {
        id: popup_text
        anchors.fill: parent
        font.pointSize: 16
        color: "#080808"
        wrapMode: Text.Wrap
        selectByMouse: true
        focus: true
        echoMode: pwd?TextInput.Password:TextInput.Normal
        placeholderText: placeholder
        Keys.onPressed: {
            if(event.key === Qt.Key_Return) {
                event.accepted = true;
                submit();
            } else if(event.modifiers === ctrlVal && event.key === Qt.Key_W) {
                event.accepted = true;
                cancel();
            }
        }
        onFocusChanged: {
            if(focus) {
                $app.regMenuReceiver(popup_text);
            }
        }
    }
    Btn {
       id: btn_x
       z:10
       anchors.right: parent.right
       anchors.rightMargin: -15
       anchors.top: parent.top
       anchors.topMargin: -15
       width: 30
       height: 30
       text:"X"
       text_size: 18
       color: "black"
       radius: width/2
       function click() {
          cancel();
       }
    }
    Btn {
        id: btn_ok
        x: parent.width/2 - width/2
        y: parent.height + 10
        z:10
        color: "black"
        text: qsTr("OK")

        function click() {
            submit();
        }
    }
    Component.onCompleted: {
        popup_text.forceActiveFocus();
    }
    onClosed: {
        if(!tmpClose) {
            cancel();
        }
    }

    function submit() {
        if(enablePwdTwiceCheck) {
            if(pwd) {
                if(tmpPwd === '') {
                    if(text !== '') {
                        tmpPwd = text;
                        text = '';
                        popup_text.placeholderText = qsTr('Input agian');
                        return;
                    }
                } else {
                    if(text === '') {
                        return;
                    }
                    if(text !== tmpPwd) {
                        tmpClose = true;
                        close();
                        tips_info.popup(qsTr("Two inputs are not equal!"), true, function() {
                            tmpClose = false;
                            open();
                        });
                        return;
                    }
                }
            }
        }
        tmpPwd = '';
        if(delegate) {
            delegate.onSubmit();
        }
    }
    function cancel() {
        tmpPwd = '';
        tmpClose = false;
        clear();
        close();
        if(delegate){
            delegate.onCancel();
        }
    }
    function clear() {
        popup_text.text = '';
        closePolicy = Popup.CloseOnEscape;
    }
    function op(twiceCheck) {
        enablePwdTwiceCheck = twiceCheck;
        popup_text.placeholderText = '';
        open();
    }
}
