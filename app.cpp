#include "app.h"
#include "com/global.h"
#include <QDesktopServices>
#include <QDir>
#include <QFile>
#include <QImage>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPdfWriter>
#include <QProcess>
#include <QSettings>
#include <QTimer>
#include "com/qaesencryption.h"
#include <QCryptographicHash>
#include <QHotkey>
#include <QWindow>
#include <iostream>
#include <string>
#include "com/myPinyin.h"
#include <QResource>
#include <QSettings>
#include <QSslCertificate>
#include <QSslKey>
#include "com/runmain.h"
#include <com/future.h>
#include <com/sslhelper.h>

tuple<QList<Work*>, QList<Note*>> parseNote(QString* cont);
QString parseBookName(QString note);
QString parseAuthorName(QString note);
tuple<uint, uint> parsePos(QString note);
qint64 parseTime(QString note);
void redoDuplicates(QList<Note*> list);
QMap<uint, QHotkey*> hotkMap;

void initPath();
void initLog();
void initDB();

App::App(): QObject() {
    QDir dir(cfg->tmpDir);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); i++) {
        QFileInfo fileInfo = list.at(i);
        tmpFileLSTMap.insert(fileInfo.fileName(), fileInfo.lastModified().toMSecsSinceEpoch());
    }
}

App::~App() {
}

int App::getPlatform() {
#ifdef Q_OS_MAC
    return MAC;
#endif
#ifdef Q_OS_WIN
    return WIN;
#else
    return UNIX;
#endif
}
QString App::getCfgFile() {
    return cfg->cfgFileName;
}
QString App::getComputerID() {
    QString uuid = ut::sys::iOPlatformUUID();
    QByteArray hashKey = QCryptographicHash::hash(uuid.toLocal8Bit(), QCryptographicHash::Md5);
    QString CID = QString(hashKey).toUtf8().toHex().toUpper();
#ifdef Q_OS_UNIX
    return CID;
#else
    QString CID2 = CID;
    CID2 = "";
    for (int i = 0; i < CID.length(); i += 2) {
        bool ok;
        int a = QString(CID.at(i)).toInt(&ok, 16);
        int b = 0;
        if (i + 1 < CID.length()) {
            b = QString(CID.at(i+1)).toInt(&ok, 16);
        }
        int c = a + b;
        CID2 += CODE36.at(c);
    }
    return CID2;
#endif
}

QString App::getDataDir() {
    return cfg->dataDir + "/xxmoon";
}
QString App::getBaseDir() {
    return cfg->userBaseDir;
}
QString App::getFileDir() {
    return cfg->fileDir;
}
QString App::getImgDir() {
    return cfg->imgDir;
}

QString App::getCfgVal(QString k) {
    return cfg->toVMap().value(k, "").toString();
}

QString App::getCtrl() {
    return cfg->ctrl;
}

void App::import(QString path, QObject *obj) {
    path = ut::str::removePrefix(path, getFilePre());
    DB_Async->exe([=] {
        QString cont = ut::file::readFile(path);
        cont = QString(ut::byte::removeBom(cont.toUtf8()));
        tuple<QList<Work*>, QList<Note*>> tup = parseNote(&cont);
        QList<Work*> works = get<0>(tup);
        QList<Note*> notes = get<1>(tup);
        if(lg->isDebug()){
            lg->debug(QString("parsed path %1 cont length %2 works %3 notes %4")
                       .arg(path)
                       .arg(cont.length())
                       .arg(works.size())
                       .arg(notes.size()));
        }
        qint64 t1 = QDateTime::currentDateTime().currentMSecsSinceEpoch();
        int size = notes.size();
        workDao->add(works);
        QList<Note*> dups = noteDao->insert(notes, [obj,size](int i){
            if(obj!=nullptr) {
                if(i+1 < size) {
                    QMetaObject::invokeMethod(obj, "onFinished",
                                              Q_ARG(QVariant, QVariant::fromValue(CONT_TYPE_BOOK)),
                                              Q_ARG(QVariant, QVariant::fromValue(i+1)),
                                              Q_ARG(QVariant, QVariant::fromValue(size)),
                                              Q_ARG(QVariant, QVariant::fromValue(0)));
                }
            }
        });
        redoDuplicates(dups);
        for(Work* w:works) {
            delete w;
        }
        for(Note* n:notes) {
            delete n;
        }
        envDao->set(ENV_K_LAST_IMP_PATH, path);
        envDao->set(ENV_K_LAST_IMP_TIME, QDateTime::currentDateTime().toMSecsSinceEpoch());
        if(obj != NULL) {
            QMetaObject::invokeMethod(obj, "onFinished",
                                  Q_ARG(QVariant, QVariant::fromValue(CONT_TYPE_BOOK)),
                                  Q_ARG(QVariant, QVariant::fromValue(size)),
                                  Q_ARG(QVariant, QVariant::fromValue(size)),
                                      Q_ARG(QVariant, QVariant::fromValue(0)));
        }
        qint64 t2 = QDateTime::currentDateTime().currentMSecsSinceEpoch();
        lg->info(QString("import finished %1 cost %2 ms").arg(size).arg(t2-t1));
    });
}

tuple<QList<Work*>, QList<Note*>> parseNote(QString* cont) {
    QList<Work*> works;
    QList<Note*> list;
    QString flag = cfg->kindle_flag;
    if(cont->indexOf(flag) < 0) {
        return make_tuple(works, list);
    }
    QStringList arr = cont->split(flag);
    for(QString note:arr) {
        note = note.trimmed();
        if(lg->isDebug()) {
            lg->debug(QString("parsing note -> %1").arg(note));
        }
        if(note.length() > 0) {
            QStringList lines = note.split("\n");
            if(lines.length() > 1) {
                QString str = lines[1];
                bool matching = Reg_Kindle_Note.match(str).hasMatch();
                if(lg->isDebug()) {
                    lg->debug(QString("parsing note matching -> %1 lines len %2 %3").arg(matching).arg(lines.size()).arg(str));
                }
                if (matching && lines.size() >= 3) {
                    Note *n = new Note();
                    n->time = parseTime(lines[1]);
                    uint id = noteDao->getIdByTime(n->time);
                    bool exists = id > 0;
                    if(!exists) {
                        n->book = parseBookName(lines[0]);
                        n->author = parseAuthorName(lines[0]);
                        tuple<uint, uint> posArr = parsePos(lines[1]);
                        n->pos0 = get<0>(posArr);
                        n->pos1 = get<1>(posArr);
                        for(int i = 2; i < lines.size(); i++) {
                            QString s = lines[i];
                            n->cont += s+ "\n";
                        }
                        n->cont = n->cont.trimmed();
                        n->bj = str.contains(cfg->kindle_flag_bj);
                        if(n->bj) {
                            n->cont = ":["+n->cont+"]";
                        }
                        //
                        uint wid = 0;
                        for(Work* w : works) {
                            if(w->name == n->book && w->author == n->author) {
                                if(n->time < w->time) {
                                    w->time = n->time;
                                }
                                wid = w->id;
                                break;
                            }
                        }
                        Work *w = NULL;
                        if(wid == 0) {
                            w = workDao->get(n->book, n->author);
                        }
                        if(w != NULL) {
                            if(n->time < w->time) {
                                w->time = n->time;
                                workDao->update(w);
                            }
                            wid = w->id;
                        }
                        if(wid == 0) {
                            wid = workDao->increID();
                            w = new Work();
                            w->id = wid;
                            w->name = n->book;
                            w->author = n->author;
                            w->time = n->time;

                            works << w;
                        }
                        n->wid = wid;
                        list << n;
                    }
                }
            }
        }
    }
    return make_tuple(works, list);
}

