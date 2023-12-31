#ifndef HSERVER_H
#define HSERVER_H
#include <QMap>
#include <QThread>
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "com/httplib.h"

using namespace httplib;

class HServer:public QThread {

public:
    HServer();

    const char* RESP_TYPE_JSON = "application/json";

protected:
    void run();
private:
    volatile bool enable;
    SSLServer *s = NULL;
    qint64 qrlst;
    QString curQRcode;
    QList<std::tuple<QString, qint64>> devs; //logined devices
    QMap<QString, QString> devTKMap;
    QMap<QString, qint64> lastGetDataTimeMap; //<dev, last get data time>
    std::mutex mtx;

private:
    void hi(const Request &req, Response &resp);
    void login(const Request &req, Response &resp);
    void getData(const Request &req, Response &resp);
    void putData(const Request &req, Response &resp);
    void enableServer();
    void disableServer();
    bool checkTK(const Request &req, Response &resp);

public:
    void close();
    QString genQRcode();
    void setPath(SSLServer* s);
    void setEnable(bool en);
    void loop();
    void exec(int cmd, QMap<QString,QString> param);
    int sizeDev();
    void clearInvalidDevices();
    void setCurQRCode(QString qr);
    QString getCurQRCode();

    static HServer& INS() {
        static HServer ins;
        return ins;
    }
};
#endif // HSERVER_H
