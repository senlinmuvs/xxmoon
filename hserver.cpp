#include "hserver.h"
#include <QTimer>
#include <QUuid>
#include <QVariant>
#include <QJsonObject>
#include <QJsonDocument>
#include "com/global.h"
#include "app.h"

/////////////////////////
class HServerLoop:public QThread {

public:
    void run() {
        while(running) {
            //event loop
            if(!serverMsgQueue->empty()) {
                std::tuple<int, QMap<QString,QString>> tp = serverMsgQueue->front();
                serverMsgQueue->pop();
                HServer::INS().exec(get<0>(tp), get<1>(tp));
            }

            //data queue check
            if(HServer::INS().sizeDev() == 0) {
                serverDataQueue->clear();
            }

            //clear invalid devices
            HServer::INS().clearInvalidDevices();

            QThread::msleep(500);
        }
        HServer::INS().close();
    }
    static HServerLoop& INS() {
        static HServerLoop ins;
        return ins;
    }
};

/////////////////////////
HServer::HServer(): QThread() {
}

void HServer::hi(const Request &req, Response &resp) {
    Headers headers = req.headers;
    QString header = "Headers:\n";
    for(auto h : headers) {
        QString k = QString::fromStdString(h.first);
        QString v = QString::fromStdString(h.second);
        header += k + "=" + v + "\n";
    }
    QString body =
            "xxmoon v"+a->getVersion() + "\n\n"
            + header;
    resp.set_content(body.toStdString(), "text/plain");
}

void HServer::login(const Request &req, Response &resp) {
    QString qr = QString::fromStdString(req.get_file_value("qr").content);
    QString dev = QString::fromStdString(req.get_file_value("dev").content);
    if(lg->isDebug()) {
        lg->debug(QString("ip %1 login %2 %3").arg("-").arg(qr).arg(dev));
    }
    QString qrcode = getCurQRCode();
    if(qr == "" || dev == "" || qrcode == "") {
        lg->error(QString("login fail param error qr %1 dev %2 qr %3").arg(qr).arg(dev).arg(qrcode));
        return;
    }
    QStringList qrarr = qrcode.split("|");
    QString qr_ = qrarr.at(qrarr.length() - 1);
    qint64 cur = ut::time::getCurMills();
    if(qr != qr_ || cur - this->qrlst >= 60000) {
        lg->error(QString("login fail qr %1").arg(qrcode));
        return;
    }
    if(lg->isDebug()) {
        lg->debug(QString("login suc qr %1").arg(qrcode));
    }
    this->devs.append(std::make_tuple(dev, cur));
    this->qrlst = 0;
    setCurQRCode("");
    QString tk = QUuid::createUuid().toString(QUuid::Id128);
    devTKMap.insert(dev, tk);
    lastGetDataTimeMap.insert(dev, cur);

    QVariantList l;
    l.append(dev);
    l.append(cur);
    pushMsg(0, l);

    QJsonObject respd = ut::json::create("tk", tk, "st", 0);
    std::string r = QJsonDocument(respd).toJson(QJsonDocument::Compact).toStdString();
    resp.set_content(r, RESP_TYPE_JSON);
}

bool HServer::checkTK(const Request &req, Response &resp) {
    QString dev = QString::fromStdString(req.get_file_value("dev").content);
    QString tk = QString::fromStdString(req.get_file_value("tk").content);
    QString tk_ = devTKMap.value(dev);
    bool ok = tk == tk_;
    if(!ok) {
        if(lg->isDebug()) {
            lg->debug(QString("checkTK ser tk %1 cli tk %2").arg(tk_).arg(tk));
        }
        QJsonObject respd = ut::json::create("st", 1);
        std::string r = QJsonDocument(respd).toJson(QJsonDocument::Compact).toStdString();
        resp.set_content(r, RESP_TYPE_JSON);
    }
    return ok;
}

