#include <QQmlApplicationEngine>
#include <iostream>
#include <QQmlContext>
#include <QQuickWindow>
#include <QIcon>
#include <QUuid>
#include <com/async.h>
#include <com/util.h>
#include "com/global.h"
#include "com/sqlite_manager.h"
#include "app.h"
#include "l.h"
#include <QApplication>
#include <QDir>
#include <QFont>
#include <QSemaphore>
#include <QStandardPaths>
#include <QTranslator>
#include <QThread>
#ifdef Q_OS_MAC
#include "com/mac.h"
#endif
#include "com/runmain.h"
#include "hserver.h"
#include "timer.h"
// #include "test.h"

using namespace std;

class MyApplication: public QApplication {
public:
    MyApplication(int &argc, char **argv): QApplication(argc, argv) {
    }
    bool event(QEvent *event) override {
        if (event->type() == QEvent::FileOpen) {
            QFileOpenEvent *openEvent = static_cast<QFileOpenEvent *>(event);
            QString curXM = openEvent->file();
            qDebug() << "Open file" << curXM;
            PK *pk = xm->openFile(curXM, "");
            QObject* root = engine->rootObjects()[0];
            QMetaObject::invokeMethod(root, "openXM", Q_ARG(QVariant, QVariant::fromValue(pk->toVMap(true))));
        }
        return QApplication::event(event);
    }
};

int start(int argc, char *argv[]);
int initGui(MyApplication* a);
void initCfg();
void exit_(int r);

int main(int argc, char *argv[]) {
    // test10();
    // return 0;
    int r = start(argc, argv);
    exit_(r);
    return r;
}

int start(int argc, char* argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    MyApplication *a = new MyApplication(argc, argv);
#ifdef Q_OS_MAC
    mac->loadBookmarks();
#endif
    initCfg();
    RunMain::INS().init();
    Com_Async->start();
    DB_Async->start();
    SM_Async->start();

//    HServer::INS().loop();
    app->init();

//    Timer::INS().init();
    return initGui(a);
//    return 0;
}
int initGui(MyApplication* a) {
    engine = new QQmlApplicationEngine();

//    app->checkAuth(ut::file::readFile(cfg->auth_file), false);

    engine->rootContext()->setContextProperty("$app", app);
    engine->rootContext()->setContextProperty("$l", l);
    engine->rootContext()->setContextProperty("$col", colAction);
    engine->rootContext()->setContextProperty("$bk", bookAction);

    //语言国际化
    QTranslator translator;
    QLocale locale;
    QString loc = cfg->lang;
    if(cfg->lang == "") {
        loc = locale.name();
    }
    bool loadSuc = translator.load(":/" + loc);
    a->installTranslator(&translator);
    app->locale_name = loc;
    lg->info(QString("load translator file %1 %2").arg(loc).arg(loadSuc));

    //
    QString mainQml = QStringLiteral("qrc:/qml/Main.qml");
    const QUrl url(mainQml);
    QObject::connect(engine, &QQmlApplicationEngine::objectCreated, app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) {
            QCoreApplication::exit(-1);
        }
    }, Qt::QueuedConnection);
    engine->load(url);
    //
    app->setGlobalHotkey(0, cfg->hot_key_pk);
    app->setGlobalHotkey(1, cfg->hot_key_show);
#ifdef Q_OS_MAC
    a->setWindowIcon(QIcon(":/assets/logo.icns"));
//    w->setIcon(QIcon(":assets/logo.icns"));
//    mac->initWindow(w);
#endif
#ifdef Q_OS_WIN
    QObject *qmlRoot = engine->rootObjects()[0];
    QWindow *w = qobject_cast<QWindow *>(qmlRoot);
    w->setIcon(QIcon(":assets/logo.ico"));
#endif
    lg->info("xxmoon started");

    QFont font;
#ifdef Q_OS_MAC
    font.setFamily("Arial");
#endif
#ifdef Q_OS_WIN
    font.setFamily("微软雅黑");
#endif
    qApp->setFont(font);
    return a->exec();
}
void initCfg() {
    if(ut::file::exists(cfg->cfgFileName)) {
        QStringList lines = ut::file::allLines(cfg->cfgFileName);
        for(QString line: lines) {
            if(line.length() > 0 &&
                    !line.startsWith("#") &&
                    line.indexOf("=") > 0) {
                QStringList kv = line.split("=");
                QString k = kv[0].trimmed();
                QString v = kv[1].trimmed();
                if(v.length() > 0){
                    if(k == "data_dir") {
                        cfg->dataDir = v;
                    } else if(k == "user") {
                        cfg->user = v;
                    } else if(k == "log_level") {
                        cfg->logLevel = v;
                    } else if(k == "editor") {
                        cfg->editor = v;
                    } else if(k == "hot_key_pk") {
                        cfg->hot_key_pk = v;
                    } else if(k == "hot_key_show") {
                        cfg->hot_key_show = v;
                    } else if(k == "lang") {
                        cfg->lang = v;
                    } else if(k == "ui_quote_bg_color") {
                        cfg->ui_quote_bg_color = v;
                    } else if(k == "ui_quote_text_color") {
                        cfg->ui_quote_text_color = v;
                    } else if(k == "ui_highlight_color") {
                        cfg->ui_highlight_color = v;
                    } else if(k == "sitedir") {
                        cfg->sitedir = v;
                    } else if(k == "sitename") {
                        cfg->sitename = v;
                    } else if(k == "sitetitle") {
                        cfg->sitetitle = v;
                    } else if(k == "site_detail_extra_id") {
                        cfg->site_detail_extra_id = v.toUInt();
                    } else if(k == "site_xmblog_tag") {
                        cfg->site_xmblog_tag = v;
                    } else if(k == "ctrl") {
                        cfg->ctrl = v;
                    }
                }
            }
        }
    }
    cfg->userBaseDir = cfg->dataDir + "/xxmoon/" + cfg->user;
    cfg->dbFile = cfg->userBaseDir + "/xxmoon.data";
    cfg->imgDir = cfg->userBaseDir + "/imgs";
    cfg->fileDir = cfg->dataDir + "/xxmoon/" + cfg->user + "/files";
    cfg->logFile = cfg->dataDir + "/" + cfg->appName +"/log.txt";
    cfg->tmpDir = cfg->userBaseDir + "/tmp";
    if(cfg->sitedir == "") {
        cfg->sitedir = cfg->fileDir+"/"+"site";
    }
    qDebug() << "================================ cfg ================================";
    qDebug() << cfg->toString().toUtf8().data();
    qDebug() << "================================ cfg ================================";
    //
    app->genCert();
}
void exit_(int r) {
    app->close(r);
#ifdef Q_OS_MAC
    mac->close();
#endif
    qDebug() << "EXITED";
}
