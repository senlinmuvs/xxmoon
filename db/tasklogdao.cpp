#include "tasklogdao.h"
#include "com/global.h"
#include "com/util.h"
#include "model/tasklog.h"

TaskLogDao::TaskLogDao() {}

QList<TaskLog> TaskLogDao::gets(QSqlQuery& q, QSqlRecord& rec) {
    QList<TaskLog> list;
    int colId = rec.indexOf("id");
    int colXmid = rec.indexOf("xmid");
    int colCt = rec.indexOf("ct");
    int colCont = rec.indexOf("cont");
    while(q.next()) {
        uint id = q.value(colId).toUInt();
        uint xmid = q.value(colXmid).toUInt();
        qint64 ct = q.value(colCt).toLongLong();
        QString cont = q.value(colCont).toString();
        TaskLog tl;
        tl.id = id;
        tl.xmid = xmid;
        tl.ct = ct;
        tl.cont = cont;
        list << tl;
    }
    return list;
}

void TaskLogDao::add(uint xmid, QString cont) {
    TaskLog tl;
    tl.id = increID();
    tl.xmid = xmid;
    tl.ct = ut::time::getCurSeconds();
    tl.cont = cont;
    QString sql = "insert into task_log(id, xmid, ct, cont) values(?,?,?,?)";
    QSqlQuery q;
    q.prepare(sql);
    q.addBindValue(tl.id);
    q.addBindValue(tl.xmid);
    q.addBindValue(tl.ct);
    q.addBindValue(tl.cont.isNull() ? "" : tl.cont);
    bool r = q.exec();
    if(!r) {
        lg->error(QString("add tasklog error %1 %2").arg(q.lastError().text(), tl.toString()));
        return;
    }
    dologTaskLogNew(tl.id);
}

uint TaskLogDao::getMaxId() {
    QSqlQuery q("select max(id) as maxid from task_log");
    bool r = q.exec();
    if(!r) {
        lg->error(QString("getMaxId task_log error %1").arg(q.lastError().text()));
        return 0;
    }
    QSqlRecord rec = q.record();
    int colMaxid = rec.indexOf("maxid");
    q.next();
    uint maxid = q.value(colMaxid).toUInt();
    return maxid;
}

QString TaskLogDao::getLastLog(uint xmid) {
    QSqlQuery q;
    q.prepare("select cont from task_log where xmid=:xmid order by ct desc limit 1");
    q.bindValue(":xmid", xmid);
    bool r = q.exec();
    if(!r) {
        lg->error(QString("getLastLog error %1 xmid %2").arg(q.lastError().text()).arg(xmid));
        return "";
    }
    if(q.next()) {
        return q.value(0).toString();
    }
    return "";
}
