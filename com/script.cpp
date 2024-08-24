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
QString Script::exeCmd(uint xmid, const QString& ty, const QString& cmd, const QString& cont) {
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
                QStringList params;
                params << scriptFile;
                params << "1";//最后一个参数表示是哪里调用的脚本 0表示从面板调用 1表示从定时器
                process.start(cfg->python, params);
                if(process.waitForStarted()) {
                    if(process.waitForFinished()) {
                        res = process.readAll();
                        if(lg->isDebug()) {
                            lg->debug(QString("exeCmd ty=%1 cmd=%2 cont len=%3 res=%4").arg(ty).arg(cmd).arg(cont.length()).arg(res));
                        }
                    } else {
                        lg->error(QString("exeCmd err %1 ty=%2 cmd=%3 cont len=%4").arg(process.errorString()).arg(ty).arg(cmd).arg(cont.length()));
                        return "失败";
                    }
                } else {
                    lg->error(QString("exeCmd err %1 ty=%2 cmd=%3 cont len=%4").arg(process.errorString()).arg(ty).arg(cmd).arg(cont.length()));
                    return "失败";
                }
            } else {
                lg->error(QString("exeCmd err %1 not exists").arg(scriptFile));
                return "失败";
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
                    return "失败";
                }
            } else {
                lg->error(QString("exeCmd err %1 ty=%2 cmd=%3 cont len=%4").arg(process.errorString()).arg(ty).arg(cmd).arg(cont.length()));
                return "失败";
            }
        }
    }
    //
    // 0   默认值，无结果
    // 1   桌面通知：不消失，手动关闭
    // 2   桌面通知：N秒后消失
    // 11  桌面通知1+微信通知
    // 21  桌面通知2+微信通知
    // 001 无结果：结果变动写入日志
    // 101 桌面通知：不消失，手动关闭，结果变动写入日志
    // 201 桌面通知：N秒后消失，结果变动写入日志
    // 102 不消失，当有变动时才通知与写日志
    // 202 消失，当有变动时才通知与写日志
    uint ty0 = 0;
    uint ty1 = 0;
    uint ty2 = 0;
    if(ty.length() > 0) {
        ty0 = QString(ty[0]).toUInt();
    }
    if(ty.length() > 1) {
        ty1 = QString(ty[1]).toUInt();
    }
    if(ty.length() > 2) {
        ty2 = QString(ty[2]).toUInt();
    }
    res = res == "" ? "成功" : res;
    bool resChanged = false;
    if(ty2 == 1 || ty2 == 2) {//变动结果写日志
        Future *f = new Future();
        DB_Async->exe("script_add_log", [=]{
            QString lastLogCont = taskLogDao->getLastLog(xmid);
            if(lastLogCont != res) {
                taskLogDao->add(xmid, res);
                f->set(QVariant(1));
            } else {
                f->set(QVariant(-1));
            }
        });
        resChanged = f->get(5000, 0).toInt() > 0;
        delete f;
    }
    if(res != "成功") {
        if(ty0 == 1) {//不消失
            if(ty2 == 2) {
                if(resChanged) {
                    notify(res.trimmed(), 1);
                }
            } else {
                notify(res.trimmed(), 1);
            }
        } else if(ty0 == 2) {//自动消失
            if(ty2 == 2) {
                if(resChanged) {
                    notify(res.trimmed());
                }
            } else {
                notify(res.trimmed());
            }
        }
        if(ty1 == 1) {//微信通知
            //TODO 微信通知
        }
    }
    return res;
}
void Script::updateStatusText(QString& cont, QString& r) {
    QString cur = ut::time::getCurrentTimeStr("yyyy/MM/dd hh:mm:ss");
    cont = cont.trimmed();
    int i = cont.lastIndexOf("----\n");
    if(i < 0) {
        cont += "\n----\n" + cur + " " + r;
    } else {
        QStringList arr = cont.mid(i+5).split(" | ");
        if(arr.length() <= 1) {
            arr << cur + " " + r;
        } else if(arr.length() == 2) {
            QString st = arr[1].trimmed().right(2);
            if(st == "成功" || st == "失败") {
                arr[1] = cur + " " + r;
            } else {
                arr << cur + " " + r;
            }
        } else {
            arr[2] = cur + " " + r;
        }
        cont = cont.mid(0, cont.lastIndexOf("\n")+1) + arr.join(" | ");
    }
    // ----
    // 2024/05/27 17:59:00 成功 | 2024/05/27 10:10:00 xxx | 2024/05/27 17:59:50 xxxx
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

        int i = cont.lastIndexOf("\n----\n");
        if(i >= 0) {
            cont = cont.mid(0, i);
        }
        QString timerLine = ut::str::getEndLine(cont);
        if (!timerLine.isEmpty()) {
            bool ok = checkFormat(timerLine);
            // qDebug() << "checkFormat" << endLine << ok;
            if(ok) {
                QStringList params = timerLine.mid(1, timerLine.size()-2).split(",");
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
                    QString ty = "";
                    QString file = "";
                    if(params.size() > 1) {
                        ty = params.at(1).trimmed();
                    }
                    if(params.size() > 2) {
                        file = params.at(2).trimmed();
                    }
                    QString r = exeCmd(xmid, ty, file, ut::str::removeEndLine(cont));
                    Future* f = new Future();
                    DB_Async->exe("更新定时器状态", [&]{
                        XM* xm = xmDao->getXM(xmid);
                        if(xm != nullptr) {
                            updateStatusText(xm->cont, r);
                            xmDao->updateXM(xmid, xm->cont, xm->jm, xm->lst);
                            xm->simpleCont = extractXMSimpleCont(xm->cont, "");
                            pushXM(xm);
                        }
                        f->set(1);
                        delete xm;
                    });
                    if(f->get(5000, 0) == 1) {
                        lastMillsMap.insert(xmid, cur.toMSecsSinceEpoch());
                    }
                    delete f;
                }
            }
        }
    }
}
