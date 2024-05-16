#include "envdao.h"
#include "com/global.h"

EnvDao::EnvDao() {
}

void EnvDao::set(const QString& k, const QString& v) {
    if(lg->isDebug()) {
        lg->debug(QString("set k=%1 v=%2").arg(k).arg(v));
    }
    QString sql = "insert or replace into env(k,v) values(:k,:v)";
    bool ok = db->execute("set env", sql, [k,v](QSqlQuery& q){
        q.bindValue(":k", k);
        q.bindValue(":v", v);
    });
    if(ok) {
        dologEnvNew(k);
    }
}
void EnvDao::set(const QString& k, qint64 v) {
    set(k, to_string(v).c_str());
}
QString EnvDao::get(const QString& k, const QString& def) {
    QString v = get(k);
    if(v == ""){
        return def;
    } else {
        return v;
    }
}
QString EnvDao::get(const QString& k) {
    if(lg->isDebug()) {
        lg->debug(QString("get k=%1").arg(k));
    }
    QString sql = "select v from env where k=:k";
    QSqlQuery q;
    q.prepare(sql);
    q.bindValue(":k", k);
    bool suc = q.exec();
    if(!suc) {
        lg->error(QString("get env error %1 [%2]").arg(q.lastError().text()).arg(k));
        return "";
    }
    QSqlRecord rec = q.record();
    int colV = rec.indexOf("v");
    if(q.first()){
        return q.value(colV).toString();
    } else {
        return "";
    }
}
uint EnvDao::getUInt(const QString& k) {
    QString v = get(k);
    if(v != "") {
        return v.toUInt();
    }
    return 0;
}

qint64 EnvDao::getQint64(const QString& k) {
    QString v = get(k);
    if(v != "") {
        return v.toLongLong();
    }
    return 0;
}
void EnvDao::addItem(const QString& k, const QVariant& item) {
    QString v = get(k);
    QStringList items = v.split(",");
    bool found = false;
    for(int i = 0; i < items.size(); i++) {
        QString it = items.at(i);
        if(it == item) {
            found = true;
            break;
        }
    }
    if(!found) {
        if(v.isEmpty()) {
            v = item.toString();
        } else {
            v += "," + item.toString();
        }
        set(k, v);
    }
}
void EnvDao::removeItem(const QString& k, const QVariant& item) {
    QString v = get(k);
    if(v.isEmpty()) {
        return;
    }
    QStringList items = v.split(",");
    int index = -1;
    for(int i = 0; i < items.size(); i++) {
        QString it = items.at(i);
        if(it == item) {
            index = i;
            break;
        }
    }
    if(index >= 0) {
        items.removeAt(index);
        v = "";
        for(int i = 0; i < items.size(); i++) {
            v += items.at(i) + ",";
        }
        if(!v.isEmpty()) {
            v = v.mid(0, v.length()-1);
        }
        set(k, v);
    }
}
