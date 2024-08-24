#ifndef SCRIPT_H
#define SCRIPT_H

#include <QMap>
#include <QObject>

class Script : public QObject {
    Q_OBJECT
private:
    explicit Script(QObject *parent = nullptr);

    QMap<uint,qint64> lastMillsMap;

public:
    static Script& INS() {
        static Script ins;
        return ins;
    }
    void checkAndRun();
    QString exeCmd(uint xmid, const QString& ty, const QString& cmd, const QString& cont);
    bool checkFormat(const QString& input);
    void updateStatusText(QString& cont, QString& r);
};

#endif // SCRIPT_H
