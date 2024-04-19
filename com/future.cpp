#include "future.h"
#include "log.h"
#include <QMutex>

Future::Future() {
    waitingResult = new QSemaphore();
    mtx = new QRecursiveMutex();
}

Future::~Future() {
    delete waitingResult;
    delete mtx;
}

QVariantList Future::get() {
    waitingResult->acquire(1);
//    Log::INS().debug(QString("get acq [%1]").arg(tag));
    mtx->lock();
//    Log::INS().debug(QString("lock [%1]").arg(tag));
    QVariantList v = res;
    mtx->unlock();
//    Log::INS().debug(QString("unlock [%1]").arg(tag));
    return v;
}

void Future::setVar(QVariant v) {
    mtx->lock();
    this->res << v;
    waitingResult->release(1);
    mtx->unlock();
}
QVariant Future::getVar() {
    waitingResult->acquire(1);
    mtx->lock();
    QVariantList v = res;
    return v.first();
    mtx->unlock();
}

void Future::set(QVariantList res) {
//    Log::INS().debug(QString("set lock [%1] mtx %2").arg(tag).arg(qintptr(mtx)));
    mtx->lock();
//    Log::INS().debug(QString("set lock [%1]").arg(tag));
    this->res = res;
    waitingResult->release(1);
//    Log::INS().debug(QString("release [%1]").arg(tag));
    mtx->unlock();
//    Log::INS().debug(QString("unlock [%1]").arg(tag));
}

namespace future {
    Future* doDB(CB_VAR cb) {
        Future* fu = new Future();
        DB_Async->exe("doDB", [fu, cb]() {
            QVariantList var = cb();
            fu->set(var);
        });
        return fu;
    }
}
