#include "pkdao.h"
#include "com/global.h"
#include "com/util.h"

PKDao::PKDao() : BaseDao() {
}

QList<PK*> PKDao::gets(QSqlQuery q, QSqlRecord rec) {
    QList<PK*> list;
    int colId = rec.indexOf("id");
    int colCid = rec.indexOf("cid");
    int colCont = rec.indexOf("cont");
    int colImg = rec.indexOf("img");
    int colTime = rec.indexOf("time");
    int colLst = rec.indexOf("lst");
    int colStime = rec.indexOf("stime");
    int colTags = rec.indexOf("tags");
    int colBj = rec.indexOf("bj");
    int colJm = rec.indexOf("jm");
    int colRefids = rec.indexOf("refids");
    int colRefimgids = rec.indexOf("refimgids");
    while (q.next()) {
        uint id = q.value(colId).toUInt();
        uint cid = q.value(colCid).toUInt();
        QString cont = q.value(colCont).toString();
        QString img = q.value(colImg).toString();
        uint time = q.value(colTime).toUInt();
        uint lst = q.value(colLst).toUInt();
        uint stime = q.value(colStime).toUInt();
        QString tags = q.value(colTags).toString();
        bool bj = q.value(colBj).toBool();
        uint jm = q.value(colJm).toBool();
        QString refids = q.value(colRefids).toString();
        QString refimgids = q.value(colRefimgids).toString();
        PK *p = new PK();
        p->id = id;
        p->cid = cid;
        p->cont = cont;
        p->img = img;
        p->time = time;
        p->lst = lst;
        p->stime = stime;
        p->tags = tags;
        p->bj = bj;
        p->jm = jm;
        p->refids = refids;
        p->refimgids = refimgids;
        list.insert(list.end(), p);
    }
    return list;
}
void PKDao::add(PK *p) {
    if(p->id <= 0){
        p->id = increID();
    }
    if(p->refids.isEmpty()) {
        p->refids = extractRefIDs(p->cont);
    }
    if(p->refimgids.isEmpty()) {
        p->refimgids = extractRefimgids(p->refimgids);
    }
    //
    QString sql = "insert into pk(id, cid, cont, img, time, lst, stime, tags, bj, jm, refids, refimgids) values(?,?,?,?,?,?,?,?,?,?,?,?)";
    if(p->time <= 0) {
        p->time = ut::time::getCurSeconds();
    }
    QSqlQuery q;
    q.prepare(sql);
    q.addBindValue(p->id);
    q.addBindValue(p->cid);
    q.addBindValue(p->cont.isNull() ? "" : p->cont);
    q.addBindValue(p->img.isNull() ? "" : p->img);
    q.addBindValue(p->time);
    q.addBindValue(p->lst);
    q.addBindValue(p->stime);
    q.addBindValue(p->tags.isNull() ? "" : p->tags);
    q.addBindValue(p->bj);
    q.addBindValue(p->jm);
    q.addBindValue(p->refids.isNull() ? "" : p->refids);
    q.addBindValue(p->refimgids.isNull() ? "" : p->refimgids);
    bool r = q.exec();
    if(!r) {
        lg->error(QString("add pk error %1 %2").arg(q.lastError().text()).arg(p->toString()));
    }
}
QString getSearchCondSql0(QString k) {
    QString sql = "(";
    QStringList arr = k.split(" ");
    for(int i = 0; i < arr.length(); i++) {
        sql += "cont like '%" + arr[i] + "%' and ";
    }
    sql = sql.mid(0, sql.length()-5);
    return sql + ")";
}
QList<PK*> PKDao::getPKList(QString k, uint cid, uint fromId) {
    QString sql = "select id,cid,cont,img,time,lst,stime,tags,bj,jm,refids,refimgids from pk where cid=:cid #id #cont #tags order by id desc limit :size";
    bool hasK = k.length() > 0;
    if(hasK) {
        k = k.replace("'","");
        QVariantList ks = parseKeyTags(k);
        QStringList tags = ks[0].toStringList();
        if(tags.length() > 0) {
            QString tagCond = tagDao->getTagCondByTags(tags);
            sql = sql.replace("#tags", tagCond);
            QString newK = ks[1].toString();
            if(newK.length() > 0) {
                sql = sql.replace("#cont", "and " + getSearchCondSql0(newK) + " and jm=0");
                k = newK;
            } else {
//                hasK = false;
                sql = sql.replace("#cont", "");
            }
        } else {
            sql = sql.replace("#cont", "and "+ getSearchCondSql0(k) +" and jm=0");
            sql = sql.replace("#tags", "");
        }
    } else {
        sql = sql.replace("#cont", "");
        sql = sql.replace("#tags", "");
    }
    if(fromId > 0) {
        sql = sql.replace("#id", "and id<:id");
    } else {
        sql = sql.replace("#id", "");
    }

    //
    QSqlQuery q;
    q.prepare(sql);
    q.bindValue(":cid", cid);
    if(fromId > 0) {
        q.bindValue(":id", fromId);
    }
    q.bindValue(":size", PAGE_SIZE);
//    if(hasK) {
//        q.bindValue(":k", "%"+k+"%");
//    }
    bool r = q.exec();
    if(!r) {
        lg->error(QString("getPKList error %1 sql[%2]").arg(q.lastError().text()).arg(sql));
    }
    QSqlRecord rec = q.record();
    QList<PK*> list = gets(q, rec);
    if(lg->isDebug()) {
        lg->debug(QString("getPKList sql [%1] args [%2 %3 %4] res %5").arg(sql).arg(k).arg(cid).arg(fromId).arg(list.size()));
    }
    return list;
}

