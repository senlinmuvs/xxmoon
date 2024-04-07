#include "work.h"
#include "com/util.h"

Work::Work() {
}

QString Work::toString() {
    return ut::str::mapToStr(toVMap());
}

QVariantMap Work::toVMap() {
    QVariantMap m;
    m.insert("id", id);
    m.insert("name", name);
    m.insert("author", author);
    m.insert("time", time);
    m.insert("t", t);
    m.insert("fro", fro);
    m.insert("total", total);
    m.insert("tag", tag);
    return m;
}

void Work::convTagPound2Comma() {
    if(tag.startsWith("#")) {
        tag = tag.mid(1);
    }
    if(tag.endsWith("#")) {
        tag = tag.mid(0, tag.length()-1);
    }
    tag = tag.replace("#", ",");
}
void Work::convTagComma2Pound() {
    tag = tag.replace(",", "#");
    tag = "#"+tag+"#";
}
