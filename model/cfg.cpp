#include "cfg.h"
#include "com/util.h"
#include <QVariantMap>
#include <QDebug>
Cfg::Cfg() {
}

QString Cfg::toString() {
    QString s;
    QVariantMap m = toVMap();
    QList<QString> ks = m.keys();
    for(QString k: ks) {
        s += k + " = " + m.value(k).toString() + "\n";
    }
    s = s.remove(s.length()-1, 1);
    return s;
}

QVariantMap Cfg::toVMap() {
    QVariantMap m;
    m.insert("data_dir", dataDir);
    m.insert("cfgFileName", cfgFileName);
    m.insert("ctrl", ctrl);
    m.insert("exchange_data_dir", exchangeDataDir);
    m.insert("tmpDir", tmpDir);
    m.insert("imgDir", imgDir);
    m.insert("appName", appName);
    m.insert("user", user);
    m.insert("log_level", logLevel);
    m.insert("logFile", logFile);
    m.insert("editor", editor);
    m.insert("hot_key_pk", hot_key_pk);
    m.insert("hot_key_show", hot_key_show);
    m.insert("lang", lang);
    m.insert("ui_highlight_color", ui_highlight_color);
    return m;
}

void Cfg::updateDataDir(QString path) {
    dataDir = path;
    userBaseDir = dataDir + "/" + appName + "/" + user;
    logFile = dataDir + "/" + appName + "/log.txt";

    dbFile = userBaseDir + "/" + dbFileName;
    imgDir = userBaseDir + "/imgs";
    fileDir = userBaseDir + "/files";
    tmpDir = userBaseDir + "/tmp";
}