QList<PK*> PKDao::getNewPKList(uint cid, uint fromId) {
    QString sql = "select id,cid,cont,img,time,lst,stime,tags,bj,jm,refids,refimgids from pk where cid=:cid and id>:id order by id asc limit :size";
    QSqlQuery q;
    q.prepare(sql);
    q.bindValue(":cid", cid);
    q.bindValue(":id", fromId);
    q.bindValue(":size", PAGE_SIZE);
    bool r = q.exec();
    if(!r) {
        lg->error(QString("getNewPKList error %1").arg(q.lastError().text()));
    }
    QSqlRecord rec = q.record();
    return gets(q, rec);
}

uint PKDao::getMaxId() const {
    QSqlQuery q("select max(id) as maxid from pk");
    bool r = q.exec();
    if(!r) {
        lg->error(QString("getMaxId error %1").arg(q.lastError().text()));
    }
    QSqlRecord rec = q.record();
    int colMaxid = rec.indexOf("maxid");
    q.next();
    uint maxid = q.value(colMaxid).toUInt();
    return maxid;
}

PK* PKDao::getPK(uint id) {
    QSqlQuery q("select id,cid,cont,img,time,lst,stime,bj,tags,jm,refids,refimgids from pk where id=" + QString::number(id));
    bool r = q.exec();
    if(!r) {
        lg->error(QString("getPK error %1").arg(q.lastError().text()));
    }
    QSqlRecord rec = q.record();
    QList<PK*> list = gets(q, rec);
    if(list.size() > 0) {
        PK* pk = list.first();
        return pk;
    } else {
        return NULL;
    }
}
QString PKDao::getTags(uint id) {
    QSqlQuery q("select tags from pk where id=" + QString::number(id));
    bool r = q.exec();
    if(!r) {
        lg->error(QString("getTags error %1").arg(q.lastError().text()));
    }
    QSqlRecord rec = q.record();
    if(q.next()) {
        return q.value(0).toString();
    }
    return "";
}
void PKDao::deletePK(uint id) {
    db->execute("deletePK", "delete from pk where id=:id", [=](QSqlQuery q) {
        q.bindValue(":id", id);
    });
}
void PKDao::updatePK(uint id, QString cont, uint jm, uint lst) {
    QString refids = extractRefIDs(cont);
    QString refimgids = extractRefimgids(cont);
    if(lg->isDebug()){
        lg->trace(QString("updatePK id %1 cont %2 jm %3 lst %4").arg(id).arg(cont.length()).arg(jm).arg(lst));
    }
    db->execute("updatePK", "update pk set cont=:cont,lst=:lst,jm=:jm,refids=:refids,refimgids=:refimgids where id=:id", [=](QSqlQuery q) {
        q.bindValue(":id", id);
        q.bindValue(":lst", lst);
        q.bindValue(":cont", cont.isNull() ? "" : cont);
        q.bindValue(":jm", jm);
        q.bindValue(":refids", refids.isNull() ? "" : refids);
        q.bindValue(":refimgids", refimgids.isNull() ? "" : refimgids);
    });
}
void PKDao::updateCid(uint pkId, uint cid) {
    db->execute("updateCid", "update pk set cid=:cid where id=:id", [=](QSqlQuery q) {
        q.bindValue(":cid", cid);
        q.bindValue(":id", pkId);
    });
}
uint PKDao::countImgRefrence(QString imgLink) {
    QSqlQuery q;
    q.prepare("select count(*) as ref from pk where cont like :k");
    q.bindValue(":k", "%"+imgLink+"%");
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("countImgRefrence error %1").arg(q.lastError().text()));
    }
    QSqlRecord rec = q.record();
    int colRef = rec.indexOf("ref");
    q.next();
    uint cid = q.value(colRef).toUInt();
    return cid;
}

