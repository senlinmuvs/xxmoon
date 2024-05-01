#include "timer.h"
#include <QDebug>
#include "com/global.h"

Timer::Timer(QObject *parent) : QObject(parent) {
}
Timer::~Timer() {
    delete timer;
}

void Timer::init() {
   timer = new QTimer();
   connect(timer, &QTimer::timeout, this, &Timer::onTriggered);
   timer->setSingleShot(true);
   timer->start(2*1000);
}

void Timer::onTriggered() {
    if(!cfg->syncUrl.isEmpty()) {
        sy->start();
    }
    timer->start(2*1000);
}
