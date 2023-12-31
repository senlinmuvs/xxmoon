import QtQuick 2.13
import "ui.js" as UI

Btn {
    id: btn
    state: "full"
    radius: height/2
    enable_drag: true

    property int st: 0
    property var delegate
    property var tag
    property int flag: 0

    Text {
        id: count
        font.pointSize: 10
        color:"#B0B0B0"
        width: parent.width - 30
        x: 15
        y: 3
        horizontalAlignment: Text.AlignRight
    }
    states: [
        State {
            name: "full"
            PropertyChanges {
                target: count
                visible: true
            }
            PropertyChanges {
                target: btn
                width: max(t.width + 32, 60)
                height: t.height + 22
                text_size: 16
            }
        },
        State {
            name: "simple"
            PropertyChanges {
                target: count
                visible: false
            }
            PropertyChanges {
                target: btn
                width: t.width + 25
                height: t.height + 10
                text_size: 11
                color:"#bababa"
                enable_click: false
            }
        }
    ]

    onStChanged: {
        if(delegate) {
            delegate.click(tag, st);
        }
    }

    function max(a,b) {
        if(a > b) {
            return a;
        }
        return b;
    }

    function selected() {
        btn.text_color = Qt.rgba(10/255, 10/255, 10/255, 0.8);
        btn.color = "white";
        st = 1;
    }

    function unSelected() {
        btn.text_color = "white";
        btn.color = Qt.rgba(10/255, 10/255, 10/255, 0.8);
        st = 0;
    }

    function click() {
        if(st === 0) {
            selected();
        } else {
            unSelected();
        }
    }

    function rightClick() {
        if(delegate) {
            delegate.rightClick(tag);
        }
    }
    function moved(mouse) {
       delegate.onMoved(flag, mouse, btn, tag);
    }
    function setData(t) {
        btn.tag = t;
        btn.text = t.tag;
        if(t.n) {
            count.text = t.n;
        } else {
            count.text = '';
        }
    }
}
