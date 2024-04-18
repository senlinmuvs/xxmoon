#ifndef XMACTION_H
#define XMACTION_H

#include <QObject>

class XMAction : public QObject {
    Q_OBJECT
public:
    explicit XMAction();

    ///
    Q_INVOKABLE void getCategories(QString k, QObject *obj);
    Q_INVOKABLE void addCategory(QString name, QObject *obj);
    Q_INVOKABLE void editCategory(uint id, QString name, QObject *obj);
    Q_INVOKABLE void delCategory(uint id, uint cbid);
    Q_INVOKABLE void sorting(uint id, uint srcIndex, uint dstIndex, uint cbid);
    Q_INVOKABLE void countCategory(uint cid, uint cbid);
    Q_INVOKABLE void getNewXMList(uint cid, uint fromId, uint pklistWidth, QObject *obj);

    Q_INVOKABLE void getXMList(QString k, uint id, uint fromId, uint pklistWidth, uint cbid);
    Q_INVOKABLE void getXM(uint id, uint listWidth, uint cbid);
    Q_INVOKABLE void deleteXM(uint id, QObject *obj);
    Q_INVOKABLE void updateXM(uint id, QString cont, QString k, uint pklistWidth, uint cbid);
    Q_INVOKABLE void updateXMCid(uint colIndex, uint pkId, uint cid, QObject *obj);
    Q_INVOKABLE void addXM(uint cid, QString txt, uint pklistWidth, QObject *obj);
    Q_INVOKABLE void copyXM(uint type, uint id);
    Q_INVOKABLE void xm(QString file, uint cbid = 0);
    Q_INVOKABLE void updateXMTags(uint pkid, QString tags, uint cbid);
    Q_INVOKABLE void clearSolvedTime(uint pkid, uint cbid);
    Q_INVOKABLE void encrypt(uint cid, QString pwd, uint cbid);
    Q_INVOKABLE void deleteEncryption(uint cid, uint cbid);
    Q_INVOKABLE void validateCategoryPWD(uint cid, QString pwd, uint cbid);
    Q_INVOKABLE void setTop(uint cid, uint xmid, uint cbid);
    Q_INVOKABLE void delTop(uint cid, uint xmid, uint cbid);

    QString xm(QImage *img, QString cont, QString file);
};

#endif // XMACTION_H
