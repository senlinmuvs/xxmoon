﻿#ifndef PK_H
#define PK_H
#include <string>
#include <QString>
#include <QVariantMap>
#include <QJsonObject>
#include "com/util.h"

using namespace std;

class PK {
public:
    PK();

    uint id = 0;
    uint cid = 0;
    QString simpleCont = "";
    QString cont = "";
    QString img = "";
    uint time = 0;
    uint lst = 0;
    uint stime = 0;
    uint jm = 0;
    bool bj = false;
    QString tags = "";
    QString refs = "";
    QString refids = "";
    QString refimgids = "";

    QString uuid;
    QString file;

    QString toString();
    QVariantMap toVMap(bool detail = false, bool parse = true, uint maxWidth = 0);
    QString getImgLink();
    bool hasTagId(uint tid);

    void fill(QVariantMap m);

    static PK* convPK(QJsonObject jo) {
        using namespace ut::json;
        PK* p = new PK();
        p->cont = getString(jo, "cont", "");
        p->img = getString(jo, "img", "");
        p->time = getQint64(jo, "ctime", 0)/1000;
        return p;
    }
};

#endif // PK_H