void PKDao::updatePKTags(uint pkid, QString tags) {
    db->execute("updatePKTags", "update pk set tags=:tags where id=:id", [=](QSqlQuery q) {
        q.bindValue(":tags", tags.toStdString().c_str());
        q.bindValue(":id", pkid);
    });
}

uint PKDao::countCol(uint cid) {
    QSqlQuery q;
    q.prepare("select count(*) as n from pk where cid=:cid");
    q.bindValue(":cid", cid);
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("countCol error %1").arg(q.lastError().text()));
    }
    QSqlRecord rec = q.record();
    if(q.next()){
        uint n = q.value(0).toUInt();
        return n;
    }
    return 0;
}

uint PKDao::getNextID(uint cid, uint id) {
    QSqlQuery q;
    q.prepare("select id from pk where cid=:cid and id>:id order by id limit 1");
    q.bindValue(":cid", cid);
    q.bindValue(":id", id);
    bool suc = q.exec();
    if(!suc) {
        lg->error(QString("getNextID error %1").arg(q.lastError().text()));
    }
    QSqlRecord rec = q.record();
    if(q.next()){
        uint id = q.value(0).toUInt();
        return id;
    } else {
        q.prepare("select id from pk where cid=:cid order by id limit 1");
        q.bindValue(":cid", cid);
        bool suc = q.exec();
        if(!suc){
            lg->error(QString("getNextID error %1").arg(q.lastError().text()));
        }
        QSqlRecord rec = q.record();
        if(q.next()){
            uint id = q.value(0).toUInt();
            return id;
        }
    }
    return 0;
}

uint PKDao::getIDByImg(QString img) {
    QSqlQuery q;
    q.prepare("select id from pk where img=:img");
    q.bindValue(":img", img);
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("getIDByImg error %1").arg(q.lastError().text()));
    }
    QSqlRecord rec = q.record();
    if(q.next()){
        uint n = q.value(0).toUInt();
        return n;
    }
    return 0;
}
uint PKDao::getSolveTime(uint id) {
    QSqlQuery q;
    q.prepare("select stime from pk where id=:id");
    q.bindValue(":id", id);
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("getSolveTime error %1").arg(q.lastError().text()));
    }
    QSqlRecord rec = q.record();
    if(q.next()){
        uint n = q.value(0).toUInt();
        return n;
    }
    return 0;
}
void PKDao::setSolveTime(uint id, uint stime) {
    db->execute("setSolveTime", "update pk set stime=:stime where id=:id", [=](QSqlQuery q) {
        q.bindValue(":stime", stime);
        q.bindValue(":id", id);
    });
}
