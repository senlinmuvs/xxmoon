#include "com/global.h"
#include "xmaction.h"
#include "com/runmain.h"
#ifdef Q_OS_MAC
#include "com/mac.h"
#endif

XMAction::XMAction() {
}
void XMAction::getCategories(QString k, QObject *obj) {
    DB_Async->exe("getCategories", [=]{
        QVariantList rlist;
        if(k.length() > 0){
            vector<Category> list = categoryDao->getCategories(k);
            for (Category c:list) {
                rlist.insert(rlist.end(), c.toVMap());
            }
        } else {
            vector<Category> all = categoryDao->getAll();
            vector<Category> list = categoryDao->getCategories(k);
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

void XMAction::getXMList(QString k, uint id, uint fromId, uint pklistWidth, uint cbid) {
    if(lg->isDebug()) {
        lg->debug(QString("getXMList k %1 id %2 fromId %3").arg(k).arg(id).arg(fromId));
    }
    k = k.trimmed();
    DB_Async->exe("getXMList", [=] {
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

void XMAction::getXM(uint id, uint listWidth, uint cbid) {
    DB_Async->exe("getXM", [=] {
        XM* xm = xmDao->getXM(id);
        if(xm) {
            xm->simpleCont = extractPKSimpleCont(xm->cont, "");
            sendMsg(cbid, xm->toVMap(1,1,listWidth));
        }
        delete xm;
    });
}

void XMAction::addCategory(QString name, QObject *obj) {
    DB_Async->exe("addCategory", [=] {
        QVariantMap m;
        QString err;
        Category *col = new Category();
        uint maxI = categoryDao->getMaxI();
        col->name = name;
        col->i = maxI + 1;
        categoryDao->add(col);
        m.insert("id", col->id);
        m.insert("i", col->i);
        m.insert("name", col->name);
        QMetaObject::invokeMethod(obj, "onAdded",
                                  Q_ARG(QVariant, QVariant::fromValue(err)),
                                  Q_ARG(QVariant, QVariant::fromValue(m)));
    });
}

void XMAction::editCategory(uint id, QString name, QObject *obj) {
    DB_Async->exe("editCategory", [=]{
        categoryDao->updateName(id, name);
        QMetaObject::invokeMethod(obj, "onUpdated");
    });
}

void XMAction::delCategory(uint id, uint cbid) {
    DB_Async->exe("delCategory", [=]{
        categoryDao->del(id);
        sendMsg(cbid, NULL);
    });
}

void XMAction::sorting(uint cid, uint srcIndex, uint dstIndex, uint cbid) {
    DB_Async->exe("sorting", [=]{
        categoryDao->updateIndex(cid, srcIndex, dstIndex);
        sendMsg(cbid, NULL);
    });
}
void XMAction::countCategory(uint cid, uint cbid) {
    DB_Async->exe("countCategory", [=]{
        uint n = xmDao->countCol(cid);
        sendMsg(cbid, n);
    });
}
void XMAction::getNewXMList(uint cid, uint fromId, uint pklistWidth, QObject *obj) {
    DB_Async->exe("getNewXMList", [=]{
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
void XMAction::deleteXM(uint id, QObject *obj) {
    DB_Async->exe("deleteXM", [=]{
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
void XMAction::updateXM(uint id, QString cont, QString k, uint pklistWidth, uint cbid) {
    DB_Async->exe("updateXM", [=]{
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

void XMAction::updateXMCid(uint colIndex, uint xmid, uint cid, QObject *obj) {
    DB_Async->exe("updateXMCid", [=] {
        xmDao->updateCid(xmid, cid);
        QMetaObject::invokeMethod(obj, "onMoved",
                                  Q_ARG(QVariant, QVariant::fromValue(colIndex)));
    });
}

void XMAction::addXM(uint cid, QString txt, uint pklistWidth, QObject *obj) {
    DB_Async->exe("addXM", [=]{
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
void XMAction::copyXM(uint type, uint id) {
    DB_Async->exe("copyXM", [=] {
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
void XMAction::xm(QString file, uint cbid) {
    file = ut::str::removePrefix(file, getFilePre());
    DB_Async->exe("xm", [=] {
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
QString XMAction::xm(QImage *img, QString cont, QString file) {
    XM *pk = new XM();
    pk->bj = false;
    pk->cont = cont;
    pk->cid = categoryDao->getFirstID();
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

void XMAction::updateXMTags(uint xmid, QString tags, uint cbid) {
    DB_Async->exe("updateXMTags", [=] {
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
void XMAction::clearSolvedTime(uint xmid, uint cbid) {
    DB_Async->exe("clearSolvedTime", [=] {
        xmDao->setSolveTime(xmid, 0);
        if(cbid>0) {
            sendMsg(cbid, 0);
        }
    });
}
void XMAction::encrypt(uint cid, QString pwd, uint cbid) {
    QString encrypted = ut::cipher::encryptTextAES(pwd, QString::number(cid));
    DB_Async->exe("encrypt", [=]{
        categoryDao->updatePwd(cid, encrypted);
        sendMsg(cbid, 0);
    });
}
void XMAction::deleteEncryption(uint cid, uint cbid) {
    DB_Async->exe("deleteEncryption", [=]{
        categoryDao->updatePwd(cid, "");
        sendMsg(cbid, 0);
    });
}
void XMAction::validateCategoryPWD(uint cid, QString pwd, uint cbid) {
    DB_Async->exe("validateCategoryPWD", [=]{
        Category *c = categoryDao->getCategory(cid);
        QString encrypted = ut::cipher::encryptTextAES(pwd, QString::number(cid));
        if(c->m == encrypted) {
            sendMsg(cbid, true);
        } else {
            sendMsg(cbid, false);
        }
        delete c;
    });
}
void XMAction::sticky(uint xmid, uint cbid) {
    DB_Async->exe("sticky", [=]{
        xmDao->setTop(xmid, 1);
        sendMsg(cbid, 0);
    });
}
void XMAction::cancelSticky(uint xmid, uint cbid) {
    DB_Async->exe("cancelSticky", [=]{
        xmDao->setTop(xmid, 0);
        sendMsg(cbid, 0);
    });
}