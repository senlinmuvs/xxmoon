#include "sync.h"
#include "model/cfg.h"
#include "com/global.h"
#include "future.h"
#include "http.h"
#include <QDirIterator>
#include <QTemporaryFile>
#include <QTimer>

Sync::Sync():QObject() {
}
class SyncException: public std::exception {
private:
    std::string message;
public:
    SyncException(const std::string& msg) : message(msg) {}
    SyncException() : message("SyncException") {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};
QString getPrimaryKey(const QString& table) {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return "";
    }

    QString primaryKey;
    QSqlQuery query(db);
    QString sql = QString("PRAGMA table_info(%1)").arg(table);
    if (query.exec(sql)) {
        while (query.next()) {
            if (query.value(5).toBool()) { // 判断是否为主键
                primaryKey = query.value(1).toString(); // 获取主键名
                break;
            }
        }
    } else {
        qDebug() << "Failed to retrieve table info for:" << table;
    }

    if (primaryKey.isEmpty()) {
        qDebug() << "No primary key found for table:" << table;
        return "";
    }

    return primaryKey;
}

QJsonObject fetchRecordAsJson(const QString& table, const QString& key, const QString& val) {
    QJsonObject json;
    QSqlQuery query;
    query.prepare(QString("SELECT * FROM %1 WHERE %2 = :key").arg(table, key));
    query.bindValue(":key", val);
    if (!query.exec()) {
        lg->error(QString("fetchRecordAsJson Database query error table %1 key %2 err %3").arg(table, key, query.lastError().text()));
        return json;
    }
    if (query.next()) {
        QSqlRecord record = query.record();
        for (int i = 0; i < record.count(); ++i) {
            json[record.fieldName(i)] = record.value(i).toString();
        }
    } else {
        lg->error(QString("fetchRecordAsJson No record found with table %1 key %2").arg(table, key));
        throw SyncException("No record found");
    }
    return json;
}
bool upfile(const QString file) {
    QMap<QString, QString> params;
    QString path = "";
    QString sub = cfg->userBaseDir+"/";
    int i0 = file.indexOf(sub);
    if(i0 >= 0) {
        int i1 = file.lastIndexOf("/");
        i0 = i0+sub.length();
        if(i1 >= 0 && i1 > i0) {
            path = file.mid(i0, i1-i0);
        }
    }
    params["path"] = path;
    params["cid"] = QString::number(cfg->cid);
    params["user"] = cfg->user;
    params["pwd"] = cfg->pwd;
    QString url = QString("https://%1/upfile").arg(cfg->server);
    Future *f = new Future();
    QEventLoop loop;
    Http http;
    http.timeout = 15000;
    // qDebug() << "upfile" << file << "params" << params;
    http.upload(url, params, file, [&,f](){
        lg->info(QString("upfile done %1").arg(file));
        f->set(QVariant(1));
        loop.quit();
    }, nullptr, [&](QNetworkReply::NetworkError err){
        lg->error(QString("upload url %1 err %2").arg(url).arg(err));
        loop.quit();
    });
    loop.exec();
    if(f->get(5000).toUInt() == 1) {
        return true;
    }
    delete f;
    return false;
}
bool uprecord(const QString& table, const QString& k, const QString& v, const QString& json) {
    if(table.isEmpty() || k.isEmpty() || json.isEmpty()) {
        return false;
    }
    QMap<QString, QString> params;
    params["cid"] = QString::number(cfg->cid);
    params["user"] = cfg->user;
    params["pwd"] = cfg->pwd;
    params["table"] = table;
    params["k"] = k;
    params["v"] = v;
    params["data"] = json;
    QString url = QString("https://%1/uprecord").arg(cfg->server);
    Future *f = new Future();
    QEventLoop loop;
    Http http;
    http.timeout = 5000;
    http.post(url, params, [&,f](QJsonObject jo){
        int st = ut::json::getInt(jo, "st", -1);
        if(st != 0) {
            QString err = ut::json::getString(jo, "msg", "");
            lg->error(QString("uprecord error [%1 %2 %3] [st %4 msg %5]").arg(table, k, v).arg(st).arg(err));
        }
        f->set(QVariant(st));
        loop.quit();
    }, [&](QNetworkReply::NetworkError err){
        lg->error(QString("post url %1 err %2").arg(url).arg(err));
        loop.quit();
    });
    loop.exec();
    bool ok = f->get(5000, -1).toInt() == 0;
    delete f;
    return ok;
}
bool delRecord(const QString& table, const QString& k, const QString& v) {
    if(table.isEmpty() || k.isEmpty() || v.isEmpty()) {
        return false;
    }
    QMap<QString, QString> params;
    params["cid"] = QString::number(cfg->cid);
    params["user"] = cfg->user;
    params["pwd"] = cfg->pwd;
    params["table"] = table;
    params["k"] = k;
    params["v"] = v;
    QString url = QString("https://%1/drecord").arg(cfg->server);
    QEventLoop loop;
    Http http;
    http.timeout = 5000;
    Future *f = new Future();
    http.post(url, params, [&,f](QJsonObject jo){
        int st = ut::json::getInt(jo, "st", -1);
        if(st != 0) {
            QString err = ut::json::getString(jo, "msg", "");
            lg->error(QString("delRecord error [%1 %2 %3] [st %4 msg %5]").arg(table, k, v).arg(st).arg(err));
        }
        f->set(QVariant(st));
        loop.quit();
    }, [&](QNetworkReply::NetworkError err){
        lg->error(QString("post url %1 err %2").arg(url).arg(err));
        loop.quit();
    });
    loop.exec();
    bool ok = f->get(5000, -1).toInt() == 0;
    delete f;
    return ok;
}
bool delFile(const QString& file) {
    QMap<QString, QString> params;
    params["cid"] = QString::number(cfg->cid);
    params["user"] = cfg->user;
    params["pwd"] = cfg->pwd;
    params["file"] = file;
    QString url = QString("https://%1/dfile").arg(cfg->server);
    QEventLoop loop;
    Http http;
    http.timeout = 5000;
    Future *f = new Future();
    http.post(url, params, [&,f](QJsonObject jo){
        int st = ut::json::getInt(jo, "st", -1);
        if(st != 0) {
            QString err = ut::json::getString(jo, "msg", "");
            lg->error(QString("delFile error [%1] [st %2 msg %3]").arg(file).arg(st).arg(err));
        }
        f->set(QVariant(st));
        loop.quit();
    }, [&](QNetworkReply::NetworkError err){
        lg->error(QString("post url %1 err %2").arg(url).arg(err));
        loop.quit();
    });
    loop.exec();
    bool ok = f->get(5000, -1).toInt() == 0;
    delete f;
    lg->info(QString("delFile suc %1").arg(file));
    return ok;
}
bool uprecordBySql(QString sql) {
    if(sql.isEmpty()) {
        return false;
    }
    QMap<QString, QString> params;
    params["cid"] = QString::number(cfg->cid);
    params["user"] = cfg->user;
    params["pwd"] = cfg->pwd;
    params["sql"] = sql;
    QString url = QString("https://%1/uprecord_").arg(cfg->server);
    QEventLoop loop;
    Http http;
    http.timeout = 5000;
    Future *f = new Future();
    http.post(url, params, [&,f](QJsonObject jo){
        int st = ut::json::getInt(jo, "st", -1);
        if(st != 0) {
            QString err = ut::json::getString(jo, "msg", "");
            lg->error(QString("uprecordBySql error [%1] [st %2 msg %3]").arg(sql).arg(st).arg(err));
        }
        f->set(QVariant(st));
        loop.quit();
    }, [&](QNetworkReply::NetworkError err){
        lg->error(QString("post url %1 err %2").arg(url).arg(err));
        loop.quit();
    });
    loop.exec();
    bool ok = f->get(5000, -1).toInt() == 0;
    delete f;
    return ok;
}
bool processMessage(const QString& msg) {
    QStringList parts = msg.split(' ');
    if (parts.size() < 2) {
        qDebug() << "Invalid message format";
        return false;
    }

    const static QMap<QString, QString> actionToTableMap = {
        {"x", "xm"},
        {"n", "note"},
        {"c", "category"},
        {"w", "work"},
        {"e", "env"},
        {"t", "tag"}
    };

    QString action = parts[0];
    QString valueOfKey = parts[1];

    if(action == "sql") {
        QString sql = msg.mid(action.length()+1);
        return uprecordBySql(sql);
    } else {
        QString table = actionToTableMap.value(action.at(1));
        Future *f = new Future();
        DB_Async->exe("get_key", [table, f]{
            QString key = getPrimaryKey(table);
            f->set(QVariant(key));
        });
        QString key = f->get().toString();
        delete f;
        if (action.startsWith('d')) {
            if(action == "dnw") {
                key = "wid";
            }
            bool ok0 = delRecord(table, key, valueOfKey);
            bool ok1 = true;
            if(parts.length() > 2) {
                QString img = parts[2];
                if(!img.isEmpty()) {
                    ok1 = delFile("imgs/"+img);
                }
            }
            return ok0 && ok1;
        } else if (action.startsWith('n')) {
            if (table.isEmpty()) {
                qDebug() << "Unknown action type";
                return false;
            }
            Future *f = new Future();
            DB_Async->exe("get_json", [&,f]{
                try {
                    QJsonObject json = fetchRecordAsJson(table, key, valueOfKey);
                    f->set(QVariant(json));
                } catch(const SyncException& e) {
                    f->set(QVariant(1));
                }
            });
            QVariant v = f->get();
            delete f;
            if(v.toUInt() == 1) {
                return true;
            }
            QJsonObject json = v.toJsonObject();
            QString jsonStr = ut::json::toString(json);
            bool ok = uprecord(table, key, valueOfKey, jsonStr);
            if(ok) {
                if(action == "nx") {
                    QString img = ut::json::getString(json, "img", "");
                    if(!img.isEmpty()) {
                        QString imgFile = cfg->imgDir+"/"+img;
                        ok = upfile(imgFile);
                    }
                }
            }
            return ok;
        } else {
            qDebug() << "Unknown action prefix";
            return false;
        }
    }
}

