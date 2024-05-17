#include <QQmlApplicationEngine>
// #include <iostream>
#include <QQmlContext>
#include <QQuickWindow>
#include <QIcon>
#include <QUuid>
#include "com/async.h"
#include "com/util.h"
#include "com/global.h"
#include "app.h"
#include <QApplication>
#include <QDir>
#include <QFont>
#include <QSemaphore>
#include <QStandardPaths>
#include <QTranslator>
#include <QThread>
#include <QClipboard>
#ifdef Q_OS_MAC
#include "com/mac.h"
#endif
#include "com/runmain.h"
// #include "hserver.h"
#include "timer.h"

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
            XM *pk = xm_format->openFile(curXM, "");
            QObject* root = engine->rootObjects().at(0);
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
    return start(argc, argv);
}
int start(int argc, char* argv[]) {
    MyApplication *ma = new MyApplication(argc, argv);
#ifdef Q_OS_MAC
    mac->loadBookmarks();
#endif
    initCfg();
    initGlobal();
    RunMain::INS().init();
    Com_Async->start();
    DB_Async->start();
    SM_Async->start();

//    HServer::INS().loop();
    a->init();
    Timer::INS().init();
    return initGui(ma);
   // return 0;
}
int initGui(MyApplication* ma) {
    engine = new QQmlApplicationEngine();

    engine->rootContext()->setContextProperty("$a", a);
    engine->rootContext()->setContextProperty("$l", l);
    engine->rootContext()->setContextProperty("$xm", xmAction);
    engine->rootContext()->setContextProperty("$bk", bookAction);

    //
    QString mainQml = QStringLiteral("qrc:/qml/Main.qml");
    const QUrl url(mainQml);
    QObject::connect(engine, &QQmlApplicationEngine::objectCreated, a, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) {
            QCoreApplication::exit(-1);
        }
    }, Qt::QueuedConnection);
    QObject::connect(engine, &QQmlEngine::quit, a, &QGuiApplication::quit);
    QObject::connect(ma, &QCoreApplication::aboutToQuit, []{
        exit_(0);
    });
    engine->load(url);
    //
    a->setGlobalHotkey(0, cfg->hotKeyXm);
    a->setGlobalHotkey(1, cfg->hotKeyShow);

#ifdef Q_OS_MAC
    ma->setWindowIcon(QIcon(":/assets/logo.icns"));
//    w->setIcon(QIcon(":assets/logo.icns"));
//    mac->initWindow(w);
#endif
#ifdef Q_OS_WIN
    QObject *qmlRoot = engine->rootObjects().at(0);
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

    // test13();
    int r = ma->exec();
    delete ma;
    return r;
}
void initCfg() {
    if(ut::file::exists(cfg->cfgFile)) {
        QStringList lines = ut::file::allLines(cfg->cfgFile);
        for(QString& line: lines) {
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
                    } else if(k == "hot_key_xm") {
                        cfg->hotKeyXm = v;
                    } else if(k == "hot_key_show") {
                        cfg->hotKeyShow = v;
                    } else if(k == "lang") {
                        cfg->lang = v;
                    } else if(k == "ui_quote_bg_color") {
                        cfg->uiQuoteBgColor = v;
                    } else if(k == "ui_quote_text_color") {
                        cfg->uiQuoteTextColor = v;
                    } else if(k == "ui_highlight_color") {
                        cfg->uiHighlightColor = v;
                    } else if(k == "sitedir") {
                        cfg->sitedir = v;
                    } else if(k == "sitename") {
                        cfg->sitename = v;
                    } else if(k == "sitetitle") {
                        cfg->sitetitle = v;
                    } else if(k == "site_detail_extra_id") {
                        cfg->siteDetailExtraId = v.toUInt();
                    } else if(k == "site_xmblog_tag") {
                        cfg->siteXmblogTag = v;
                    } else if(k == "ctrl") {
                        cfg->ctrl = v;
                    } else if(k == "sync_url") {
                        cfg->syncUrl = v;
                    }
                }
            }
        }
    } else {
        QDir dir;
        if(!dir.exists(cfg->xmCfgDir)) {
            dir.mkpath(cfg->xmCfgDir);
        }
        ut::file::writeText(cfg->cfgFile, "");
    }
    QStringList syncUrlArr = cfg->syncUrl.split("|");
    if(syncUrlArr.length() >= 3) {
        cfg->server = syncUrlArr.at(0);
        cfg->cid = syncUrlArr.at(1).toUInt();
        cfg->pwd = syncUrlArr.at(2);
    } else {
        qDebug() << "warning sync_url len < 3 sync_url=" << cfg->syncUrl;
    }
    cfg->userBaseDir = cfg->dataDir + "/xxmoon/" + cfg->user;
    cfg->dbFile = cfg->userBaseDir + "/xxmoon.data";
    cfg->imgDir = cfg->userBaseDir + "/imgs";
    cfg->fileDir = cfg->userBaseDir + "/files";
    cfg->scriptDir = cfg->userBaseDir + "/scripts";
    cfg->tmpDir = cfg->userBaseDir + "/tmp";
    if(cfg->sitedir == "") {
        cfg->sitedir = cfg->fileDir+"/"+"site";
    }
    if(cfg->lang == "") {
        cfg->lang = QLocale().name();
    }
    qDebug() << "================================ cfg ================================";
    qDebug() << cfg->toString().toUtf8().data();
    qDebug() << "================================ cfg ================================";
    //
    a->genCert();
}
void exit_(int r) {
    a->close(r);
#ifdef Q_OS_MAC
    mac->close();
#endif
    qDebug() << "XXMOON EXITED";
}
