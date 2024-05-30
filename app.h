#ifndef APP_H
#define APP_H

#include <QObject>
#include "com/const.h"
#include <QQuickTextDocument>

using namespace std;

class App: public QObject {
    Q_OBJECT
    Q_PROPERTY(uint pageSize READ getPageSize CONSTANT)
    Q_PROPERTY(QString tag1 READ getTag1 CONSTANT)
    Q_PROPERTY(QString tag2 READ getTag2 CONSTANT)
    Q_PROPERTY(uint maxTag READ getMaxTag CONSTANT)
    Q_PROPERTY(QString dataDir READ getDataDir CONSTANT)
    Q_PROPERTY(QString baseDir READ getBaseDir CONSTANT)
    Q_PROPERTY(QString imgDir READ getImgDir CONSTANT)
    Q_PROPERTY(QString fileDir READ getFileDir CONSTANT)
    Q_PROPERTY(QString ENV_K_LAST_SORT READ getENV_K_LAST_SORT CONSTANT)
    Q_PROPERTY(QString ENV_K_LAST_VIEW_TYPE READ getLAST_VIEW_TYPE CONSTANT)
    Q_PROPERTY(QString ENV_K_LAST_WH READ getLAST_WH CONSTANT)
    Q_PROPERTY(QString ENV_K_LAST_CATEGORY_LEFT_WIDTH READ getLAST_CATEGORY_LEFT_WIDTH CONSTANT)
    Q_PROPERTY(QString ENV_K_LAST_BOOK_LEFT_WIDTH READ getLAST_BOOK_LEFT_WIDTH CONSTANT)
    Q_PROPERTY(QString cfgFile READ getCfgFile CONSTANT)

private:
    QMap<QString, uint> tmpFileLSTMap;

    void init0();
    void updateXM0(uint id, QString cont);
    void updateNote0(uint id, QString cont);

public:
    void setGlobalHotkey(uint ty, QString k);
    void showOrHide();

public:
    explicit App();
    ~App();
    uint getPageSize() const{return PAGE_SIZE;}
    uint getMaxTag() const{return MAX_TAG;}
    QString getTag1() const{return Tag1;}
    QString getTag2() const{return Tag2;}
    QString getDataDir();
    QString getBaseDir();
    QString getFileDir();
    QString getImgDir();
    QString getENV_K_LAST_SORT() const{return ENV_K_LAST_SORT;}
    QString getLAST_VIEW_TYPE() const{return ENV_K_LAST_VIEW_TYPE;}
    QString getLAST_CATEGORY_LEFT_WIDTH() const{return ENV_K_LAST_CATEGORY_LEFT_WIDTH;}
    QString getLAST_BOOK_LEFT_WIDTH() const{return ENV_K_LAST_BOOK_LEFT_WIDTH;}
    QString getLAST_WH() const{return ENV_K_LAST_WH;}
    QString getCfgFile();

    Q_INVOKABLE int getPlatform();
    Q_INVOKABLE QString getComputerID();
    Q_INVOKABLE QString getCfgVal(QString k);
    Q_INVOKABLE QString getCtrl();

    Q_INVOKABLE void import(QString path, QObject *obj);
    Q_INVOKABLE void checkImport();
    Q_INVOKABLE void checkExport();
    Q_INVOKABLE void getLastPath(QObject *obj);

    Q_INVOKABLE void tagList(QString k, uint target, QObject* obj);
    Q_INVOKABLE void addTag(QString tag, QObject *obj);
    Q_INVOKABLE void delTag(uint tid, QObject *obj);
    Q_INVOKABLE void getTagById(uint id, uint cbid);
    ///
    Q_INVOKABLE void set(QString k, QString v, bool init = false);
    Q_INVOKABLE void setLocal(QString k, QString v);
    Q_INVOKABLE void encrypt(uint id, QString k, uint listWidth, uint cbid);
    Q_INVOKABLE void decrypt(uint id, QString k, uint listWidth, uint cbid);
    Q_INVOKABLE void ensureEncryptOrDecrypt(uint id, QString cont, uint cbid);
    Q_INVOKABLE void genFile(uint fileType, uint type, uint gid, uint id, bool batch = false, QString pwd = "");
    Q_INVOKABLE void deleteFromSite(uint id, uint type = 0);
    Q_INVOKABLE QStringList getFilesInDir(QString dir);
    Q_INVOKABLE void openInExternal(int type = 0, QString img = "", uint obj = 0);
    Q_INVOKABLE void openDir(QString path);
    Q_INVOKABLE void openVideo(QString path);
    Q_INVOKABLE void close(int r = 0);
    Q_INVOKABLE void checkTmpFile();
    Q_INVOKABLE void plainText(QString html, uint cbid);
    Q_INVOKABLE void getCfg(QObject *obj);
    Q_INVOKABLE QString getKeyName(int key, int modifiers);
    Q_INVOKABLE void setCfg(QString k, QString v);
    Q_INVOKABLE void openXMFile(QString file, QString pwd, uint cbid);
    Q_INVOKABLE void importXM(QVariantMap pkdata);
    Q_INVOKABLE void copy(QString s);
    Q_INVOKABLE QString getVersion();
    Q_INVOKABLE QVariantMap getUIData();
    Q_INVOKABLE void copyImg(QString path);

    Q_INVOKABLE bool importDouban();
    Q_INVOKABLE bool importWechatRead();

    Q_INVOKABLE QString tr(QString k);
    Q_INVOKABLE void cp(QString txt);
    Q_INVOKABLE void count(uint cbid);

    QString createSiteFile(QString filename, QString cont, qint64 ct);
    QString insertIndexItem(QString indexhtml, QMap<QString,QString> indexmap);

    //server
    Q_INVOKABLE void enableServer();
    Q_INVOKABLE void disableServer();
    Q_INVOKABLE void genQRCode(int cbid);
    Q_INVOKABLE void devices(int cbid);
    Q_INVOKABLE void delDev(QString dev, int cbid);
    Q_INVOKABLE void sendToPhone(int ty, int id, int cbid);
    Q_INVOKABLE void getCurQRCode(int cbid);
    Q_INVOKABLE void genCert(bool force = false, bool al = false);

    Q_INVOKABLE void regMenuReceiver(QObject* o);
    Q_INVOKABLE void triggerMenu(int act);
    Q_INVOKABLE bool existsAllowedURL();
    Q_INVOKABLE void alertMacTip(QString tip1, QString tip2);
    Q_INVOKABLE QString selectDataDir();
    void initCfg();
    Q_INVOKABLE void init();
    Q_INVOKABLE void xm();
    Q_INVOKABLE void setUIVal(uint k, QString v);
    Q_INVOKABLE QString getUIVal(uint k);
    Q_INVOKABLE QString test();
    Q_INVOKABLE uint calLine(QString txt, int index);
    Q_INVOKABLE bool existFile(QString file);
};

#endif // APP_H
