#include "notedao.h"
#include "com/global.h"
#include "com/const.h"
#include "com/util.h"

NoteDao::NoteDao(): BaseDao() {
}

QList<Note*> gets(QSqlQuery q) {
    QList<Note*> list;
    QSqlRecord rec = q.record();
    int colId = rec.indexOf("id");
    int colWid = rec.indexOf("wid");
    int colPos0 = rec.indexOf("pos0");
    int colPos1 = rec.indexOf("pos1");
    int colTime= rec.indexOf("time");
    int colCont = rec.indexOf("cont");
    int colTags = rec.indexOf("tags");
    int colRefids = rec.indexOf("refids");
    int colRefimgids = rec.indexOf("refimgids");
    while (q.next()) {
        uint id = q.value(colId).toUInt();
        uint wid = q.value(colWid).toUInt();
        uint pos0 = q.value(colPos0).toUInt();
        uint pos1 = q.value(colPos1).toUInt();
        uint time = q.value(colTime).toUInt();
        QString cont = q.value(colCont).toString();
        QString tags = q.value(colTags).toString();
        QString refids = q.value(colRefids).toString();
        QString refimgids = q.value(colRefimgids).toString();
        Note *n = new Note();
        n->id = id;
        n->wid = wid;
        n->pos0 = pos0;
        n->pos1 = pos1;
        n->time = time;
        n->cont = cont;
        n->tags = tags;
        n->refids = refids;
        n->refimgids = refimgids;
        list.insert(list.end(), n);
    }
    return list;
}
Note* NoteDao::get(uint id) {
    QSqlQuery q;
    q.prepare("select * from note where id=:id");
    q.bindValue(":id", id);
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("get note error %1").arg(q.lastError().text()));
    }
    QList<Note*> list = gets(q);
    if(list.size() > 0) {
        return list.first();
    }
    return nullptr;
}
uint NoteDao::getIdByTime(qint64 time) {
    QSqlQuery q;
    q.prepare("select id from note where time=:time");
    q.bindValue(":time", time);
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("get note error %1").arg(q.lastError().text()));
    }
    if(q.next()) {
        return q.value(0).toUInt();
    } else {
        return 0;
    }
}

void NoteDao::insert(Note *n) {
    if(n->id <= 0) {
        n->id = increID();
    }
    QString insert_sql = "insert into note(id, wid, pos0, pos1, time, cont, tags, refids,refimgids) "
                        "values(:id,:wid,:pos0,:pos1,:time,:cont, :tags,:refids,:refimgids);";
    if(n->refids.isEmpty()){
        n->refids = extractRefIDs(n->cont);
    }
    if(n->refimgids.isEmpty()){
        n->refimgids = extractRefimgids(n->cont);
    }
    db->execute("insert note", insert_sql, [&n](QSqlQuery q) {
        q.bindValue(":id", n->id);
        q.bindValue(":wid", n->wid);
        q.bindValue(":pos0", n->pos0);
        q.bindValue(":pos1", n->pos1);
        q.bindValue(":time", n->time);
        q.bindValue(":cont", n->cont.isNull() ? "" : n->cont);
        q.bindValue(":tags", n->tags.isNull() ? "" : n->tags);
        q.bindValue(":refids", n->refids.isNull() ? "" : n->refids);
        q.bindValue(":refimgids", n->refimgids.isNull() ? "" : n->refimgids);
    });
}

