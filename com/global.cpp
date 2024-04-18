#include "com/global.h"
#include <QDir>
#include <QWindow>

Async *Com_Async = new Async("com");
Async *DB_Async = new Async("db");
Async *SM_Async = new Async("sm");
std::queue<std::tuple<int, QMap<QString, QString>>> *serverMsgQueue = new std::queue<std::tuple<int, QMap<QString, QString>>>();
std::mutex mtx;
QMap<QString, std::queue<QString>> *serverDataQueue = new QMap<QString, std::queue<QString>>();

volatile bool running = true;

QQmlApplicationEngine *engine;
#ifdef Q_OS_MAC
MenuManager *menuManager = new MenuManager();
#endif
Cfg *cfg = new Cfg();
App *app = new App();
XMAction* xmAction = new XMAction();
BookAction* bookAction = new BookAction();
L* l = new L();
SQLiteManager *db = new SQLiteManager();
WorkDao *workDao = new WorkDao();
NoteDao *noteDao = new NoteDao();
EnvDao *envDao = new EnvDao();
XMDao *xmDao = new XMDao();
CategoryDao *colDao = new CategoryDao();
TagDao *tagDao = new TagDao();
#ifdef Q_OS_MAC
Mac *mac = new Mac();
#endif
QProcess *process = new QProcess();
DocParser *doc_parser = new DocParser();
Log *lg = new Log();
XMFormat *xm_format = new XMFormat();
SM *sm = new SM();

QRegularExpression Reg_Kindle_Note(cfg->reg_kindle_flag);
QRegularExpression Reg_Text_Img(".+[.](txt|png|jpg|jpeg|bmp)$");
QRegularExpression Reg_Find_Img("[^`]![(](.+)[)]");
QRegularExpression Reg_Find_Refid("(?!`)![[](\\d+):?.*?[]]");
QRegularExpression Reg_Win_Path("^[a-zA-Z]:.+$");

bool activated = false;

///
//#tag1#tag2 x
QVariantList parseKeyTags(QString k) {
    QStringList tagList;
    k = k.trimmed();
    QString newK = k;
    if(k.startsWith("#")) {
        QStringList tags = k.split("#");
        for(int i = tags.length()-1; i >= 0; i--) {
            if(tags[i].trimmed().length()==0){
                tags.removeAt(i);
            }
        }
        for(int i = 0; i < tags.length(); i++) {
            QString tag = tags[i].trimmed();
            if(i == tags.length() - 1) {
                if(tag.contains(" ")) {
                    QStringList ks = tag.split(" ");
                    if(ks.length() > 1) {
                        newK = ks[1];
                        tagList.append(ks[0]);
                    }
                } else {
                    tagList.append(tag);
                    newK = "";
                }
            } else {
                tagList.append(tag);
            }
        }
    }
    return {tagList, newK};
}

QStringList parseTagIds(QString tags) {
    QStringList ids;
    if(tags.length()>0) {
        QStringList arr = tags.split("#");
        for(int i = 0; i < arr.length(); i++) {
            if(arr[i].length()>0){
                ids.append(arr[i]);
            }
        }
    }
    return ids;
}

QString fullImg(QString img) {
    return cfg->imgDir + "/" + img;
}
QList<double> calImgSizeByWidth(double srcW, double srcH, double maxWidth) {
    if(srcW <= 0 || srcH <= 0) {
        return {0, 0};
    }
    double w = srcW > maxWidth ? maxWidth : srcW;
    double ratio = srcW/srcH;
    double h = w/ratio;
    return {w, h};
}
QVariantList calWinHeight(QString k, uint maxWidth) {
    QStringList arr = k.split('.');
    if(maxWidth <= 0) {
        QWindow *w = qobject_cast<QWindow *>(engine->rootObjects()[0]);
        uint win_width = w->width();
        maxWidth = win_width - 310;
    }
    if(arr.length()>2) {
        uint w = arr[arr.length()-3].toUInt();
        uint h = arr[arr.length()-2].toUInt();
        QList<double> wh = calImgSizeByWidth(w, h, maxWidth);
        return {k, wh[0], wh[1]};
    } else {
        return {k, maxWidth, 200};
    }
}
QString getFilePre() {
#ifdef Q_OS_MAC
    return FILE_PRE_MAC;
#endif
    return FILE_PRE;
}