QString parseBookName(QString line) {
    if (line.length() > 0) {
        int i = line.lastIndexOf("(");
        if (i >= 0) {
            return line.mid(0, i).trimmed();
        } else {
            return line.trimmed();
        }
    }
    return "";
}
QString parseAuthorName(QString line) {
    if (line.length() > 0) {
        int i = line.lastIndexOf("(") + 1;
        int j = line.lastIndexOf(")");
        if (i >= 0 && j >= 0) {
            return line.mid(i, j-i).trimmed();
        }
    }
    return "";
}
vector<uint> findPos(string s) {
    QString pos[] = {"", ""};
    ushort i = 0;
    bool start = false;
    for(char c : s) {
        if(c >= '0' && c <= '9') {
            start = true;
            pos[i] += c;
        } else {
            if(start) {
                i++;
                if(i>1){
                    break;
                }
            }
        }
    }
    return {pos[0].toUInt(), pos[1].toUInt()};
}
tuple<uint, uint> parsePos(QString line) {
    string s = line.toStdString();
    QString pos[] = {"", ""};
    ushort i = 0;
    bool start = false;
    for(char c : s) {
        if(c >= '0' && c <= '9') {
            start = true;
            pos[i] += c;
        } else {
            if(start) {
                i++;
                if(i>1){
                    break;
                }
            }
        }
    }
    return make_tuple(pos[0].toUInt(), pos[1].toUInt());
}
qint64 parseTime(QString line) {
    if (line.length() > 0) {
        int i = line.indexOf("添加于");
        if (i >= 0) {
            int addHours = 0;
            int time_index = line.indexOf("下午");
            if(time_index >= 0){
                addHours = 12;
            }
            QString datePart = line.mid(i + 3, time_index - i - 3).trimmed(),
                    timePart = line.mid(time_index + 2,  line.length() - time_index - 2).trimmed();
            int yIndex = datePart.indexOf("年"),
                    mIndex = datePart.indexOf("月"),
                    dIndex = datePart.indexOf("日");
            int y = datePart.mid(0, yIndex).toInt(),
                    m = datePart.mid(yIndex+1, mIndex - yIndex - 1).toInt(),
                    d = datePart.mid(mIndex+1, dIndex - mIndex - 1).toInt();
            //
            QStringList timeArr = timePart.split(":");
            int h = timeArr[0].toInt() + addHours;
            int min = timeArr[1].toInt();
            int sec = timeArr[2].toInt();
            QDateTime time(QDate(y,m,d), QTime(h, min, sec));
//            qDebug("%d-%d-%d %d:%d:%d", y, m, d, h, min, sec);
            return time.toMSecsSinceEpoch() / 1000;
        }
    }
    return 0;
}

//重新处理插入错误的项(time相同导致)，如果内容也相同则移除，内容不同则把time+1，加1还重复一直加
void redoDuplicates(QList<Note*> list) {
    int c = 0;
    for(Note* n:list) {
        if(lg->isDebug()){
            lg->debug("-> " + n->toString());
        }
        int max = 10000;
        while(max-->0) {
            uint existsId = noteDao->getIdByTime(n->time);
            if(existsId <= 0) {
                c++;
                noteDao->insert(n);
                if(lg->isDebug()){
                    lg->debug("<- " + n->toString());
                }
                break;
            }
            Note* existsNote = noteDao->get(existsId);
            if(existsNote->cont == n->cont) {
                break;
            } else {
                n->time += 1;
            }
        }
    }
    if(lg->isDebug()){
        lg->debug(QString("redo dups %1/%2").arg(c).arg(list.size()));
    }
}

//检测是否上次未导入完成就关闭了,是就继续
void App::checkImport() {
    DB_Async->exe([=] {
        QString lastPath = envDao->get(ENV_K_LAST_IMP_PATH);
        lastPath = ut::str::removePrefix(lastPath, getFilePre());
        QFileInfo fi(lastPath);
        if(fi.exists()){
            uint lastTime = envDao->getUInt(ENV_K_LAST_IMP_TIME);
            uint lm = fi.lastModified().toMSecsSinceEpoch();
            if(lm > lastTime) {
//                qDebug() << "import" << lastPath << lastTime << lm;
                import(lastPath, nullptr);
            }
        }
    });
}
void App::checkExport() {
    if(cfg->exchangeDataDir.isEmpty()) {
        return;
    }
    DB_Async->exe([=] {
        QFileInfo fi(cfg->exchangeDataDir + "/" + cfg->dbFileName);
        if(fi.exists()) {
            uint lastExchangeVersion = envDao->getUInt(ENV_K_LAST_EXCHANGE_VERSION);
        }
    });
}

void App::getLastPath(QObject *obj){
    DB_Async->exe([=]{
        QString lastPath = envDao->get(ENV_K_LAST_IMP_PATH);
        QString lastTime = envDao->get(ENV_K_LAST_IMP_TIME);
        QVariantList list;
        list.append(lastPath);
        list.append(lastTime);
        QMetaObject::invokeMethod(obj, "onGetLastPath", Q_ARG(QVariant, QVariant::fromValue(list)));
    });
}

void App::showOrHide() {
    qDebug() << "showOrHide";
    QObject* root = engine->rootObjects()[0];
    QMetaObject::invokeMethod(root, "showOrHide");
}
void App::setGlobalHotkey(uint ty, QString k) {
    QString hotv = k;
    #ifdef Q_OS_MAC
        //mac的cmd在qt里是ctrl，当配置cmd时实际要换成ctrl

        if(k.startsWith("Cmd+")) {
            hotv = hotv.replace("Cmd+", "Ctrl+");
        }
        if(k.startsWith("Ctrl+")) {
            hotv = hotv.replace("Ctrl+", "Meta+");
        }
    #endif
    QHotkey* hk = new QHotkey(QKeySequence(hotv), true);
    hotkMap.insert(ty, hk);
    QObject::connect(hk, &QHotkey::activated, qApp, [=](){
        if(ty == 0) {
            this->pk();
        } else if(ty == 1) {
            this->showOrHide();
    }
    });
}

void App::pk() {
    DB_Async->exe([=] {
        QString cont = ut::cpb::getText();
        QImage img = ut::cpb::getImage();
        if(lg->isDebug()) {
            lg->debug(QString("pk cont len %1 img [%2x%3]").arg(cont.length()).arg(img.size().width()).arg(img.size().height()));
        }
        if(cont == "" && img.isNull()) {
            return;
        }
        QObject *qmlRoot = engine->rootObjects()[0];
        QVariant suc;
        QMetaObject::invokeMethod(qmlRoot, "startPK",
                                  Qt::ConnectionType::DirectConnection,
                                  Q_RETURN_ARG(QVariant, suc));
        colAction->pk(&img, cont, "");
        if(suc.toBool()) {
            if(img.isNull()) {
                if(cont.length() > 0) {
                    QString s = tr("Words")+QString(": %1").arg(cont.length());
                    notify(s);
                }
            } else {
                QString s = tr("Picture");
                notify(s);
            }
        } else {
            lg->error(QString("pk failure cont len %1 img [%2*%3]").arg(cont.length()).arg(img.size().width()).arg(img.size().height()));
        }
    });
}


///tag
void App::tagList(QString k, uint target, QObject* obj) {
    DB_Async->exe([=] {
        vector<Tag> list = tagDao->list(k);
        QMap<uint,uint> countMap = tagDao->countTag(target);
        QVariantList resp;
        for(Tag t:list) {
            t.n = countMap[t.id];
            resp.insert(resp.end(), t.toVMap());
        }
        if(lg->isDebug()) {
            lg->trace(QString("app.cpp tagList k %2 target %3").arg(k).arg(target));
        }
        bool all = k.length() == 0;
        QMetaObject::invokeMethod(obj, "onTagList",
                    Q_ARG(QVariant, QVariant::fromValue(all)),
                    Q_ARG(QVariant, QVariant::fromValue(resp)));
    });
}

void App::addTag(QString tag, QObject *obj) {
    DB_Async->exe([=] {
        Tag *t = tagDao->getByName(tag);
        int st = 0;
        if(t == nullptr) {
            t = new Tag();
            t->tag = tag;
            tagDao->add(t);
        } else {
            st = 1;
        }
        alert(QObject::tr("Add Success!"));
        QMetaObject::invokeMethod(obj, "onAddTag",
                    Q_ARG(QVariant, QVariant::fromValue(st)),
                    Q_ARG(QVariant, QVariant::fromValue(t->toVMap())));
        delete t;
    });
}

void App::delTag(uint tid, QObject *obj) {
    DB_Async->exe([=] {
        uint ref_pk = tagDao->countTag(tid, 0);
        uint ref_note = tagDao->countTag(tid, 1);
        uint ref = ref_pk + ref_note;
        if (ref == 0) {
            tagDao->del(tid);
        }
        QMetaObject::invokeMethod(obj, "onDelete",
                    Q_ARG(QVariant, QVariant::fromValue(tid)),
                    Q_ARG(QVariant, QVariant::fromValue(ref)));
    });
}

void App::getTagById(uint id, uint cbid) {
    DB_Async->exe([=] {
        Tag *tag = tagDao->get(id);
        if(tag != NULL) {
            sendMsg(cbid, tag->toVMap());
            delete tag;
        }
    });
}

void App::setLocal(QString k, QString v) {
    QString s;
    QStringList localCfgLines = ut::file::allLines(cfg->localCfgFileName);
    bool up = false;
    if(localCfgLines.length() > 0) {
        for(int i = 0; i < localCfgLines.length(); i++) {
            QString line = localCfgLines.at(i);
            line = line.trimmed();
            if(!line.isEmpty()) {
                QStringList kv = line.split("=");
                if(kv.length() > 1) {
                    QString k_ = kv.at(0).trimmed();
                    if(k == k_) {
                        line = k + "=" + v;
                        up = true;
                    }
                }
            }
            s += line + "\n";
        }
    }
    if(!up) {
        s += k + "=" + v + "\n";
    }
    ut::file::writeText(cfg->localCfgFileName, s.trimmed());
}

