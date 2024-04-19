#ifndef ASYNCQUEUE_H
#define ASYNCQUEUE_H

#include <QThread>
#include <queue>
#include <QString>
#include <QWaitCondition>

class Async: public QThread {
public:
    Async(QString name);
    ~ Async();
    void exe(QString tag, std::function<void()> cb);
    void run();
    void close();

private:

    class Task {
    public:
        Task(QString tag, std::function<void()> cb) {
            this->tag = tag;
            this->cb = cb;
        };
        QString tag;
        std::function<void()> cb;
    };

    bool running = true;
    QString name;
    std::queue<Task> *queue;
    QWaitCondition condNotEmpty;
    QMutex *mutex;
};

#endif // ASYNCQUEUE_H
