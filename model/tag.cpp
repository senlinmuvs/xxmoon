#include "tag.h"
#include "com/util.h"

Tag::Tag() {
}

QString Tag::toString() {
    return ut::str::mapToStr(toVMap());
}

QVariantMap Tag::toVMap() {
    QVariantMap m;
    m.insert("id", id);
    m.insert("tag", tag);
    m.insert("n", n);
    return m;
}
