#include "timer.h"
#include <QDebug>
#include "com/global.h"

Timer::Timer(QObject *parent) : QObject(parent) {
}

void Timer::init() {
    QThread* thread = new QThread(this);
    timer = new QTimer(this);
    this->moveToThread(thread);
    timer->moveToThread(thread);
    connect(timer, &QTimer::timeout, this, &Timer::onTriggered);
    timer->setSingleShot(true);
    connect(thread, &QThread::started, timer, [&]() {
        timer->start(2*1000);
    });
    thread->start();
}

void Timer::onTriggered() {
    if(!cfg->syncUrl.isEmpty()) {
        sy->start();
    }
    timer->start(2*1000);
}
