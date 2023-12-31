#ifndef FUNCTIONTRANSFER_H
#define FUNCTIONTRANSFER_H

#include <QObject>

class RunMain: QObject {

    Q_OBJECT
private:
    explicit RunMain(QObject *parent = 0);
    RunMain& operator=(const RunMain&);

signals:
    void comming(std::function<void()> f);

public slots:
    void init();
    void exec(std::function<void()> f);
    static RunMain& INS() {
        static RunMain ins;
        return ins;
    }
};

#endif // FUNCTIONTRANSFER_H
