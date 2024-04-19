#ifndef TRANS_H
#define TRANS_H

#include <QMap>
#include <QString>


class Trans {
public:
    Trans();

    QString tr(QString k);

private:
    QMap<QString, QString> trans_zh_map;
};

#endif // TRANS_H