QList<Note*> NoteDao::insert(QList<Note*> notes, std::function<void (int)> cb) {
    QList<Note*> dups;
    if(db->transaction()) {
        QString sql = "insert into note(id, wid, pos0, pos1, time, cont, tags, refids, refimgids)values(?,?,?,?,?,?,?,?,?)";
        QSqlQuery q;
        q.prepare(sql);
        int i = 0;
        for(Note* n:notes) {
            qint64 t1 = QDateTime::currentDateTime().currentMSecsSinceEpoch();
            if(n->id <= 0) {
                n->id = increID();
            }
            if(n->refids.isEmpty()){
                n->refids = extractRefIDs(n->cont);
            }
            if(n->refimgids.isEmpty()){
                n->refimgids = extractRefimgids(n->cont);
            }
            if(lg->isDebug()) {
                lg->trace(QString("insert note %1").arg(n->toString()));
            }
            q.addBindValue(n->id);
            q.addBindValue(n->wid);
            q.addBindValue(n->pos0);
            q.addBindValue(n->pos1);
            q.addBindValue(n->time);
            q.addBindValue(n->cont.isNull() ? "" : n->cont);
            q.addBindValue(n->tags.isNull() ? "" : n->tags);
            q.addBindValue(n->refids.isNull() ? "" : n->refids);
            q.addBindValue(n->refimgids.isNull() ? "" : n->refimgids);
            bool st = q.exec();
            if(!st) {
                QString err = q.lastError().text();
                lg->error(QString("insert note(%1) error: %2").arg(n->toString()).arg(err));
                if(err.contains("UNIQUE constraint failed")) {
                    dups << n;
                }
            }
            qint64 t2 = QDateTime::currentDateTime().currentMSecsSinceEpoch();
            if(lg->isDebug()){
                lg->debug(QString("insert %1 cost %2 ms st %3").arg(n->id).arg(t2-t1).arg(st));
            }
            cb(i);
            i++;
        }
        db->commit();
    } else {
         lg->error("insert note failed to start transaction mode");
    }
    return dups;
}
uint NoteDao::getMaxId() const {
    QSqlQuery q("select max(id) as maxid from note");
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("get getMaxId error %1").arg(q.lastError().text()));
    }
    QSqlRecord rec = q.record();
    int colMaxid = rec.indexOf("maxid");
    q.next();
    uint maxid = q.value(colMaxid).toUInt();
    return maxid;
}
QVariantList filterK(QString k) {
    QString k1 = k.trimmed(), k2 = "";
    bool searchAuthor = k.startsWith("a ");
    bool searchBook = k.startsWith("b ");
    if(searchAuthor || searchBook) {
        QString tmp = k.mid(2).trimmed();
        int i = tmp.indexOf(" ");
        if(i >= 0) {
            k1 = tmp.mid(0, i);
            k2 = tmp.mid(i+1);
        } else {
            k1 = tmp;
        }
    }
    return {searchAuthor, searchBook, k1, k2};
}
QString getSearchCondSql1(QString k) {
    QString sql = "(";
    QStringList arr = k.split(" ");
    for(int i = 0; i < arr.length(); i++) {
        sql += "cont like '%" + arr[i] + "%' and ";
    }
    sql = sql.mid(0, sql.length()-5);
    return sql + ")";
}
vector<Work> NoteDao::getWorkList(QString k, ulong fromTime) {
    vector<Work> list;
    ///
    QVariantList v = filterK(k);
    bool searchAuthor = v[0].toBool();
    bool searchBook = v[1].toBool();
    QString k1 = v[2].toString();
    QString k2 = v[3].toString();
    bool hasK = k1.length() > 0;
    QString sql;
    QString pageSize = QString::number(PAGE_SIZE);
    if(hasK) {
        sql = "select w.id, w.name,author,w.time,count(*) as c from note n join work w on w.id=n.wid where del=0 #cond_time #cont #tags group by n.wid order by n.time desc limit "+ pageSize;
        if(searchAuthor) {
            if(k2.length() > 0) {
                sql = sql.replace("#cont", "and w.author like :k1 and cont like :k2");
                sql = sql.replace("#tags", "");
            } else {
                sql = sql.replace("#cont", "and w.author like :k1");
                sql = sql.replace("#tags", "");
            }
        } else if(searchBook) {
            if(k2.length() > 0) {
                sql = sql.replace("#cont", "and w.name like :k1 and cont like :k2");
                sql = sql.replace("#tags", "");
            } else {
                sql = sql.replace("#cont", "and w.name like :k1");
                sql = sql.replace("#tags", "");
            }
         } else {
            QVariantList ks = parseKeyTags(k);
            QStringList tags = ks[0].toStringList();
            if(tags.length() > 0) {
                QString tagCond = tagDao->getTagCondByTags(tags);
                sql = sql.replace("#tags", tagCond);
                QString newK = ks[1].toString();
                if(newK.length() > 0) {
                    sql = sql.replace("#cont", "and cont like :k1");
                    k1 = newK;
                } else {
                    hasK = false;
                    sql = sql.replace("#cont", "");
                }
            } else {
                sql = sql.replace("#tags", "");
                sql = sql.replace("#cont", "and cont like :k1");
            }
        }
        if(fromTime > 0){
            sql.replace("#cond_time", "and n.time<:time");
        } else {
            sql.replace("#cond_time", "");
        }
    } else {
        sql =
        "select t1.*,t2.c from "
            "(select id,name,author,`time` from work #cond_time_t1) t1 "
        "left outer join "
            "(select wid, w.name,author,w.time,count(*) as c from note n join work w on w.id=n.wid where del=0 #cond_time_t2 group by n.wid) t2 "
        "on t1.id = t2.wid "
        "order by t1.time desc limit "+pageSize;
        if(fromTime > 0) {
            sql.replace("#cond_time_t1", "where `time`<:time");
            sql.replace("#cond_time_t2", "and n.time<:time");
        } else {
            sql.replace("#cond_time_t1", "");
            sql.replace("#cond_time_t2", "");
        }
    }
    ///
    QSqlQuery q;
    q.prepare(sql);
    if(fromTime > 0) {
        q.bindValue(":time", uint(fromTime));
    }
    q.bindValue(":size", PAGE_SIZE);
    if(hasK) {
        q.bindValue(":k1", "%"+k1+"%");
        if(k2.length()>0) {
            q.bindValue(":k2", "%"+k2+"%");
        }
    }
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("get getWorkList error %1").arg(q.lastError().text()));
    }
    QSqlRecord rec = q.record();
    int colId = rec.indexOf("id");
    int colBook = rec.indexOf("name");
    int colAuthor = rec.indexOf("author");
    int colTime = rec.indexOf("time");
    int colC= rec.indexOf("c");
    while (q.next()) {
        uint id = q.value(colId).toUInt();
        QString book = q.value(colBook).toString();
        QString author = q.value(colAuthor).toString();
        uint time = q.value(colTime).toUInt();
        uint c= q.value(colC).toUInt();
        Work w;
        w.id = id;
        w.time = time;
        w.total = c;
        w.author = author;
        w.name = book;
        list.insert(list.end(), w);
    }
