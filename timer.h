#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimer>

class Timer : public QObject {
    Q_OBJECT
private:
    explicit Timer(QObject *parent = nullptr);
    ~Timer();

public:
    static Timer& INS() {
        static Timer ins;
        return ins;
    }

     QTimer *timer;
     void init();
     void onTriggered();
signals:
};

#endif // TIMER_H
