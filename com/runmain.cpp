#include "runmain.h"
#include <QCoreApplication>
#include <QThread>

RunMain::RunMain(QObject *parent): QObject(parent) {

}

void RunMain::init() {
    connect(this, SIGNAL(comming(std::function<void()>)),
            this, SLOT(exec(std::function<void()>)),
            Qt::BlockingQueuedConnection);
}
void RunMain::exec(std::function<void()> f) {
    QThread* mainThread = QCoreApplication::instance()->thread();
    QThread* curThread = QThread::currentThread();
    if(mainThread == curThread) {
        f();
    } else {
        emit this->comming(f);
    }
}
