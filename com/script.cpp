#include "script.h"
#include "com/future.h"
#include "com/global.h"

Script::Script(QObject* parent): QObject(parent){}

bool Script::checkFormat(const QString& input) {
    if(input.isEmpty()) {
        return false;
    }
    // 正则表达式匹配各种时间格式和可选的结果方式和脚本路径
    static QRegularExpression re(
        "^<("
        "每隔(\\d+)(秒|分|时|天)|"
        "每天(\\d{2}):(\\d{2}):(\\d{\2})|"
        "每月(\\d{2}):(\\d{2}):(\\d{2}):(\\d{2})|"
        "每年(\\d{2}):(\\d{2}):(\\d{2}):(\\d{2}):(\\d{2})|"
        "每周(\\d{2}):(\\d{2}):(\\d{2})"
        ")(,\\s*(\\d+))?(,\\s*([^>]+))?\\>$"
        );

    QRegularExpressionMatch match = re.match(input);
    return match.hasMatch();
}

int delay = 10000;
qint64 convertToMilliseconds(const QString& timeString) {
    static QMap<QString, int> timeUnits = {
        {"秒", 1000},
        {"分", 1000 * 60},
        {"时", 1000 * 60 * 60},
        {"天", 1000 * 60 * 60 * 24}
    };
    int value = timeString.left(timeString.length() - 1).toInt();
    QString unit = timeString.right(1);
    qint64 milliseconds = value * timeUnits[unit];
    return milliseconds;
}
bool checkTimeWithDelay(const QDateTime& current, const QDateTime& check) {
    qint64 diff = check.msecsTo(current);
    // qDebug() << "diff" << diff << current << check;
    return diff >= 0 && diff <= delay;
}
bool checkEveryInterval(const QDateTime& timestamp, qint64 lastTime, const QString& time) {
    qint64 cur = timestamp.toMSecsSinceEpoch();
    qint64 interval = convertToMilliseconds(time.mid(2));
    qint64 diff = cur - lastTime;
    return diff >= interval;
}
bool checkEveryDay(const QDateTime& timestamp, const QString& time) {
    QTime checkTime = QTime::fromString(time.mid(2), "H:m:s");
    bool ok = timestamp.time().hour() == checkTime.hour() &&
              timestamp.time().minute() == checkTime.minute() &&
              timestamp.time().second() == checkTime.second();
    if(!ok) {
        ok = checkTimeWithDelay(timestamp, QDateTime(timestamp.date(), checkTime));
    }
    return ok;
}

bool checkEveryMonth(const QDateTime& timestamp, const QString& dateTime) {
    QDateTime checkDateTime = QDateTime::fromString(dateTime.mid(2), "d H:m:s");
    // qDebug() << "checkDateTime ::" << checkDateTime << dateTime.mid(2) << checkDateTime.date().day();
    bool ok = timestamp.date().day() == checkDateTime.date().day() &&
              timestamp.time().hour() == checkDateTime.time().hour() &&
              timestamp.time().minute() == checkDateTime.time().minute() &&
              timestamp.time().second() == checkDateTime.time().second();
    if(!ok) {
        QDate d = timestamp.date();
        ok = checkTimeWithDelay(timestamp, QDateTime(QDate(d.year(), d.month(), checkDateTime.date().day()), checkDateTime.time()));
    }
    return ok;
}

bool checkEveryYear(const QDateTime& timestamp, const QString& dateTime) {
    QDateTime checkDateTime = QDateTime::fromString(dateTime.mid(2), "M/d H:m:s");
    bool ok = timestamp.date().month() == checkDateTime.date().month() &&
              timestamp.date().day() == checkDateTime.date().day() &&
              timestamp.time().hour() == checkDateTime.time().hour() &&
              timestamp.time().minute() == checkDateTime.time().minute() &&
              timestamp.time().second() == checkDateTime.time().second();
    if(!ok) {
        QDate d = timestamp.date();
        ok = checkTimeWithDelay(timestamp, QDateTime(QDate(d.year(), checkDateTime.date().month(), checkDateTime.date().day()), checkDateTime.time()));
    }
    return ok;
}

