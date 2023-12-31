#ifndef TAG_H
#define TAG_H

#include <QString>
#include <QVariantMap>


class Tag {
public:
    Tag();
    uint id = 0;
    QString tag = "";
    uint n = 0;

    QString toString();
    QVariantMap toVMap();
};

#endif // TAG_H
