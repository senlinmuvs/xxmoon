import QtQuick 2.0
import QtQuick.Controls 2.12
import "com"
import "com/com.js" as Com

Popup {
    id: root
    property var delegate: null

    width: 600
    height: 400
    x:(parent.width-width)/2
    y:(parent.height-height)/2
    modal: true
    focus: true
    background: Rectangle {color: "white"}
    clip: true

    ListModel {
        id: model
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        Column {
            id: col
            anchors.top: parent.top
            anchors.left:parent.left
            anchors.right: parent.right
            spacing: dp(10)
            Text {
                text: qsTr("Server")
                width: parent.width
                font.pointSize: sp(20)
                font.weight: Font.Black
                horizontalAlignment: Text.AlignHCenter
            }
            Rectangle {
                width: parent.width
                height: dp(10)
            }
            Row {
                width: parent.width
                spacing: dp(10)
                MyRadioBtn {
                    id: btn_enserv
                    width: dp(150)
                    text: st ? qsTr("Disable Server") : qsTr("Enable Server")
                    anchors.verticalCenter: parent.verticalCenter
                    function click() {
                        if(st) {
                            $app.disableServer();
                            st = 0;
                        } else {
                            $app.enableServer();
                            st = 1;
                        }
                    }
                    function fkEntered() {
                        e_st.text = "开启本地服务器，连手机后可相互发送数据。";
                    }
                    function fkExited() {
                        e_st.text = "";
                    }
                }
                Btn {
                    text_size: sp(10)
                    text: "生成证书"
                    border.width: dp(1)
                    border.color: "#afafaf"
                    color: "transparent"
                    radius: height/2
                    text_color: "#595959"
                    width: dp(100)
                    height: btn_enserv.height
                    anchors.verticalCenter: parent.verticalCenter
                    function click() {
                        $app.genCert(1, 1);
                    }
                    function fkEntered() {
                        e_st.text = "若自动生成的丢失，可点此生成新的SSL证书。";
                    }
                    function fkExited() {
                        e_st.text = "";
                    }
                }
                Btn {
                    visible: btn_enserv.st === 1
                    text_size: sp(10)
                    text: qsTr("Gen QR Code")
                    border.width: dp(1)
                    border.color: "#afafaf"
                    color: "transparent"
                    radius: height/2
                    text_color: "#595959"
                    width: dp(150)
                    height: btn_enserv.height
                    anchors.verticalCenter: parent.verticalCenter
                    function click() {
                        $app.genQRCode(Com.putFunc(function(r) {
                            qrimg.value = r;
                        }));
                    }
                    function fkEntered() {
                        e_st.text = "用手机扫码连接电脑";
                    }
                    function fkExited() {
                        e_st.text = "";
                    }
                }
                QRCode {
                    id: qrimg
                    visible: btn_enserv.st === 1 && qrimg.value !== ""
                    width: dp(50)
                    height: width
                    anchors.verticalCenter: parent.verticalCenter
                    value: ""
                }
            }
            Rectangle {
                width: parent.width
                height: dp(30)
                Column {
                    width: parent.width
                    height: parent.height
                    spacing: dp(2)
                    Rectangle {
                        width: parent.width
                        height: dp(1)
                        color: "#191919"
                    }
                    Row {
                        width: parent.width
                        height: parent.height - dp(2)
                        Text {
                            text: qsTr("Device")
                            font.bold: true
                            font.pointSize: sp(14)
                            width: parent.width/10 * 5
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Text {
                            text: qsTr("Time")
                            font.bold: true
                            font.pointSize: sp(14)
                            width: parent.width/10 * 3
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Text {
                            width: parent.width/10 * 2
                        }
                    }
                    Rectangle {
                        width: parent.width
                        height: dp(1)
                        color: "#191919"
                    }
                }
            }
        }
        MyList {
            id: list
            model: model
            Component {
                id: delegate
                Column {
                    width: list.width
                    height: dp(40)
                    spacing: dp(1)
                    Row {
                        width: parent.width
                        height: parent.height - dp(1)
                        Text {
                            id: devname
                            text: dev
                            color: "#595959"
                            font.pointSize: sp(10)
                            width: parent.width/10 * 5
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Text {
                            text: Com.getTimeStr(Number(ct)/1000)
                            color: "#595959"
                            font.pointSize: sp(10)
                            width: parent.width/10 * 3
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Row {
                            width: parent.width/10 * 2
                            anchors.verticalCenter: parent.verticalCenter
                            Btn {
                                text_size: sp(10)
                                text: qsTr("Del")
                                border.width: dp(1)
                                border.color: "#afafaf"
                                color: "transparent"
                                radius: height/2
                                text_color: "#595959"
                                width: dp(40)
                                height: dp(25)
                                function click() {
                                    delDev(devname.text, index);
                                }
                            }
                        }
                    }
                    Rectangle {
                        width: parent.width
                        height: dp(1)
                        color: "#efefef"
                    }
                }
            }
            delegate: delegate
            anchors.top: col.bottom
            anchors.topMargin: dp(10)
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
        }
        Text {
            id: e_st
            font.pointSize: sp(10)
            color: "#595959"
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: dp(20)
            text: ""
            horizontalAlignment: Text.AlignHCenter
        }
    }

    function op() {
        open();
        $app.getCurQRCode(Com.putFunc(function(r){
            qrimg.value = r;
        }));
        model.clear();
        $app.devices(Com.putFunc(function(r) {
            if(r && r.length > 0) {
                JSON.stringify(r);
                model.append(r);
            }
        }));
    }
    function onPush(ty, d) {
        if(d && d.length>1) {
            model.append({dev:d[0], ct:d[1]});
        }
    }
    function delDev(dev, i) {
        $app.delDev(dev, Com.putFunc(function(r) {
            if(r === 0) {
                model.remove(i);
            }
        }));
    }
}
