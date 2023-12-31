import QtQuick 2.13
import QtQuick.Controls 2.13
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
    background: Rectangle{
        color: "transparent"
    }
    property int bid: 0
    Column {
        anchors.fill: parent
        spacing: 8
        TextField {
            id: tf_book_name
            width: parent.width
            placeholderText: qsTr("Book Name")
            font.pointSize: UI.book_edit_label_font_size
            text: ""
            color: "#080808"
            wrapMode: Text.Wrap
            selectByMouse: true
            maximumLength: 50
            onFocusChanged: {
                if(focus) {
                    $app.regMenuReceiver(tf_book_name);
                }
            }
        }
        TextField {
            id: tf_author_name
            width: parent.width
            placeholderText: qsTr("Author Name")
            font.pointSize: UI.book_edit_label_font_size
            text: ""
            color: "#080808"
            wrapMode: Text.Wrap
            selectByMouse: true
            maximumLength: 50
            onFocusChanged: {
                if(focus) {
                    $app.regMenuReceiver(tf_author_name);
                }
            }
        }
        DateInput {
            id: di_date
            width: parent.width
            font.pointSize: UI.book_edit_label_font_size
        }
        Btn {
            x: parent.width/2 - width/2
            y: 8
            color: "black"
            text: qsTr("OK")
            function click() {
                submit();
            }
        }
        Keys.onPressed: {
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
       text_size: 18
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
    function setData(name='', author='', date='', bid=0) {
        tf_book_name.text = name;
        tf_author_name.text = author;
        di_date.text = date;
        root.bid = bid;
    }
    function op(name='', author='', date='', bid=0) {
        setData(name, author, date, bid);
        open();
        tf_book_name.forceActiveFocus();
    }
    function getData() {
        return [tf_book_name.text, tf_author_name.text, di_date.text];
    }
    function cl() {
        setData();
        close();
    }
}
