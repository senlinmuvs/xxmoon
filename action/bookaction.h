#ifndef BOOKACTION_H
#define BOOKACTION_H

#include <QObject>

class BookAction: public QObject {
    Q_OBJECT
public:
    BookAction();

    Q_INVOKABLE void getWorkList(QString k, QString tag, ulong fromTime, QObject *obj);
    Q_INVOKABLE void addWork(QString name,QString author,uint time, QString tag, QObject *obj);
    Q_INVOKABLE void updateWork(uint bid, QString name, QString author, uint time, QString tag, QObject *obj);
    Q_INVOKABLE void delWork(uint id, uint cbid);

    Q_INVOKABLE void getNoteList(QString k, uint wid, uint page, QString sort, uint listWidth, QObject *obj);
    Q_INVOKABLE void addNote(uint wid, QString cont, uint pos0, uint pos1, uint listWidth, uint cbid);
    Q_INVOKABLE void updateNote(uint id, QString cont, uint pos0, uint pos1, uint bklistWidth, uint cbid);
    Q_INVOKABLE void updateNoteTags(uint id, QString tags, uint cbid);
    Q_INVOKABLE void deleteNote(uint id, QObject *obj);
    Q_INVOKABLE void getNote(uint id, uint cbid);
    Q_INVOKABLE void getWorkTagList(uint cbid);
    Q_INVOKABLE void countWork(uint cbid);
};

#endif // BOOKACTION_H