void App::set(QString k, QString v, bool init) {
    DB_Async->exe([=] {
       envDao->set(k,v);
       if(init){
         init0();
       }
    });
}

void App::init0() {
    QObject *obj = engine->rootObjects()[0];
    QMetaObject::invokeMethod(obj, "init",
                Q_ARG(QVariant, QVariant::fromValue(this->getUIData())));
}
QVariantMap App::getUIData() {
    uint lastCollectLeftWidth = 0;
    uint lastBookLeftWidth = 0;
    QString wh = "";
    uint maxWindow = 0;
    QStringList localCfgLines = ut::file::allLines(cfg->localCfgFileName);
    if(localCfgLines.length() > 0) {
        for(QString line : localCfgLines) {
            line = line.trimmed();
            if(!line.isEmpty()) {
                QStringList kv = line.split("=");
                if(kv.length() > 1) {
                    QString k = kv.at(0).trimmed();
                    QString v = kv.at(1).trimmed();
                    if(k == ENV_K_LAST_BOOK_LEFT_WIDTH) {
                        lastBookLeftWidth = v.toUInt();
                    } else if(k == ENV_K_LAST_COLLECT_LEFT_WIDTH) {
                        lastCollectLeftWidth = v.toUInt();
                    } else if(k == ENV_K_LAST_WH) {
                        wh = v;
                    } else if(k == "maxWindow") {
                        maxWindow = v.toUInt();
                    }
                }
            }
        }
    }

    QVariantMap data;
    uint vt = envDao->getUInt(ENV_K_LAST_VIEW_TYPE);
    QString sort = envDao->get(ENV_K_LAST_SORT, "p");
    data.insert(ENV_K_LAST_VIEW_TYPE, vt);
    data.insert(ENV_K_LAST_SORT, sort);
    data.insert(ENV_K_LAST_WH, wh.split(","));
    data.insert(ENV_K_LAST_COLLECT_LEFT_WIDTH, lastCollectLeftWidth);
    data.insert(ENV_K_LAST_BOOK_LEFT_WIDTH, lastBookLeftWidth);
    data.insert("maxWindow", maxWindow);
    return data;
}
void App::encrypt(uint id, QString k, uint listWidth, uint cbid) {
    if(lg->isDebug()){
        lg->debug(QString("encrypt pk id %1").arg(id));
    }
    DB_Async->exe([=]{
        PK *pk = pkDao->getPK(id);
        Com_Async->exe([=]{
            if(pk && !pk->jm) {
                if(pk->cont.length() > 0) {
                    uint len = pk->cont.length();
                    pk->cont = ut::cipher::encryptTextAES(k, pk->cont);
                    if(lg->isDebug()){
                        lg->debug(QString("encrypt pk cont len %1 -> %2").arg(len).arg(pk->cont.length()));
                    }
                }
                if(pk->img.length() > 0) {
                    QString imgPath = cfg->imgDir + "/" + pk->img;
                    QByteArray imgData = ut::img::toByteArray(imgPath);
                    QByteArray encodeData = ut::cipher::encryptAES(k, imgData);
                    QFileInfo tmpImgFile(cfg->tmpDir + "/" + pk->img);
                    QDir d;
                    if(!d.exists(tmpImgFile.path())) {
                        d.mkpath(tmpImgFile.path());
                    }
                    ut::file::writeData(tmpImgFile.filePath(), encodeData);
                    if(lg->isDebug()){
                        lg->debug(QString("encrypt pk img %1 %2 tmp img %3 %4")
                                   .arg(imgData.size()).arg(imgPath)
                                   .arg(encodeData.size()).arg(tmpImgFile.filePath()));
                    }
                }
            }
            QVariantMap resp;
            resp.insert("cid", pk->cid);
            resp.insert("cont", pk->cont);
            QString simpleCont = extractPKSimpleCont(pk->cont, "");
            resp.insert("simple_qmls", doc_parser->parseQML(simpleCont, listWidth));
            sendMsg(cbid, resp);
            delete pk;
        });
    });
}
void App::decrypt(uint id, QString k, uint listWidth, uint cbid) {
    if(lg->isDebug()) {
        lg->debug(QString("decrypt %1").arg(id));
    }
    DB_Async->exe([=]{
        PK *pk = pkDao->getPK(id);
        Com_Async->exe([=]{
            if(pk && pk->jm) {
                if(pk->cont.length() > 0) {
                    uint len = pk->cont.length();
                    pk->cont = ut::cipher::decryptTextAES(k, pk->cont);
                    if(lg->isDebug()){
                        lg->debug(QString("decrypt id %1 cont len %2 -> %3")
                                   .arg(id).arg(len).arg(pk->cont.length()));
                    }
                }
                if(pk->img.length() > 0) {
                    QString imgPath = cfg->imgDir + "/" + pk->img;
                    QByteArray data = ut::file::toByteArray(imgPath);
                    QByteArray decodeData = ut::cipher::decryptAES(k, data);
                    QFileInfo tmpImgFile(cfg->tmpDir + "/" + pk->img);
                    QDir d;
                    if(!d.exists(tmpImgFile.path())) {
                        d.mkpath(tmpImgFile.path());
                    }
                    ut::file::writeData(tmpImgFile.filePath(), decodeData);
                    if(lg->isDebug()) {
                        lg->debug(QString("decrypt id %1 img %2 len %3 tmpImg %4 len %5")
                                   .arg(id).arg(imgPath).arg(data.size()).arg(tmpImgFile.filePath()).arg(decodeData.size()));
                    }
                }
            }
            pk->simpleCont = extractPKSimpleCont(pk->cont, "");
            sendMsg(cbid, pk->toVMap(1,1,listWidth));
            delete pk;
        });
    });
}
void App::ensureEncryptOrDecrypt(uint id, QString cont, uint cbid) {
    DB_Async->exe([=]{
        int st = 0;
        PK *pk = pkDao->getPK(id);
        if(pk) {
            bool up = false;
            if(cont.length() > 0) {
                if(lg->isDebug()){
                    lg->debug(QString("ensureEncryptOrDecrypt id %1 jm %2").arg(id).arg(pk->jm));
                }
                pk->cont = cont;
                up = true;
            }
            QString imgPath = cfg->imgDir + "/" + pk->img;
            QString enOrDecryptFile = cfg->tmpDir + "/" + pk->img;
            if(ut::file::exists(enOrDecryptFile)) {
                if(lg->isDebug()) {
                    lg->debug(QString("ensureEncryptOrDecrypt exists enOrDecryptFile %1 id %2 jm %3")
                               .arg(imgPath).arg(id).arg(pk->jm));
                }
                ut::file::rm(imgPath);
                ut::file::rename(enOrDecryptFile, imgPath);
                up = true;
            }
            if(up) {
                pk->jm = !pk->jm;
                pkDao->updatePK(id, pk->cont, pk->jm);
            }
        } else {
            st = 1;
        }
        sendMsg(cbid, st);
        delete pk;
    });
}

QString mainImgConvHtml(QString img) {
    if(img.length() > 0){
        QString imgPath = cfg->imgDir + "/" + img;
        QVariantList r = calWinHeight(img, GEN_PDF_MAX_WIDTH);
        return "<img src='" + getFilePre() + imgPath+"' width='"+r[1].toString()+"' height='"+r[2].toString()+"'/>";
    }
    return "";
}

