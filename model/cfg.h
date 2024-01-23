#ifndef CFG_H
#define CFG_H

#include <QDir>
#include <QString>


class Cfg {
public:
    Cfg();

    QString dataDir = QDir::homePath();
    QString exchangeDataDir = "";
    QString initImgNamePre = "2020";
    QString appName = "xxmoon";
    QString user = "xxmoon";
    QString userBaseDir = dataDir + "/" + appName + "/" + user;
    QString dbFileName = "xxmoon.data";
    QString dbFile = userBaseDir + "/" + dbFileName;
    QString imgDir = userBaseDir + "/imgs";
    QString fileDir = userBaseDir + "/files";
    QString tmpDir = userBaseDir + "/tmp";
    QString logLevel = "error";
    QString logFile = dataDir + "/" + appName + "/log.txt";
    QString localCfgFileName = QDir::homePath() + "/xxmoon_local.cfg";
    QString tmpPKPre = "pk_";
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
    QString cfgFileName = QDir::homePath() + "/xxmoon.cfg";
    QString auth_file = QDir::homePath() + "/.xxmoon_auth";
#ifdef Q_OS_MAC
    QString ctrl = "Cmd";
#else
    QString ctrl = "Ctrl";
#endif
    QString hot_key_pk = ctrl+"+Alt+X";
    QString hot_key_show = ctrl+"+Alt+Z";
    QString lang = "";
    QString tmpActFile = "act";
    //
    QString ui_quote_bg_color = "#303030";
    QString ui_quote_text_color = "#FFFFFF";
    QString ui_highlight_color = "#000000";

    QString kindle_flag = "==========";
    QString kindle_flag_bj = "笔记";
//    uint simple_cont_front_line = 1;
    uint simple_cont_key_front = 30;
    uint simple_cont_max_line = 10;
    QString reg_kindle_flag = "-.+您在.+[0-9]+.*的.+|.+添加于.+";
    QString sitedir = "";
    QString sitename = "摘月生成站点";
    QString sitetitle = "";
    uint site_detail_extra_id = 0;
    QString site_xmblog_tag = "xmblog";
    uint port = 10000;

    QString toString();
    QVariantMap toVMap();
    void updateDataDir(QString path);
};

#endif // CFG_H
