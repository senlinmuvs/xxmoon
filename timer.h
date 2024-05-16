#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimer>

class Worker: public QObject {
    Q_OBJECT
public:
    explicit Worker(QObject *parent=nullptr):QObject(parent){};
};

class Timer : public QObject {
    Q_OBJECT
private:
    explicit Timer();
    ~Timer();

    QThread* threadSync;
    QTimer *timerSync;
    Worker *workerSync;

    QThread* threadScript;
    QTimer *timerScript;
    Worker *workerScript;

public:
    static Timer& INS() {
        static Timer ins;
        return ins;
    }

    void init();
    void close();
};
#endif // TIMER_H