QString extractName(QString cont, int len=16) {
    QString name = cont.mid(0, 200);
    //
    QRegularExpression reg_title("# (.+)");
    QRegularExpressionMatch match = reg_title.match(cont);
    if(match.hasMatch()) {
        name = match.captured(1);
    }
    return name.replace(",", "")
    //            .replace(".", "")
                .replace("`", "")
                .replace(":", "")
                .replace("：", "")
                .replace("/", "")
                .replace("\\", "")
                .replace("*", "")
                .replace("?", "")
                .replace("\"", "")
                .replace("'", "")
                .replace("<", "")
                .replace(">", "")
                .replace("|", "")
    //            .replace(" ", "_")
                .replace("\n", "")
                .trimmed().mid(0, len);
}
void setXMBlogTag(uint id) {
    DB_Async->exe([id] {
        Tag *tag = tagDao->getByName(cfg->site_xmblog_tag);
        if(!tag) {
            tag = new Tag();
            tag->tag = cfg->site_xmblog_tag;
            tagDao->add(tag);
        }
        PK *pk = pkDao->getPK(id);
        QString tagId_ = QString("#%1#").arg(tag->id);
        if(!pk->tags.contains(tagId_)) {
            QString tags = pk->tags;
            if(tags.isEmpty()) {
                tags = tagId_;
            } else {
                tags = tags + QString::number(tag->id) + "#";
            }
            pkDao->updatePKTags(id, tags);
            pushMsg(PUSH_UP_TAGS, ut::col::createMap("id", id, "tags", tags));
        }
        delete tag;
        delete pk;
    });
}
void delXMBlogTag(uint id) {
    DB_Async->exe([id] {
        Tag *tag = tagDao->getByName(cfg->site_xmblog_tag);
        if(!tag) {
            return;
        }
        PK *pk = pkDao->getPK(id);
        if(pk) {
            QString tagId_ = QString("#%1#").arg(tag->id);
            if(pk->tags.contains(tagId_)) {
                //#1#2#3#4#5#
                pk->tags = pk->tags.replace("#"+QString::number(tag->id), "");
                pkDao->updatePKTags(id, pk->tags);
                pushMsg(PUSH_UP_TAGS, ut::col::createMap("id", id, "tags", pk->tags));
            }
            delete pk;
        }
        delete tag;
    });
}
void App::genFile(uint fileType, uint type, uint gid, uint id, bool batch, QString pwd) {
    if(lg->isDebug()) {
        lg->debug(QString("genFile fileType %1 type %2 gid %3 id %4").arg(fileType).arg(type).arg(gid).arg(id));
    }
    DB_Async->exe([=] {
        QString *cont = new QString();
        QString filename = "";
        QString file = cfg->fileDir;
        uint maxWidth = fileType == FILE_TYPE_PDF ? GEN_PDF_MAX_WIDTH : 0;
        if(type == CONT_TYPE_PK) {
            if(gid > 0) {
                uint fromId = 0;
                while(true) {
                    QList<PK*> list = pkDao->getPKList("", gid, fromId);
                    if(lg->isDebug()) {
                        lg->debug(QString("gen pk file %1 %2 %3 fromId %4").arg(fileType).arg(gid).arg(list.size()).arg(fromId));
                    }
                    if(list.size() == 0) {
                        break;
                    }
                    for(int i = 0; i < list.size(); i++) {
                        PK *pk = list.at(i);
                        if(fileType == FILE_TYPE_XM) {
                            if(batch) {
                                if(!pk->jm) {
                                    file = xm->createXMFile(extractName(pk->cont), pk->img, pk->cont, pwd);
                                }
                            } else {
                                if(!pk->jm) {
                                    if(pk->img.length() > 0) {
                                        cont->append("!(" + pk->img + ")\n");
                                    }
                                    if(pk->cont.length() > 0) {
                                        cont->append(pk->cont+"\n\n");
                                    }
                                }
                            }
                        } else {
                            if(!pk->jm) {
                                if(pk->img.length() > 0) {
                                    cont->append("<p>"+mainImgConvHtml(pk->img)+"</p>");
                                }
                                if(pk->cont.length() > 0){
                                    cont->append("<p>"+doc_parser->parseHtml(pk->cont, maxWidth)+"</p>");
                                }
                            }
                        }
                        delete pk;
                    }
                    fromId = list.last()->id;
                }
                Collect *c = colDao->getCollect(gid);
                if(c) {
                    filename = extractName(c->name, c->name.length());
                }
                delete c;
            } else if(id > 0) {
                if(lg->isDebug()) {
                    lg->debug(QString("gen pk file %1 %2").arg(fileType).arg(id));
                }
                PK *pk = pkDao->getPK(id);
                if(pk) {
                    filename = extractName(pk->cont, fileType == FILE_TYPE_SITE?50:16);
                    if(fileType == FILE_TYPE_XM) {
                        file = xm->createXMFile(filename, pk->img, pk->cont, pwd);
                    } else {
                        if(pk->img.length() > 0) {
                            cont->append(mainImgConvHtml(pk->img));
                        }
                        if(pk->cont.length() > 0) {
                            cont->append(doc_parser->parseHtml(pk->cont, maxWidth));
                        }
                        if(fileType == FILE_TYPE_SITE) {
                            file = createSiteFile(filename, *cont, pk->time);
                            setXMBlogTag(pk->id);
                        }
                    }
                }
                delete pk;
            }
        } else if(type == CONT_TYPE_BOOK) {
            if(gid > 0) {
                uint page = 0;
                QString xmCont;
                while(true) {
                    QString sort = envDao->get(ENV_K_LAST_SORT);
                    QList<Note*> list = noteDao->getNoteList("", gid, page, sort);
                    if(list.size() == 0) {
                        break;
                    }
                    for(int i = 0; i < list.size(); i++) {
                        Note *n = list.at(i);
                        if(n->cont.length() > 0) {
                            if(fileType == FILE_TYPE_XM) {
                                xmCont += n->cont + "\n\n";
                            } else {
                                if(n->bj) {
                                    cont->append("<p class='item-bj'>"+doc_parser->parseHtml(n->cont, maxWidth)+"</p>");
                                } else {
                                    cont->append("<p class='item'>"+doc_parser->parseHtml(n->cont, maxWidth)+"</p>");
                                }
                            }
                        }
                        delete n;
                    }
                    page++;
                }
                Work *w = workDao->get(gid);
                if(w) {
                    filename = "《" + w->name + "》笔记";
                    filename = extractName(filename, filename.length());
                    delete w;
                }
                if(fileType == FILE_TYPE_XM) {
                    file = xm->createXMFile(filename, "", xmCont, "");
                } else {
                    if(fileType == FILE_TYPE_SITE) {
                        file = createSiteFile(filename, *cont, w->time);
//                            setXMBlogTag(w->id);
                    }
                }
            } else if(id > 0) {
                Note *n = noteDao->get(id);
                if(n) {
                    if(n->cont.length() > 0) {
                        filename = extractName(n->cont);
                        if(fileType == FILE_TYPE_XM){
                            file = xm->createXMFile(filename, "", n->cont, "");
                        } else {
                            if(n->bj) {
                                cont->append("<p"+NOTE_BJ_STYLE+">"+doc_parser->parseHtml(n->cont, maxWidth)+"</p>");
                            } else {
                                cont->append(doc_parser->parseHtml(n->cont, maxWidth));
                            }
                        }
                    }
                    delete n;
                }
            }
        }
        //
        if(cont->length() > 0) {
            if(filename.length() == 0) {
                filename = "xxmoon_" + ut::time::getCurrentTimeStr();
            }
            if(fileType == FILE_TYPE_PDF) {
                file = cfg->fileDir + "/" + (filename+".pdf");
                QFile pdf_file(file);
                pdf_file.open(QIODevice::WriteOnly);
                QPdfWriter *pdf_writer = new QPdfWriter(&pdf_file);
                pdf_writer->setPageSize(QPagedPaintDevice::A4);
    //            pdf_writer->setResolution(30);
    //            qDebug() << "pdf" << pdf_writer->pageSize() << pdf_writer->pageSizeMM();
                pdf_writer->setCreator("xxmoon");
                pdf_writer->setTitle("xxmoon");
                QTextDocument doc;
                doc.setHtml(*cont);
                doc.print(pdf_writer);
                delete pdf_writer;
            } else if(fileType == FILE_TYPE_HTML) {
                file = cfg->fileDir + "/" + (filename+".html");
                QString css = "<style>"+ut::file::readFile(":assets/com.css")+"</style><div class='main'>";
                cont->insert(0, css);
                cont->append("</div>");
                ut::file::writeText(file, *cont);
            } else if(fileType == FILE_TYPE_XM) {
                file = xm->createXMFile(filename, "", *cont, "");
            }
        }
        QObject *root = engine->rootObjects()[0];
        QMetaObject::invokeMethod(root, "onGenFile",
                                  Q_ARG(QVariant, QVariant::fromValue(file)));
        delete cont;
    });
}

