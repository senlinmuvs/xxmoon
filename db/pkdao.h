#ifndef PKDAO_H
#define PKDAO_H

#include <QString>
#include <vector>
#include <model/pk.h>
#include <QSqlQuery>
#include "com/util.h"
#include "basedao.h"

class PKDao: public BaseDao {
public:
    PKDao();

    void add(PK *p);
    PK* getPK(uint id);
    QString getTags(uint id);
    QList<PK*> getPKList(QString k, uint cid, uint fromId);
    QList<PK*> getNewPKList(uint cid, uint fromId);
    virtual uint getMaxId() const;
    void deletePK(uint id);
    void updatePK(uint id, QString cont, uint jm, uint lst = ut::time::getCurSeconds());
    void updateCid(uint pkId, uint cid);
    uint countImgRefrence(QString imgLink);
    void updatePKTags(uint pkid, QString tags);
    uint countCol(uint cid);
    uint getNextID(uint cid, uint id);
    uint getIDByImg(QString img);
    uint getSolveTime(uint id);
    void setSolveTime(uint id, uint stime);
private:
    QList<PK*> gets(QSqlQuery q, QSqlRecord rec);
};

#endif // PKDAO_H
