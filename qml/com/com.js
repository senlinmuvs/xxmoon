.import "com_ext.js" as Ext
const reg_find_img = new RegExp('![(](.+?)[)]','g');
//
const type_pk = 0;
const type_book = 1;

const PUSH_SERVER = 0;
const PUSH_OPENFILE = 1;
const PUSH_OPEN_ABOUT = 2;
const PUSH_UP_TAGS = 3;

let tag1 = $app.tag1;
let tag2 = $app.tag2;
let MAX_TAG = $app.maxTag;
let urls = {
    'main': 'https://xxmoon.com',
    'buy': 'https://xxmoon.com/buy.html'
};

let img_logo = "/assets/logo64.png";
let img_kindle = "/assets/kindle64.png";
///
let file_type_img = 1;
let file_type_txt = 2;
let file_type_pdf = 3;
let file_type_html = 4;
let file_type_xm = 5;
let file_type_site = 6;
let reg_img = /^.+[.](png|jpg|jpeg|bmp|gif|webp)$/i;
let reg_number = /^\d+$/;
let reg_file = /^[/].+$|^[a-zA-Z]:.+$/;

let platform_win = 0;
let platform_linux = 1;
let platform_mac = 2;

let file_pre = $app.getPlatform() === platform_win ? "file:///" : "file://";
let msgs = {
    0: qsTr("Success"),
    1: qsTr("Failure")
};
///error code
//let ret_e
function wrapKey(cont, k) {
    if(cont) {
        return cont.replace(new RegExp(k, 'gi'), "<font color='red'>"+k+"</font>");
    } else {
        return "";
    }
}
function conv2Str(arr) {
    let s = '';
    for(let i in arr){
        s += arr[i] + " ";
    }
    return s;
}

function trace(...arr) {
    $l.trace(conv2Str(arr));
}
function debug(...arr) {
    $l.debug(conv2Str(arr));
}
function info(...arr) {
    $l.info(conv2Str(arr));
}
function warn(...arr) {
    $l.warn(conv2Str(arr));
}
function error(...arr) {
    $l.error(conv2Str(arr));
}
///
function eq(...args) {
    if(args.length<2){
      return true;
    }
    let first = args[0];
    for(let i = 1; i < args.length; i++) {
      if(args[i] === first){
          return true;
      }
    }
    return false;
}
function min(a,b) {
	if(a>b){
		return b;
	}
	return a;
}
function max(a,b) {
	if(a>b){
		return a;
	}
	return b;
}
function viewTime(time) {
    let a = parseTime(time, 1);
    return a[0] + ' ' + a[1];
}
//1490718372 -> [2019年9月23日,22:08]
function parseTime(t, f) {
    if(t<=0) {
       return ['',''];
    }
    let time = new Date(parseInt(t)*1000);
    let date_ = '';
    let mzero = (time.getMonth()+1) < 10 ? '0' : '';
    let dzero = time.getDate() < 10 ? '0' : '';
    let hzero = time.getHours() < 10 ? '0' : '';
    let mizero = time.getMinutes() < 10 ? '0' : '';
    if(f>0) {
        date_ = time.getFullYear() + "/" + (mzero) + (time.getMonth()+1) + "/" + (dzero) + time.getDate();
    } else {
        date_ = time.getFullYear() + "/" + (mzero) + (time.getMonth()+1);
    }
    let time_ = (hzero) + time.getHours() + ":" + (mizero) + time.getMinutes();
    return [date_, time_];
}
function convStrToTime(s) {
    let arr = s.split('/');
    for(let i = 0; i < arr.length; i++){
        let it = arr[i];
        if(!/[0-9]+/.test(it)){
            return 0;
        }
    }
    let y = Number(arr[0]);
    let m = Number(arr[1]);
    let d = Number(arr[2]);
    return new Date(y, m-1, d).getTime();
}
function getTimeStr(t) {
    if(t<=0){
       return '';
    }
    let time = new Date(parseInt(t)*1000);
    return time.getFullYear() + "/" +
            (time.getMonth()+1) +"/" +
            time.getDate() + " " +
            time.getHours() + ":" +
            time.getMinutes() + ":" +
            time.getSeconds();
}
function getMonth(t) {
    let time = new Date(parseInt(t)*1000);
    return time.getMonth() + 1;
}
/*
* 设置状态提示
* st: 0 不会消失 1 会几秒后消失
*/
function st(st, tip) {
    window.title = tip;
    window.st = st;
}
function request(url, method, cb) {
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
        if (xhr.readyState === XMLHttpRequest.HEADERS_RECEIVED) {
//            console.log('HEADERS_RECEIVED');
        } else if(xhr.readyState === XMLHttpRequest.DONE) {
            cb(xhr.responseText.toString());
        }
    }
    xhr.open(method, url);
    xhr.send();
}
function get(url, cb) {
    request(url, 'GET', cb);
}
///
function calculateTextHeight(font, line_height=1, width=font, text='X') {
    if(text==='') {
        return 0;
    }
//    console.log(font+","+line_height+","+width+","+text);
    return 0;
}
///
function calImgSizeByWidth(srcW, srcH, maxWidth=screen.width - 100) {
    if(srcW <= 0 || srcH <= 0) {
        return [0, 0];
    }
    let w = min(maxWidth, srcW);
    let ratio = srcW/srcH;
    let h = w/ratio;
    return [w, h];
}
function calImgSizeByHeight(srcW, srcH, maxHeight=screen.height - 130) {
    if(srcW <= 0 || srcH <= 0) {
        return [0, 0];
    }
    let h = min(maxHeight, srcH);
    let ratio = srcW/srcH;
    let w = h * ratio;
    return [w, h];
}
function zoom(w, h, factor=1.2) {
    let w2 = w * factor;
    let ratio = w/h;
    let h2 = w2/ratio;
    return [w2,h2];
}
function parseWithHeightInImgName(imgName) {
    if(imgName) {
        let arr = imgName.split('.');
        if(arr.length>2){
            let w = Number(arr[arr.length-3]);
            let h = Number(arr[arr.length-2]);
            return [w,h];
        }
    }
    return 0;
}
function abs(x) {
    return x>0?x:-x;
}
function contains(arr, e) {
    for(let i = 0; i < arr.length; i++) {
        if(arr[i] === e) {
            return true;
        }
    }
    return false;
}
function isDir(path) {
    return path.trim().endsWith('/');
}

