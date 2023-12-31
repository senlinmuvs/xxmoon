#ifndef ENVDAO_H
#define ENVDAO_H

#include <QString>

class EnvDao {
public:
    EnvDao();

    void set(QString k, QString v);
    void set(QString k, uint v);
    QString get(QString k);
    QString get(QString k, QString def);
    uint getUInt(QString k);
};

#endif // ENVDAO_H
