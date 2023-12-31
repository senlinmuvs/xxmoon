#include "com/global.h"
#include "collectaction.h"
#include "com/runmain.h"
#ifdef Q_OS_MAC
#include "com/mac.h"
#endif

CollectAction::CollectAction() {
}
void CollectAction::getCollects(QString k, QObject *obj) {
    DB_Async->exe([=]{
        QVariantList rlist;
        if(k.length() > 0){
            vector<Collect> list = colDao->getCollects(k);
            for (Collect c:list) {
                rlist.insert(rlist.end(), c.toVMap());
            }
        } else {
            vector<Collect> all = colDao->getAll();
            vector<Collect> list = colDao->getCollects(k);
            for (Collect c:all) {
                for(Collect c2:list) {
                    if(c.id == c2.id) {
                        c = c2;
                        break;
                    }
                }
                rlist.insert(rlist.end(), c.toVMap());
            }
        }
        QMetaObject::invokeMethod(obj, "onGetCollects",
                    Q_ARG(QVariant, QVariant::fromValue(rlist)));
    });
}

void CollectAction::getPKList(QString k, uint id, uint fromId, uint pklistWidth, QObject *obj) {
    if(lg->isDebug()) {
        lg->debug(QString("getPKList k %1 id %2 fromId %3").arg(k).arg(id).arg(fromId));
    }
    k = k.trimmed();
    DB_Async->exe([=] {
        QList<PK*> list = pkDao->getPKList(k, id, fromId);
        QVariantList rlist;
        for (PK *p:list) {
            p->simpleCont = extractPKSimpleCont(p->cont, k);
            rlist << p->toVMap(0,0,pklistWidth);
            delete p;
        }
        QMetaObject::invokeMethod(obj, "pushPK",
                    Q_ARG(QVariant, QVariant::fromValue(rlist)));
    });
}

void CollectAction::getPK(uint id, uint listWidth, uint cbid) {
    DB_Async->exe([=] {
        PK* pk = pkDao->getPK(id);
        if(pk) {
            pk->simpleCont = extractPKSimpleCont(pk->cont, "");
            sendMsg(cbid, pk->toVMap(1,1,listWidth));
        }
        delete pk;
    });
}

void CollectAction::addCol(QString name, QObject *obj) {
    DB_Async->exe([=] {
        QVariantMap m;
        QString err;
        if(!app->isActivated()) {
            uint c = colDao->count();
            if(c >= MAX_FOLDER_TRIAL) {
                if(DEPLOY == 0) {
                    err = QObject::tr("Please activate");
                } else {
                    //TODO tips 升级
//                    err = QObject::tr("Please activate");
                }
                QMetaObject::invokeMethod(obj, "onAdded",
                                          Q_ARG(QVariant, QVariant::fromValue(err)),
                                          Q_ARG(QVariant, QVariant::fromValue(m)));
                return;
            }
        }
        Collect *col = new Collect();
        uint maxI = colDao->getMaxI();
        col->name = name;
        col->i = maxI + 1;
        colDao->add(col);
        m.insert("id", col->id);
        m.insert("i", col->i);
        m.insert("name", col->name);
        QMetaObject::invokeMethod(obj, "onAdded",
                                  Q_ARG(QVariant, QVariant::fromValue(err)),
                                  Q_ARG(QVariant, QVariant::fromValue(m)));
    });
}

void CollectAction::editCol(uint id, QString name, QObject *obj) {
    DB_Async->exe([=]{
        colDao->updateName(id, name);
        QMetaObject::invokeMethod(obj, "onUpdated");
    });
}

void CollectAction::delCol(uint id, uint cbid) {
    DB_Async->exe([=]{
        colDao->del(id);
        sendMsg(cbid, NULL);
    });
}

