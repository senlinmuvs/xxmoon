#include "sm.h"
#include "com/const.h"

SM::SM() {
    qsm = new QSharedMemory();
}

bool SM::createShareMemory() {
    qsm->setKey(SM_FLAG);
    if (qsm->attach(QSharedMemory::ReadOnly)){
        qsm->detach();
    }
    return qsm->create(1);
}

void SM::close() {
    qsm->detach();
    delete qsm;
}
