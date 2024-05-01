#include "cfg.h"
#include <QVariantMap>
#include <QDebug>
Cfg::Cfg() {
}

QString Cfg::toString() {
    QString s;
    QVariantMap m = toVMap();
    QList<QString> ks = m.keys();
    for(const QString& k: ks) {
        s += k + " = " + m.value(k).toString() + "\n";
    }
    s = s.remove(s.length()-1, 1);
    return s;
}

QVariantMap Cfg::toVMap() {
    QVariantMap map;
    map["dataDir"] = dataDir;
    map["exchangeDataDir"] = exchangeDataDir;
    map["initImgNamePre"] = initImgNamePre;
    map["appName"] = appName;
    map["xmCfgDir"] = xmCfgDir;
    map["syncUrl"] = syncUrl;
    map["server"] = server;
    map["cid"] = cid;
    map["user"] = user;
    map["pwd"] = pwd;
    map["userBaseDir"] = userBaseDir;
    map["dbFileName"] = dbFileName;
    map["dbFile"] = dbFile;
    map["imgDir"] = imgDir;
    map["fileDir"] = fileDir;
    map["tmpDir"] = tmpDir;
    map["logLevel"] = logLevel;
    map["logFile"] = logFile;
    map["localCfgFileName"] = localCfgFileName;
    map["tmpPKPre"] = tmpPKPre;
    map["tmpNotePre"] = tmpNotePre;
    map["editor"] = editor;
    map["ctrl"] = ctrl;
    map["cfgFile"] = cfgFile;
    map["hotKeyXm"] = hotKeyXm;
    map["hotKeyShow"] = hotKeyShow;
    map["lang"] = lang;
    map["tmpActFile"] = tmpActFile;
    map["uiQuoteBgColor"] = uiQuoteBgColor;
    map["uiQuoteTextColor"] = uiQuoteTextColor;
    map["uiHighlightColor"] = uiHighlightColor;
    map["kindleFlag"] = kindleFlag;
    map["kindleFlagBj"] = kindleFlagBj;
    map["simpleContKeyFront"] = simpleContKeyFront;
    map["simpleContMaxLine"] = simpleContMaxLine;
    map["regKindleFlag"] = regKindleFlag;
    map["sitedir"] = sitedir;
    map["sitename"] = sitename;
    map["sitetitle"] = sitetitle;
    map["siteDetailExtraId"] = siteDetailExtraId;
    map["siteXmblogTag"] = siteXmblogTag;
    map["port"] = port;
    map["dologFile"] = dologFile;
    return map;
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
