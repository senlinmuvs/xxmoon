#include "com/global.h"
#include "categoryaction.h"
#include "com/runmain.h"
#ifdef Q_OS_MAC
#include "com/mac.h"
#endif

CategoryAction::CategoryAction() {
}
void CategoryAction::getCategories(QString k, QObject *obj) {
    DB_Async->exe([=]{
        QVariantList rlist;
        if(k.length() > 0){
            vector<Category> list = colDao->getCategories(k);
            for (Category c:list) {
                rlist.insert(rlist.end(), c.toVMap());
            }
        } else {
            vector<Category> all = colDao->getAll();
            vector<Category> list = colDao->getCategories(k);
            for (Category c:all) {
                for(Category c2:list) {
                    if(c.id == c2.id) {
                        c = c2;
                        break;
                    }
                }
                rlist.insert(rlist.end(), c.toVMap());
            }
        }
        QMetaObject::invokeMethod(obj, "onGetCategories",
                    Q_ARG(QVariant, QVariant::fromValue(rlist)));
    });
}

void CategoryAction::getXMList(QString k, uint id, uint fromId, uint pklistWidth, uint cbid) {
    if(lg->isDebug()) {
        lg->debug(QString("getXMList k %1 id %2 fromId %3").arg(k).arg(id).arg(fromId));
    }
    k = k.trimmed();
    DB_Async->exe([=] {
        QList<XM*> list = xmDao->getXMList(k, id, fromId);
        QVariantList rlist;
        for (XM *xm:list) {
            xm->simpleCont = extractPKSimpleCont(xm->cont, k);
            rlist << xm->toVMap(0,0,pklistWidth);
            delete xm;
        }
        sendMsg(cbid, rlist);
    });
}

void CategoryAction::getXM(uint id, uint listWidth, uint cbid) {
    DB_Async->exe([=] {
        XM* xm = xmDao->getXM(id);
        if(xm) {
            xm->simpleCont = extractPKSimpleCont(xm->cont, "");
            sendMsg(cbid, xm->toVMap(1,1,listWidth));
        }
        delete xm;
    });
}