void writeDirectoryContentsToFile(const QString &directoryPath, const QString &outputFilePath) {
    QDir dir(directoryPath);
    if (!dir.exists()) {
        qWarning() << "Directory does not exist:" << directoryPath;
        return;
    }

    QFile outputFile(outputFilePath);
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Cannot open file for writing:" << outputFilePath;
        return;
    }

    QTextStream out(&outputFile);
    QDirIterator it(directoryPath, QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();
        QFileInfo fileInfo = it.fileInfo();
        if (fileInfo.isFile()) {
            QString relativePath = dir.relativeFilePath(fileInfo.filePath());
            out << relativePath << "\n";
        }
    }
    outputFile.close();
    qDebug() << "Directory contents written to:" << outputFilePath;
}
bool processLines(const QStringList &lines) {
    for(const QString &line : lines) {
        lg->info(QString("process line %1").arg(line));
        QString file = cfg->userBaseDir+"/"+line;
        bool ok = upfile(file);
        if(!ok) {
            lg->error(QString("upfile error stop %1").arg(file));
            return false;
        }
    }
    return true;
}

void processFileInBatches(const QString &inputFilePath, const QString &outputFilePath, int batchSize) {
    QFile inputFile(inputFilePath);
    QFile outputFile(outputFilePath);

    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open input file for reading:" << inputFilePath;
        return;
    }
    if (!outputFile.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Cannot open output file for appending:" << outputFilePath;
        return;
    }

    QTextStream in(&inputFile);
    QTextStream out(&outputFile);
    QStringList batchLines;
    QString line;
    int lineCount = 0;
    while (in.readLineInto(&line)) {
        batchLines.append(line);
        lineCount++;

        if (lineCount == batchSize) {
            bool ok = processLines(batchLines); // 处理批次中的行
            if(!ok) {
                inputFile.close();
                outputFile.close();
                return;
            }
            // 将处理过的行写入输出文件
            for (const QString &processedLine : batchLines) {
                out << processedLine << "\n";
            }
            out.flush(); // 确保写入到文件

            batchLines.clear(); // 清空列表以准备下一批次
            lineCount = 0; // 重置行计数器
        }
    }

    // 处理剩余的行（如果有）
    if (!batchLines.isEmpty()) {
        bool ok = processLines(batchLines);
        if(!ok) {
            inputFile.close();
            outputFile.close();
            return;
        }
        for (const QString &processedLine : batchLines) {
            out << processedLine << "\n";
        }
        out.flush();
    }
    inputFile.close();
    outputFile.close();
}
bool removeProcessedLine(const QString &fileAPath, const QString &fileBPath) {
    QFile fileA(fileAPath);
    QFile fileB(fileBPath);

    if(!fileA.exists()) {
        return false;
    }

    if (!fileA.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file A for reading:" << fileAPath;
        return false;
    }

    QSet<QString> linesInFileA;
    QTextStream streamA(&fileA);
    QString lineA;
    while (streamA.readLineInto(&lineA)) {
        linesInFileA.insert(lineA);
    }
    fileA.close();

    // 重新打开文件B进行读写操作
    if (!fileB.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Cannot open file B for reading and writing:" << fileBPath;
        return false;
    }

    // 读取文件B的内容，同时准备覆盖写入
    QString contentsB;
    QTextStream streamB(&fileB);
    while (streamB.readLineInto(&lineA)) {
        if (!linesInFileA.contains(lineA)) {
            contentsB += lineA + "\n";
        }
    }

    // 重置文件指针到开头，并裁剪文件
    fileB.resize(0);
    streamB.seek(0);

    // 写入新内容
    streamB << contentsB;

    fileB.close();
    return true;
}
void setInitStartTime() {
    QMap<QString, QString> params;
    params["cid"] = QString::number(cfg->cid);
    params["user"] = cfg->user;
    params["pwd"] = cfg->pwd;
    QString url = QString("https://%1/setInitStartTime").arg(cfg->server);
    QEventLoop loop;
    Http http;
    http.timeout = 5000;
    http.post(url, params, [&loop](QJsonObject jo){
        int st = ut::json::getInt(jo, "st", -1);
        if(st != 0) {
            lg->error("setInitStartTime error");
        }
        loop.quit();
    }, [&](QNetworkReply::NetworkError err){
        lg->error(QString("post url %1 err %2").arg(url).arg(err));
        loop.quit();
    });
    loop.exec();
}
void setInitDoneTime() {
    QMap<QString, QString> params;
    params["cid"] = QString::number(cfg->cid);
    params["user"] = cfg->user;
    params["pwd"] = cfg->pwd;
    QString url = QString("https://%1/setInitDoneTime").arg(cfg->server);
    QEventLoop loop;
    Http http;
    http.timeout = 5000;
    http.post(url, params, [&loop](QJsonObject jo){
        int st = ut::json::getInt(jo, "st", -1);
        if(st == 0) {
            qint64 t = ut::json::getQint64(jo, "t", 0);
            ut::file::writeText(cfg->xmCfgDir+"/.init_done_time", QString::number(t));
        } else {
            lg->error("setInitDoneTime error");
        }
        loop.quit();
    }, [&](QNetworkReply::NetworkError err){
        lg->error(QString("post url %1 err %2").arg(url).arg(err));
        loop.quit();
    });
    loop.exec();
}
QList<QStringList> Sync::getUploadFiles() {
    QList<QStringList> list;
    QStringList files;
    QMap<QString, qint64> fileMap;
    QDirIterator it(cfg->userBaseDir, QDir::Files|QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();
        QFileInfo fileInfo = it.fileInfo();
        if (fileInfo.isFile()) {
            QString filePath = fileInfo.filePath();
            fileMap.insert(filePath, fileInfo.lastModified().toMSecsSinceEpoch());
        }
    }
    bool init = fileModTimeMap.isEmpty();
    foreach(const QString &filePath, fileMap.keys()) {
        qint64 v = fileModTimeMap[filePath];
        if(v > 0) {
            qint64 modTime = fileMap[filePath];
            if(modTime - v > 0) {
                files << filePath;
            }
        } else {
            fileModTimeMap.insert(filePath, fileMap.value(filePath));
            if(!init) {
                files << filePath;
            }
        }
    }
    //去掉已经不存在的，如改名或删除后
    QStringList dels;
    for(auto it = fileModTimeMap.begin(); it != fileModTimeMap.end();) {
        if(!fileMap.contains(it.key())) {
            dels << it.key();
            it = fileModTimeMap.erase(it);
        } else {
            ++it;
        }
    }
    return list << files << dels;
}
void Sync::start() {
    QString error = "";
    if(lg->isDebug()) {
        lg->debug("sync start");
    }
    bool initDone = ut::file::readFile(cfg->xmCfgDir+"/.init_done_time").toLongLong() > 0;
    if(initDone) {
        fq->dequeue([&](const QString& msg)->bool{
            lg->info(QString("dolog [%1] start").arg(msg));
            bool ok = processMessage(msg);
            if(!ok) {
                error = "同步数据错误";
            }
            lg->info(QString("dolog [%1] done ok=%2").arg(msg).arg(ok));
            return ok;
        });
    } else {
        QMap<QString, QString> params;
        params["cid"] = QString::number(cfg->cid);
        params["user"] = cfg->user;
        params["pwd"] = cfg->pwd;
        QString url = QString("https://%1/getInitDoneTime").arg(cfg->server);
        QEventLoop loop;
        Http http;
        http.timeout = 5000;
        http.post(url, params, [&](QJsonObject jo){
            int st = ut::json::getInt(jo, "st", -1);
            if(st == 0) {
                qint64 t = ut::json::getQint64(jo, "t", 0);
                if(t == 0) {
                    lg->info("sync first init data to server");
                    sync0();
                } else {
                    ut::file::writeText(cfg->xmCfgDir+"/.init_done_time", QString::number(t));
                }
            }
            loop.quit();
        }, [&](QNetworkReply::NetworkError err){
            lg->error(QString("post url %1 err %2").arg(url).arg(err));
            loop.quit();
            error = "请求服务器错误";
        });
        loop.exec();
    }
    //
    qint64 cur = ut::time::getCurMills();
    if(cur - lastCheckFileTime > 30000) {
        QList<QStringList> files = getUploadFiles();
        QString dbfile = cfg->appName+"/"+cfg->user+"/"+cfg->dbFileName;
        for(QString& f:files[0]) {
            if(f.endsWith(dbfile)) {
                continue;
            }
            bool ok = upfile(f);
            if(!ok) {
                lg->error(QString("upfile error stop %1").arg(f));
                error = "上传文件错误";
            }
        }
        for(QString& f:files[1]) {
            if(f.endsWith(dbfile)) {
                continue;
            }
            f = f.mid(f.indexOf(cfg->userBaseDir) + cfg->userBaseDir.length());
            bool ok = delFile(f);
            if(!ok) {
                lg->error(QString("delFile error stop %1").arg(f));
                error = "删除文件错误";
            }
        }
        lastCheckFileTime = ut::time::getCurMills();
    }
    // qDebug() << "push error" << error;
    pushMsg(PUSH_ERR, error);
}
void Sync::sync0() {
    QString dataPath = cfg->dataDir + "/" + cfg->appName + "/" + cfg->user;
    QString sync0File = cfg->xmCfgDir + "/." + cfg->user + "-sync0";
    QString sync1File = cfg->xmCfgDir + "/." + cfg->user + "-sync1";
    bool first = false;
    if (QFile::exists(sync0File)) {
        removeProcessedLine(sync1File, sync0File);
    } else {
        first = true;
        writeDirectoryContentsToFile(dataPath, sync0File);
    }
    if(first) {
        setInitStartTime();
    }
    processFileInBatches(sync0File, sync1File, 1);
    removeProcessedLine(sync1File, sync0File);
    lg->info("sync done");
    setInitDoneTime();
    QFile::remove(sync0File);
    QFile::remove(sync1File);
}

qint64 Sync::valueOfFileMod(QString file) {
    return fileModTimeMap.value(file);
}
