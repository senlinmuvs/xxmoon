#include "coldao.h"
#include "com/global.h"
#include "com/util.h"

ColDao::ColDao():BaseDao() {
}

void ColDao::add(Collect *c) {
    if(c->id<=0){
        c->id = increID();
    }
    QString insert_sql = "insert into col(id, name, i, x) values(:id,:name,:i,:x)";
    db->execute("add col", insert_sql, [&c](QSqlQuery q) {
        q.bindValue(":id", c->id);
        q.bindValue(":name", c->name);
        q.bindValue(":i", c->i);
        q.bindValue(":x", c->x);
    });
}
void ColDao::del(uint id) {
    db->execute("del col", "delete from col where id=:id", [=](QSqlQuery q) {
        q.bindValue(":id", id);
    });
}
void ColDao::updateName(uint id, QString name) {
    QString sql = "update col set name=:name where id=:id";
    db->execute("update name", sql, [=](QSqlQuery q) {
        q.bindValue(":id", id);
        q.bindValue(":name", name);
    });
}
void ColDao::updateIndex(uint id, uint srcIndex, uint dstIndex) {
    if(srcIndex == dstIndex) {
        return;
    }
    QString sql1, sql2;
    if(srcIndex < dstIndex) {
        sql1 = "update col set i=i-1 where i > #srcIndex and i <=#dstIndex";
    } else {
        sql1 = "update col set i=i+1 where i < #srcIndex and i >=#dstIndex";
    }
    sql2 = "update col set i = #dstIndex where id = #id";
    sql1.replace("#srcIndex", QString::number(srcIndex));
    sql1.replace("#dstIndex", QString::number(dstIndex));
    sql2.replace("#dstIndex", QString::number(dstIndex));
    sql2.replace("#id", QString::number(id));
    QSqlQuery q;
    q.exec(sql1);
    q.exec(sql2);
}
uint ColDao::getMaxId() const {
    QSqlQuery q("select max(id) as maxid from col");
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("getMaxId error %1").arg(q.lastError().text()));
    }
    QSqlRecord rec = q.record();
    int colMaxid = rec.indexOf("maxid");
    q.next();
    uint maxid = q.value(colMaxid).toUInt();
    return maxid;
}
uint ColDao::getMaxI() {
    QSqlQuery q("select max(i) as maxI from col");
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("getMaxI error %1").arg(q.lastError().text()));
    }
    QSqlRecord rec = q.record();
    int colMaxI = rec.indexOf("maxI");
    q.next();
    uint maxI = q.value(colMaxI).toUInt();
    return maxI;
}
Collect* ColDao::getCollect(uint id) {
    QSqlQuery q;
    q.prepare("select name,i,x from col where id=:id");
    q.bindValue(":id", id);
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("getCollect error %1").arg(q.lastError().text()));
    }
    if(q.next()) {
        QString name = q.value(0).toString();
        uint i = q.value(1).toUInt();
        uint x = q.value(2).toUInt();
        Collect *c = new Collect();
        c->id = id;
        c->name = name;
        c->i = i;
        c->x = x;
        return c;
    } else {
        return NULL;
    }
}
Collect* ColDao::getCollectByIndex(uint index) {
    QSqlQuery q;
    q.prepare("select id,name,i,x from col where i=:i");
    q.bindValue(":i", index);
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("getCollectByIndex error %1").arg(q.lastError().text()));
    }
    if(q.next()) {
        uint id = q.value(0).toUInt();
        QString name = q.value(1).toString();
        uint i = q.value(2).toUInt();
        uint x = q.value(3).toUInt();
        Collect *c = new Collect();
        c->id = id;
        c->name = name;
        c->i = i;
        c->x = x;
        return c;
    } else {
        return NULL;
    }
}
void fillData(QSqlQuery *q, vector<Collect> *list) {
    QSqlRecord rec = q->record();
    int colId = rec.indexOf("id");
    int colName = rec.indexOf("name");
    int colI = rec.indexOf("i");
    int colN = rec.indexOf("n");
    int colX = rec.indexOf("x");
    while (q->next()) {
        uint id = q->value(colId).toUInt();
        QString name = q->value(colName).toString();
        uint n = q->value(colN).toUInt();
        uint i = q->value(colI).toUInt();
        uint x = q->value(colX).toUInt();
        Collect c;
        c.id = id;
        c.name = name;
        c.i = i;
        c.total = n;
        c.x = x;
        list->insert(list->end(), c);
    }
}
vector<Collect> ColDao::getAll() {
    vector<Collect> list;
    QSqlQuery q;
    q.exec("select id,name,i,0 as n,x from col order by i");
    fillData(&q, &list);
    return list;
}

