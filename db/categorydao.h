#ifndef CATEGORYDAO_H
#define CATEGORYDAO_H

#include "basedao.h"

#include <model/category.h>
#include <QString>
#include <QVariantList>
#include <vector>

using namespace std;

class CategoryDao : public BaseDao {
public:
    CategoryDao();

    void add(Category *col);
    void del(uint id);
    void updateName(uint id, QString name);
    void updateIndex(uint id, uint srcIndex, uint dstIndex);
    virtual uint getMaxId() const;
    uint getMaxI();
    Category* getCategory(uint id);
    Category* getCategoryByIndex(uint index);
    vector<Category> getAll();
    vector<Category> getCategories(QString k);
    uint count();
    uint getIDByName(QString name);
    uint getFirstID();
    void setX(uint id, uint x);
    void updatePwd(uint id, QString encrypted);
};

#endif // CATEGORYDAO_H