void App::deleteFromSite(uint id, uint type) {
    DB_Async->exe([id, type]() {
        QString filename = "";
        if(type == CONT_TYPE_PK) {
            PK *pk = pkDao->getPK(id);
            if(pk) {
                filename = extractName(pk->cont, 50);
            }
            delete pk;
        } else if(type == CONT_TYPE_BOOK) {
            Work *w = workDao->get(id);
            if(w) {
                filename = "《" + w->name + "》笔记";
                filename = extractName(filename, filename.length());
            }
            delete w;
        }
        if(!filename.isEmpty()) {
            wstring str = getNamePingyin(filename.toStdWString(), true);
            filename = QString::fromWCharArray(str.c_str());
            QString path = cfg->sitedir + "/" + filename + ".html";
            bool ok = QFile::remove(path);
            qDebug() << "del file" << path << ok;

            QString indexFile = cfg->sitedir + "/index.html";
            QString cont = ut::file::readFile(indexFile);
            filename = filename.replace("(", "[(]")
                               .replace(")", "[)]");
            QString regStr = "[<]li[>].+"+filename+".+([<]/li[>])?";
            qDebug() << "reg" << regStr;
            QRegularExpression reg(regStr);
            QRegularExpressionMatchIterator it = reg.globalMatch(cont);
            if (it.hasNext()) {
                QRegularExpressionMatch match = it.next();
                if(match.hasMatch()) {
                    QString li_ = match.captured(0);
                    cont = cont.replace(li_, "");
                    cont = cont.replace("\n\n", "\n");
                    ut::file::writeText(indexFile, cont);
                }
            }
            alert(QObject::tr("Delete Success!"));
        }
        delXMBlogTag(id);
    });
}

QString getExtra(QString filename) {
    if(cfg->site_detail_extra_id == 0) {
        return "";
    }
    PK *pk = pkDao->getPK(cfg->site_detail_extra_id);
    QString cont = pk->cont;
    if(cont.length() > 0) {
        QString tag1 = "---\n";
        int start = cont.indexOf(tag1);
        QString extraTmp = "";
        if(start >= 0) {
            extraTmp = cont.mid(start+tag1.length()).trimmed();
        } else {
            extraTmp = cont.trimmed();
        }
        if(extraTmp.startsWith("```")) {
            extraTmp = ut::str::removeFirstLine(extraTmp);
            if(extraTmp.endsWith("```")) {
                extraTmp = ut::str::removeEndLine(extraTmp);
            }
        }
        QMap<QString,QString> map;
        map.insert("filename", filename);
        QString extra = ut::str::fillTmpl(extraTmp, map);
        return extra;
    }
    return "";
}

QString App::createSiteFile(QString filename, QString cont, qint64 ct) {
    //去掉cont中---\n以下的内容
    QString tag = "---<br>";
    int i = cont.lastIndexOf(tag);
    if(i >= 0) {
        cont = cont.mid(0, i);
    }
    QString title = filename;
    wstring str = getNamePingyin(filename.toStdWString(), true);
    filename = QString::fromWCharArray(str.c_str());

    QDir dir;
    if(!dir.exists(cfg->sitedir)) {
        dir.mkpath(cfg->sitedir);
    }
    //
    QString stylefile = cfg->sitedir + "/com.css";
    if(!ut::file::exists(stylefile)) {
        ut::file::writeText(cfg->sitedir+"/com.css", ut::file::readFile(":assets/com.css"));
    }
    QString jsfile = cfg->sitedir + "/com.js";
    if(!ut::file::exists(jsfile)) {
        ut::file::writeText(cfg->sitedir+"/com.js", ut::file::readFile(":assets/com.js"));
    }

    QString sitename = cfg->sitename;
    QString sitetitle = cfg->sitetitle;
    QString time = QDateTime::fromSecsSinceEpoch(ct).toString("yyyy/MM/dd hh:mm");
    QString date = QDateTime::fromSecsSinceEpoch(ct).toString("yyyy/MM/dd");

    QString indexfile = cfg->sitedir+"/index.html";
    QMap<QString,QString> indexmap;
    indexmap.insert("name", sitename);
    indexmap.insert("title", sitetitle);
    indexmap.insert("date", date);
    indexmap.insert("href", filename+".html");
    indexmap.insert("itemTitle", title);
    indexmap.insert("ct", QString::number(ct));
    if(!ut::file::exists(indexfile)) {
        QString indextmpl = ut::file::readFile(":assets/tmpl_index.html");
        QString indexhtml = ut::str::fillTmpl(indextmpl, indexmap);
        ut::file::writeText(indexfile, indexhtml);
    } else {
        QString indexhtml = ut::file::readFile(indexfile);
        QString newindexhtml = insertIndexItem(indexhtml, indexmap);
        if(newindexhtml.length() > 0) {
            ut::file::writeText(indexfile, newindexhtml);
        }
    }
    QString detailtmpl = ut::file::readFile(":assets/tmpl_detail.html");
    QString targetFile = cfg->sitedir + "/" + filename + ".html";
    QMap<QString, QString> m;
    m.insert("itemTitle", title);
    m.insert("cont", cont);
    m.insert("time", time);
    m.insert("extra", getExtra(filename));
    qDebug() << m.value("extra");
    QString html = ut::str::fillTmpl(detailtmpl, m);

    //img
    QString tag1 = "<img src='";
    QString tag2 = "/>";
    QString tag3 = "<img src='";
    QString tag4 = "' width='";
    QStringList imgs;
    QStringList newimgs;
    int fromI = 0;
    while(fromI >= 0) {
        std::tuple<QString,int,int> tp = ut::str::findByTag(html, tag1, tag2, fromI);
        QString img = get<0>(tp);
        int i1 = get<2>(tp);
        if(img.length() > 0) {
            QString imgtag = tag1+img+tag2;
            imgs.append(imgtag);
            tuple<QString, int, int> imgtagTP = ut::str::findByTag(imgtag, tag3, tag4);
            QString imgFile = get<0>(imgtagTP);
            if(imgFile.length() > 0) {
                imgFile = ut::str::removePrefix(imgFile, getFilePre());
                QString newImgRef = imgFile.mid(imgFile.indexOf(cfg->userBaseDir)+cfg->userBaseDir.length()+1);
                int i4 = get<2>(imgtagTP);
                QString newImgTag = tag1 + newImgRef + imgtag.mid(i4);
                newimgs.append(newImgTag);
                //
                QString newImgFilePath = cfg->sitedir + "/" + newImgRef;
                QFileInfo newImgFileInfo(newImgFilePath);
                QDir d = newImgFileInfo.absoluteDir();
                d.mkpath(d.absolutePath());
                QFile f;
                f.copy(imgFile, newImgFilePath);
            } else {
                newimgs.append("");
            }
            fromI = i1 + tag2.length();
        } else {
            break;
        }
    }
    if(imgs.length() > 0 && imgs.length() == newimgs.length()) {
        for(int i = 0; i < imgs.length(); i++) {
            QString oldImg = imgs.at(i);
            QString newImg = newimgs.at(i);
            html.replace(oldImg, newImg);
        }
    }
    //
    ut::file::writeText(targetFile, html);
    return targetFile;
}

QString App::insertIndexItem(QString indexhtml, QMap<QString,QString> indexmap) {
    QString itemtmpl = "<li><a href=\"${href}\">${itemTitle}</a><span class=\"date\">${date}</span></li>";
    QString itemhtml = ut::str::fillTmpl(itemtmpl, indexmap);
    QStringList lines = indexhtml.split("\n");
    //
    QString t1 = "<a href=\"";
    QString t2 = "\">";
    QString curherf = indexmap.value("href");
    qint64 curct = indexmap.value("ct").toLongLong();
    for(QString line : lines) {
        line = line.trimmed();
        QString href = get<0>(ut::str::findByTag(line, t1, t2));
        if(href == curherf) {
            return "";
        }
    }
    //
    QString tag1 = "<span class=\"date\">";
    QString tag2 = "</span>";
    QString df = "yyyy/MM/dd";
    QString newhtml = "";
    bool found = false;
    bool scanListStart = false;
    bool scanListEnd = false;
    int insertCount = 0;
    for(QString line : lines) {
        line = line.trimmed();
        if(!found) {
            QString datestr = get<0>(ut::str::findByTag(line, tag1, tag2));
            if(datestr.length() > 0) {
                scanListStart = true;
                qint64 itemSec = QDateTime::fromString(datestr, df).toSecsSinceEpoch();
                if(curct >= itemSec) {
                    newhtml += "\n" + itemhtml + "\n";
                    found = true;
                    insertCount++;
                }
            } else {
                if(scanListStart) {
                    if(!scanListEnd) {
                        newhtml += "\n" + itemhtml + "\n";
                        scanListEnd = true;
                        insertCount++;
                    }
                }
            }
        }
        newhtml += line+"\n";
    }

    if(insertCount == 0) {
        QString ulTag = "<ul class=\"list\">";
        int i = newhtml.indexOf(ulTag);
        if(i >= 0) {
            newhtml.insert(i + ulTag.length(), "\n"+itemhtml+"\n");
        }
    }
    newhtml = newhtml.replace("\n\n", "\n");
    return newhtml.trimmed();
}

