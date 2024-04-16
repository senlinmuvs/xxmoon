#ifndef COLDAO_H
#define COLDAO_H

#include "basedao.h"

#include <model/collect.h>
#include <QString>
#include <QVariantList>
#include <vector>

using namespace std;

class ColDao : public BaseDao {
public:
    ColDao();

    void add(Collect *col);
    void del(uint id);
    void updateName(uint id, QString name);
    void updateIndex(uint id, uint srcIndex, uint dstIndex);
    virtual uint getMaxId() const;
    uint getMaxI();
    Collect* getCollect(uint id);
    Collect* getCollectByIndex(uint index);
    vector<Collect> getAll();
    vector<Collect> getCollects(QString k);
    uint count();
    uint getIDByName(QString name);
    uint getFirstID();
    void setX(uint id, uint x);
    void updatePwd(uint id, QString encrypted);
};

#endif // COLDAO_H
