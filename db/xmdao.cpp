#include "xmdao.h"
#include "com/global.h"
#include "com/util.h"

XMDao::XMDao() : BaseDao() {
}

QList<XM*> XMDao::gets(QSqlQuery q, QSqlRecord rec) {
    QList<XM*> list;
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
        XM *p = new XM();
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
void XMDao::add(XM *p) {
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
    QString sql = "insert into xm(id, cid, cont, img, time, lst, stime, tags, bj, jm, refids, refimgids) values(?,?,?,?,?,?,?,?,?,?,?,?)";
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
        lg->error(QString("add xm error %1 %2").arg(q.lastError().text()).arg(p->toString()));
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
QList<XM*> XMDao::getXMList(QString k, uint cid, uint fromId) {
    QString sql = "select id,cid,cont,img,time,lst,stime,tags,bj,jm,refids,refimgids from xm where cid=:cid #id #cont #tags order by id desc limit :size";
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
        lg->error(QString("getXMList error %1 sql[%2]").arg(q.lastError().text()).arg(sql));
        return QList<XM*>();
    }
    QSqlRecord rec = q.record();
    QList<XM*> list = gets(q, rec);
    if(lg->isDebug()) {
        lg->debug(QString("getXMList sql[%1] args [%2 %3 %4] res %5").arg(sql).arg(k).arg(cid).arg(fromId).arg(list.size()));
    }
    return list;
}

QList<XM*> XMDao::getNewXMList(uint cid, uint fromId) {
    QString sql = "select id,cid,cont,img,time,lst,stime,tags,bj,jm,refids,refimgids from xm where cid=:cid and id>:id order by id asc limit :size";
    QSqlQuery q;
    q.prepare(sql);
    q.bindValue(":cid", cid);
    q.bindValue(":id", fromId);
    q.bindValue(":size", PAGE_SIZE);
    bool r = q.exec();
    if(!r) {
        lg->error(QString("getNewXMList error %1").arg(q.lastError().text()));
        return QList<XM*>();
    }
    QSqlRecord rec = q.record();
    return gets(q, rec);
}

uint XMDao::getMaxId() const {
    QSqlQuery q("select max(id) as maxid from xm");
    bool r = q.exec();
    if(!r) {
        lg->error(QString("getMaxId error %1").arg(q.lastError().text()));
        return 0;
    }
    QSqlRecord rec = q.record();
    int colMaxid = rec.indexOf("maxid");
    q.next();
    uint maxid = q.value(colMaxid).toUInt();
    return maxid;
}

XM* XMDao::getXM(uint id) {
    QSqlQuery q("select id,cid,cont,img,time,lst,stime,bj,tags,jm,refids,refimgids from xm where id=" + QString::number(id));
    bool r = q.exec();
    if(!r) {
        lg->error(QString("getXM error %1").arg(q.lastError().text()));
        return NULL;
    }
    QSqlRecord rec = q.record();
    QList<XM*> list = gets(q, rec);
    if(list.size() > 0) {
        XM* pk = list.first();
        return pk;
    } else {
        return NULL;
    }
}
QString XMDao::getTags(uint id) {
    QSqlQuery q("select tags from xm where id=" + QString::number(id));
    bool r = q.exec();
    if(!r) {
        lg->error(QString("getTags error %1").arg(q.lastError().text()));
        return "";
    }
    QSqlRecord rec = q.record();
    if(q.next()) {
        return q.value(0).toString();
    }
    return "";
}
void XMDao::deleteXM(uint id) {
    db->execute("deleteXM", "delete from xm where id=:id", [=](QSqlQuery q) {
        q.bindValue(":id", id);
    });
}
void XMDao::updateXM(uint id, QString cont, uint jm, uint lst) {
    QString refids = extractRefIDs(cont);
    QString refimgids = extractRefimgids(cont);
    if(lg->isDebug()){
        lg->trace(QString("updateXM id %1 cont %2 jm %3 lst %4").arg(id).arg(cont.length()).arg(jm).arg(lst));
    }
    db->execute("updateXM", "update xm set cont=:cont,lst=:lst,jm=:jm,refids=:refids,refimgids=:refimgids where id=:id", [=](QSqlQuery q) {
        q.bindValue(":id", id);
        q.bindValue(":lst", lst);
        q.bindValue(":cont", cont.isNull() ? "" : cont);
        q.bindValue(":jm", jm);
        q.bindValue(":refids", refids.isNull() ? "" : refids);
        q.bindValue(":refimgids", refimgids.isNull() ? "" : refimgids);
    });
}
void XMDao::updateCid(uint xmid, uint cid) {
    db->execute("updateCid", "update pk set cid=:cid where id=:id", [=](QSqlQuery q) {
        q.bindValue(":cid", cid);
        q.bindValue(":id", xmid);
    });
}
uint XMDao::countImgRefrence(QString imgLink) {
    QSqlQuery q;
    q.prepare("select count(*) as ref from xm where cont like :k");
    q.bindValue(":k", "%"+imgLink+"%");
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("countImgRefrence error %1").arg(q.lastError().text()));
        return 0;
    }
    QSqlRecord rec = q.record();
    int colRef = rec.indexOf("ref");
    q.next();
    uint cid = q.value(colRef).toUInt();
    return cid;
}

void XMDao::updateXMTags(uint xmid, QString tags) {
    db->execute("updateXMTags", "update xm set tags=:tags where id=:id", [=](QSqlQuery q) {
        q.bindValue(":tags", tags.toStdString().c_str());
        q.bindValue(":id", xmid);
    });
}

uint XMDao::countCol(uint cid) {
    QSqlQuery q;
    q.prepare("select count(*) as n from xm where cid=:cid");
    q.bindValue(":cid", cid);
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("countCol error %1").arg(q.lastError().text()));
        return 0;
    }
    QSqlRecord rec = q.record();
    if(q.next()){
        uint n = q.value(0).toUInt();
        return n;
    }
    return 0;
}

uint XMDao::getNextID(uint cid, uint id) {
    QSqlQuery q;
    q.prepare("select id from xm where cid=:cid and id>:id order by id limit 1");
    q.bindValue(":cid", cid);
    q.bindValue(":id", id);
    bool suc = q.exec();
    if(!suc) {
        lg->error(QString("getNextID error %1").arg(q.lastError().text()));
        return 0;
    }
    QSqlRecord rec = q.record();
    if(q.next()){
        uint id = q.value(0).toUInt();
        return id;
    } else {
        q.prepare("select id from xm where cid=:cid order by id limit 1");
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

uint XMDao::getIDByImg(QString img) {
    QSqlQuery q;
    q.prepare("select id from xm where img=:img");
    q.bindValue(":img", img);
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("getIDByImg error %1").arg(q.lastError().text()));
        return 0;
    }
    QSqlRecord rec = q.record();
    if(q.next()){
        uint n = q.value(0).toUInt();
        return n;
    }
    return 0;
}
uint XMDao::getSolveTime(uint id) {
    QSqlQuery q;
    q.prepare("select stime from xm where id=:id");
    q.bindValue(":id", id);
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("getSolveTime error %1").arg(q.lastError().text()));
        return 0;
    }
    QSqlRecord rec = q.record();
    if(q.next()){
        uint n = q.value(0).toUInt();
        return n;
    }
    return 0;
}
void XMDao::setSolveTime(uint id, uint stime) {
    db->execute("setSolveTime", "update xm set stime=:stime where id=:id", [=](QSqlQuery q) {
        q.bindValue(":stime", stime);
        q.bindValue(":id", id);
    });
}