QStringList App::getFilesInDir(QString path) {
    QStringList files;
    path = ut::str::removePrefix(path, getFilePre());
    QDir dir(path);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        QString fileName = fileInfo.fileName();
        QRegularExpressionMatch match = Reg_Text_Img.match(fileName, 0, QRegularExpression::MatchType::PartialPreferCompleteMatch);
        bool matching = match.hasMatch();
        if(matching) {
            QString fullPath = path + fileName;
            files.append(fullPath);
        }
    }
    return files;
}

void openFile(QString file) {
    #ifdef Q_OS_MAC
    if(cfg->editor == "vi") {
        QString tmpCmdFile = cfg->tmpDir + "/vi.command";
        ut::file::writeText(tmpCmdFile, "#!/bin/sh \nvim "+file+"\n",
                            QFile::Permission::ReadUser |
                            QFile::Permission::ReadGroup |
                            QFile::Permission::ReadOther |
                            QFile::Permission::WriteUser |
                            QFile::Permission::ExeUser |
                            QFile::Permission::ExeGroup |
                            QFile::Permission::ExeOther);
        process->startDetached("open "+ tmpCmdFile);
    } else {
        process->startDetached("open -a \"" + cfg->editor + "\" " + file);
    }
    #endif
    #ifdef Q_OS_WIN
    if(cfg->editor == "vi") {

    } else {
        process->startDetached("\"" + cfg->editor + "\" " + file);
    }
    #endif
    #ifdef Q_OS_LINUX
    if(cfg->editor == "vi"){

    } else {
        process->startDetached(cfg->editor + " " + file);
    }
    #endif
}
void App::openInExternal(int type, QString param, uint obj) {
    if(type == 0) {
        QString img = ut::str::removePrefix(param, getFilePre());
        #ifdef Q_OS_MAC
        process->start("open -a Preview "+img);
        #endif
        #ifdef Q_OS_WIN
        img = img.replace("/", "\\");
        process->start("mspaint.exe " + img);
        #endif
    } else if(type == 1) {
        uint id = param.toUInt();
        DB_Async->exe([=] {
            bool ok = false;
            QString cont = "";
            QString pre = "";
            if(obj == 0) {
                PK* pk = pkDao->getPK(id);
                if(pk) {
                    cont = pk->cont;
                    pre = cfg->tmpPKPre;
                    ok = true;
                }
                delete pk;
            } else {
                Note* n = noteDao->get(id);
                if(n) {
                    cont = n->cont;
                    pre = cfg->tmpNotePre;
                    ok = true;
                }
                delete n;
            }
            if(ok) {
                QString tmpFile = cfg->tmpDir + "/" + pre + QString::number(id) + ".txt";
                ut::file::writeText(tmpFile, cont);
                openFile(tmpFile);
            }
        });
    } else if(type == 2) {
        openFile(param);
    }
}
void App::openDir(QString path) {
    if(lg->isDebug()){
        lg->debug(QString("openDir %1").arg(path));
    }
#if defined(Q_OS_MAC)
    process->start("open -R \"" + path+"\"");
#elif defined(Q_OS_WIN)
    const QString explorer = "explorer";
    QStringList param;
    if (!QFileInfo(path).isDir())
        param << QLatin1String("/select,");
    param << QDir::toNativeSeparators(path);
    QProcess::startDetached(explorer, param);
    #endif
}

void App::checkTmpFile() {
    QDir dir(cfg->tmpDir);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        bool isAct = fileInfo.fileName() == cfg->tmpActFile;
        bool isPK = fileInfo.fileName().startsWith(cfg->tmpPKPre);
        bool isNote = fileInfo.fileName().startsWith(cfg->tmpNotePre);
        if(isAct) {
            QString data = ut::file::readFile(cfg->tmpDir+"/"+cfg->tmpActFile);
            QObject *qmlRoot = engine->rootObjects()[0];
            if(data.length() > 0){
                if(lg->isDebug()){
                    lg->debug(QString("act data %1").arg(data));
                }
                QStringList arr = data.split("\n");
                if(arr.length() > 0){
                    QString xmFile = arr[0].trimmed();
                    PK *pk = xm->openFile(xmFile, "");
                    if(pk) {
                        QMetaObject::invokeMethod(qmlRoot, "openXM",
                                                  Q_ARG(QVariant, QVariant::fromValue(pk->toVMap(true))));
                    }
                }
            }
            QWindow *w = qobject_cast<QWindow*>(qmlRoot);
            w->show();

            ut::file::rm(cfg->tmpDir + "/" + cfg->tmpActFile);
        } else if(isPK || isNote) {
            bool needUpdate = false;
            uint lastModTime = tmpFileLSTMap.value(fileInfo.fileName(), 0);
            if(lastModTime > 0) {
                if(fileInfo.lastModified().toMSecsSinceEpoch() > lastModTime) {
                    needUpdate = true;
                }
            } else {
                needUpdate = true;
            }
            if(needUpdate) {
                uint len = isPK ? cfg->tmpPKPre.length() : cfg->tmpNotePre.length();
                uint id = fileInfo.fileName().mid(len, fileInfo.fileName().length()-len-4).toUInt();
                QString cont = ut::file::readFile(fileInfo.filePath());
                if(fileInfo.fileName().startsWith(cfg->tmpPKPre)) {
                    updatePK0(id, cont);
                } else {
                    updateNote0(id, cont);
                }
                tmpFileLSTMap.insert(fileInfo.fileName(), fileInfo.lastModified().toMSecsSinceEpoch());
            }
        }
    }
}
void App::updatePK0(uint id, QString cont) {
    DB_Async->exe([=]{
        PK *pk = pkDao->getPK(id);
        if(pk != NULL) {
            if(pk->cont != cont) {
                if(!pk->jm) {
                    uint lst = ut::time::getCurSeconds();
                    pkDao->updatePK(id, cont, 0, lst);

                    pk->simpleCont = extractPKSimpleCont(cont, "");
                    pk->cont = cont;
                    QObject *root = engine->rootObjects()[0];
                    float w = ui::getUIVal(0).toFloat();
                    QMetaObject::invokeMethod(root, "onUpdatedPK",
                                              Q_ARG(QVariant, QVariant::fromValue(pk->toVMap(1, 1, w))));
                }
            }
        }
        delete pk;
    });
}
void App::updateNote0(uint id, QString cont) {
    DB_Async->exe([=]{
        Note *n = noteDao->get(id);
        if(n != NULL) {
            if(n->cont != cont) {
                noteDao->updateNote(id, n->pos0, n->pos1, cont);
                n->cont = cont;
                QObject *qmlRoot = engine->rootObjects()[0];
                float w = ui::getUIVal(1).toFloat();
                QMetaObject::invokeMethod(qmlRoot, "onUpdatedNote",
                                          Q_ARG(QVariant, QVariant::fromValue(n->toVMap(1, w))));
            }
        }
        delete n;
    });
}
void App::plainText(QString html, uint cbid) {
    QTextDocument doc;
    doc.setHtml(html);
    QString text = doc.toPlainText();
    sendMsg(cbid, text);
}

QString convComputerIDToKey(QString cid) {
    QString k;
    for(int i = 0; i < cid.length(); i++) {
        QChar c = cid.at(i);
        bool ok;
        int n = QString(c).toInt(&ok, 36);
        if(ok) {
            k += CODE_TABLE.at(n);
        }
    }
    return k;
}

bool App::checkAuth(QString auth, bool save) {
    if(auth.length() > 50) {
        QString k = convComputerIDToKey(getComputerID());
        QByteArray hashKey = QCryptographicHash::hash(k.toUtf8(), QCryptographicHash::Sha512);
        QString x = hashKey.toHex().toUpper();
        if(x == auth) {
            activated = true;
            if(save) {
                ut::file::writeText(cfg->auth_file, auth);
            }
        }
    }
    return activated;
}

void App::getCfg(QObject *obj) {
    DB_Async->exe([=] {
        QMetaObject::invokeMethod(obj, "onCfg", Q_ARG(QVariant, cfg->toVMap()));
    });
}

QString App::getKeyName(int key, int modifiers) {
    QString modi = QKeySequence(modifiers).toString().toUtf8();
    QString k = QKeySequence(key).toString().toUtf8();
    QByteArray kbytes = k.toLocal8Bit();
    QString kb64 = kbytes.toBase64();
    QString x;
#ifdef Q_OS_MAC
    x = "4Z+APw==";
    if(modi.startsWith("Ctrl+")) {
        modi = modi.replace("Ctrl+", "Cmd+");
    }
    if(modi.startsWith("Meta+")) {
        modi = modi.replace("Meta+", "Ctrl+");
    }
#endif
#ifdef Q_OS_WIN
    x = "Pz8=";
#endif
    if(kb64 == x) {//过滤非正常字符
        k = "";
    }
    if(lg->isDebug()) {
        lg->debug(QString("%1 %2 %3 %4 %5").arg(key).arg(modifiers).arg(modi).arg(k).arg(kb64));
    }
    return modi + k;
}

