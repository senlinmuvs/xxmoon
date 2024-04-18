#include "category.h"
#include "com/util.h"

Category::Category() {
}

QString Category::toString() {
    return ut::str::mapToStr(toVMap());
}
QVariantMap Category::toVMap() {
    QVariantMap m;
    m.insert("id", id);
    m.insert("name", name);
    m.insert("total", total);
    m.insert("i", i);
    m.insert("x", x);
    // m.insert("m", this->m);
    m.insert("jm", this->m.length() > 0);
    return m;
}
