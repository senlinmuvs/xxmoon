#include "envdao.h"
#include "com/global.h"
#include "com/const.h"

EnvDao::EnvDao() {
}

void EnvDao::set(QString k, QString v) {
    QString oldV = get(k);
    QString sql;
    if(oldV == nullptr) {
        sql = "insert into env(k,v) values(:k,:v)";
    } else {
        sql = "update env set v=:v where k=:k";
    }
    db->execute("set env", sql, [k,v](QSqlQuery q){
        q.bindValue(":k", k);
        q.bindValue(":v", v);
    });
}
void EnvDao::set(QString k, uint v) {
    set(k, to_string(v).c_str());
}
QString EnvDao::get(QString k, QString def) {
    QString v = get(k);
    if(v == ""){
        return def;
    } else {
        return v;
    }
}
QString EnvDao::get(QString k) {
    QString sql = "select v from env where k=:k";
    QSqlQuery q;
    q.prepare(sql);
    q.bindValue(":k", k);
    bool suc = q.exec();
    if(!suc){
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
uint EnvDao::getUInt(QString k) {
    QString v = get(k);
    if(v!=nullptr){
        return v.toUInt();
    }
    return 0;
}