void App::setCfg(QString k, QString v) {
    qDebug() << "setCfg" << k << v;
    QString newCfg;
    bool found = false;
    if(ut::file::exists(cfg->cfgFileName)) {
        QStringList lines = ut::file::allLines(cfg->cfgFileName);
        for(QString line: lines) {
            if(line.length() > 0 &&
                    !line.startsWith("#") &&
                    line.indexOf("=") > 0) {
                QStringList kv = line.split("=");
                QString k_ = kv[0].trimmed();
                if(k == k_){
                    found = true;
                    line = k + "=" + v.trimmed();
                }
            }
            newCfg += line.trimmed() + "\n";
        }
    }
    if(!found) {
        newCfg += k+"="+v+"\n";
    }
    ut::file::writeText(cfg->cfgFileName, newCfg.trimmed());
    //
    if(k == "hot_key_pk"){
        QHotkey *hk = hotkMap.take(0);
        cfg->hot_key_pk = v;
        if(hk) {
            hk->destroyed();
            delete hk;
        }
        setGlobalHotkey(0, cfg->hot_key_pk);
    } else if(k == "hot_key_show") {
        QHotkey *hk = hotkMap.take(1);
        cfg->hot_key_show = v;
        if(hk) {
            hk->destroyed();
            delete hk;
        }
        setGlobalHotkey(0, cfg->hot_key_pk);
    } else if(k == "editor") {
        cfg->editor = v;
    }
}

void App::openXMFile(QString file, QString pwd, uint cbid) {
    file = ut::str::removePrefix(file, getFilePre());
    PK *pk = xm->openFile(file, pwd);
    if(pk) {
        sendMsg(cbid, pk->toVMap(true));
        delete pk;
    }
}

void App::importXM(QVariantMap pkdata) {
    DB_Async->exe([=]{
        PK *pk = new PK();
        pk->fill(pkdata);
        if(lg->isDebug()) {
            lg->trace(QString("importXM pkdata %1 -> %2").arg(ut::str::mapToStr(pkdata)).arg(pk->toString()));
        }
        QObject* root = engine->rootObjects()[0];
        if(!pk) {
            QMetaObject::invokeMethod(root, "onFinished",
                                  Q_ARG(QVariant, QVariant::fromValue(CONT_TYPE_PK)),
                                  Q_ARG(QVariant, QVariant::fromValue(-1)),
                                  Q_ARG(QVariant, QVariant::fromValue(-1)),
                                  Q_ARG(QVariant, QVariant::fromValue(0)));
            return;
        }
        //copy资源
        QString year = ut::time::getYearStr();
        QDir resDir(cfg->imgDir+"/tmp/"+pk->uuid);
        QFileInfoList files = resDir.entryInfoList();
        QMap<QString, QString> nameMap;
        for(QFileInfo f:files) {
//            if(f.fileName().endsWith(".png")) {
                QString path = cfg->imgDir + "/" + year;
                QDir dir(path);
                if(!dir.exists()){
                    dir.mkpath(path);
                }
                int from = f.fileName().indexOf(".");
                if(from > 0) {
                    QString filename = ut::time::getCurrentTimeStr()+f.fileName().mid(from);
                    nameMap.insert(f.fileName(), filename);
                    QString from = f.filePath();
                    QString to = path + "/" + filename;
                    QFile::copy(from, to);
                    if(lg->isDebug()){
                        lg->debug(QString("nameMap k %1 v %2").arg(f.fileName()).arg(filename));
                        lg->debug(QString("copy res %1 to %2").arg(from).arg(to));
                    }
                }
//            }
        }

        if(lg->isDebug()) {
            lg->debug(QString("nameMap %1").arg(ut::str::mapToStr(nameMap)));
        }

        //创建数据
        QStringList refs = extractImgsAsList(pk->cont);
        if(lg->isDebug()){
            lg->debug(QString("exists main img %1 refs size %2")
                       .arg(pk->img.length()>0).arg(refs.size()));
        }
        //如果有图片则创建一个Resource Folder
        Collect* resCol = NULL;
        uint resColID = colDao->getIDByName(FOLDER_RESOURCES);
        if(lg->isDebug()){
            lg->debug(QString("find res folder %1 %2").arg(resColID).arg(FOLDER_RESOURCES));
        }
        if(pk->img.length() > 0 || refs.size() > 0) {
            if(resColID <= 0) {
                uint maxI = colDao->getMaxI();
                resCol = new Collect();
                resCol->name = FOLDER_RESOURCES;
                resCol->i = maxI + 1;
                colDao->add(resCol);
                resColID = colDao->getIDByName(FOLDER_RESOURCES);
                if(lg->isDebug()) {
                    lg->debug(QString("add folder %1").arg(resCol->toString()));
                }
            }
        }
        //创建资源pk
        if(pk->img.length() > 0) {
            int i = pk->img.lastIndexOf("/");
            if(i > 0) {
                QString newName = year + "/" + nameMap.value(pk->img.mid(i+1), "");
                if(lg->isDebug()){
                    lg->debug(QString("rename main img %1 to %2").arg(pk->img).arg(newName));
                }
                pk->img = newName;
            }
        }
        for(QString ref:refs) {
            int i = ref.lastIndexOf("/");
            if(i > 0) {
                QString newName = year + "/" + nameMap.value(ref.mid(i+1), "");
                if(newName.length() > 0){
                    pk->cont.replace(ref, newName);
                    if(lg->isDebug()) {
                        lg->debug(QString("replace ref %1 to %2").arg(ref, newName));
                    }
                    //
                    PK *refPK = new PK();
                    refPK->cid = resColID;
                    refPK->img = newName;
                    pkDao->add(refPK);
                    if(lg->isDebug()) {
                        lg->debug(QString("add ref pk %1").arg(refPK->toString()));
                    }
                    delete refPK;
                }
            }
        }
        //
        Collect* defCol = colDao->getCollectByIndex(0);
        if(defCol) {
            pk->cid = defCol->id;
        }
        pkDao->add(pk);
        if(lg->isDebug()) {
            lg->debug(QString("add pk %1").arg(pk->toString()));
        }
        //
        if(resCol == NULL && resColID > 0) {
            resCol = colDao->getCollect(resColID);
        }
        if(resCol) {
            resCol->total = pkDao->countCol(resCol->id);
            if(lg->isDebug()) {
                lg->debug(QString("ret resCol %1").arg(resCol->toString()));
            }
            QMetaObject::invokeMethod(root, "onFinished",
                                  Q_ARG(QVariant, QVariant::fromValue(CONT_TYPE_PK)),
                                  Q_ARG(QVariant, QVariant::fromValue(-1)),
                                  Q_ARG(QVariant, QVariant::fromValue(-1)),
                                  Q_ARG(QVariant, QVariant::fromValue(resCol->toVMap())));
        } else {
            QMetaObject::invokeMethod(root, "onFinished",
                                  Q_ARG(QVariant, QVariant::fromValue(CONT_TYPE_PK)),
                                  Q_ARG(QVariant, QVariant::fromValue(-1)),
                                  Q_ARG(QVariant, QVariant::fromValue(-1)),
                                  Q_ARG(QVariant, QVariant::fromValue(0)));
        }
        delete pk;
        delete resCol;
        delete defCol;
    });
}

void App::copy(QString s) {
    ut::cpb::setText(s);
    st(0);
}

void App::copyImg(QString path) {
#ifdef Q_OS_WIN
    path = path.mid(8);
#endif
#ifdef Q_OS_MAC
    path = path.mid(7);
#endif
    QImage img(path);
    ut::cpb::setImage(img);
    st(0);
}
QString App::getVersion() {
    return VERSION;
}

void App::enableServer() {
    QMap<QString, QString> m;
    serverMsgQueue->push(std::make_tuple(Cmd_EnableServer, m));
}
void App::disableServer() {
    QMap<QString, QString> m;
    serverMsgQueue->push(std::make_tuple(Cmd_DisableServer, m));
}

void App::close(int r) {
    if(r < 0){
        return;
    }
    if(lg->isDebug()){
        lg->debug("close app");
    }
    DB_Async->exe([](){
        db->close();
    });
    DB_Async->close();
    Com_Async->close();
    SM_Async->close();
    running = false;
      
    QObject* root = engine->rootObjects()[0];
    QMetaObject::invokeMethod(root, "onClose");
    //
    for(uint ty: hotkMap.keys()) {
        QHotkey *hk = hotkMap.take(ty);
        if(hk) {
            hk->destroyed();
            delete hk;
        }
    }

    lg->close();
    db->close();
    sm->close();
    //
    QDir(cfg->tmpDir).removeRecursively();
    QDir(cfg->imgDir+"/tmp").removeRecursively();
    
    QThread::msleep(500);
    
    if(lg->isDebug()){
        lg->debug("close app done.");
    }
}

