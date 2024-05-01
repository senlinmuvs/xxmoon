#ifndef FILEQUEUE_H
#define FILEQUEUE_H

#include "com/const.h"
#include <QMutex>
#include <QString>

class FileQueue {

private:
    QString file;
    QMutex mtx;

    const QString POSTFIX_DOLOGX = "x";
    const QString POSTFIX_DOLOGXN = "xn";

public:
    explicit FileQueue(const QString& file);

    void enqueue(const QString& msg);
    void dequeue(CB_BL_STR cb);
};

#endif // FILEQUEUE_H
