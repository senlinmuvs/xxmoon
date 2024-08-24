#include "tasklog.h"
#include "com/util.h"
#include <QVariantMap>

TaskLog::TaskLog() {}

QString TaskLog::toString() {
    return ut::str::mapToStr(toVMap());
}

QVariantMap TaskLog::toVMap() {
    QVariantMap m;
    m.insert("id", id);
    m.insert("xmid", xmid);
    m.insert("ct", ct);
    m.insert("cont", cont);
    return m;
}