void App::genQRCode(int cbid) {
    QMap<QString, QString> m;
    m.insert("cbid", QString::number(cbid));
    serverMsgQueue->push(std::make_tuple(Cmd_GenQRCode, m));
}

void App::devices(int cbid) {
    QMap<QString, QString> m;
    m.insert("cbid", QString::number(cbid));
    serverMsgQueue->push(std::make_tuple(Cmd_DeviceList, m));
}
void App::delDev(QString dev, int cbid) {
    QMap<QString, QString> m;
    m.insert("cbid", QString::number(cbid));
    m.insert("dev", dev);
    serverMsgQueue->push(std::make_tuple(Cmd_DelDevice, m));
}
void App::sendToPhone(int ty, int id, int cbid) {
    DB_Async->exe([ty, id, cbid](){
        QString data = "";
        if(ty == CONT_TYPE_PK) {
            PK *pk = pkDao->getPK(id);
            QJsonObject jo = QJsonObject::fromVariantMap(pk->toVMap(true, false));
            data = QJsonDocument(jo).toJson(QJsonDocument::Compact);
            delete pk;
        } else if(ty == CONT_TYPE_BOOK) {
            Note *n = noteDao->get(id);
            if(n->wid > 0) {
                Work *w = workDao->get(n->wid);
                n->book = w->name;
                n->author = w->author;
                delete w;
            }
            QJsonObject jo = QJsonObject::fromVariantMap(n->toVMap(false));
            data = QJsonDocument(jo).toJson(QJsonDocument::Compact);
            delete n;
        }
        if(lg->isDebug()) {
            lg->debug(QString("sendToPhone %1").arg(data));
        }

        QMap<QString, QString> m;
        m.insert("cbid", QString::number(cbid));
        m.insert("data", data);
        serverMsgQueue->push(std::make_tuple(Cmd_SendToPhone, m));
    });
}

void App::getCurQRCode(int cbid) {
    QMap<QString, QString> m;
    m.insert("cbid", QString::number(cbid));
    serverMsgQueue->push(std::make_tuple(Cmd_GetCurQRCode, m));
}

void App::genCert(bool force, bool al) {
    if(force || !ut::file::exists(cfg->userBaseDir + "/public.crt") || !ut::file::exists(cfg->userBaseDir+"/private.key")) {
        QSslKey key;
        QSslCertificate cert;
        QString c="ZH", o="Senli", cn="Senli", ou="Senli", l="Senli", st="SZ";
        if(SslHelper::generateCredentials(cert,key,c,o,cn,ou,l,st) != SslHelper::ErrorNone) {
            lg->error("ERROR: Could not generate certificate.");
            if(al) alert(QObject::tr("cert gen fail"));
        } else {
            SslHelper::saveCertificate(cert, cfg->userBaseDir + "/public.crt");
            SslHelper::saveKey(key, cfg->userBaseDir + "/private.key");
            lg->info("cert gen suc");
            if(al) alert(QObject::tr("cert gen suc"));
        }
    }
}

void App::regMenuReceiver(QObject* o) {
#ifdef Q_OS_MAC
    menuManager->regReceiver(o);
#endif
}

void App::triggerMenu(int act) {
#ifdef Q_OS_MAC
    if(act == 3) {
        menuManager->onCopy(false);
    } else if(act == 4) {
        menuManager->onPaste(false);
    } else if(act == 5) {
        menuManager->onCut(false);
    }
#endif
}

bool App::existsAllowedURL() {
#ifdef Q_OS_MAC
    return mac->existsAllowedURL();
#endif
    return true;
}
void App::alertMacTip(QString tip1, QString tip2) {
#ifdef Q_OS_MAC
    mac->alert(tip1, tip2);
#endif
}
QString App::selectDataDir() {
#ifdef Q_OS_MAC
    QString path = mac->openSelectFile();
    if(path.isEmpty()) {
        lg->error(QString("selecte data path err"));
    } else {
        cfg->updateDataDir(path);
        setCfg("data_dir", cfg->dataDir);
    }
    return path;
#endif
    return "";
}

void App::init() {
    initPath();
    initLog();
#ifdef Q_OS_MAC
    menuManager->init();
#endif
    initDB();
}

void App::setUIVal(uint k, QString v) {
    ui::setUIVal(k, v);
}
QString App::getUIVal(uint k) {
    return ui::getUIVal(k);
}

void initPath() {
    QDir dir;
    if(!dir.exists(cfg->imgDir)) {
        dir.mkpath(cfg->imgDir);
    }
    if(!dir.exists(cfg->fileDir)) {
        dir.mkpath(cfg->fileDir);
    }
    if(!dir.exists(cfg->tmpDir)) {
        dir.mkpath(cfg->tmpDir);
    }
}

void initLog() {
    lg->init(cfg->logFile);
}

void initDB() {
    DB_Async->exe([=] {
        if (db->openDB()) {
            db->init();
            workDao->init();
            noteDao->init();
            colDao->init();
            pkDao->init();
            tagDao->init();
        } else {
            qDebug("db open error");
        }
    });
}

QString App::test() {
    return ut::file::readFile("/Users/sen/Desktop/go.html");
}

uint App::calLine(QString txt, int index) {
    uint curLine = txt.isEmpty()?0:1;
    for(int i = 0; i < txt.length(); i++) {
        if(txt[i] == "\u2029") {
            curLine++;
        }
        if(index == i) {
            return curLine;
        }
    }
    return curLine;
}
bool App::existFile(QString file) {
    QFile f(file);
    return f.exists();
}

Work* parseWork4Douban(QString s) {
    Work *w = new Work();
    int i = s.indexOf("《");
    if(i < 0) {
        return w;
    }
    int j = s.indexOf("》");
    if(j < 0) {
        return w;
    }
    int len = j - i - 1;
    if(len <= 0) {
        return w;
    }
    w->name = s.mid(i+1, len);
    return w;
}

Note* parseNote4Douban(QString s) {
    s = s.trimmed();
    Note *n = new Note();
    QString cont = "";
    QStringList lines = s.split("\n");
    for(int i = 0; i < lines.length()-1; i++) {
        lines[i] = lines[i].trimmed();
        if(lines[i].isEmpty()) {
            continue;
        }
        if(lines[i].startsWith("## 章节：")) {
            lines[i] = "## " + lines[i].mid(6);
        }
        if(lines[i].startsWith("> ")) {
            lines[i] = lines[i].mid(2);
        }
        cont += lines[i] + "\n";
    }
    n->cont = cont;

    QString lastLine = lines[lines.length()-1];
    QStringList arr = lastLine.split("% · ");
    if(arr.length() > 1) {
        n->pos0 = arr[0].toUInt();
        QString time_ = arr[1];
//        qDebug() << time_ << time_.mid(0,4) << time_.mid(5,2);
        QDateTime time(QDate(time_.mid(0,4).toInt(), time_.mid(5,2).toInt(), time_.mid(8,2).toInt()),
                       QTime(time_.mid(11,2).toInt(), time_.mid(14,2).toInt(), 0));
        n->time = time.toMSecsSinceEpoch() / 1000;
    }
    return n;
}

bool App::importDouban() {
    QString cont = ut::cpb::getText();
    if(cont.isEmpty()) {
        return false;
    }
    QStringList lines = cont.split("\n");
    if(lines.length() < 6) {
        return false;
    }
    if(!lines[2].contains("豆瓣阅读")) {
        return false;
    }
    DB_Async->exe([=] {
        QString item = "";
        Work *w = parseWork4Douban(lines[0]);
        w->fro = 1;
        uint c = 0;
        Note preNote;
        for(int i = 6; i < lines.length(); i++) {
            QString it = lines[i];
            item += it + "\n";
            if(it.contains("% · ")) {
                Note *n = parseNote4Douban(item);
                if(w->time <= 0) {
                    w->time = n->time;
                    workDao->add(w);
                }
                if(preNote.id > 0) {
                    if(n->time <= preNote.time) {
                        n->time = preNote.time + (preNote.time-n->time) + 1;
                    }
                }
                n->wid = w->id;
                noteDao->insert(n);
    //            qDebug() << w.toString();
    //            qDebug() << n.toString();
    //            qDebug() << "-----------------------";
                item = "";
                c++;
                preNote = *n;
                delete n;
            }
        }
        delete w;
        st(0, QString("已添加 %1 条笔记").arg(c));
        ut::cpb::clear();
    });
    return true;
}

bool App::importWechatRead() {
    return false;
}
