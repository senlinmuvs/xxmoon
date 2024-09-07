#ifndef CFG_H
#define CFG_H

#include <QDir>
#include <QString>


class Cfg: public QObject {
public:
    explicit Cfg(QObject *parent = nullptr);
    QString dataDir = QDir::homePath();
    QString exchangeDataDir = "";
    QString initImgNamePre = "";
    QString appName = "xxmoon";
    QString xmCfgDir = QDir::homePath() + "/."+appName;
    QString syncUrl = "";
    QString server = "";
    uint cid = 0;
    QString user = "xxmoon";
    QString pwd = "";
    QString userBaseDir = dataDir + "/" + appName + "/" + user;
    QString dbFileName = "xxmoon.data";
    QString dbFile = userBaseDir + "/" + dbFileName;
    QString imgDir = userBaseDir + "/imgs";
    QString fileDir = userBaseDir + "/files";
    QString attachesDir = userBaseDir + "/attaches";
    QString scriptDir = userBaseDir + "/scripts";
    QString tmpDir = userBaseDir + "/tmp";
    QString logLevel = "error";
    QString logFile = xmCfgDir + "/"+ user + ".log";
    QString localCfgFileName = xmCfgDir + "/.xm";
    QString tmpPKPre = "xm_";
    QString tmpNotePre = "note_";
#ifdef Q_OS_MAC
    QString editor = "TextEdit";//vi, Sublime Text
#endif
#ifdef Q_OS_WIN
    QString editor = "notepad.exe";//vi, Sublime Text
#endif
#ifdef Q_OS_LINUX
    QString editor = "vi";//vi, Sublime Text
#endif
#ifdef Q_OS_MAC
    QString ctrl = "Cmd";
#else
    QString ctrl = "Ctrl";
#endif
    QString cfgFile = xmCfgDir + "/" + appName +  ".cfg";
    QString hotKeyXm = ctrl+"+Alt+X";
    QString hotKeyShow = ctrl+"+Alt+Z";
    QString hotKeyCmd = "F6";
    QString lang = "";
    QString tmpActFile = "act";
    QString xmImgCategory = "";
    //
    QString uiQuoteBgColor = "#303030";
    QString uiQuoteTextColor = "#FFFFFF";
    QString uiHighlightColor = "#000000";

    QString kindleFlag = "==========";
    QString kindleFlagBj = "笔记";
//    uint simple_cont_front_line = 1;
    uint simpleContKeyFront = 30;
    uint simpleContMaxLine = 10;
    QString regKindleFlag = "-.+您在.+[0-9]+.*的.+|.+添加于.+";
    QString sitedir = "";
    QString sitename = "摘月生成站点";
    QString sitetitle = "";
    uint siteDetailExtraId = 0;
    QString siteXmblogTag = "xmblog";
    uint port = 10000;

    QString dologFile = xmCfgDir + "/."+ user +"-dolog";

    uint cmdSrc = 0;
    QString python = "python";

    QString toString();
    QVariantMap toVMap();
    void updateDataDir(QString path);
};

#endif // CFG_H
