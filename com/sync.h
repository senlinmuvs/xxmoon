#ifndef SYNC_H
#define SYNC_H

#include <QMap>
#include <QList>
#include <QObject>


class Sync : public QObject {

    Q_OBJECT
public:
    explicit Sync();

    void start();
    QList<QStringList> getUploadFiles();
    qint64 valueOfFileMod(QString file);

private:
    QMap<QString, qint64> fileModTimeMap;
    qint64 lastCheckFileTime = 0;
    void sync0();
};
#endif // SYNC_H
