import QtQuick 2.0

MyBtn {
    id: root
    property int st: 0
    property var labs
    property var colors: ["transparent", "black"]
    property var txtColors: ["black", "white"]
    width: dp(50)
    height: dp(30)
    radius: height/2
    text_color: txtColors[st]
    color: colors[st]
    border.color: "#292929"
    border.width: dp(1)
    text_bold: true
    text_size: sp(12)
    function click() {
        st = st ? 0 : 1;
    }
    function setStyle() {
        if(labs) {
            text = labs[st];
        }
        text_color = txtColors[st];
        color = colors[st];
    }
    onStChanged: {
        setStyle();
    }
    Component.onCompleted: {
        setStyle();
    }
}
