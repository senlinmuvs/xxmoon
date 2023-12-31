import QtQuick 2.0
import QtQuick.Controls 2.12
import "com"
import "com/com.js" as Com
import "com/ui.js" as UI

Popup {
    id: root
    width: 400
    height: $app.getDeploy() === 0 ? ($app.isActivated() ? 300 : 380) : 200
    x: navigation.width
    y: parent.height - height
    topPadding: 0
    rightPadding: 0
    leftPadding: 0
    bottomPadding: 0
    background: Rectangle {
        color: Qt.rgba(0/255,0/255,0/255,0.8)
    }
    property int leftOff: 73
    property string oldHotKeyPK
    Rectangle {
        x: 10
        y: 10
        width: parent.width - x*2
        height: parent.height - y*2
        color: "transparent"
        Column {
            spacing: 5
            Title {
                text: $app.getCfgVal("user") === "xxmoon" ? qsTr("xxmoon") : $app.getCfgVal("user")
                color: "white"
            }
            Title2 {
                text: qsTr("Collecting & Clippings & Note")
                color: "#a8a8a8"
            }
        }

        Column {
            id: col_setup
            anchors {
                bottom: col_act.top
                bottomMargin: 8
                left: parent.left
                right: parent.right
            }
            spacing: 8
            Rectangle {
                width: parent.width
                height: 1
                color: "#565656"
            }
            Row {
                spacing: 4
                width: parent.width
                Title2 {
                    text: qsTr("Data Path")
                    width: parent.width/2 - leftOff
                    y:5
                }
                MyTextField {
                    id: setup_data_path
                    width: parent.width/2 + leftOff - 4
                    readOnly: true
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if($app.getPlatform() === Com.platform_mac) {
                                let path = $app.selectDataDir();
                                if(path && setup_data_path.text !== path) {
                                    $app.alertMacTip(qsTr("Please restart the app!"),
                                                     qsTr("And copy the old data to the new directory.") + "\n" +
                                                     setup_data_path.text + "/xxmoon -> " + path);
                                    setup_data_path.text = path;
                                    Qt.exit(0);
                                }
                            } else {
                                folderDialog.currentFolder = setup_data_path.text;
                                folderDialog.onFinished = function() {
                                    let path = String(folderDialog.currentFolder).replace(Com.file_pre, "");
                                    if(path.startsWith("data:text/plain;base64")){
                                        return;
                                    }
                                    if($app.getPlatform() === Com.platform_mac){
                                        path = "/" + path;
                                    }
                                    setup_data_path.text = path;
                                    $app.setCfg("data_dir", setup_data_path.text);
                                }
                                folderDialog.open();
                            }
                        }
                    }
                }
            }
            Row {
                spacing: 4
                width: parent.width
                Title2 {
                    text: qsTr("Editor")
                    width: parent.width/2 - leftOff
                    y:5
                }
                MyTextField {
                    id: setup_editor
                    width: parent.width/2 + leftOff - 4
                    readOnly: true
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
//                            normalFileDialog.currentFile = setup_editor.text;
                            if($app.getPlatform() === Com.platform_win) {
                                normalFileDialog.nameFilters = ["Exe (*.exe)"];
                            }
                            if($app.getPlatform() === Com.platform_mac) {
                                normalFileDialog.nameFilters = ["App (*.app)"];
                            }
                            normalFileDialog.onFinished = function() {
                                let path = String(normalFileDialog.currentFile).replace(Com.file_pre, "");
                                if(path.startsWith("data:text/plain;base64")){
                                    return;
                                }
                                if($app.getPlatform() === Com.platform_mac) {
                                    if(/.+[/]Terminal.app|.+[/]iTerm.app/.test(path)) {
                                        path = "vi";
                                    } else {
                                        path = "/" + path;
                                    }
                                }
                                setup_editor.text = path;
                                $app.setCfg("editor", setup_editor.text);
                            }
                            normalFileDialog.open();
                        }
                    }
                }
            }
            Row {
                spacing: 4
                width: parent.width
                visible: $app.getDeploy() === 0
                Title2 {
                    text: qsTr("Pick Hotkey")
                    width: parent.width/2 - leftOff
                    y:5
                }
                HotkeyInput {
                    id: setup_hot_key_pk
                    width: parent.width/2 + leftOff - 4
                    function submit() {
                        if(oldHotKeyPK !== setup_hot_key_pk.text) {
                            $app.setCfg("hot_key_pk", setup_hot_key_pk.text);
                        }
                    }
                }
            }
        }

        Column {
            id: col_act
            anchors {
                bottom: parent.bottom
                bottomMargin: 0
                left: parent.left
                right: parent.right
            }
            spacing: 10
            Rectangle {
                width: parent.width
                height: 1
                color: "#565656"
                visible: $app.getDeploy() === 0
            }
            Row {
                spacing: 4
                width: parent.width
                visible: $app.getDeploy() === 0
                Text {
                    id: cid_lab
                    color:"#FFFFFF"
                    text: qsTr("Computer ID")
                    font.pointSize: UI.about_label_font_size
                }
                Text {
                    id: activation_flag
                    text:"("+qsTr("Activated")+")"
                    color:"white"
                    visible: $app.isActivated()
                    font.pointSize: UI.about_label_font_size
                }
                Link {
                    id: link_buy
                    width: parent.width - cid_lab.width - 5
                    horizontalAlignment: Text.AlignRight
                    text: qsTr("buy")
                    font.pointSize: UI.about_label_font_size
                    url: Com.urls['buy']+"?cid="+$app.getComputerID()
                    visible: !$app.isActivated()
                }
            }
            TextArea {
                visible: $app.getDeploy() === 0
                color:"#FFFFFF"
                font.pointSize: UI.about_label_font_size
                readOnly: true
                width: parent.width
                text: $app.getComputerID()
                wrapMode: Text.WrapAnywhere
                selectByMouse: true
                selectByKeyboard: true
                background: Rectangle {color:Qt.rgba(0.1, 0.1, 0.1, 0.8)}
            }
            TextArea {
                id: activation_area
                width: parent.width
                height: 60
                color:"#FFFFFF"
                background: Rectangle{color: Qt.rgba(0.1, 0.1, 0.1, 0.8)}
                placeholderText: qsTr("input activation code")
                selectByMouse: true
                selectByKeyboard: true
                visible: $app.getDeploy() === 0 && !$app.isActivated()
                onTextChanged: {
                    if($app.checkAuth(activation_area.text, true)) {
                        visible = false;
                        activation_flag.visible = true;
                        link_buy.visible = false;
                    }
                }
            }
            Rectangle {
                width: parent.width
                height: 1
                color: "#565656"
            }
            Row {
                spacing: 5
                Text {
                    text:"v"+ $app.getVersion() +" | "
                    color: "white"
                    font.bold: true
                    font.pointSize: UI.font_size_title2
                }
                Link {
                    font.bold: true
                    text: "email"
                    color: "white"
                    font.pointSize: UI.font_size_title2
                    url: "mailto:sen@senli.tech?subject=xxmoon"
                }
                Text {
                    text:"|"
                    color: "white"
                    font.bold: true
                }
                Link {
                    font.bold: true
                    text: "xxmoon.com"
                    color: "white"
                    url: Com.urls['main']
                    font.pointSize: UI.font_size_title2
                }
            }
        }
    }

    Component.onCompleted: {
        $app.getCfg(root);
    }
    onClosed: {
        setup_hot_key_pk.submit();
    }

    function op() {
        open();
    }
    function onCfg(cfg) {
        setup_data_path.text = cfg['data_dir'];
//        setup_current_user.text = cfg['current_user'];
        setup_editor.text = cfg['editor'];
        setup_hot_key_pk.text = cfg['hot_key_pk'];
        oldHotKeyPK = setup_hot_key_pk.text;
    }
}
