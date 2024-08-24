#ifndef TASKLOG_H
#define TASKLOG_H

#include <QString>

class TaskLog {
public:
    TaskLog();

    uint id;
    uint xmid;
    qint64 ct;
    QString cont;

    QString toString();
    QVariantMap toVMap();
};

#endif // TASKLOG_H
