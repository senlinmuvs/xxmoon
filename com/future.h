#ifndef FUTURE_H
#define FUTURE_H

#include <QString>
#include <QSemaphore>
#include <iostream>
#include <QVariantList>
#include "global.h"
#include "const.h"

class Future {
public:
    Future();
    ~Future();
private:
    QSemaphore* waitingResult;
    QVariantList res;
    QRecursiveMutex* mtx;

public:
    QVariantList get();
    QVariant getVar();
    void setVar(QVariant v);
    void set(QVariantList res = QVariantList());
};

namespace future {
    extern Future* doDB(CB_VAR cb);
}

#endif // FUTURE_H
