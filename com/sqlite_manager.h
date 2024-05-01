#ifndef SQLITEMANAGER_H
#define SQLITEMANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

using namespace std;

class SQLiteManager {
private:
    QSqlDatabase db;
public:
    SQLiteManager();
    bool openDB();
    void init();
    bool execute(const QString& tag, const QString& sql, std::function<void (QSqlQuery&)> cb);
    void close();
    bool transaction();
    bool commit();
    void rollback();
};

#endif //SQLITEMANAGER_H
