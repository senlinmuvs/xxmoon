#ifndef SYNC_H
#define SYNC_H

#include <QObject>


class Sync : public QObject {

    Q_OBJECT
public:
    explicit Sync();

    void start();

private:
    void sync0();
};
#endif // SYNC_H