void CollectAction::sortingCol(uint cid, uint srcIndex, uint dstIndex, uint cbid) {
    DB_Async->exe([=]{
        colDao->updateIndex(cid, srcIndex, dstIndex);
        sendMsg(cbid, NULL);
    });
}
void CollectAction::countCol(uint cid, uint cbid) {
    DB_Async->exe([=]{
        uint n = pkDao->countCol(cid);
        sendMsg(cbid, n);
    });
}
void CollectAction::getNewPKList(uint cid, uint fromId, uint pklistWidth, QObject *obj) {
    DB_Async->exe([=]{
        QList<PK*> list = pkDao->getNewPKList(cid, fromId);
        QVariantList rlist;
        for (PK *p:list) {
            QVariantList eList;
            p->simpleCont = extractPKSimpleCont(p->cont, "");
            rlist.insert(rlist.end(), p->toVMap(0,0,pklistWidth));
            delete p;
        }
        QMetaObject::invokeMethod(obj, "onGetNewPKList",
                    Q_ARG(QVariant, QVariant::fromValue(rlist)));
    });
}
void CollectAction::deletePK(uint id, QObject *obj) {
    DB_Async->exe([=]{
        PK *pk = pkDao->getPK(id);
        if(pk!=nullptr){
            QString imgLink = pk->getImgLink();
            if(imgLink.length()>0){
                uint ref = pkDao->countImgRefrence(imgLink);
                if(ref>0){
                    QMetaObject::invokeMethod(obj, "onDeleted", Q_ARG(QVariant, QVariant::fromValue(ref)));
                    return;
                }
            }
            pkDao->deletePK(id);
            if(pk->img != "") {
                deleteFile(cfg->imgDir + "/" + pk->img);
                QString imgName = pk->img.mid(0, pk->img.lastIndexOf("."));
                QString postfix = pk->img.mid(pk->img.lastIndexOf("."));
                deleteFile(cfg->imgDir + "/" + imgName + "_original" + postfix);
//                qDebug() << "<<<<<<<<<<<delete file" << imgName << postfix;
            }
            QMetaObject::invokeMethod(obj, "onDeleted",
                                      Q_ARG(QVariant, QVariant::fromValue(0)));
            delete pk;
        }
    });
}
void CollectAction::updatePK(uint id, QString cont, QString k, uint pklistWidth, uint cbid) {
    DB_Async->exe([=]{
        PK *pk = pkDao->getPK(id);
        int st = 0;
        if(pk != nullptr) {
            if(pk->cont != cont) {
                if(!pk->jm) {
                    pkDao->updatePK(id, cont, 0);
                    QString tmpFile = cfg->tmpDir + "/" + cfg->tmpPKPre + QString::number(id);
                    if(ut::file::exists(tmpFile)){
                        ut::file::writeText(tmpFile, cont);
                    }
                } else {
                    st = 3;
                }
            } else {
                st = 2;
            }
        } else {
            st = 1;
        }
        QVariantMap param;
        param.insert("st", st);
        if(st == 0) {
            QString simpleCont = extractPKSimpleCont(cont, k);
            param.insert("simple_cont", simpleCont);
            param.insert("cont", cont);
            param.insert("qmls", doc_parser->parseQML(cont));
            param.insert("simple_qmls", doc_parser->parseQML(simpleCont, pklistWidth));
            param.insert("imgs", extractImgs(cont));
        }
        sendMsg(cbid, param);
        delete pk;
    });
}

void CollectAction::updatePKCid(uint colIndex, uint pkId, uint cid, QObject *obj) {
    DB_Async->exe([=] {
        QVariantMap m;
        QString err;
        if(!app->isActivated()) {
            uint c = pkDao->countCol(cid);
            if(c >= MAX_PK_EACH_FOLDER_TRIAL) {
                alert(QObject::tr("Please activate"));
                return;
            }
        }
        pkDao->updateCid(pkId, cid);
        QMetaObject::invokeMethod(obj, "onMoved",
                                  Q_ARG(QVariant, QVariant::fromValue(colIndex)));
    });
}

