#include "com/global.h"
#include "bookaction.h"

BookAction::BookAction() {
}

void BookAction::addWork(QString name,QString author,uint time, QString tag, QString extra, QObject *obj) {
    DB_Async->exe("addWork", [=] {
        Work *w = new Work();
        w->name = name;
        w->author = author;
        w->time = time;
        w->tag = tag;
        w->extra = extra;
        w->t = 1;
        w->convTagComma2Pound();
        workDao->add(w);
        w->convTagPound2Comma();
        QMetaObject::invokeMethod(obj, "onAddWork", Q_ARG(QVariant, QVariant::fromValue(w->toVMap())));
        delete w;
    });
}
void BookAction::updateWork(uint bid, QString name, QString author, uint time, QString tag, QString extra, QObject *obj) {
    DB_Async->exe("updateWork", [=]{
        Work *w = workDao->get(bid);
        if(w) {
            w->name = name;
            w->author = author;
            w->time = time;
            w->tag = tag;
            w->extra = extra;
            w->t = 1;
            w->convTagComma2Pound();
            workDao->update(w);
            w->convTagPound2Comma();
            QMetaObject::invokeMethod(obj, "onUpdateWork", Q_ARG(QVariant, QVariant::fromValue(w->toVMap())));
        }
        delete w;
    });
}
void BookAction::delWork(uint id, uint cbid) {
    DB_Async->exe("delWork", [=]{
        workDao->del(id);
        noteDao->deleteByWid(id);
        sendMsg(cbid, nullptr);
    });
}
void BookAction::getNote(uint id, uint cbid) {
    DB_Async->exe("getNote", [=]{
        Note *n = noteDao->get(id);
        sendMsg(cbid, n->toVMap());
    });
}

void BookAction::getWorkList(QString k, QString tag, ulong fromTime, QObject *obj) {
    filterSearchKey(k);
    DB_Async->exe("getWorkList", [=]{
        vector<Work> list = noteDao->getWorkList(k, tag, fromTime);
        QVariantList rlist;
        for (Work w:list) {
            w.convTagPound2Comma();
            rlist << w.toVMap();
        }
        QMetaObject::invokeMethod(obj, "pushWork",
                    Q_ARG(QVariant, QVariant::fromValue(rlist)));
    });
}

void BookAction::getNoteList(QString k, uint wid, uint page, QString sort, uint listWidth, uint cbid) {
    filterSearchKey(k);
    DB_Async->exe("getNoteList", [=] {
        QList<Note*> list = noteDao->getNoteList(k, wid, page, sort);
        QVariantList rlist;
        for (Note *n:list) {
            n->cont = extractNoteSimpleCont(n->cont, k);
            rlist << n->toVMap(1,listWidth);
            delete n;
        }

        envDao->set(ENV_K_LAST_SORT, sort);
        sendMsg(cbid, rlist);
    });
}

void BookAction::addNote(uint wid, QString cont, uint pos0, uint pos1, uint listWidth, uint cbid) {
    DB_Async->exe("addNote", [=] {
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
    DB_Async->exe("updateNote", [=] {
        noteDao->updateNote(id, pos0, pos1, cont);
        Note *n = noteDao->get(id);
        sendMsg(cbid, n->toVMap(1, bklistWidth));
        delete n;
    });
}
void BookAction::updateNoteTags(uint id, QString tags, uint cbid) {
    DB_Async->exe("updateNoteTags", [=] {
        noteDao->updateTags(id, tags);
        Note *n = noteDao->get(id);
        sendMsg(cbid, ut::col::createMap("tags", n->tags));
        delete n;
    });
}
void BookAction::deleteNote(uint id, QObject *obj) {
    DB_Async->exe("deleteNote", [=] {
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

void BookAction::getWorkTagList(uint cbid) {
    DB_Async->exe("getWorkTagList", [=] {
        QList<QString> list = workDao->getWorkTagList();
        sendMsg(cbid, list);
    });
}
void BookAction::countWork(uint cbid) {
    DB_Async->exe("countWork", [=] {
        uint c = workDao->count();
        sendMsg(cbid, c);
    });
}