QString extractImgs(QString cont, bool rmdup) {
    QString s;
    QStringList imgs = extractImgsAsList(cont, rmdup);
    for(QString img:imgs) {
        s += img + ",";
    }
    return s;
}
QStringList extractImgsAsList(QString cont, bool rmdup) {
    QStringList imgs;
    QRegularExpressionMatchIterator it = Reg_Find_Img.globalMatch(" "+cont);
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        if(match.hasMatch()) {
            QString img = match.captured(1);
            if(!img.isEmpty()) {
                if(rmdup) {
                    if(!imgs.contains(img)) {
                        imgs << img;
                    }
                } else {
                    imgs << img;
                }
            }
        }
    }
    return imgs;
}
QString extractRefimgids(QString cont) {
    QString s;
    QStringList imgs = extractImgsAsList(cont, true);
    for(QString img:imgs) {
        uint id = xmDao->getIDByImg(img);
        if(id > 0) {
            s += "#" + QString::number(id);
        }
    }
    if(s.length() > 0) {
        s += "#";
    }
    return s;
}
QString extractRefIDs(QString cont) {
    QList<uint> refids = extractRefIDsAsList(cont);
    QString ids = "";
    for(uint id:refids) {
        ids += "#"+QString::number(id);
    }
    if(ids.length() > 0) {
        ids += "#";
    }
    return ids;
}
QList<uint> extractRefIDsAsList(QString cont) {
    QList<uint> refs;
    QRegularExpressionMatchIterator it = Reg_Find_Refid.globalMatch(" "+cont);
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        if(match.hasMatch()) {
            uint id = match.captured(1).toUInt();
            if(!refs.contains(id)) {
                refs << id;
            }
        }
    }
    return refs;
}
QString extractNoteSimpleCont(const QString& cont, const QString& k) {
    if(k.trimmed().length() == 0) {
        return cont.mid(0, SIMPLE_SIZE);
    }
    QString s = "";
    QString keyInCont = "";
    QStringList keys;
    if(k.startsWith("# ") || k.startsWith("a ") || k.startsWith("b ")) {
        QStringList arr =  k.split(" ");
        for(int i = 0; i < arr.length(); i++) {
            if(!arr[i].startsWith("# ") && !arr[i].startsWith("a ") && !arr[i].startsWith("b ")) {
                keyInCont = arr[i];
                keys.append(arr[i]);
            }
        }
    } else {
        keys = k.split(" ");
        if(keys.length() > 0) {
            keyInCont = keys[0];
        }
    }
    if(keyInCont != "") {
        int i = cont.indexOf(keyInCont, 0, Qt::CaseInsensitive);
        if(i > 0) {
//            i = ut::str::findFrontLine(cont, cfg->simple_cont_front_line, i);
            i = i - cfg->simple_cont_key_front;
        }
        s = cont.mid(max(0, i), SIMPLE_SIZE);
        s = ut::str::frontLine(s, cfg->simple_cont_max_line);
    } else {
        s = cont.mid(0, SIMPLE_SIZE);
    }
    //
    QList<tuple<int,int>> his;//之前的key的索引范围
    for(int i = 0; i < keys.length(); i++) {
        int ind = s.indexOf(keys[i], 0, Qt::CaseSensitivity::CaseInsensitive);
        if(ind >= 0) {
            bool ok = true;
            QString oldKey = s.mid(ind, keys[i].length());
            if(his.length() > 0) {
                for(int j = 0; j < his.length(); j++) {
                    if(ind >= std::get<0>(his[j]) && ind < std::get<1>(his[j])) {
                        ok = false;
                        break;
                    }
                }
            }
            if(ok) {//不在之前的key的索引范围内时才替换
                s = s.replace(ind, oldKey.length(), "@#red "+oldKey+"@");
                his.append(std::make_tuple(ind, ind+oldKey.length() + 7));
            } else {
                his.append(std::make_tuple(ind, ind+oldKey.length()));
            }
        }
    }
    return s;
}