bool checkEveryWeek(const QDateTime& timestamp, const QString& time) {
    uint w = time.mid(2, 1).toUInt();
    uint dayOfWeek = timestamp.date().dayOfWeek();
    // qDebug() << "week" << dayOfWeek << timestamp;
    if(w != dayOfWeek) {
        return false;
    }
    QTime checkTime = QTime::fromString(time.mid(4), "H:m:s");
    QTime ts = timestamp.time();
    bool ok = ts.hour() == checkTime.hour() &&
              ts.minute() == checkTime.minute() &&
              ts.second() == checkTime.second();
    if(!ok) {
        ok = checkTimeWithDelay(timestamp, QDateTime(timestamp.date(), checkTime));
    }
    return ok;
}
void Script::exeCmd(int ty, const QString& cmd, const QString& cont) {
    // qDebug() << "exeCmd" << ty << file << cont;
    QString res;
    if(cmd.isEmpty()) {
        if(!cont.isEmpty()) {
            //todo
        }
    } else {
        if(cmd.endsWith(".py")) {
            QProcess process;
            QString scriptFile = cmd;
            if(QDir::isRelativePath(cmd)) {
                scriptFile = cfg->scriptDir + "/" + cmd;
            }
            if(ut::file::exists(scriptFile)) {
                process.start("/usr/local/bin/python3", QStringList() << scriptFile);
                if(process.waitForStarted()) {
                    if(process.waitForFinished()) {
                        res = process.readAll();
                        if(lg->isDebug()) {
                            lg->debug(QString("exeCmd ty=%1 cmd=%2 cont len=%3 res=%4").arg(ty).arg(cmd).arg(cont.length()).arg(res));
                        }
                    } else {
                        lg->error(QString("exeCmd err %1 ty=%2 cmd=%3 cont len=%4").arg(process.errorString()).arg(ty).arg(cmd).arg(cont.length()));
                    }
                } else {
                    lg->error(QString("exeCmd err %1 ty=%2 cmd=%3 cont len=%4").arg(process.errorString()).arg(ty).arg(cmd).arg(cont.length()));
                }
            } else {
                lg->error(QString("exeCmd err %1 not exists").arg(scriptFile));
            }
        } else {
            QProcess process;
            process.start(cmd);
            if(process.waitForStarted()) {
                if(process.waitForFinished()) {
                    res = process.readAll();
                    if(lg->isDebug()) {
                        lg->debug(QString("exeCmd ty=%1 cmd=%2 cont len=%3 res=%4").arg(ty).arg(cmd).arg(cont.length()).arg(res));
                    }
                } else {
                    lg->error(QString("exeCmd err %1 ty=%2 cmd=%3 cont len=%4").arg(process.errorString()).arg(ty).arg(cmd).arg(cont.length()));
                }
            } else {
                lg->error(QString("exeCmd err %1 ty=%2 cmd=%3 cont len=%4").arg(process.errorString()).arg(ty).arg(cmd).arg(cont.length()));
            }
        }
    }
    if(!res.isEmpty()) {
        if(ty == 1) {
            notify(res.trimmed(), 1);
        } else if(ty == 2) {
            notify(res.trimmed());
        }
    }
}
void Script::checkAndRun() {
    Future* f = new Future();
    DB_Async->exe("checkAndRun", [&]{
        QString ids = envDao->get(ENV_K_SCRIPTS);
        f->set(QVariant(ids));
    });
    QString ids = f->get(5000, "").toString();
    delete f;
    if(ids.isEmpty()) {
        return;
    }
    QStringList arr = ids.split(",");
    for(const QString& id: arr) {
        Future* f = new Future();
        DB_Async->exe("getXM", [&]{
            XM* xm = xmDao->getXM(id.toUInt());
            if(xm == nullptr) {
                f->set(QVariant(""));
            } else {
                f->set(QVariant(xm->cont));
            }
            delete xm;
        });
        QString cont = f->get(5000, "").toString();
        delete f;
        uint xmid = id.toUInt();
        if(cont.isEmpty()) {
            lg->error(QString("script not found xmid %1").arg(xmid));
            continue;
        }
        lg->info(QString("check script %1").arg(xmid));
        cont = cont.trimmed();
        QString endLine = ut::str::getEndLine(cont);
        if (!endLine.isEmpty()) {
            bool ok = checkFormat(endLine);
            // qDebug() << "checkFormat" << endLine << ok;
            if(ok) {
                QStringList params = endLine.mid(1, endLine.size()-2).split(",");
                if(params.isEmpty()) {
                    continue;
                }
                QString time = params.at(0).trimmed();
                QDateTime cur = QDateTime::currentDateTime();
                qint64 lastMills = lastMillsMap.value(xmid, 0);
                if(lastMills <= 0) {
                    lastMills = cur.toMSecsSinceEpoch();
                    lastMillsMap.insert(xmid, lastMills);
                }
                if(time.startsWith("每隔")) {
                    ok = checkEveryInterval(cur, lastMills, time);
                } else if(time.startsWith("每天")) {
                    ok = checkEveryDay(cur, time);
                } else if(time.startsWith("每月")) {
                    ok = checkEveryMonth(cur, time);
                } else if(time.startsWith("每年")) {
                    ok = checkEveryYear(cur, time);
                } else if(time.startsWith("每周")) {
                    ok = checkEveryWeek(cur, time);
                } else {
                    ok = false;
                }
                if(ok) {
                    lg->info(QString("execute script %1").arg(xmid));
                    int ty = 0;
                    QString file = "";
                    if(params.size() > 1) {
                        ty = params.at(1).trimmed().toInt();
                    }
                    if(params.size() > 2) {
                        file = params.at(2).trimmed();
                    }
                    exeCmd(ty, file, ut::str::removeEndLine(cont));
                    lastMillsMap.insert(xmid, cur.toMSecsSinceEpoch());
                }
            }
        }
    }
}
