#include "com/global.h"
#include "bookaction.h"

BookAction::BookAction() {
}

void BookAction::addWork(QString name,QString author,uint time, QObject *obj) {
    DB_Async->exe([=] {
        Work *w = new Work();
        w->name = name;
        w->author = author;
        w->time = time;
        w->t = 1;
        workDao->add(w);
        QMetaObject::invokeMethod(obj, "onAddWork", Q_ARG(QVariant, QVariant::fromValue(w->toVMap())));
    });
}
void BookAction::updateWork(uint bid, QString name, QString author, uint time, QObject *obj) {
    DB_Async->exe([=]{
        Work *w = workDao->get(bid);
        if(w) {
            w->name = name;
            w->author = author;
            w->time = time;
            w->t = 1;
            workDao->update(w);
            QMetaObject::invokeMethod(obj, "onUpdateWork", Q_ARG(QVariant, QVariant::fromValue(w->toVMap())));
        }
    });
}
void BookAction::delWork(uint id, uint cbid) {
    DB_Async->exe([=]{
        workDao->del(id);
        noteDao->deleteByWid(id);
        sendMsg(cbid, NULL);
    });
}
void BookAction::getNote(uint id, uint cbid) {
    DB_Async->exe([=]{
        Note *n = noteDao->get(id);
        sendMsg(cbid, n->toVMap());
    });
}

void BookAction::getWorkList(QString k, ulong fromTime, QObject *obj) {
    DB_Async->exe([=]{
        vector<Work> list = noteDao->getWorkList(k, fromTime);
        QVariantList rlist;
        for (Work w:list) {
            rlist << w.toVMap();
        }
        QMetaObject::invokeMethod(obj, "pushWork",
                    Q_ARG(QVariant, QVariant::fromValue(rlist)));
    });
}

void BookAction::getNoteList(QString k, uint wid, uint page, QString sort, uint listWidth, QObject *obj) {
    DB_Async->exe([=] {
        QList<Note*> list = noteDao->getNoteList(k, wid, page, sort);
        QVariantList rlist;
        for (Note *n:list) {
            n->cont = extractNoteSimpleCont(n->cont, k);
            rlist << n->toVMap(1,listWidth);
            delete n;
        }
        QMetaObject::invokeMethod(obj, "pushNote",
                    Q_ARG(QVariant, QVariant::fromValue(rlist)));
    });
}

void BookAction::addNote(uint wid, QString cont, uint pos0, uint pos1, uint listWidth, uint cbid) {
    DB_Async->exe([=] {
        Note *n = new Note();
        n->wid = wid;
        n->cont = cont;
        n->pos0 = pos0;
        n->pos1 = pos1;
        n->time = ut::time::getCurSeconds();
        noteDao->insert(n);
        sendMsg(cbid, n->toVMap(1,listWidth));
        delete n;
    });
}
void BookAction::updateNote(uint id, QString cont, uint pos0, uint pos1, uint bklistWidth, uint cbid) {
    DB_Async->exe([=] {
        noteDao->updateNote(id, pos0, pos1, cont);
        Note *n = noteDao->get(id);
        sendMsg(cbid, n->toVMap(1, bklistWidth));
        delete n;
    });
}
void BookAction::updateNoteTags(uint id, QString tags, uint cbid) {
    DB_Async->exe([=] {
        noteDao->updateTags(id, tags);
        Note *n = noteDao->get(id);
        sendMsg(cbid, ut::col::createMap("tags", n->tags));
        delete n;
    });
}
void BookAction::deleteNote(uint id, QObject *obj) {
    DB_Async->exe([=] {
        Note *n = noteDao->get(id);
        if(n->id > 0) {
            Work *w = workDao->get(n->wid);
            if(w->fro > 0) {
                noteDao->deleteNote_(id);
            } else {
                noteDao->deleteNote(id);
            }
        }
        QMetaObject::invokeMethod(obj, "onDeletedNote");
    });
}
