#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimer>

class Timer : public QObject {
    Q_OBJECT
private:
    explicit Timer(QObject *parent = nullptr);

    QThread* threadSych;
    QTimer *timerSych;
    QThread* threadScript;
    QTimer *timerScript;

public:
    static Timer& INS() {
        static Timer ins;
        return ins;
    }

    void init();
    void onTriggeredSych();
    void onTriggeredScript();
    void close();
};

#endif // TIMER_H
