#ifndef COLLECTACTION_H
#define COLLECTACTION_H

#include <QObject>

class CollectAction : public QObject {
    Q_OBJECT
public:
    explicit CollectAction();

    ///
    Q_INVOKABLE void getCollects(QString k, QObject *obj);
    Q_INVOKABLE void addCol(QString name, QObject *obj);
    Q_INVOKABLE void editCol(uint id, QString name, QObject *obj);
    Q_INVOKABLE void delCol(uint id, uint cbid);
    Q_INVOKABLE void sortingCol(uint id, uint srcIndex, uint dstIndex, uint cbid);
    Q_INVOKABLE void countCol(uint cid, uint cbid);
    Q_INVOKABLE void getNewPKList(uint cid, uint fromId, uint pklistWidth, QObject *obj);

    Q_INVOKABLE void getPKList(QString k, uint id, uint fromId, uint pklistWidth, QObject *obj);
    Q_INVOKABLE void getPK(uint id, uint listWidth, uint cbid);
    Q_INVOKABLE void deletePK(uint id, QObject *obj);
    Q_INVOKABLE void updatePK(uint id, QString cont, QString k, uint pklistWidth, uint cbid);
    Q_INVOKABLE void updatePKCid(uint colIndex, uint pkId, uint cid, QObject *obj);
    Q_INVOKABLE void addPK(uint cid, QString txt, uint pklistWidth, QObject *obj);
    Q_INVOKABLE void copyPK(uint type, uint id);
    Q_INVOKABLE void pk(QString file, uint cbid = 0);
    Q_INVOKABLE void updatePKTags(uint pkid, QString tags, uint cbid);
    Q_INVOKABLE void clearSolvedTime(uint pkid, uint cbid);

    QString pk(QImage *img, QString cont, QString file);
};

#endif // COLLECTACTION_H
