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
App *a = new App();
XMAction* xmAction = new XMAction();
BookAction* bookAction = new BookAction();
L* l = new L();
SQLiteManager *db = new SQLiteManager();
WorkDao *workDao = new WorkDao();
NoteDao *noteDao = new NoteDao();
EnvDao *envDao = new EnvDao();
XMDao *xmDao = new XMDao();
CategoryDao *categoryDao = new CategoryDao();
TagDao *tagDao = new TagDao();
TaskLogDao *taskLogDao = new TaskLogDao();
#ifdef Q_OS_MAC
Mac *mac = new Mac();
#endif
QProcess *process = new QProcess();
DocParser *doc_parser = new DocParser();
Log *lg = new Log();
XMFormat *xm_format = new XMFormat();
SM *sm = new SM();
Trans *trans = new Trans();
Sync *sy = new Sync();
FileQueue *fq;

QRegularExpression Reg_Kindle_Note(cfg->regKindleFlag);
QRegularExpression Reg_Text_Img(".+[.](txt|png|jpg|jpeg|bmp)$");
QRegularExpression Reg_Find_Img("[^`]![(](.+)[)]");
QRegularExpression Reg_Find_Refid("(?!`)![[](\\d+):?.*?[]]");
QRegularExpression Reg_Win_Path("^[a-zA-Z]:.+$");

bool activated = false;

///
void initGlobal() {
    fq = new FileQueue(cfg->dologFile);
}

