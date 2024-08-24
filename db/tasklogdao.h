#ifndef TASKLOGDAO_H
#define TASKLOGDAO_H

#include "basedao.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <model/tasklog.h>

class TaskLogDao : public BaseDao {
public:
    TaskLogDao();

    void add(uint xmid, QString cont);
    QString getLastLog(uint xmid);
    uint getMaxId() override;

private:
    QList<TaskLog> gets(QSqlQuery& q, QSqlRecord& rec);
};

#endif // TASKLOGDAO_H
