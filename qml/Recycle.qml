import QtQuick
import QtQuick.Controls.Fusion
import Qt.labs.platform

import "com"
import "com/com.js" as Com
import "xm/XM.js" as XM
import "com/ui.js" as UI

Rectangle {
    id: root_recycle

    signal st(int type, string tip)
    signal key(var e)
    signal tipsInfo(string txt)


    MyList {
        anchors.fill: parent
        id: list_view
        Component {
            id: btn_list_more
            MoreBtn {
                function click() {
                    if(list_view.footer) {
                        // XM.loadXM();
                    }
                }
            }
        }
        model: list_model
        delegate: ComponentXM {}
    }

    Component.onCompleted: {
    }
}
