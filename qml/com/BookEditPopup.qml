﻿import QtQuick
import QtQuick.Controls.Fusion
import "ui.js" as UI

Popup {
    id: root
    width: 280
    height: 200
    modal: true
    topPadding: 0
    rightPadding: 0
    leftPadding: 0
    bottomPadding: 0
    focus: true
    background: Rectangle {
        color: "transparent"
    }
    property int bid: 0
    Column {
        anchors.fill: parent
        spacing: 8
        TextField {
            id: tf_book_name
            width: parent.width
            height: 40
            placeholderTextColor: "#808080"
            placeholderText: $a.tr("Book Name")
            font.pointSize: UI.book_edit_label_font_size
            color: "white"
            wrapMode: Text.Wrap
            selectByMouse: true
            maximumLength: 50
            onFocusChanged: {
                if(focus) {
                    $a.regMenuReceiver(tf_book_name);
                }
            }
            background: Rectangle {
                color: "#222"
            }
        }
        TextField {
            id: tf_author_name
            width: parent.width
            height: 40
            placeholderTextColor: "#808080"
            placeholderText: $a.tr("Author Name")
            font.pointSize: UI.book_edit_label_font_size
            color: "white"
            wrapMode: Text.Wrap
            selectByMouse: true
            maximumLength: 50
            background: Rectangle {
                color: "#222"
            }
            onFocusChanged: {
                if(focus) {
                    $a.regMenuReceiver(tf_author_name);
                }
            }
        }
        DateInput {
            id: di_date
            width: parent.width
            height: 40
            font.pointSize: UI.book_edit_label_font_size
        }
        TextField {
            id: tf_tag
            width: parent.width
            height: 40
            placeholderTextColor: "#808080"
            placeholderText: $a.tr("Tag(separated by commas)")
            font.pointSize: UI.book_edit_label_font_size
            color: "white"
            wrapMode: Text.Wrap
            selectByMouse: true
            maximumLength: 50
            background: Rectangle {
                color: "#222"
            }
        }
        TextField {
            id: tf_extra
            width: parent.width
            height: 40
            placeholderTextColor: "#808080"
            placeholderText: $a.tr("Extra")
            font.pointSize: UI.book_edit_label_font_size
            color: "white"
            wrapMode: Text.Wrap
            selectByMouse: true
            maximumLength: 50
            background: Rectangle {
                color: "#222"
            }
        }
        Btn {
            x: parent.width/2 - width/2
            y: 8
            color: "black"
            text: $a.tr("OK")
            text_size: UI.font_size_btn
            function click() {
                submit();
            }
        }
        Keys.onPressed: function(event) {
            if(event.key === Qt.Key_Return) {
                submit();
            }
        }
    }
    Btn {
       z:10
       anchors.right: parent.right
       anchors.rightMargin: -15
       anchors.top: parent.top
       anchors.topMargin: -15
       width: 30
       height: 30
       text:"X"
       text_size: UI.btn_close_font_size
       color: "black"
       radius: width/2
       function click() {
          cancel();
       }
    }
    onClosed: {
        cancel();
    }
    function submit() {
    }
    function cancel() {
    }
    function setData(name='', author='', date='', tag='', extra='', bid=0) {
        tf_book_name.text = name;
        tf_author_name.text = author;
        di_date.text = date;
        tf_tag.text = tag;
        tf_extra.text = extra;
        root.bid = bid;
    }
    function op(name='', author='', date='', tag='', extra='', bid=0) {
        if($l.isTrace()) {
            console.log("op", name, author, date, tag, extra, bid);
        }
        setData(name, author, date, tag, extra, bid);
        open();
        tf_book_name.forceActiveFocus();
    }
    function getData() {
        return [tf_book_name.text, tf_author_name.text, di_date.text, tf_tag.text, tf_extra.text];
    }
    function cl() {
        setData();
        close();
    }
}