function getFileType(file) {
    if(reg_img.test(file)) {
      return file_type_img;
    } else if(file.endsWith(".txt")) {
      return file_type_txt;
    } else if(file.endsWith(".pdf")) {
      return file_type_pdf;
    } else if(file.endsWith(".xm")){
      return file_type_xm;
    }
    return -1;
}
function isNumber(x) {
    return reg_number.test(x);
}
function isFile(x) {
    return reg_file.test(x);
}
function putFunc(cb) {
    let i = window.cbid;
    window.cbs[i] = cb;
    window.cbid++;
    return i;
}
function wrapKey(cont, k) {
    if(cont) {
        return cont.replace(new RegExp(k, 'gi'), tag1+k+tag2);
    } else {
        return "";
    }
}

function convPK(preDateStr, preTimeStr, e) {
    let simpleQmlsStr = JSON.stringify(e.simple_qmls);
//    console.log("convPK", simpleQmlsStr);
    let n = {
        id: e.id,
        cont: e.cont ? e.cont : '',
//        html: e.html ? e.html : '',
        qmls: e.qmls ? e.qmls : [],
        qmls_: "",
        simple_cont: e.simple_cont,
//        simple_html: e.simple_html,
        simple_qmls: simpleQmlsStr,
        img: e.img,
        time: e.time,
        lst: e.lst,
        stime: e.stime,
        tags: e.tags,
        imgs: e.imgs,
        bj: e.bj,
        cid: e.cid,
        jm: e.jm,
        img_path: '',
        date_str: '',
        time_str: '',
        src_w:0,
        src_h:0,
        visible_date: false,
        visible_time: false,
        total_h:0,
        jm_ensure: false,
        cont_bak: '',
        uuid: e.uuid,
        file: e.file,
        extra: "",
        forceMaxWidth: false
    };

    let arr = parseTime(n.time, 1);
    n.date_str = arr[0];
    n.time_str = arr[1];
    n.visible_date = preDateStr !== n.date_str;
//    n.visible_time = preTimeStr !== n.time_str;
    n.visible_time = true;
    //
    if(n.img) {
        n.img_path = file_pre + $app.imgDir + "/" + n.img;
        let arr = parseWithHeightInImgName(n.img_path);
        n.src_w = arr[0];
        n.src_h = arr[1];
    }
    return n;
}

function str(format, ...args) {
//    for(let i in args){
//        s += arr[i] + " ";
//    }
}

////字母快速导航
let preKeys = "";
let lastKeyTime = 0;
function jump(event, m, vc) {
    if(event.key === Qt.Key_Space) {
        return;
    } else if(event.key === Qt.Key_Escape) {
        preKeys = "";
        st(1, "");
        return;
    }

    let excepts_keys = "jk";
    let curKey = event.text ? event.text[0] : "";
    let cur = new Date().getTime();
    if(lastKeyTime) {
        if(cur - lastKeyTime > 1000){
            preKeys = "";
        }
    }
    //
    preKeys += curKey;
    lastKeyTime = cur;
    let keys = preKeys;

    let tip = false;
    for(let i = 0; i < keys.length; i++) {
        if(keys[i] !== 'j' && keys[i] !== 'k' && keys[i] !== 'J' && keys[i] !== 'K') {
            tip = true;
            break;
        }
    }
    if(tip) {
        st(1, keys);
    }

    for(let i = 0; i < m.count; i++) {
        let c = m.get(i);
        if(c) {
            if(keys) {
                if(c.name.startsWith(keys) && excepts_keys.indexOf(keys) < 0) {
                    vc.currentIndex = i;
                    break;
                }
            }
        }
    }
}

function removeEmpty(list) {
    let arr = [];
    for(let i = 0; i < list.length; i++) {
        let e = list[i].trim();
        if(e) {
            arr[arr.length] = e;
        }
    }
    return arr;
}
function extraImgname(path) {
    let arr = path.split("/");
    if(arr.length > 1){
        return arr[arr.length-2]+"/"+arr[arr.length-1];
    }
    return "";
}
function getWinKey() {
    let plat = $app.getPlatform();
    if(plat === platform_win) {
        return "Win";
    } else if(plat === platform_mac) {
        return "Cmd";
    }
}
let chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
function randomStr(length = 30) {
    let str = '';
    for (let i = 0; i < length; i++) {
        str += chars.charAt(Math.floor(Math.random() * chars.length));
    }
    return str;
};
function isAnimation(s) {
    return s.endsWith(".gif") || s.endsWith(".webp");
}
function verText(txt) {
    txt = String(txt);
    let x = '';
    for(let i = 0; i < txt.length; i++) {
        x += txt[i]+'\n';
    }
    return x;
}
function getPos(pos0, pos1) {
    if(pos0 && pos1) {
        return pos0 + "-" + pos1;
    } else {
        if(pos0 > 0) {
            return pos0;
        }
        if(pos1 > 0) {
            return pos1;
        }
    }
    return "";
}
