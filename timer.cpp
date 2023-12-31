#include "timer.h"
#include "com/util.h"
#include "com/log.h"
#include <QDebug>
#include "com/global.h"

Timer::Timer(QObject *parent) : QObject(parent) {
}
Timer::~Timer() {
    delete timer;
}

void Timer::init() {
//    timer = new QTimer();
//    connect(timer, &QTimer::timeout, this, &Timer::onTriggered);
//    timer->start(5*60*1000);
//    timer->start(5*1000);
}

void Timer::onTriggered() {
    ensure("是否购买永久使用授权?");
}