QString extractPKSimpleCont(const QString& cont, const QString& k) {
    if(k.trimmed().length() == 0) {
        return cont.mid(0, SIMPLE_SIZE);
    }
    QString s = "";
    QString keyInCont = "";
    QStringList keys;
    if(k.startsWith("# ")) {
        QStringList arr =  k.split(" ");
        for(int i = 0; i < arr.length(); i++) {
            if(!arr[i].startsWith("# ")) {
                keyInCont = arr[i];
                keys.append(arr[i]);
            }
        }
    } else {
        keys = k.split(" ");
        if(keys.length() > 0) {
            keyInCont = keys[0];
        }
    }
    if(keyInCont != "") {
        int i = cont.indexOf(keyInCont, 0, Qt::CaseInsensitive);
        if(i > 0) {
//            i = ut::str::findFrontLine(cont, cfg->simple_cont_front_line, i);
            i = i - cfg->simple_cont_key_front;
        }
        s = cont.mid(max(0, i), SIMPLE_SIZE);
        s = ut::str::frontLine(s, cfg->simple_cont_max_line);
    } else {
        s = cont.mid(0, SIMPLE_SIZE);
    }
    //
    QList<tuple<int,int>> his;//之前的key的索引范围
    for(int i = 0; i < keys.length(); i++) {
        int ind = s.indexOf(keys[i], 0, Qt::CaseSensitivity::CaseInsensitive);
        if(ind >= 0) {
            bool ok = true;
            QString oldKey = s.mid(ind, keys[i].length());
            if(his.length() > 0) {
                for(int j = 0; j < his.length(); j++) {
                    if(ind >= std::get<0>(his[j]) && ind < std::get<1>(his[j])) {
                        ok = false;
                        break;
                    }
                }
            }
            if(ok) {//不在之前的key的索引范围内时才替换
                s = s.replace(ind, oldKey.length(), "@#red "+oldKey+"@");
                his.append(std::make_tuple(ind, ind+oldKey.length() + 7));
            } else {
                his.append(std::make_tuple(ind, ind+oldKey.length()));
            }
        }
    }
    return s;
}

void alert(const QString &msg, bool autoclose) {
    QObject* root = engine->rootObjects()[0];
    QMetaObject::invokeMethod(root, "alert",
                Q_ARG(QVariant, QVariant::fromValue(msg)),
                Q_ARG(QVariant, QVariant::fromValue(autoclose)));
}
void ensure(const QString &msg) {
    QObject* root = engine->rootObjects()[0];
    QMetaObject::invokeMethod(root, "ensure",
                Q_ARG(QVariant, QVariant::fromValue(msg)));
}
void st(uint st, QString msg) {
    QObject* root = engine->rootObjects()[0];
    QMetaObject::invokeMethod(root, "setStat",
                Q_ARG(QVariant, QVariant::fromValue(st)),
                Q_ARG(QVariant, QVariant::fromValue(msg)));
}

void pushServerData(QString dev, QString data) {
    mtx.lock();
    std::queue q = serverDataQueue->value(dev);
    q.push(data);
    serverDataQueue->insert(dev, q);
    mtx.unlock();
}

QString takeServerData(QString dev) {
    mtx.lock();
    QString data;
    auto q = serverDataQueue->value(dev);
    if(!q.empty()) {
        data = q.front();
        q.pop();
        serverDataQueue->insert(dev, q);
    }
    mtx.unlock();
    return data;
}
std::tuple<uint, uint> getWHFromFileName(QString fn) {
    int n = 0;
    int startIndex = -1;
    int endIndex = -1;
    for(int i = fn.size()-1; i >= 0; i--) {
        if(fn.at(i) == '.') {
            n++;
        }
        if(endIndex < 0 && n == 1) {
            endIndex = i;
        } else if(startIndex < 0 && n == 3) {
            startIndex = i;
            break;
        }
    }
    if(startIndex >= 0 && endIndex >= 0) {
        QString wh_ = fn.mid(startIndex+1, endIndex-startIndex-1);
        QStringList arr = wh_.split(".");
        if(arr.size() > 1) {
            return {arr[0].toUInt(), arr[1].toUInt()};
        }
    }
    return {0,0};
}
namespace ui {
    QMap<uint, QString> uiVals;
    void setUIVal(uint k, QString v) {
        uiVals.insert(k, v);
    }
    QString getUIVal(uint k) {
        return uiVals.value(k);
    }
}

void deleteFile(QString file) {
    QFile f(file);
    f.remove();
}
