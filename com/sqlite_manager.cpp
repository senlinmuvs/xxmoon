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
    query.exec(sql_category_table);
    query.exec(sql_xm_table);
    query.exec(sql_tag_table);
    //
    if(categoryDao->getMaxId() == 0) {
        Category *c = new Category();
        c->id = 1;
        c->name = "Default";
        c->i = 0;
        categoryDao->add(c);
        delete c;
    }
}

void SQLiteManager::execute(QString tag, QString sql, std::function<void (QSqlQuery)> cb) {
    if(lg->isTrace()) {
        lg->trace(QString("execute start tag %1 sql %2").arg(tag).arg(sql));
    }
    QSqlQuery q;
    q.prepare(sql);
    cb(q);
    bool r = q.exec();
    if(!r) {
        lg->error(QString("%1 error %2").arg(tag).arg(q.lastError().text()));
    }
    if(lg->isTrace()) {
        lg->trace(QString("execute end tag %1").arg(tag));
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