//    qDebug() << sql << k1 << k2 << k << fromTime;
    return list;
}

QList<Note*> NoteDao::getNoteList(QString k, uint wid, uint page, QString sort) {
    QString sql = "select n.id,wid,pos0,pos1,n.time,cont,tags,bj,refids,refimgids from note n join work w on w.id=n.wid where del=0 and n.wid=:wid #cont #tags order by #sort limit :start,:size";
    ///
    bool sortByPos = sort == "p";
    if(sortByPos) {
        sql = sql.replace("#sort", "pos0 asc,n.time asc");
    } else {
        sql = sql.replace("#sort", "n.time desc");
    }

    QVariantList v = filterK(k);
    bool searchAuthor = v[0].toBool();
    bool searchBook = v[1].toBool();
    QString k1 = v[2].toString();
    QString k2 = v[3].toString();
    bool hasK = k1.length() > 0;
//    qDebug() << searchAuthor << searchBook << k1 << k2 << hasK;
    if(hasK) {
        if(!searchAuthor && !searchBook) {
            k = k1;
            QVariantList ks = parseKeyTags(k);
            QStringList tags = ks[0].toStringList();
            if(tags.length() > 0) {
                QString tagCond = tagDao->getTagCondByTags(tags);
                sql = sql.replace("#tags", tagCond);
                QString newK = ks[1].toString();
                if(newK.length() > 0) {
                    sql = sql.replace("#cont", "and cont like :k");
                    k = newK;
                } else {
                    hasK = false;
                    sql = sql.replace("#cont", "");
                }
            } else {
                sql = sql.replace("#cont", "and cont like :k");
                sql = sql.replace("#tags", "");
            }
        } else {
            if(k2.length()>0) {
                k = k2;
                sql = sql.replace("#cont", "and cont like :k");
                sql = sql.replace("#tags", "");
            } else {
                sql = sql.replace("#cont", "");
                sql = sql.replace("#tags", "");
                hasK = false;
            }
        }
    } else {
        sql = sql.replace("#cont", "");
        sql = sql.replace("#tags", "");
    }
    QSqlQuery q;
    q.prepare(sql);
    q.bindValue(":wid", wid);
    uint size = PAGE_SIZE;
    uint start = page * size;
    q.bindValue(":start", start);
    q.bindValue(":size", size);
    if(hasK) {
        q.bindValue(":k", "%"+k+"%");
    }
    bool suc = q.exec();
    if(!suc) {
        lg->error(QString("getNoteList error %1").arg(q.lastError().text()));
    }
    QList<Note*> list = gets(q);
//    qDebug() << sql;
//    qDebug() << k << wid << page << start << sort << list.size();
    return list;
}

void NoteDao::updateNote(uint id, uint pos0, uint pos1, QString cont) {
    QString refids = extractRefIDs(cont);
    QString refimgids = extractRefimgids(cont);
    db->execute("upateNote", "update note set cont=:cont,pos0=:pos0,pos1=:pos1,refids=:refids,refimgids=:refimgids where id=:id", [=](QSqlQuery q) {
        q.bindValue(":id", id);
        q.bindValue(":pos0", pos0);
        q.bindValue(":pos1", pos1);
        q.bindValue(":cont", cont.isNull() ? "" : cont);
        q.bindValue(":refids", refids.isNull() ? "" : refids);
        q.bindValue(":refimgids", refimgids.isNull() ? "" : refimgids);
    });
}
void NoteDao::updateTags(uint id, QString tags) {
    db->execute("updateTags", "update note set tags=:tags where id=:id", [=](QSqlQuery q) {
        q.bindValue(":tags", tags.toStdString().c_str());
        q.bindValue(":id", id);
    });
}
void NoteDao::deleteNote(uint id) {
    db->execute("deleteNote", "update note set del=1,pos0=0,pos1=0,cont='' where id=:id", [id](QSqlQuery q){
        q.bindValue(":id", id);
    });
}
void NoteDao::deleteNote_(uint id) {
    db->execute("deleteNote_", "delete from note where id=:id", [id](QSqlQuery q){
        q.bindValue(":id", id);
    });
}
