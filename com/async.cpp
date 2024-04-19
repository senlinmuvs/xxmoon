#include "async.h"
#include "com/global.h"
#include <QMutex>

Async::Async(QString name) : QThread() {
    this->name = name;
    this->queue = new std::queue<Task>();
    this->mutex = new QMutex();
}

Async::~Async() {
    delete mutex;
    delete queue;
}

void Async::exe(QString tag, std::function<void()> cb) {
    if(!running) {
        lg->warn(QString("put async task stop name[%1] tag[%2] queue size %3").arg(name).arg(tag).arg(queue->size()));
        return;
    }
    bool b = mutex->tryLock(5000);
    if(b) {
        queue->push(Task(tag, cb));
        if(lg->isTrace()) {
            lg->trace(QString("put async task name[%1] tag[%2] queue size %3").arg(name).arg(tag).arg(queue->size()));
        }
        QString threadText = QStringLiteral("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
        condNotEmpty.wakeAll();
        mutex->unlock();
    } else {
        lg->warn(QString("put async task name[%1] tag[%2] lock timeout queue size %3").arg(name).arg(tag).arg(queue->size()));
    }
}
void Async::run() {
    lg->info(QString("%1 start").arg(name));
    while (running) {
        bool b = mutex->tryLock(5000);
        if(b) {
            if(queue->empty()) {
                if(lg->isTrace()) {
                    lg->trace(QString("async task name[%1] queue empty wait running=%2").arg(name).arg(running));
                }
                condNotEmpty.wait(mutex);
                mutex->unlock();
                if(lg->isTrace()) {
                    lg->trace(QString("async task name[%1] unlock running=%2 queue size %3").arg(name).arg(running).arg(queue->size()));
                }
            } else {
                Task t = queue->front();
                if(lg->isTrace()) {
                    lg->trace(QString("async task name[%1] tag[%2] start running=%3 queue size %4").arg(name).arg(t.tag).arg(running).arg(queue->size()));
                }
                queue->pop();
                mutex->unlock();
                t.cb();
                if(lg->isTrace()) {
                    lg->trace(QString("async task name[%1] tag[%2] end running=%3 queue size %4").arg(name).arg(t.tag).arg(running).arg(queue->size()));
                }
            }
        } else {
            lg->warn(QString("async task lock timeout %1 queue size %2").arg(name).arg(queue->size()));
        }
    }
}

void Async::close() {
    exe("close", [this]() {
        running = false;
    });
//    condNotEmpty.wakeAll();
}
