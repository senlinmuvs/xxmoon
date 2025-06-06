﻿#include "categorydao.h"
#include "com/global.h"

CategoryDao::CategoryDao():BaseDao() {
}

void CategoryDao::add(Category *c) {
    if(c->id<=0){
        c->id = increID();
    }
    QString insert_sql = "insert into category(id, name, i, x, m, ty) values(:id,:name,:i,:x,:jm,:ty)";
    bool ok = db->execute("add category", insert_sql, [&c](QSqlQuery& q) {
        q.bindValue(":id", c->id);
        q.bindValue(":name", c->name);
        q.bindValue(":i", c->i);
        q.bindValue(":x", c->x);
        q.bindValue(":m", c->m.isNull()?"":c->m);
        q.bindValue(":ty", c->ty);
    });
    if(ok) {
        dologCategoryNew(c->id);
    }
}
void CategoryDao::del(uint id) {
    bool ok = db->execute("del category", "delete from category where id=:id", [=](QSqlQuery& q) {
        q.bindValue(":id", id);
    });
    if(ok) {
        dologCategoryDel(id);
    }
}
void CategoryDao::moveUp(uint fromIndex) {
    QString sql = QString("update category set i=i-1 where i>%1").arg(fromIndex);
    bool ok = db->execute("moveUp", sql, [=](QSqlQuery&) {
    });
    if(ok) {
        dologSql(sql);
    }
}
void CategoryDao::updateName(uint id, QString name) {
    QString sql = "update category set name=:name where id=:id";
    bool ok = db->execute("update name", sql, [=](QSqlQuery& q) {
        q.bindValue(":id", id);
        q.bindValue(":name", name);
    });
    if(ok) {
        dologCategoryNew(id);
    }
}
void CategoryDao::updateIndex(uint id, uint srcIndex, uint dstIndex) {
    // qDebug() << ">>>>updateIndex" << id << srcIndex << dstIndex;
    if(srcIndex == dstIndex) {
        return;
    }
    QString sql1, sql2;
    if(srcIndex < dstIndex) {
        sql1 = "update category set i=i-1 where i > #srcIndex and i <=#dstIndex";
    } else {
        sql1 = "update category set i=i+1 where i < #srcIndex and i >=#dstIndex";
    }
    sql2 = "update category set i = #dstIndex where id = #id";
    sql1.replace("#srcIndex", QString::number(srcIndex));
    sql1.replace("#dstIndex", QString::number(dstIndex));
    sql2.replace("#dstIndex", QString::number(dstIndex));
    sql2.replace("#id", QString::number(id));
    QSqlQuery q;
    q.exec(sql1);
    q.exec(sql2);
    dologSql(sql1);
    dologSql(sql2);
}
uint CategoryDao::getMaxId() {
    QSqlQuery q("select max(id) as maxid from category");
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
uint CategoryDao::getMaxI() {
    QSqlQuery q("select max(i) as maxI from category");
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
Category* CategoryDao::getCategory(uint id) {
    QSqlQuery q;
    q.prepare("select name,i,x,m,ty from category where id=:id");
    q.bindValue(":id", id);
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("getCategory error %1").arg(q.lastError().text()));
    }
    if(q.next()) {
        QString name = q.value(0).toString();
        uint i = q.value(1).toUInt();
        uint x = q.value(2).toUInt();
        QString m = q.value(3).toString();
        uint ty = q.value(4).toUInt();
        Category *c = new Category();
        c->id = id;
        c->name = name;
        c->i = i;
        c->x = x;
        c->m = m;
        c->ty = ty;
        return c;
    } else {
        return nullptr;
    }
}
Category* CategoryDao::getCategoryByIndex(uint index) {
    QSqlQuery q;
    q.prepare("select id,name,i,x,m,ty from category where i=:i");
    q.bindValue(":i", index);
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("getCategoryByIndex error %1").arg(q.lastError().text()));
    }
    if(q.next()) {
        uint id = q.value(0).toUInt();
        QString name = q.value(1).toString();
        uint i = q.value(2).toUInt();
        uint x = q.value(3).toUInt();
        QString m = q.value(4).toString();
        uint ty = q.value(5).toUInt();
        Category *c = new Category();
        c->id = id;
        c->name = name;
        c->i = i;
        c->x = x;
        c->m = m;
        c->ty = ty;
        return c;
    } else {
        return nullptr;
    }
}
void fillData(QSqlQuery *q, vector<Category> *list) {
    QSqlRecord rec = q->record();
    int colId = rec.indexOf("id");
    int colName = rec.indexOf("name");
    int colI = rec.indexOf("i");
    int colN = rec.indexOf("n");
    int colX = rec.indexOf("x");
    int colM = rec.indexOf("m");
    int colty = rec.indexOf("ty");
    while (q->next()) {
        uint id = q->value(colId).toUInt();
        QString name = q->value(colName).toString();
        uint n = q->value(colN).toUInt();
        uint i = q->value(colI).toUInt();
        uint x = q->value(colX).toUInt();
        uint ty = q->value(colty).toUInt();
        QString m = q->value(colM).toString();
        Category c;
        c.id = id;
        c.name = name;
        c.i = i;
        c.total = n;
        c.x = x;
        c.m = m;
        c.ty = ty;
        list->insert(list->end(), c);
    }
}
vector<Category> CategoryDao::getAll() {
    vector<Category> list;
    QSqlQuery q;
    q.exec("select id,name,i,0 as n,x,m,ty from category order by i");
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

vector<Category> CategoryDao::getCategories(QString k) {
    k = k.trimmed();
    vector<Category> list;
    QString sql = "select * from (select c.id, c.name, c.i, c.x, c.m, c.ty, count(*) as n "
                  "from xm "
                  "join category c on xm.cid == c.id "
                  "where 1=1 #cont #tags "
                  "group by xm.cid)t order by t.i";

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
        lg->error(QString("getCategories error %1 sql[%2]").arg(q.lastError().text()).arg(sql));
    }
    fillData(&q, &list);
//    qDebug() << sql;
    return list;
}

