import QtQuick
import QtMultimedia
import QtQuick.Controls
import Qt.labs.platform

ApplicationWindow {
    property int videoWidth: 800
    property int videoHeight: 450

    visible: true
    width: Math.min(1920, videoWidth)
    height: Math.min(videoHeight, videoHeight*videoHeight/videoWidth)
    x: screen.width/2-width/2
    y: screen.height/2-height/2
    flags: Qt.FramelessWindowHint|Qt.Window
    color: "transparent"
    MediaPlayer {
        id: mediaPlayer
        source: "file:///Volumes/F/video/zb/A.webm"
        videoOutput: videoOutput
        audioOutput: audioOutput
        autoPlay: true
        onMediaStatusChanged: {
            if(mediaPlayer.mediaStatus === MediaPlayer.LoadedMedia) {

            }
        }
    }
    VideoOutput {
        id: videoOutput
        anchors.centerIn: parent
        AudioOutput {
            id: audioOutput
        }
    }
    Row {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 10
        Button {
            text: mediaPlayer.playbackState === MediaPlayer.PlayingState ? "暂停" : "播放"
            onClicked: {
                if (mediaPlayer.playbackState === MediaPlayer.PlayingState) {
                    mediaPlayer.pause();
                } else {
                    mediaPlayer.play();
                }
            }
        }
        Button {
            text: mediaPlayer.playbackRate === 2.0 ? "正常速度" : "加速"
            onClicked: {
                if (mediaPlayer.playbackRate === 2.0) {
                    mediaPlayer.playbackRate = 1.0;
                } else {
                    mediaPlayer.playbackRate = 2.0;
                }
            }
        }
    }
    Slider {
        id: progressSlider
        from: 0
        to: mediaPlayer.duration
        // value: mediaPlayer.position
        onValueChanged: mediaPlayer.position = value
        Timer {
            interval: 1000
            running: mediaPlayer.playbackState === MediaPlayer.PlayingState
            repeat: true
            onTriggered: {
                console.log("----->>>>>>>>>>", mediaPlayer.position);
            }
        }
    }
    // Text {
    //     id: durationText
    //     text: formatTime(mediaPlayer.duration)
    //     anchors {
    //         bottom: progressSlider.top
    //         horizontalCenter: progressSlider.horizontalCenter
    //     }
    // }
    // Text {
    //     id: remainingTimeText
    //     text: formatTime(mediaPlayer.duration - mediaPlayer.position)
    //     anchors {
    //         top: progressSlider.bottom
    //         horizontalCenter: progressSlider.horizontalCenter
    //     }
    // }
    // function formatTime(time) {
    //     var minutes = Math.floor(time / 60000);
    //     var seconds = Math.floor((time % 60000) / 1000);
    //     return minutes + ":" + (seconds < 10 ? "0" : "") + seconds;
    // }
}
