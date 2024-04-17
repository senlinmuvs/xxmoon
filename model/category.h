#ifndef CATEGORY_H
#define CATEGORY_H
#include <QString>
#include <QVariantMap>

using namespace std;

class Category {
public:
    Category();

    uint id;
    QString name;
    uint total;
    uint i;
    uint x;
    QString m;
    bool jm;

    QString toString();
    QVariantMap toVMap();
};

#endif // CATEGORY_H
