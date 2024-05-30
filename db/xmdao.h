#ifndef XMDAO_H
#define XMDAO_H

#include <QString>
#include <model/xm.h>
#include <QSqlQuery>
#include "com/util.h"
#include "basedao.h"

class XMDao: public BaseDao {
public:
    XMDao();

    void add(XM *p);
    XM* getXM(uint id);
    QString getTags(uint id);
    QList<XM*> getXMList(QString k, uint cid, uint fromId);
    QList<XM*> getNewXMList(uint cid, uint fromId);
    uint getMaxId() override;
    bool deleteXM(uint id);
    void updateXM(uint id, QString cont, uint jm, uint lst = ut::time::getCurSeconds());
    void updateCid(uint pkId, uint cid);
    uint countImgRefrence(QString imgLink);
    void updateXMTags(uint pkid, QString tags);
    uint countCategory(uint cid);
    uint count();
    uint getNextID(uint cid, uint id);
    uint getIDByImg(QString img);
    uint getSolveTime(uint id);
    void setSolveTime(uint id, uint stime);
    void setTop(uint xmid, uint top);
    void setDtime(uint id, qint64 dtime);
private:
    QList<XM*> gets(QSqlQuery& q, QSqlRecord& rec);
};

#endif // XMDAO_H
