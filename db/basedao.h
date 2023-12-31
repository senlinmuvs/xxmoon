#ifndef BASEDAO_H
#define BASEDAO_H

#include <QMutex>

class BaseDao {
public:
    BaseDao();
    virtual ~BaseDao() = 0;

    virtual void init();
    uint increID();
    virtual uint getMaxId() const {
        return 0;
    }

protected:
    QMutex *mutex;
    uint maxid = 0;
};

#endif // BASEDAO_H