void CollectAction::addPK(uint cid, QString txt, uint pklistWidth, QObject *obj) {
    DB_Async->exe([=]{
        if(!app->isActivated()) {
            uint c = pkDao->countCol(cid);
            if(c >= MAX_PK_EACH_FOLDER_TRIAL) {
                alert(QObject::tr("Please activate"));
                return;
            }
        }
        PK *pk = new PK();
        pk->cont = txt;
        pk->cid = cid;
        pkDao->add(pk);

        PK *newPK = pkDao->getPK(pk->id);
        QVariantMap m;
        if(newPK!=nullptr) {
            newPK->simpleCont = extractPKSimpleCont(newPK->cont, "");
            m = newPK->toVMap(0,0,pklistWidth);
        } else {
            alert(QObject::tr("Failure.Not found the doc!"));
            return;
        }
        QMetaObject::invokeMethod(obj, "onAdded",
                                  Q_ARG(QVariant, QVariant::fromValue(m)));
        delete newPK;
        delete pk;
    });
}
void CollectAction::copyPK(uint type, uint id) {
    DB_Async->exe([=] {
        PK *pk = pkDao->getPK(id);
        if(pk!=nullptr) {
            if(lg->isDebug()){
                lg->debug(QString("copy type %1 id %2 pk %3").arg(type).arg(id).arg(pk->toString()));
            }
            if(type == 0) {//copy img
                if(pk->img.length() > 0) {
                    QImage qimg;
                    qimg.load(cfg->imgDir + "/" + pk->img);
                    RunMain::INS().exec(([qimg]{
                        ut::cpb::setImage(qimg);
                    }));
                }
                st(0);
            } else if(type == 1) {//copy img link
                if(pk->img.length() > 0) {
                    RunMain::INS().exec(([pk]{
                        ut::cpb::setText("!("+pk->img+")");
                        st(0);
                    }));
                }
            } else if(type == 2) {//copy text
                RunMain::INS().exec(([pk]{
                    ut::cpb::setText(pk->cont);
                    st(0);
                }));
            }
            delete pk;
        } else {
            if(lg->isDebug()){
                lg->debug(QString("copy type %1 id %2 pk is null").arg(type).arg(id));
            }
        }
    });
}
void CollectAction::pk(QString file, uint cbid) {
    file = ut::str::removePrefix(file, getFilePre());
    DB_Async->exe([=] {
        QImage *qimg = new QImage();
        QString path = file;
#ifdef Q_OS_WIN
        path = path.replace("//", "\\").replace("/", "\\");
#endif
        qimg->load(path);
        QString pkimg = pk(qimg, "", path);
        delete qimg;

        if(cbid>0) {
            sendMsg(cbid, pkimg);
        }
    });
}
QString CollectAction::pk(QImage *img, QString cont, QString file) {
    PK *pk = new PK();
    pk->bj = false;
    pk->cont = cont;
    pk->cid = colDao->getFirstID();
    QString tip = "";
    if(pk->cont != "") {
        tip += QString("%1 %2").arg(QObject::tr("Text")).arg(pk->cont.length());
    }

    QString new_clipboard_text;
    QString year = ut::time::getYearStr();
    QString time_str = ut::time::getCurrentTimeStr();
    QString path = cfg->imgDir + "/" + year;
    QDir dir;
    if(!dir.exists(path)) {
        dir.mkpath(path);
    }
    if(!img->isNull()) {
        QString w = QString::number(img->width());
        QString h = QString::number(img->height());
        QString postfix = file.isEmpty() ? ".png" : ut::file::postfix(file);
        QString file_name = time_str+"."+w+"."+h+postfix;
        QString full_path = path+"/"+file_name;
        QFile f;
        if(!file.isEmpty()) {
            f.setFileName(file);
            f.copy(full_path);
        } else {
            img->save(full_path);
            f.setFileName(full_path);
        }
        qint64 imgSize = f.size();
        if(imgSize > 1024*1024) {
            QString original_file = path+"/"+time_str+"."+w+"."+h+ "_original" + postfix;
            f.copy(original_file);
            ut::img::reduceImage(full_path, full_path, 50, 0, 0, 0);
        }
        pk->img = (year + "/" + file_name);
        new_clipboard_text = "!("+pk->img+")";
    }
    pkDao->add(pk);
    if(lg->isDebug()){
        lg->debug(QString("add pk %1").arg(pk->toString()));
    }
    QString pkimg = pk->img;
    RunMain::INS().exec([pk, new_clipboard_text]{
        QMetaObject::invokeMethod(engine->rootObjects()[0], "onFinished",
                Q_ARG(QVariant, QVariant::fromValue(CONT_TYPE_PK)),
                Q_ARG(QVariant, QVariant::fromValue(-1)),
                Q_ARG(QVariant, QVariant::fromValue(-1)),
                Q_ARG(QVariant, QVariant::fromValue(0)));
        ut::cpb::clear();

        delete pk;
        if(new_clipboard_text.length()>0) {
            ut::cpb::setText(new_clipboard_text);
        }
    });
    return pkimg;
}

void CollectAction::updatePKTags(uint pkid, QString tags, uint cbid) {
    DB_Async->exe([=] {
        QString oldTags = pkDao->getTags(pkid);
        pkDao->updatePKTags(pkid, tags);
        Tag *tag = tagDao->getByName("?");
        uint stime = 0;
        if(tag) {
            QString ques = QString("#%1#").arg(tag->id);
            bool oldExists = oldTags.contains(ques);
            bool newExists = tags.contains(ques);
            if(!oldExists && newExists) {
                pkDao->setSolveTime(pkid, 0);
            }
            if(oldExists && !newExists) {
                stime = ut::time::getCurSeconds();
                pkDao->setSolveTime(pkid, stime);
            }
        }
        sendMsg(cbid, ut::col::createMap("pkid", pkid, "tags", tags, "stime", stime));
    });
}
void CollectAction::clearSolvedTime(uint pkid, uint cbid) {
    DB_Async->exe([=] {
        pkDao->setSolveTime(pkid, 0);
        if(cbid>0) {
            sendMsg(cbid, 0);
        }
    });
}
