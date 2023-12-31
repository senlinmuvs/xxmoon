#include "workdao.h"
#include "com/global.h"

WorkDao::WorkDao() : BaseDao() {
}

QList<Work*> gets(QSqlQuery *q) {
    QSqlRecord rec = q->record();
    QList<Work*> list;
    int colId = rec.indexOf("id");
    int colWork = rec.indexOf("name");
    int colAuthor = rec.indexOf("author");
    int colTime= rec.indexOf("time");
    int colT = rec.indexOf("t");
    if(q->next()) {
        uint id = q->value(colId).toUInt();
        QString name = q->value(colWork).toString();
        QString author = q->value(colAuthor).toString();
        uint time = q->value(colTime).toUInt();
        uint t = q->value(colT).toUInt();
        Work *w = new Work();
        w->id = id;
        w->name = name;
        w->author = author;
        w->time = time;
        w->t = t;
        list.insert(list.end(), w);
    }
    return list;
}
Work* WorkDao::get(QString name, QString author) {
    QSqlQuery q;
    q.prepare("select id,name,author,time,t from work where name=:name and author=:author");
    q.bindValue(":name", name);
    q.bindValue(":author", author);
    bool suc = q.exec();
    if(!suc) {
        lg->error(QString("get work error %1").arg(q.lastError().text()));
        return NULL;
    }
    QList<Work*> list = gets(&q);
    if(list.size() > 0) {
        return list.at(0);
    }
    return NULL;
}
Work* WorkDao::get(uint id) {
    QSqlQuery q;
    q.prepare("select * from work where id=:id");
    q.bindValue(":id", id);
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("get work error %1").arg(q.lastError().text()));
        return NULL;
    }
    QList<Work*> list = gets(&q);
    if(list.size() > 0) {
        return list.at(0);
    }
    return NULL;
}
void WorkDao::del(uint id) {
    db->execute("del work", "delete from work where id=:id", [=](QSqlQuery q) {
        q.bindValue(":id", id);
    });
}
void WorkDao::update(Work *w) {
    QString sql = "update work set name=:name, author=:author, time=:time, t=:t where id=:id";
    db->execute("update work", sql, [=](QSqlQuery q) {
        q.bindValue(":id", w->id);
        q.bindValue(":name", w->name);
        q.bindValue(":author", w->author);
        q.bindValue(":time", w->time);
        q.bindValue(":t", w->t);
    });
}
uint WorkDao::getMaxId() const {
    QSqlQuery q("select max(id) as maxid from work");
    q.exec();
    QSqlRecord rec = q.record();
    int colMaxid = rec.indexOf("maxid");
    if(q.next()) {
        return q.value(colMaxid).toUInt();
    }
    return 0;
}
void WorkDao::add(Work *w) {
    if(w->id <= 0) {
        w->id = increID();
    }
    if(w->time == 0) {
        w->time = ut::time::getCurSeconds();
    }
    if(lg->isDebug()) {
        lg->trace(QString("add work %1").arg(w->toString()));
    }
    QString insert_sql = "insert into work(id,name,author,time,t) values(:id,:name,:author,:time,:t)";
    db->execute("add work", insert_sql, [&w](QSqlQuery q) {
        q.bindValue(":id", w->id);
        q.bindValue(":name", w->name);
        q.bindValue(":author", w->author);
        q.bindValue(":time", w->time);
        q.bindValue(":t", w->t);
    });
}

void WorkDao::add(const QList<Work*> &list) {
    if(db->transaction()) {
        for(Work* w : list) {
            add(w);
        }
        if(!db->commit()) {
            db->rollback();
            lg->error(QString("add works error %1").arg(list.size()));
        }
    } else {
        lg->error(QString("add workds failed to start transaction mode %1").arg(list.size()));
    }
}
