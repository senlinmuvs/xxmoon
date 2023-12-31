#ifndef XM_H
#define XM_H

#include <QString>
#include "model/pk.h"

class XM {
public:
    XM();

    QString createXMFile(QString name, QString mainImg, QString& cont, QString pwd);
    PK* openFile(QString file, QString pwd);
};

#endif // XM_H
