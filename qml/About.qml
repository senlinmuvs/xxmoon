import QtQuick
import QtQuick.Controls.Fusion
import "com"
import "com/com.js" as Com
import "com/ui.js" as UI

Popup {
    id: root
    width: 450
    height: 200
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

    MouseArea {
        width: parent.width;
        height: parent.height;
        onClicked: {
            setup_hot_key_xm.focus = false;
            root.forceActiveFocus();
        }
    }

    Rectangle {
        x: 10
        y: 10
        width: parent.width - x*2
        height: parent.height - y*2
        color: "transparent"
        Column {
            spacing: 5
            Title {
                text: $a.getCfgVal("user") === "xxmoon" ? $a.tr("xxmoon") : $a.getCfgVal("user")
                color: "white"
            }
            Text {
                id: e_count
                font.pointSize: 12
                color:"white"
            }
        }
        Column {
            id: col_setup
            anchors {
                bottom: col_ext.top
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
                    text: $a.tr("Data Path")
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
                            if($a.getPlatform() === Com.platform_mac) {
                                let path = $a.selectDataDir();
                                if(path && setup_data_path.text !== path) {
                                    $a.alertMacTip($a.tr("Please restart the app!"),
                                                     $a.tr("And copy the old data to the new directory.") + "\n" +
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
                                    if($a.getPlatform() === Com.platform_mac){
                                        path = "/" + path;
                                    }
                                    setup_data_path.text = path;
                                    $a.setCfg("data_dir", setup_data_path.text);
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
                    text: $a.tr("Editor")
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
                            if($a.getPlatform() === Com.platform_win) {
                                normalFileDialog.nameFilters = ["Exe (*.exe)"];
                            }
                            if($a.getPlatform() === Com.platform_mac) {
                                normalFileDialog.nameFilters = ["App (*.app)"];
                            }
                            normalFileDialog.onFinished = function() {
                                let path = String(normalFileDialog.currentFile).replace(Com.file_pre, "");
                                if(path.startsWith("data:text/plain;base64")){
                                    return;
                                }
                                if($a.getPlatform() === Com.platform_mac) {
                                    if(/.+[/]Terminal.app|.+[/]iTerm.app/.test(path)) {
                                        path = "vi";
                                    }
                                }
                                setup_editor.text = path;
                                $a.setCfg("editor", setup_editor.text);
                            }
                            normalFileDialog.open();
                        }
                    }
                }
            }
            Row {
                spacing: 4
                width: parent.width
                Title2 {
                    text: $a.tr("Pick Hotkey")
                    width: parent.width/2 - leftOff
                    y:5
                }
                HotkeyInput {
                    id: setup_hot_key_xm
                    width: parent.width/2 + leftOff - 4
                    function submit() {
                        if(oldHotKeyPK !== setup_hot_key_xm.text) {
                            $a.setCfg("hot_key_xm", setup_hot_key_xm.text);
                        }
                    }
                }
            }
        }

        Column {
            id: col_ext
            anchors {
                bottom: parent.bottom
                bottomMargin: 0
                left: parent.left
                right: parent.right
            }
            spacing: 10
            Row {
                spacing: 5
                Text {
                    text:"v"+ $a.getVersion()
                    color: "white"
                    font.bold: true
                    font.pointSize: UI.font_size_title2
                }
                Text {
                    text:"|"
                    color: "white"
                    font.bold: true
                }
                Link {
                    font.bold: true
                    text: "xxmoon"
                    color: "white"
                    url: "https://github.com/senlinmuvs/xxmoon"
                    font.pointSize: UI.font_size_title2
                }
            }
        }
    }

    Component.onCompleted: {
        $a.getCfg(root);
        $a.count(Com.putFunc(function(s){
            e_count.text = s;
        }));
    }
    onClosed: {
        setup_hot_key_xm.submit();
    }

    function op() {
        open();
    }
    function onCfg(cfg) {
        setup_data_path.text = cfg['dataDir'];
//        setup_current_user.text = cfg['current_user'];
        setup_editor.text = cfg['editor'];
        setup_hot_key_xm.text = cfg['hotKeyXm'];
        oldHotKeyPK = setup_hot_key_xm.text;
    }
}
