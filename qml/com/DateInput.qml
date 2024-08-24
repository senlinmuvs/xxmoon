import QtQuick
import QtQuick.Controls.Fusion
import "ui.js" as UI

TextField {
    id: root
    color: "white"
    placeholderTextColor: "#808080"
    placeholderText: "____/__/__"
    verticalAlignment: Text.AlignVCenter
    font.pointSize: 12
    background: Rectangle {
        color: "#222"
    }
    onTextChanged: {
        text = vdate(text);
    }

    function vdate(text) {
      if(text.length > 10) {
          text = text.substring(0, 10);
      }
      if(text.length > 7) {
        if(text[7] !== '/') {
          text = text.replaceAt(7, '/');
        }
      }
      if(text.length > 4) {
        if(text[4] !== '/') {
          text = text.replaceAt(4, '/');
        }
      }
      for(let i = 0; i < text.length; i++) {
          if(i !== 4 && i !== 7) {
              let t = text[i];
              let reg = /[0-9]/
              if(!reg.test(t)) {
                  text = text.substring(0, i);
                  return text;
              }
              if(i === 3) {
                 let y = Number(text.substring(0, 4));
                 if(y <= 1970 || y > 2089) {
                   return '';
                 }
              }
              if(i === 5) {
                let m0 = Number(t);
                if(t > 1) {
                  text = text.substring(0, i);
                  return text;
                }
              }
              if(i === 6) {
                let m = Number(text[i-1] + t);
                if(m < 1 || m > 12) {
                  text = text.substring(0, i);
                  return text;
                }
              }
              if(i === 8) {
                let d = Number(t);
                if(d > 3) {
                  text = text.substring(0, i);
                  return text;
                }
              }
              if(i === 9) {
                let d = Number(text[i-1] + t);
                if(d < 1 || d > 31) {
                  text = text.substring(0, i);
                  return text;
                }
              }
          }
      }
      return text;
    }
}
