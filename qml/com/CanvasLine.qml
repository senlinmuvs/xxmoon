import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Rectangle {
    id: root
    color: "transparent"

    //鼠标点击坐标位置
    property real startX     //储存鼠标开始时的坐标
    property real startY
    property real stopX      //储存鼠标结束时的坐标
    property real stopY
    property bool isMouseMoveEnable: false //是否允许鼠标移动绘制事件
    property bool isLeft: false // 是否点击的是左键

    Canvas {
        id:canvas
        anchors.fill:parent
        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0,0,width,height);
            if (!isMouseMoveEnable) {
                return;
            }
            //开始绘制
            ctx.beginPath()
            ctx.moveTo(startX,startY)

            //记录移动终点
            stopX = area.mouseX
            stopY = area.mouseY

            // Draw a line
            ctx.lineWidth = 2;
            ctx.strokeStyle = "red"
            ctx.lineTo(stopX, stopY);
            ctx.stroke();
//            console.log(stopX + ", " + stopY);
        }
    }

    MouseArea {
        id:area
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        //当鼠标按下时调用本函数
        onPressed: {
            isLeft = mouse.buttons === Qt.LeftButton
            startX = mouse.x;
            startY = mouse.y;
            isMouseMoveEnable = true;
            onStart();
        }
        //当鼠标释放时调用本函数
        onReleased: {
            isMouseMoveEnable = false;
            canvas.requestPaint();
            onFinished();
        }
        //当鼠标press位置改变，调用本函数
        onPositionChanged: {
            if (isMouseMoveEnable){
                canvas.requestPaint()
            }
        }
        onDoubleClicked: {
            onDoubleClicked0();
        }
    }
    function onStart() {
    }
    function onFinished() {
    }
    function onDoubleClicked0() {
    }
}
