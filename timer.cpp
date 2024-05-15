#include "timer.h"
#include <QDebug>
#include "com/global.h"

Timer::Timer(QObject *parent) : QObject(parent) {
}

void Timer::init() {
    threadSych = new QThread(this);
    timerSych = new QTimer(this);
    this->moveToThread(threadSych);
    timerSych->moveToThread(threadSych);
    connect(timerSych, &QTimer::timeout, this, &Timer::onTriggeredSych);
    timerSych->setSingleShot(true);
    connect(threadSych, &QThread::started, timerSych, [&]() {
        timerSych->start(2*1000);
    });
    threadSych->start();

    //
    // threadScript = new QThread(this);
    // timerScript = new QTimer(this);
    // timerScript->moveToThread(threadScript);
    // connect(timerScript, &QTimer::timeout, this, &Timer::onTriggeredScript);
    // connect(threadScript, &QThread::started, timerScript, [&]() {
    //     timerScript->start(10*1000);
    // });
    // threadScript->start();
}

void Timer::onTriggeredSych() {
    if(!cfg->syncUrl.isEmpty()) {
        sy->start();
    }
    timerSych->start(2*1000);
}

void Timer::onTriggeredScript() {
    qDebug() << "onTriggeredScript";
}

void Timer::close() {
    QMetaObject::invokeMethod(timerSych, "stop", Qt::QueuedConnection);
    //thread是timer的线程不能在别的线程里执行quit，和stop一样
    QMetaObject::invokeMethod(threadSych, "quit", Qt::QueuedConnection);
    if (QThread::currentThread() != threadSych) {
        threadSych->wait();
    }

    // QMetaObject::invokeMethod(timerScript, "stop", Qt::QueuedConnection);
    // //thread是timer的线程不能在别的线程里执行quit，和stop一样
    // QMetaObject::invokeMethod(threadScript, "quit", Qt::QueuedConnection);
    // if (QThread::currentThread() != threadScript) {
    //     threadScript->wait();
    // }
}
