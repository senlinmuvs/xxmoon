#ifndef CATEGORY_H
#define CATEGORY_H
#include <QString>
#include <QVariantMap>

using namespace std;

class Category {
public:
    Category();

    uint id = 0;
    QString name = "";
    uint total = 0;
    uint i = 0;
    uint x = 0;
    QString m = "";
    bool jm = false;

    QString toString();
    QVariantMap toVMap();
};

#endif // CATEGORY_H
