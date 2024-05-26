#ifndef NOTE_H
#define NOTE_H

#include <QJsonObject>
#include <QString>
#include <QVariantMap>
#include "com/util.h"

using namespace std;

class Note {
public:
    Note();

    uint id = 0;
    QString book = "";
    QString author = "";
    uint wid = 0;
    qint64 time = 0;
    uint pos0 = 0;
    uint pos1 = 0;
    QString cont = "";
    QString html = "";
    QString tags = "";
    QString refids = "";
    QString refimgids = "";
    qint64 lst = 0;
    bool bj = false;

    QString toString();
    QVariantMap toVMap(bool parse = true, uint maxWidth = 0);

    static Note* convNote(QJsonObject jo) {
        using namespace ut::json;
        Note* n = new Note();
        n->cont = getString(jo, "cont", "");
        n->time = getQint64(jo, "ntime", 0)/1000;
        return n;
    }
};
#endif //NOTE_H