void HServer::getData(const Request &req, Response &resp) {
    if(!checkTK(req, resp)) {
        return;
    }
    if(lg->isDebug()) {
        lg->debug(QString("getData data queue devs %1").arg(serverDataQueue->size()));
        for(QString k:serverDataQueue->keys()) {
            bool b = serverDataQueue->value(k).empty();
            lg->debug(QString("getData dev %1 data queue isEmpty %2").arg(k).arg(b?"yes":"no"));
        }
    }
    QString dev = QString::fromStdString(req.get_file_value("dev").content);
    QString lines = "";
    QString data = "";
    while((data = takeServerData(dev)).length() > 0) lines += data + "\n";

    qint64 cur = ut::time::getCurMills();
    lastGetDataTimeMap.insert(dev, cur);
    //
    QJsonObject respd = ut::json::create("data", lines, "st", 0);
    std::string r = QJsonDocument(respd).toJson(QJsonDocument::Compact).toStdString();
    resp.set_content(r, RESP_TYPE_JSON);
}

void HServer::putData(const Request &req, Response &resp) {
    if(!checkTK(req, resp)) {
        return;
    }
    QString data = QString::fromStdString(req.get_file_value("data").content);
    QJsonObject jo = QJsonDocument::fromJson(data.toUtf8()).object();
    DB_Async->exe("putData", [data,jo] {
        QString wname = ut::json::getString(jo, "wname", "");
        QString aname = ut::json::getString(jo, "aname", "");
        int ty = 0;
        if(wname.isEmpty() && aname.isEmpty()) {
            ty = CONT_TYPE_PK;
            if(lg->isDebug()) {
                lg->debug(QString("putData pk %1").arg(data));
            }
            XM *p = XM::convXM(jo);
            Category* defCol = categoryDao->getCategoryByIndex(0);
            p->cid = defCol->id;
            xmDao->add(p);
            delete p;
        } else {
            ty = CONT_TYPE_BOOK;
            if(lg->isDebug()) {
                lg->debug(QString("putData note %1").arg(data));
            }
            Note *n = Note::convNote(jo);
            Work *w = Work::convWork(jo);
            Work *w_ = workDao->get(w->name, w->author);
            if(w_ == nullptr) {
                w->id = workDao->increID();
                w->time = n->time;
                workDao->add(w);
                n->wid = w->id;
            } else {
                n->wid = w_->id;
            }
            noteDao->insert(n);
            delete w;
            delete w_;
            delete n;
        }
        QMetaObject::invokeMethod(engine->rootObjects().at(0), "hasNew", Q_ARG(QVariant, QVariant::fromValue(ty)));
    });
    //
    QJsonObject respd = ut::json::create("st", 0);
    std::string r = QJsonDocument(respd).toJson(QJsonDocument::Compact).toStdString();
    resp.set_content(r, RESP_TYPE_JSON);
}

void HServer::enableServer() {
    start();
}

void HServer::disableServer() {
    s->stop();
}

void HServer::close() {
    if(lg->isDebug()) {
        lg->debug(QString("http server close"));
    }
    running = false;
    if(s != nullptr) {
        s->stop();
        delete s;
    }
    if(lg->isDebug()) {
        lg->debug(QString("http server close done."));
    }
}

QString HServer::genQRcode() {
    QString ip = ut::sys::getLocalIP();
    QString qr = "XM|" + ip+":"+ QString::number(cfg->port) + "|" + ut::str::randomStr(6);
    setCurQRCode(qr);
    this->qrlst = ut::time::getCurMills();
    return qr;
}

