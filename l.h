#ifndef L_H
#define L_H

#include <QObject>

class L : public QObject {
    Q_OBJECT
public:
    explicit L();
    Q_INVOKABLE bool isDebug();
    Q_INVOKABLE bool isTrace();
    Q_INVOKABLE void trace(QString msg);
    Q_INVOKABLE void debug(QString msg);
    Q_INVOKABLE void info(QString msg);
    Q_INVOKABLE void warn(QString msg);
    Q_INVOKABLE void error(QString msg);
};

#endif // L_H
