#ifndef LOG_H
#define LOG_H

#include <QFile>
#include <QMap>
#include <QString>



class Log
{
public:
    Log();

    QFile *logFile;
    void init(QString file);
    void close();
    void log(QString level, QString msg);
    void trace(QString msg);
    void debug(QString msg);
    void info(QString msg);
    void warn(QString msg);
    void error(QString msg);

    bool isDebug();
    bool isTrace();

    QMap<QString, uint> name_level;
};

#endif // LOG_H
