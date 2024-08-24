#ifndef GLOBAL_H
#define GLOBAL_H

#include "async.h"
#include "db/tasklogdao.h"
#include "docparser.h"
#ifdef Q_OS_MAC
#include "mac.h"
#include "menumanager.h"
#include "sync.h"
#include "trans.h"
#include "filequeue.h"
#endif
#include <l.h>
#include <QProcess>
#include <QRegularExpression>
#include <app.h>
#include "com/sqlite_manager.h"
#include "com/log.h"
#include "com/trans.h"
#include "com/sync.h"
#include "com/filequeue.h"
#include "db/envdao.h"
#include "db/notedao.h"
#include "db/xmdao.h"
#include "db/categorydao.h"
#include <QDateTime>
#include <QFile>
#include <QQmlApplicationEngine>
#include <db/tagdao.h>
#include <db/workdao.h>
#include <model/cfg.h>
#include <action/bookaction.h>
#include <action/xmaction.h>
#include "com/xm_format.h"
#include "com/sm.h"

extern Async *Com_Async;
extern Async *DB_Async;
extern Async *SM_Async;
extern std::queue<std::tuple<int, QMap<QString, QString>>> *serverMsgQueue; //server msg queue
extern QMap<QString, std::queue<QString>> *serverDataQueue; //<devid, data queue>

extern volatile bool running;

extern QQmlApplicationEngine *engine;
extern Cfg *cfg;
extern App* a;
extern XMAction* xmAction;
extern BookAction* bookAction;
extern L* l;
extern SQLiteManager *db;
extern WorkDao *workDao;
extern NoteDao *noteDao;
extern EnvDao *envDao;
extern XMDao *xmDao;
extern CategoryDao *categoryDao;
extern TagDao *tagDao;
extern TaskLogDao *taskLogDao;
#ifdef Q_OS_MAC
extern Mac *mac;
extern MenuManager *menuManager;
#endif
extern QProcess *process;
extern DocParser *doc_parser;
extern Log *lg;
extern XMFormat *xm_format;
extern SM *sm;
extern Trans *trans;
extern Sync *sy;
extern FileQueue *fq;

extern QRegularExpression Reg_Kindle_Note;
extern QRegularExpression Reg_Text_Img;
extern QRegularExpression Reg_Find_Img;
extern QRegularExpression Reg_Find_Refid;
extern QRegularExpression Reg_Win_Path;

extern bool activated;

void initGlobal();
QVariantList parseKeyTags(const QString& k);
QStringList parseTagIds(const QString& tags);
QString fullImg(const QString& img);
QList<double> calImgSizeByWidth(double srcW, double srcH, double maxWidth);
QVariantList calWinHeight(const QString& k, uint maxWidth = 0);
QString getFilePre();
QString extractImgs(const QString& cont, bool rmdup = false);
QStringList extractImgsAsList(const QString& cont, bool rmdup = false);
QString extractRefimgids(const QString& cont);
QString extractRefIDs(const QString& cont);
QList<uint> extractRefIDsAsList(const QString& cont);
QString extractNoteSimpleCont(const QString& cont, const QString& k);
QString extractXMSimpleCont(const QString& cont, const QString& k);
void pushServerData(const QString& dev, const QString& data);
QString takeServerData(const QString& dev);
std::tuple<uint, uint> getWHFromFileName(const QString& fn);
void filterSearchKey(QString& k);
QString replaceHighlightKey(const QString& cont, QStringList keys);
int replaceHighlightKey(QString& s, const QString& oldKey, int ind);

namespace ui {
    extern void setUIVal(uint k, const QString& v);
    extern QString getUIVal(uint k);
}

template<typename T>
void sendMsg(uint cbid, const T &data) {
    QObject* root = engine->rootObjects().at(0);
    QMetaObject::invokeMethod(root, "onCallback",
                Q_ARG(QVariant, QVariant::fromValue(cbid)),
                Q_ARG(QVariant, QVariant::fromValue(data)));
}
template<typename T>
void pushMsg(uint ty, const T &data = 0) {
    QObject* root = engine->rootObjects().at(0);
    QMetaObject::invokeMethod(root, "onPush",
                Q_ARG(QVariant, QVariant::fromValue(ty)),
                Q_ARG(QVariant, QVariant::fromValue(data)));
}
template<typename T>
void notify(const T &data, const uint ty = 0) {
    QObject* root = engine->rootObjects().at(0);
    QMetaObject::invokeMethod(root, "notify",
                Q_ARG(QVariant, QVariant::fromValue(data)),
                Q_ARG(QVariant, QVariant::fromValue(ty)));
}
void pushXM(XM* xm);
void alert(const QString &msg, bool autoclose = true);
void ensure(const QString &msg);
void st(uint st = 0, const QString& msg = "");

void dologXMNew(uint id);
void dologXMDel(uint id, QString img = "");
void dologNoteNew(uint id);
void dologNoteDel(uint id);
void dologNoteByWidDel(uint id);
void dologCategoryNew(uint id);
void dologCategoryDel(uint id);
void dologWorkNew(uint id);
void dologWorkDel(uint id);
void dologTagNew(uint id);
void dologTagDel(uint id);
void dologEnvNew(const QString& k);
void dologEnvDel(const QString& k);
void dologSql(const QString& sql);
void dologTaskLogNew(uint id);
#endif // GLOBAL_H
