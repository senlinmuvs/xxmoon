#ifndef WORK_H
#define WORK_H

#include <QString>
#include <QVariantMap>
#include "com/util.h"
#include <QJsonObject>

using namespace std;

class Work {
public:
    Work();

    uint id = 0;
    QString name = "";
    QString author = "";
    uint time = 0;
    uint total = 0;
    uint t = 0;//0 导入 1 手动

    QString toString();
    QVariantMap toVMap();

    static Work* convWork(QJsonObject jo) {
        using namespace ut::json;
        Work* w = new Work();
        w->author = getString(jo, "aname", "--");
        if(w->author == "") {
            w->author = "--";
        }
        w->name = getString(jo, "wname", "--");
        if(w->name == "") {
            w->name = "--";
        }
        return w;
    }
};

#endif // WORK_H
