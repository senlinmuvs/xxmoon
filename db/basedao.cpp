#include "basedao.h"

BaseDao::BaseDao() {
    this->mutex = new QMutex();
}
BaseDao::~BaseDao(){
    delete mutex;
};

void BaseDao::init() {
    maxid = getMaxId();
}
uint BaseDao::increID() {
    this->mutex->lock();
    maxid++;
    this->mutex->unlock();
    return maxid;
}
