import QtQuick 2.0

Rectangle {
    width: ai.width
    height: ai.height
    property alias gif: ai.source
    AnimatedImage {
        id: ai
    }
}
