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
    int colFro = rec.indexOf("fro");
    int colTag = rec.indexOf("tag");
    int colExtra = rec.indexOf("extra");
    if(q->next()) {
        uint id = q->value(colId).toUInt();
        QString name = q->value(colWork).toString();
        QString author = q->value(colAuthor).toString();
        uint time = q->value(colTime).toUInt();
        uint t = q->value(colT).toUInt();
        uint fro = q->value(colFro).toUInt();
        QString tag = q->value(colTag).toString();
        QString extra = q->value(colExtra).toString();
        Work *w = new Work();
        w->id = id;
        w->name = name;
        w->author = author;
        w->time = time;
        w->t = t;
        w->fro = fro;
        w->tag = tag;
        w->extra = extra;
        list << w;
    }
    return list;
}
Work* WorkDao::get(QString name, QString author) {
    QSqlQuery q;
    q.prepare("select id,name,author,time,t,fro,tag,extra from work where name=:name and author=:author limit 1");
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
Work* WorkDao::get(QString name) {
    QSqlQuery q;
    q.prepare("select id,name,author,time,t,fro,tag,extra from work where name=:name limit 1");
    q.bindValue(":name", name);
    bool suc = q.exec();
    if(!suc) {
        lg->error(QString("get work by name error %1").arg(q.lastError().text()));
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
    QString sql = "update work set name=:name, author=:author, time=:time, t=:t, tag=:tag, extra=:extra where id=:id";
    db->execute("update work", sql, [=](QSqlQuery q) {
        q.bindValue(":id", w->id);
        q.bindValue(":name", w->name);
        q.bindValue(":author", w->author);
        q.bindValue(":time", w->time);
        q.bindValue(":t", w->t);
        q.bindValue(":tag", w->tag);
        q.bindValue(":extra", w->extra);
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
    QString insert_sql = "insert into work(id,name,author,time,t,fro,tag,extra) values(:id,:name,:author,:time,:t,:fro,:tag,:extra)";
    db->execute("add work", insert_sql, [&w](QSqlQuery q) {
        q.bindValue(":id", w->id);
        q.bindValue(":name", w->name);
        q.bindValue(":author", w->author);
        q.bindValue(":time", w->time);
        q.bindValue(":t", w->t);
        q.bindValue(":fro", w->fro);
        q.bindValue(":tag", w->tag);
        q.bindValue(":extra", w->extra);
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
QList<QString> WorkDao::getWorkTagList() {
    QSqlQuery q;
    q.prepare("select tag from work");
    bool suc = q.exec();
    QList<QString> list;
    if(!suc) {
        lg->error(QString("getWorkTagList error %1").arg(q.lastError().text()));
        return list;
    }
    while(q.next()) {
        QString tag = q.value(0).toString().trimmed();
        if(!tag.isEmpty()) {
            list << tag;
        }
    }
    return list;
}
uint WorkDao::count() {
    QSqlQuery q;
    q.prepare("select count(*) from work");
    bool ok = q.exec();
    if(!ok) {
        lg->error(QString("count error %1").arg(q.lastError().text()));
        return 0;
    }
    if(q.next()) {
        return q.value(0).toUInt();
    }
    return 0;
}
