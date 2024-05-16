#include "future.h"
#include <QMutex>

Future::Future() {
}
QVariantList Future::getList(uint timeout) {
    if (!sem.tryAcquire(1, timeout)) {
        return QVariantList(); // 超时返回空 QVariantList
    }
    QMutexLocker locker(&mtx); // RAII lock
    return res;
}
void Future::set(const QVariant& v) {
    QMutexLocker locker(&mtx); // RAII lock
    res << v;
    sem.release(1);
}
QVariant Future::get(uint timeout, QVariant def) {
    if (!sem.tryAcquire(1, timeout)) {
        return def; // 超时返回空 QVariant
    }

    QMutexLocker locker(&mtx); // RAII lock
    if (res.isEmpty()) {
        return def; // 防止并发情况下的异常返回
    }

    QVariant result = res.first();
    res.removeFirst();
    return result;
}
void Future::setList(const QVariantList& newRes) {
    QMutexLocker locker(&mtx); // RAII lock
    res = newRes;
    sem.release(1);
}
