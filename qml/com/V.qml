import QtQuick 2.0
import QtMultimedia 5.14

Video {
  id: video
  MouseArea {
      anchors.fill: parent
      onClicked: {
          video.play();
      }
  }
  focus: true
  Keys.onSpacePressed: video.playbackState == MediaPlayer.PlayingState ? video.pause() : video.play()
  Keys.onLeftPressed: video.seek(video.position - 5000)
  Keys.onRightPressed: video.seek(video.position + 5000)
}
