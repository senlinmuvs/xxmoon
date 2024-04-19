#ifndef GLOBAL_H
#define GLOBAL_H

#include "async.h"
#include "docparser.h"
#ifdef Q_OS_MAC
#include "mac.h"
#include "menumanager.h"
#include "trans.h"
#endif
#include <l.h>
#include <QProcess>
#include <QRegularExpression>
#include <app.h>
#include "com/sqlite_manager.h"
#include "com/log.h"
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
extern App* app;
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

extern QRegularExpression Reg_Kindle_Note;
extern QRegularExpression Reg_Text_Img;
extern QRegularExpression Reg_Find_Img;
extern QRegularExpression Reg_Find_Refid;
extern QRegularExpression Reg_Win_Path;

extern bool activated;

extern QVariantList parseKeyTags(QString k);
extern QStringList parseTagIds(QString tags);
extern QString fullImg(QString img);
extern QList<double> calImgSizeByWidth(double srcW, double srcH, double maxWidth);
extern QVariantList calWinHeight(QString k, uint maxWidth = 0);
extern QString getFilePre();
extern QString extractImgs(QString cont, bool rmdup = false);
extern QStringList extractImgsAsList(QString cont, bool rmdup = false);
extern QString extractRefimgids(QString cont);
extern QString extractRefIDs(QString cont);
extern QList<uint> extractRefIDsAsList(QString cont);
extern QString extractNoteSimpleCont(const QString& cont, const QString& k);
extern QString extractPKSimpleCont(const QString& cont, const QString& k);
extern void pushServerData(QString dev, QString data);
extern QString takeServerData(QString dev);
extern std::tuple<uint, uint> getWHFromFileName(QString fn);

namespace ui {
    extern void setUIVal(uint k, QString v);
    extern QString getUIVal(uint k);
}

template<typename T>
void sendMsg(uint cbid, const T &data) {
    QObject* root = engine->rootObjects()[0];
    QMetaObject::invokeMethod(root, "onCallback",
                Q_ARG(QVariant, QVariant::fromValue(cbid)),
                Q_ARG(QVariant, QVariant::fromValue(data)));
}
template<typename T>
void pushMsg(uint ty, const T &data) {
    QObject* root = engine->rootObjects()[0];
    QMetaObject::invokeMethod(root, "onPush",
                Q_ARG(QVariant, QVariant::fromValue(ty)),
                Q_ARG(QVariant, QVariant::fromValue(data)));
}
template<typename T>
void notify(const T &data) {
    QObject* root = engine->rootObjects()[0];
    QMetaObject::invokeMethod(root, "notify",
                Q_ARG(QVariant, QVariant::fromValue(data)));
}
void alert(const QString &msg, bool autoclose = true);
void ensure(const QString &msg);
void st(uint st = 0, QString msg = "");
void deleteFile(QString file);
#endif // GLOBAL_H
