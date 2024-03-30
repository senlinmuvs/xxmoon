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
    return m;
}