QString getSearchCondSql(QString k) {
    QString sql = "(";
    QStringList arr = k.split(" ");
    for(int i = 0; i < arr.length(); i++) {
        sql += "cont like '%" + arr[i] + "%' and ";
    }
    sql = sql.mid(0, sql.length()-5);
    return sql + ")";
}

vector<Collect> ColDao::getCollects(QString k) {
    k = k.trimmed();
    vector<Collect> list;
    QString sql = "select * from (select col.id, col.name, col.i, col.x, count(*) as n "
                  "from pk "
                  "join col on pk.cid == col.id "
                  "where 1=1 #cont #tags "
                  "group by pk.cid)t order by t.i";

    bool hasK = k.length() > 0;
    if(hasK) {
        QVariantList ks = parseKeyTags(k);
        QStringList tags = ks[0].toStringList();
//        qDebug() << "tags" << tags;
        if(tags.length() > 0) {
            QString tagCond = tagDao->getTagCondByTags(tags);
            sql = sql.replace("#tags", tagCond);
            QString newK = ks[1].toString();
//            qDebug() << "newK" << newK;
            if(newK.length() > 0) {
                sql = sql.replace("#cont", "and "+getSearchCondSql(newK)+" and jm=0");
                k = newK;
            } else {
//                hasK = false;
                sql = sql.replace("#cont", "");
            }
        } else {
            sql = sql.replace("#cont", "and "+getSearchCondSql(k)+" and jm=0");
            sql = sql.replace("#tags", "");
        }
    } else {
        sql = sql.replace("#cont", "");
        sql = sql.replace("#tags", "");
    }
    QSqlQuery q;
    q.prepare(sql);

//    if(hasK) {
//        q.bindValue(":k", "%"+k+"%");
//    }
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("getCollects error %1 sql[%2]").arg(q.lastError().text()).arg(sql));
    }
    fillData(&q, &list);
//    qDebug() << sql;
    return list;
}

uint ColDao::count() {
    QSqlQuery q("select count(*) as c from col");
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("count col error %1").arg(q.lastError().text()));
    }
    QSqlRecord rec = q.record();
    int colCount = rec.indexOf("c");
    q.next();
    return q.value(colCount).toUInt();
}

uint ColDao::getIDByName(QString name) {
    QSqlQuery q;
    q.prepare("select id from col where name=:name");
    q.bindValue(":name", name);
    bool suc = q.exec();
    if(!suc) {
        lg->error(QString("getIDByName error %1").arg(q.lastError().text()));
    }
    QSqlRecord rec = q.record();
    if(q.next()) {
        int i = rec.indexOf("id");
        return q.value(i).toUInt();
    }
    return 0;
}

uint ColDao::getFirstID() {
    Collect* col = getCollectByIndex(0);
    if(col) {
        return col->id;
    }
    return 0;
}

void ColDao::setX(uint id, uint x) {
    QSqlQuery q;
    q.prepare("update col set x=:x where id=:id");
    q.bindValue(":x", x);
    q.bindValue(":id", id);
    bool suc = q.exec();
    if(!suc) {
        lg->error(QString("coldao setX error %1 %2 %3").arg(q.lastError().text()).arg(id).arg(x));
    }
}
