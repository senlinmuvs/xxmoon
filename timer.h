#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimer>

class Timer : public QObject {
    Q_OBJECT
private:
    explicit Timer(QObject *parent = nullptr);

    QThread* thread;
    QTimer *timer;

public:
    static Timer& INS() {
        static Timer ins;
        return ins;
    }

    void init();
    void onTriggered();
    void close();
};

#endif // TIMER_H
