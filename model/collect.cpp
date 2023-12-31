﻿#include "collect.h"
#include "com/util.h"

Collect::Collect() {
}

QString Collect::toString() {
    return ut::str::mapToStr(toVMap());
}
QVariantMap Collect::toVMap() {
    QVariantMap m;
    m.insert("id", id);
    m.insert("name", name);
    m.insert("total", total);
    m.insert("i", i);
    m.insert("x", x);
    return m;
}
