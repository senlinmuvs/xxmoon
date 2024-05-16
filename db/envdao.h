#ifndef ENVDAO_H
#define ENVDAO_H

#include <QString>

class EnvDao {
public:
    EnvDao();

    void set(const QString& k, const QString& v);
    void set(const QString& k, qint64 v);
    QString get(const QString& k);
    QString get(const QString& k, const QString& def);
    uint getUInt(const QString& k);
    qint64 getQint64(const QString& k);
    void addItem(const QString& k, const QVariant& item);
    void removeItem(const QString& k, const QVariant& item);
};

#endif // ENVDAO_H
