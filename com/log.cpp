#include "log.h"
#include "com/const.h"
#include "com/global.h"
#include <QDateTime>
#include <QThread>
#include <QDebug>

Log::Log(){
}

void Log::init(QString file) {
    name_level.insert(LOG_LEVEL_TRACE, LOG_LEVEL_TRACE_VAL);
    name_level.insert(LOG_LEVEL_DEBUG, LOG_LEVEL_DEBUG_VAL);
    name_level.insert(LOG_LEVEL_INFO, LOG_LEVEL_INFO_VAL);
    name_level.insert(LOG_LEVEL_WARN, LOG_LEVEL_WARN_VAL);
    name_level.insert(LOG_LEVEL_ERROR, LOG_LEVEL_ERROR_VAL);
    logFile = new QFile(file);
    logFile->open(QIODevice::Append);
}
void Log::close(){
//    if(logFile->isOpen()) {
//        logFile->close();
//    }
//    delete logFile;
}
void Log::log(QString level, QString msg) {
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString log = QString("[%1] %2 [%3] %4").arg(QStringLiteral("%1").arg(level, 5).toUpper(),
                                               time,
                                               QStringLiteral("%1").arg(quintptr(QThread::currentThreadId()), 4, 16),
                                               msg);
    qDebug() << log.toUtf8().data();
    if(logFile->isOpen()){
        QByteArray data;
        data.append(log.toUtf8()).append("\r\n");
        logFile->write(data);
        logFile->flush();
    }
}
void Log::trace(QString msg) {
    uint level = name_level.value(cfg->logLevel, 999);
    if(level<=LOG_LEVEL_TRACE_VAL) {
        log(LOG_LEVEL_TRACE, msg);
    }
}
void Log::debug(QString msg) {
    uint level = name_level.value(cfg->logLevel, 999);
    if(level<=LOG_LEVEL_DEBUG_VAL) {
        log(LOG_LEVEL_DEBUG, msg);
    }
}
void Log::info(QString msg) {
    uint level = name_level.value(cfg->logLevel, 999);
    if(level<=LOG_LEVEL_INFO_VAL) {
        log(LOG_LEVEL_INFO, msg);
    }
}
void Log::warn(QString msg) {
    uint level = name_level.value(cfg->logLevel, 999);
    if(level<=LOG_LEVEL_WARN_VAL) {
        log(LOG_LEVEL_WARN, msg);
    }
}
void Log::error(QString msg) {
    uint level = name_level.value(cfg->logLevel, 999);
    if(level<=LOG_LEVEL_ERROR_VAL) {
        log(LOG_LEVEL_ERROR, msg);
    }
}
bool Log::isDebug() {
    uint level = name_level.value(cfg->logLevel, 999);
    if(level<=LOG_LEVEL_DEBUG_VAL) {
        return true;
    }
    return false;
}
bool Log::isTrace() {
    uint level = name_level.value(cfg->logLevel, 999);
    if(level<=LOG_LEVEL_TRACE_VAL) {
        return true;
    }
    return false;
}
