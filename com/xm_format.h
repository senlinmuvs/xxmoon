#ifndef XM_FORMAT_H
#define XM_FORMAT_H

#include <QString>
#include "model/xm.h"

class XMFormat {
public:
    XMFormat();

    QString createXMFile(QString name, QString mainImg, QString& cont, QString pwd);
    XM* openFile(QString file, QString pwd);
};

#endif // XM_FORMAT_H
