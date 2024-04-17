#include "tagdao.h"
#include "com/global.h"

void fillData(QSqlQuery *q, vector<Tag> *list);

TagDao::TagDao() : BaseDao() {
}

void TagDao::add(Tag *t) {
    if(t->id <= 0) {
        t->id = increID();
    }
    QString insert_sql = "insert into tag(id, tag) values(:id,:tag)";
    db->execute("add tag", insert_sql, [=](QSqlQuery q) {
        q.bindValue(":id", t->id);
        q.bindValue(":tag", t->tag);
    });
}
Tag* TagDao::get(uint id){
    QSqlQuery q("select * from tag where id=" + QString::number(id));
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("get tag error %1").arg(q.lastError().text()));
    }
    if(q.next()){
        uint id = q.value(0).toUInt();
        QString tag = q.value(1).toString();
        Tag *t = new Tag();
        t->id = id;
        t->tag = tag;
        return t;
    } else {
        return NULL;
    }
}
Tag* TagDao::getByName(QString name) {
    QSqlQuery q;
    q.prepare("select * from tag where tag=:tag");
    q.bindValue(":tag", name);
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("getByName error %1").arg(q.lastError().text()));
    }
    if(q.next()){
        uint id = q.value(0).toUInt();
        QString tag = q.value(1).toString();
        Tag *t = new Tag();
        t->id = id;
        t->tag = tag;
        return t;
    } else {
        return nullptr;
    }
}
void fillData(QSqlQuery *q, vector<Tag> *list) {
    QSqlRecord rec = q->record();
    int colId = rec.indexOf("id");
    int colTag = rec.indexOf("tag");
    while (q->next()) {
        uint id = q->value(colId).toUInt();
        QString tag = q->value(colTag).toString();
        Tag t;
        t.id = id;
        t.tag = tag;
        list->insert(list->end(), t);
    }
}
vector<Tag> TagDao::list(QString k) {
    vector<Tag> list;
    QString sql = "select id,tag from tag where 1=1 #search";
    bool hasK = k.length() > 0;
    if(hasK){
        sql = sql.replace("#search", "and tag like :k");
    } else {
        sql = sql.replace("#search", "");
    }
    QSqlQuery q;
    q.prepare(sql);
    if(hasK){
        q.bindValue(":k", "%"+k+"%");
    }
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("list tag error %1").arg(q.lastError().text()));
    }
    fillData(&q, &list);
//    qDebug() << sql << k;
    return list;
}
uint TagDao::getMaxId() const {
    QSqlQuery q("select max(id) as maxid from tag");
    q.exec();
    QSqlRecord rec = q.record();
    int colMaxid = rec.indexOf("maxid");
    q.next();
    uint maxid = q.value(colMaxid).toUInt();
    return maxid;
}
void TagDao::del(uint id) {
    db->execute("del tag", "delete from tag where id=:id", [=](QSqlQuery q) {
        q.bindValue(":id", id);
    });
}
QMap<uint,uint> TagDao::countTag(uint target) {
    QString table = target == 0 ? "xm" : "note";
    QString sql = "select tags,count(*) as n from "+ table +" where tags!='' #del group by tags";
    if(table == "xm") {
        sql.replace("#del", "");
    } else {
        sql.replace("#del", "and del=0");
    }
    //
    QMap<uint,uint> map;
    QSqlQuery q;
    q.exec(sql);
    QSqlRecord rec = q.record();
    int colTags = rec.indexOf("tags");
    int colN = rec.indexOf("n");
    while(q.next()) {
        QString tags = q.value(colTags).toString();
        uint n = q.value(colN).toUInt();
        QStringList list = tags.split("#");
        for(QString e:list) {
            if(e.length()>0){
                uint k = e.toUInt();
                map[k] = map[k] + n;
            }
        }
    }
    return map;
}
uint TagDao::countTag(uint tid, uint target) {
    QString table = target == 0 ? "xm" : "note";
    QString sql = "select count(*) as n from "+ table +" where tags like :tid #del";
    if(table == "xm") {
        sql.replace("#del", "");
    } else {
        sql.replace("#del", "and del=0");
    }
    //
    QSqlQuery q;
    q.prepare(sql);
    q.bindValue(":tid", "%#"+QString::number(tid)+"#%");
    QSqlRecord rec = q.record();
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("countTag error %1").arg(q.lastError().text()));
    }
    if(q.next()) {
        uint ref = q.value(0).toUInt();
//        qDebug() << tid << ref;
        return ref;
    }
    return 0;
}
vector<uint> TagDao::findTagIdByTag(QString tag) {
    vector<uint> ids;
    QSqlQuery q;
    q.prepare("select id from tag where tag like :tag");
    q.bindValue(":tag", "%"+tag+"%");
    QSqlRecord rec = q.record();
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("findTagIdByTag error %1").arg(q.lastError().text()));
    }
    while(q.next()) {
        uint id = q.value(0).toUInt();
        ids.insert(ids.end(), id);
    }
//    qDebug() << "get tag id" << tag << ids.size();
    return ids;
}

QString TagDao::getTagCondByTags(QStringList tags) {
    QString s;
    for(QString tag: tags){
        vector<uint> tids = findTagIdByTag(tag);
        if(tids.size() == 0) {
            return "and 0=1";
        }
        QString orsql;
        for(uint i = 0; i < tids.size(); i++){
            uint id = tids[i];
            orsql += "tags like '%#"+QString::number(id)+"#%' or ";
        }
        if(orsql.length()>0) {
            s += "and ("+orsql.mid(0, orsql.length()-3)+") ";
        }
    }
    return s;
}
