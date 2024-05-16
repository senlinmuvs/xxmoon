#include "timer.h"
#include <QDebug>
#include "com/global.h"
#include "com/script.h"

Timer::Timer() : QObject() {
}
Timer::~Timer() {
    delete workerSync;
    delete timerSync;
    delete threadSync;
    delete workerScript;
    delete timerScript;
    delete threadScript;
}
void Timer::init() {
    threadSync = new QThread(this);
    timerSync = new QTimer();
    workerSync = new Worker();
    workerSync->moveToThread(threadSync);
    timerSync->moveToThread(threadSync);
    timerSync->setSingleShot(true);
    connect(timerSync, &QTimer::timeout, workerSync, [&]{
        if(!cfg->syncUrl.isEmpty()) {
            sy->start();
        }
        timerSync->start(2*1000);
    });
    connect(threadSync, &QThread::started, timerSync, [&]{
        timerSync->start(2*1000);
    });
    threadSync->start();

    //
    threadScript = new QThread(this);
    workerScript = new Worker();
    timerScript = new QTimer();
    workerScript->moveToThread(threadScript);
    timerScript->moveToThread(threadScript);
    timerScript->setSingleShot(true);
    connect(timerScript, &QTimer::timeout, workerScript, [&]{
        Script::INS().checkAndRun();
        timerScript->start(10*1000);
    });
    connect(threadScript, &QThread::started, timerScript, [&]{
        timerScript->start(10*1000);
    });
    threadScript->start();
}

void Timer::close() {
    lg->info("close timer");
    QMetaObject::invokeMethod(timerSync, "stop", Qt::QueuedConnection);
    lg->info("timerSync stop");
    //thread是timer的线程不能在别的线程里执行quit，和stop一样
    QMetaObject::invokeMethod(threadSync, "quit", Qt::QueuedConnection);
    lg->info("threadSync quit");
    threadSync->terminate();
    QMetaObject::invokeMethod(timerScript, "stop", Qt::QueuedConnection);
    lg->info("timerScript stop");
    //thread是timer的线程不能在别的线程里执行quit，和stop一样
    QMetaObject::invokeMethod(threadScript, "quit", Qt::QueuedConnection);
    lg->info("timerScript quit");
    threadScript->terminate();
}