void HServer::setPath(SSLServer* s) {
    s->Get("/", [=](const Request&, Response &res) {res.set_redirect("/hi");});
    s->Get("/hi", [this](const Request &req, Response &resp) {this->hi(req, resp);});
    s->Post("/lg", [this](const Request &req, Response &resp) {this->login(req, resp);});
    s->Post("/gd", [this](const Request &req, Response &resp) {this->getData(req, resp);});
    s->Post("/pd", [this](const Request &req, Response &resp) {this->putData(req, resp);});
}
void HServer::run() {
    QByteArray pub_ = (cfg->userBaseDir + "/public.crt").toLocal8Bit();
    QByteArray pri_ = (cfg->userBaseDir + "/private.key").toLocal8Bit();
    const char* pub = pub_.data();
    const char* pri = pri_.data();
    if(lg->isDebug()) {
        lg->debug(QString("init sslserver %1 %2").arg(pub).arg(pri));
    }
    s = new SSLServer(pub, pri);
    setPath(s);
    if(lg->isDebug()) {
        lg->debug(QString("start http server on port %1 is_running %2, is_valid %3")
                  .arg(cfg->port).arg(s->is_running()).arg(s->is_valid()));
    }
    s->listen("0.0.0.0", cfg->port);
}

void HServer::exec(int cmd, QMap<QString,QString> param) {
    if(lg->isDebug()) {
        lg->debug(QString("send cmd %1 param %2").arg(cmd).arg(ut::str::mapToStr(param)));
    }
    if(cmd == Cmd_EnableServer) {
        if(s == nullptr || s->is_valid() || !s->is_running()) {
            enableServer();
        }
    } else if(cmd == Cmd_DisableServer) {
        if(s != nullptr && s->is_running()) {
            disableServer();
        }
    } else if(cmd == Cmd_GenQRCode) {
        int cbid = param.value("cbid").toInt();
        QString qr = genQRcode();
        sendMsg(cbid, qr);
    } else if(cmd == Cmd_DeviceList) {
        int cbid = param.value("cbid").toInt();
        QVariantList l;
        for(std::tuple<QString, qint64> tp:devs) {
            QVariantMap m;
            m.insert("dev", get<0>(tp));
            m.insert("ct", get<1>(tp));
            l.append(m);
        }
        sendMsg(cbid, l);
    } else if(cmd == Cmd_DelDevice) {
        int cbid = param.value("cbid").toInt();
        QString dev = param.value("dev");
        int targetIndex = -1;
        for(int i = 0; i < devs.size(); i++) {
            std::tuple<QString, qint64> tp = devs.at(i);
            if(get<0>(tp) == dev) {
                targetIndex = i;
            }
        }
        if(targetIndex >= 0) {
            devs.removeAt(targetIndex);
            devTKMap.remove(dev);
        }
        if(lg->isDebug()) {
            lg->debug(QString("del device dev %1 targetIndex %2").arg(dev).arg(targetIndex));
        }
        sendMsg(cbid, 0);
    } else if(cmd == Cmd_SendToPhone) {
        int cbid = param.value("cbid").toInt();
        QString data = param.value("data");
        for(std::tuple<QString,qint64> tp :devs) {
            QString dev = get<0>(tp);
            pushServerData(dev, data);
        }
        sendMsg(cbid, 0);
    } else if(cmd == Cmd_GetCurQRCode) {
        int cbid = param.value("cbid").toInt();
        QString qrcode = getCurQRCode();
        sendMsg(cbid, qrcode);
    }
}

void HServer::loop() {
    HServerLoop::INS().start();
}

int HServer::sizeDev() {
    return devs.size();
}

QString HServer::getCurQRCode() {
    mtx.lock();
    QString qr = this->curQRcode;
    mtx.unlock();
    return qr;
}

void HServer::setCurQRCode(QString qr) {
    mtx.lock();
    this->curQRcode = qr;
    mtx.unlock();
}

void HServer::clearInvalidDevices() {
    qint64 cur = ut::time::getCurMills();
    for(QString k : devTKMap.keys()) {
        qint64 lst = lastGetDataTimeMap.value(k);
        if(lst > 0 && cur - lst >= 30000) {
            int i = 0;
            int targetI = -1;
            for(std::tuple<QString, qint64> tp: devs) {
                QString dev = get<0>(tp);
                if(dev == k) {
                    targetI = i;
                    break;
                }
                i++;
            }
            if(targetI >= 0) {
                devs.removeAt(targetI);
                devTKMap.remove(k);
            }
        }
    }
}
