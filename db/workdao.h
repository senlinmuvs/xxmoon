#ifndef WORKDAO_H
#define WORKDAO_H

#include "basedao.h"

#include <model/work.h>
#include <QMutex>
#include <QSqlQuery>

class WorkDao: public BaseDao {
public:
    WorkDao();

    Work* get(QString name, QString author);
    Work* get(QString name);
    Work* get(uint id);
    void add(Work *w);
    void add(const QList<Work*> &list);
    void del(uint id);
    void update(Work *w);
    virtual uint getMaxId() const;
    QList<QString> getWorkTagList();
};

#endif // WORKDAO_H
