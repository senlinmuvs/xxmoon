#ifndef SM_H
#define SM_H

#include <QSharedMemory>



class SM {
public:
    SM();
    bool createShareMemory();
    void close();
private:
    QSharedMemory* qsm;
};

#endif // SM_H
