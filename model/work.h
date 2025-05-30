﻿#ifndef WORK_H
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
    uint fro = 0; //0 kindle 1 douban 2 wechat read
    QString tag = "";
    QString extra = "";

    QString toString();
    QVariantMap toVMap();
    void convTagPound2Comma();
    void convTagComma2Pound();

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
    static QString convTagPound2Comma(QString tag) {
        if(tag.startsWith("#")) {
            tag = tag.mid(1);
        }
        if(tag.endsWith("#")) {
            tag = tag.mid(0, tag.length()-1);
        }
        tag = tag.replace("#", ",");
        return tag;
    }
    static QString convTagComma2Pound(QString tag) {
        tag = tag.replace(",", "#");
        tag = "#"+tag+"#";
        return tag;
    }

};

#endif // WORK_H
