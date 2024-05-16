#ifndef FUTURE_H
#define FUTURE_H

#include <QString>
#include <QSemaphore>
#include <QMutex>
#include <QVariantList>

class Future {
public:
    explicit Future();

private:
    QSemaphore sem;
    QVariantList res;
    QMutex mtx;

public:
    QVariantList getList(uint timeout=30000);
    QVariant get(uint timeout=30000, QVariant def=0);
    void set(const QVariant& v);
    void setList(const QVariantList& res);
};

#endif // FUTURE_H