void CategoryAction::addCategory(QString name, QObject *obj) {
    DB_Async->exe([=] {
        QVariantMap m;
        QString err;
        Category *col = new Category();
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

void CategoryAction::editCategory(uint id, QString name, QObject *obj) {
    DB_Async->exe([=]{
        colDao->updateName(id, name);
        QMetaObject::invokeMethod(obj, "onUpdated");
    });
}

void CategoryAction::delCategory(uint id, uint cbid) {
    DB_Async->exe([=]{
        colDao->del(id);
        sendMsg(cbid, NULL);
    });
}

void CategoryAction::sorting(uint cid, uint srcIndex, uint dstIndex, uint cbid) {
    DB_Async->exe([=]{
        colDao->updateIndex(cid, srcIndex, dstIndex);
        sendMsg(cbid, NULL);
    });
}
void CategoryAction::countCategory(uint cid, uint cbid) {
    DB_Async->exe([=]{
        uint n = xmDao->countCol(cid);
        sendMsg(cbid, n);
    });
}
void CategoryAction::getNewXMList(uint cid, uint fromId, uint pklistWidth, QObject *obj) {
    DB_Async->exe([=]{
        QList<XM*> list = xmDao->getNewXMList(cid, fromId);
        QVariantList rlist;
        for (XM *p:list) {
            QVariantList eList;
            p->simpleCont = extractPKSimpleCont(p->cont, "");
            rlist.insert(rlist.end(), p->toVMap(0,0,pklistWidth));
            delete p;
        }
        QMetaObject::invokeMethod(obj, "onGetNewPKList",
                    Q_ARG(QVariant, QVariant::fromValue(rlist)));
    });
}
void CategoryAction::deleteXM(uint id, QObject *obj) {
    DB_Async->exe([=]{
        XM *xm = xmDao->getXM(id);
        if(xm!=nullptr){
            QString imgLink = xm->getImgLink();
            if(imgLink.length()>0){
                uint ref = xmDao->countImgRefrence(imgLink);
                if(ref>0){
                    QMetaObject::invokeMethod(obj, "onDeleted", Q_ARG(QVariant, QVariant::fromValue(ref)));
                    return;
                }
            }
            xmDao->deleteXM(id);
            if(xm->img != "") {
                deleteFile(cfg->imgDir + "/" + xm->img);
                QString imgName = xm->img.mid(0, xm->img.lastIndexOf("."));
                QString postfix = xm->img.mid(xm->img.lastIndexOf("."));
                deleteFile(cfg->imgDir + "/" + imgName + "_original" + postfix);
//                qDebug() << "<<<<<<<<<<<delete file" << imgName << postfix;
            }
            QMetaObject::invokeMethod(obj, "onDeleted",
                                      Q_ARG(QVariant, QVariant::fromValue(0)));
            delete xm;
        }
    });
}
void CategoryAction::updateXM(uint id, QString cont, QString k, uint pklistWidth, uint cbid) {
    DB_Async->exe([=]{
        XM *xm = xmDao->getXM(id);
        int st = 0;
        if(xm != nullptr) {
            if(xm->cont != cont) {
                if(!xm->jm) {
                    xmDao->updateXM(id, cont, 0);
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
        delete xm;
    });
}

void CategoryAction::updateXMCid(uint colIndex, uint xmid, uint cid, QObject *obj) {
    DB_Async->exe([=] {
        xmDao->updateCid(xmid, cid);
        QMetaObject::invokeMethod(obj, "onMoved",
                                  Q_ARG(QVariant, QVariant::fromValue(colIndex)));
    });
}

void CategoryAction::addXM(uint cid, QString txt, uint pklistWidth, QObject *obj) {
    DB_Async->exe([=]{
        XM *xm = new XM();
        xm->cont = txt;
        xm->cid = cid;
        xmDao->add(xm);

        XM *newXM = xmDao->getXM(xm->id);
        QVariantMap m;
        if(newXM!=nullptr) {
            newXM->simpleCont = extractPKSimpleCont(newXM->cont, "");
            m = newXM->toVMap(0,0,pklistWidth);
        } else {
            alert(QObject::tr("Failure.Not found the doc!"));
            return;
        }
        QMetaObject::invokeMethod(obj, "onAdded",
                                  Q_ARG(QVariant, QVariant::fromValue(m)));
        delete newXM;
        delete xm;
    });
}
void CategoryAction::copyXM(uint type, uint id) {
    DB_Async->exe([=] {
        XM *pk = xmDao->getXM(id);
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
void CategoryAction::xm(QString file, uint cbid) {
    file = ut::str::removePrefix(file, getFilePre());
    DB_Async->exe([=] {
        QImage *qimg = new QImage();
        QString path = file;
#ifdef Q_OS_WIN
        path = path.replace("//", "\\").replace("/", "\\");
#endif
        qimg->load(path);
        QString xmimg = xm(qimg, "", path);
        delete qimg;

        if(cbid>0) {
            sendMsg(cbid, xmimg);
        }
    });
}
QString CategoryAction::xm(QImage *img, QString cont, QString file) {
    XM *pk = new XM();
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
    xmDao->add(pk);
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

void CategoryAction::updateXMTags(uint xmid, QString tags, uint cbid) {
    DB_Async->exe([=] {
        QString oldTags = xmDao->getTags(xmid);
        xmDao->updateXMTags(xmid, tags);
        Tag *tag = tagDao->getByName("?");
        uint stime = 0;
        if(tag) {
            QString ques = QString("#%1#").arg(tag->id);
            bool oldExists = oldTags.contains(ques);
            bool newExists = tags.contains(ques);
            if(!oldExists && newExists) {
                xmDao->setSolveTime(xmid, 0);
            }
            if(oldExists && !newExists) {
                stime = ut::time::getCurSeconds();
                xmDao->setSolveTime(xmid, stime);
            }
        }
        sendMsg(cbid, ut::col::createMap("pkid", xmid, "tags", tags, "stime", stime));
    });
}
void CategoryAction::clearSolvedTime(uint xmid, uint cbid) {
    DB_Async->exe([=] {
        xmDao->setSolveTime(xmid, 0);
        if(cbid>0) {
            sendMsg(cbid, 0);
        }
    });
}
void CategoryAction::encrypt(uint cid, QString pwd, uint cbid) {
    QString encrypted = ut::cipher::encryptTextAES(pwd, QString::number(cid));
    DB_Async->exe([=]{
        colDao->updatePwd(cid, encrypted);
        sendMsg(cbid, 0);
    });
}
void CategoryAction::deleteEncryption(uint cid, uint cbid) {
    DB_Async->exe([=]{
        colDao->updatePwd(cid, "");
        sendMsg(cbid, 0);
    });
}
void CategoryAction::validateCategoryPWD(uint cid, QString pwd, uint cbid) {
    DB_Async->exe([=]{
        Category *c = colDao->getCategory(cid);
        QString encrypted = ut::cipher::encryptTextAES(pwd, QString::number(cid));
        if(c->m == encrypted) {
            sendMsg(cbid, true);
        } else {
            sendMsg(cbid, false);
        }
        delete c;
    });
}