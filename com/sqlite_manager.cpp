#include "sqlite_manager.h"
#include "com/global.h"
#include "com/util.h"

#include <QCoreApplication>

SQLiteManager::SQLiteManager() {
}

bool SQLiteManager::openDB() {
    if(lg->isDebug()) {
        lg->debug(QString("open db %1").arg(cfg->dbFile));
    }
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(cfg->dbFile);
    return db.open();
}

void SQLiteManager::init() {
    if(lg->isDebug()) {
        lg->debug("init db");
    }
    QSqlQuery query;
    query.exec(sql_work_table);
    query.exec(sql_note_table);
    query.exec(sql_note_script);
    query.exec(sql_env_table);
    query.exec(sql_col_table);
    query.exec(sql_pk_table);
    query.exec(sql_tag_table);
    //
    if(colDao->getMaxId() == 0) {
        Collect *c = new Collect();
        c->id = 1;
        c->name = "Default";
        c->i = 0;
        colDao->add(c);
        delete c;
    }
}

void SQLiteManager::execute(QString tag, QString sql, std::function<void (QSqlQuery)> cb) {
    QSqlQuery q;
    q.prepare(sql);
    cb(q);
    bool r = q.exec();
    if(!r) {
        lg->error(QString("%1 error %2").arg(tag).arg(q.lastError().text()));
    }
}

void SQLiteManager::close() {
    db.close();
}

bool SQLiteManager::transaction() {
    return db.transaction();
}
bool SQLiteManager::commit() {
    return db.commit();
}
void SQLiteManager::rollback() {
    db.rollback();
}
