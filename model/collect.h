#ifndef COLLECT_H
#define COLLECT_H
#include <QString>
#include <QVariantMap>

using namespace std;

class Collect {
public:
    Collect();

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

#endif // COLLECT_H
