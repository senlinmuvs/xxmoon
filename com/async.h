#ifndef ASYNCQUEUE_H
#define ASYNCQUEUE_H

#include <QThread>
#include <queue>
#include <iostream>
#include <QString>
#include <QWaitCondition>

class Async: public QThread {
public:
    Async(QString name);
    ~ Async();
    void exe(std::function<void()> cb);
    void run();
    void close();

private:
    bool running = true;
    QString name;
    std::queue<std::function<void()>> *queue;
    QWaitCondition condNotEmpty;
    QMutex *mutex;
};

#endif // ASYNCQUEUE_H
