﻿#ifndef NOTEDAO_H
#define NOTEDAO_H

#include "model/note.h"
#include "model/work.h"

#include "basedao.h"

#include <QObject>

class NoteDao: public BaseDao {

public:
    NoteDao();

    Note* get(uint id);
    uint getIdByTime(qint64 time);
    void insert(Note *n);
    QList<Note*> insert(QList<Note*> list, std::function<void (int)> cb);
    uint getMaxId() override;
    vector<Work> getWorkList(QString k, QString tag, ulong fromTime);
    QList<Note*> getNoteList(QString k, uint wid, uint page, QString sort);
    void updateNote(uint id, uint pos0, uint pos1, QString cont);
    void updateTags(uint id, QString tags);
    void deleteNote(uint id);
    void deleteNote_(uint id);
    void deleteByWid(uint wid);
    bool exists(uint wid, QString cont);
    uint count();
    qint64 getEarliestTime();
    qint64 getLastTime();
};

#endif // NOTEDAO_H
