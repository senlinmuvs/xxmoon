#include "xm.h"
#include "com/global.h"

XM::XM() {
}

QString XM::toString() {
    return ut::str::mapToStr(toVMap(true));
}

QVariantMap XM::toVMap(bool detail, bool parse, uint maxWidth) {
    QVariantMap m;
    m.insert("id", id);
    m.insert("cid", cid);
    cont = cont.replace("\r", "\n");
    m.insert("simple_cont", simpleCont);
//    m.insert("simple_html", doc_parser->parseHtml(simpleCont));
    m.insert("simple_qmls", doc_parser->parseQML(simpleCont, maxWidth));
    if(detail) {
        m.insert("cont", cont);
        if(parse) {
//            m.insert("html", doc_parser->parseHtml(cont));
            m.insert("qmls", doc_parser->parseQML(cont, maxWidth));
        }
    }
    m.insert("img", img);
    m.insert("time", time);
    m.insert("lst", lst);
    m.insert("stime", stime);
    m.insert("bj", bj);
    m.insert("jm", jm);
    m.insert("tags", tags);
    m.insert("imgs", extractImgs(cont));
    m.insert("uuid", uuid);
    m.insert("file", file);
    m.insert("refids", refids);
    m.insert("refimgids", refimgids);
    return m;
}

QString XM::getImgLink() {
    if(img.length()>0){
        return "!("+img+")";
    } else {
        return "";
    }
}

bool XM::hasTagId(uint tid) {
    return tags.contains("#"+QString::number(tid)+"#");
}

void XM::fill(QVariantMap m) {
    id = m.value("id", 0).toUInt();
    cid = m.value("cid", 0).toUInt();
    cont = m.value("cont", "").toString();
    img = m.value("img", "").toString();
    jm = m.value("jm", 0).toUInt();
    bj = m.value("bj", 0).toBool();
    uuid = m.value("uuid", "").toString();
}
