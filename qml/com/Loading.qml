import QtQuick 2.0

Text {
    text: ""
    font.bold: true
    font.pointSize: 20
    color:"#A3A3A3"
    property alias timer: timer
    property int timeout: 8//秒
    property int total: 0//秒
    Timer {
        id: timer
        repeat: true
        interval: 500
        triggeredOnStart: true
        onTriggered: {
            let x = text.length;
            let len = (x + 1) % 7;
            let t = '';
            for (let i = 0; i < len; i++) {
                t += '.';
            }
            text = t;

            if(total++ == timeout/(interval/1000)) {
                timer.stop();
                text = '';
            }
        }
    }
}