uint CategoryDao::count() {
    QSqlQuery q("select count(*) as c from category");
    bool suc = q.exec();
    if(!suc){
        lg->error(QString("count category error %1").arg(q.lastError().text()));
    }
    QSqlRecord rec = q.record();
    int colCount = rec.indexOf("c");
    q.next();
    return q.value(colCount).toUInt();
}

uint CategoryDao::getIDByName(QString name) {
    QSqlQuery q;
    q.prepare("select id from category where name=:name");
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

uint CategoryDao::getFirstID() {
    Category* col = getCategoryByIndex(0);
    if(col) {
        return col->id;
    }
    return 0;
}

void CategoryDao::setX(uint id, uint x) {
    QSqlQuery q;
    q.prepare("update category set x=:x where id=:id");
    q.bindValue(":x", x);
    q.bindValue(":id", id);
    bool suc = q.exec();
    if(!suc) {
        lg->error(QString("categorydao setX error %1 %2 %3").arg(q.lastError().text()).arg(id).arg(x));
        return;
    }
    dologCategoryNew(id);
}
void CategoryDao::updatePwd(uint id, QString encrypted) {
    QSqlQuery q;
    q.prepare("update category set m=:m where id=:id");
    q.bindValue(":m", encrypted);
    q.bindValue(":id", id);
    bool suc = q.exec();
    if(!suc) {
        lg->error(QString("categorydao updatePwd error %1 %2 %3").arg(q.lastError().text()).arg(id).arg(encrypted));
        return;
    }
    dologCategoryNew(id);
}
void CategoryDao::setType(uint id, uint ty) {
    QSqlQuery q;
    q.prepare("update category set ty=:ty where id=:id");
    q.bindValue(":ty", ty);
    q.bindValue(":id", id);
    bool suc = q.exec();
    if(!suc) {
        lg->error(QString("categorydao setType error %1 %2 %3").arg(q.lastError().text()).arg(id).arg(ty));
        return;
    }
    dologCategoryNew(id);
}