//#tag1#tag2 x
QVariantList parseKeyTags(const QString& k_) {
    QStringList tagList;
    QString k = k_.trimmed();
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

QStringList parseTagIds(const QString& tags) {
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

QString fullImg(const QString& img) {
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
QVariantList calWinHeight(const QString& k, uint maxWidth) {
    QStringList arr = k.split('.');
    if(maxWidth <= 0) {
        QWindow *w = qobject_cast<QWindow *>(engine->rootObjects().at(0));
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

QString extractImgs(const QString& cont, bool rmdup) {
    QString s;
    QStringList imgs = extractImgsAsList(cont, rmdup);
    for(QString& img:imgs) {
        s += img + ",";
    }
    return s;
}
QStringList extractImgsAsList(const QString& cont, bool rmdup) {
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
QString extractRefimgids(const QString& cont) {
    QString s;
    QStringList imgs = extractImgsAsList(cont, true);
    for(QString& img:imgs) {
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
QString extractRefIDs(const QString& cont) {
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
QList<uint> extractRefIDsAsList(const QString& cont) {
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
QString extractNoteSimpleCont(const QString& cont, const QString& k_) {
    QString k = k_.trimmed();
    if(k.length() == 0) {
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
            i = i - cfg->simpleContKeyFront;
        }
        s = ut::str::substrUniformWidth(cont, max(0, i), SIMPLE_SIZE);
        s = ut::str::frontLine(s, cfg->simpleContMaxLine);
    } else {
        s = ut::str::substrUniformWidth(cont, 0, SIMPLE_SIZE);
    }
    return replaceHighlightKey(cont, keys);
}

QString extractXMSimpleCont(const QString& cont, const QString& k_) {
    QString k = k_.trimmed();
    if(k.length() == 0) {
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
            i = i - cfg->simpleContKeyFront;
        }
        s = ut::str::substrUniformWidth(cont, max(0, i), SIMPLE_SIZE);
        s = ut::str::frontLine(s, cfg->simpleContMaxLine);
    } else {
        s = ut::str::substrUniformWidth(cont, 0, SIMPLE_SIZE);
    }
    return replaceHighlightKey(cont, keys);
}
QString replaceHighlightKey(const QString& cont, QStringList keys) {
    QStringList lines = cont.split("\n");
    int code = 0;
    for(int i = 0; i < lines.length(); i++) {
        static QRegularExpression re("^```\\w+$");
        bool b1 = re.match(lines[i]).hasMatch();
        bool b2 = lines[i]=="```";
        if(b1) {
            code = 1;
        }
        if(b2) {
            code = 2;
        }
        if(b1 || b2) {
            continue;
        }
        if(code == 1) {
            continue;
        }
        static QRegularExpression re1("^!\\(.+\\)$");
        if(re1.match(lines[i]).hasMatch()) {
            continue;
        }

        int from = 0;
        for(int j = 0; j < keys.length(); j++) {
            from = replaceHighlightKey(lines[i], keys[j], from);
        }
    }
    QString s = "";
    for(int i = 0; i < lines.length(); i++) {
        if(i == lines.length()-1) {
            s += lines[i];
        } else {
            s += lines[i] + "\n";
        }
    }
    return s;
}
void pushXM(XM* xm) {
    QObject* root = engine->rootObjects().at(0);
    QMetaObject::invokeMethod(root, "onUpdatedXM",
                Q_ARG(QVariant, QVariant::fromValue(xm->toVMap(1, 1, 600))));
}
void alert(const QString &msg, bool autoclose) {
    QObject* root = engine->rootObjects().at(0);
    QMetaObject::invokeMethod(root, "_alert",
                Q_ARG(QVariant, QVariant::fromValue(msg)),
                Q_ARG(QVariant, QVariant::fromValue(autoclose)));
}
void ensure(const QString &msg) {
    QObject* root = engine->rootObjects().at(0);
    QMetaObject::invokeMethod(root, "ensure",
                Q_ARG(QVariant, QVariant::fromValue(msg)));
}
void st(uint st, const QString& msg) {
    QObject* root = engine->rootObjects().at(0);
    QMetaObject::invokeMethod(root, "setStat",
                Q_ARG(QVariant, QVariant::fromValue(st)),
                Q_ARG(QVariant, QVariant::fromValue(msg)));
}

void pushServerData(const QString& dev, const QString& data) {
    mtx.lock();
    std::queue q = serverDataQueue->value(dev);
    q.push(data);
    serverDataQueue->insert(dev, q);
    mtx.unlock();
}

QString takeServerData(const QString& dev) {
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
std::tuple<uint, uint> getWHFromFileName(const QString& fn) {
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
void filterSearchKey(QString& k) {
    static QRegularExpression regex("[^\\p{L}\\p{N}\\s#]+");
    k.replace(regex, "");
}
int replaceHighlightKey(QString& line, const QString& k, int from) {
    if(from < 0 || from >= line.length()) {
        return 0;
    }
    int i = line.mid(from).indexOf(k);
    if(i != -1) {
        QString tag1 = "@#red ";
        QString tag2 = "@";
        line.replace(from+i, k.length(), tag1+k+tag2);
        from = from+i+k.length()+tag1.length()+tag2.length();
    }
    return from;
}
namespace ui {
    QMap<uint, QString> uiVals;
    void setUIVal(uint k, const QString& v) {
        uiVals.insert(k, v);
    }
    QString getUIVal(uint k) {
        return uiVals.value(k);
    }
}

void dolog(const QString& s) {
    fq->enqueue(s);
}
void dologXMNew(uint id) {
    dolog(QString(DOLOG_XM_NEW).arg(id));
}
void dologXMDel(uint id, QString img) {
    dolog(QString(DOLOG_XM_DEL).arg(id).arg(img));
}
void dologNoteNew(uint id) {
    dolog(QString(DOLOG_NOTE_NEW).arg(id));
}
void dologNoteDel(uint id) {
    dolog(QString(DOLOG_NOTE_DEL).arg(id));
}
void dologNoteByWidDel(uint id) {
    dolog(QString(DOLOG_NOTE_BY_WID_DEL).arg(id));
}
void dologCategoryNew(uint id) {
    dolog(QString(DOLOG_CATEGORY_NEW).arg(id));
}
void dologCategoryDel(uint id) {
    dolog(QString(DOLOG_CATEGORY_DEL).arg(id));
}
void dologWorkNew(uint id) {
    dolog(QString(DOLOG_WORK_NEW).arg(id));
}
void dologWorkDel(uint id) {
    dolog(QString(DOLOG_WORK_DEL).arg(id));
}
void dologTagNew(uint id) {
    dolog(QString(DOLOG_TAG_NEW).arg(id));
}
void dologTagDel(uint id) {
    dolog(QString(DOLOG_TAG_DEL).arg(id));
}
void dologEnvNew(const QString& k) {
    dolog(QString(DOLOG_ENV_NEW).arg(k));
}
void dologEnvDel(const QString& k) {
    dolog(QString(DOLOG_ENV_DEL).arg(k));
}
void dologSql(const QString& sql) {
    dolog(QString(DOLOG_SQL).arg(sql));
}
void dologTaskLogNew(uint id) {
    dolog(QString(DOLOG_TaskLog_NEW).arg(id));
}
