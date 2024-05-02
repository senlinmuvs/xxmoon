// http.h

#ifndef HTTP_H
#define HTTP_H

#include "com/const.h"
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QTimer>

class Http : public QObject {
    Q_OBJECT

public:
    explicit Http(QObject *parent = nullptr);

    void upload(const QString &url, const QMap<QString, QString>& params, const QString &filePath, CB onUploaded, CB_INT64_2 onProgress = nullptr, CB_ERR onError = nullptr);
    void upload(const QString &url, const QMap<QString, QString>& params, const QStringList &filePaths, CB onUploaded, CB_INT64_2 onProgress = nullptr, CB_ERR onError = nullptr);
    void get(const QString &url, CB_JSON onSuccess, CB_ERR onError = nullptr);
    void post(const QString &url, const QMap<QString, QString>& params, CB_JSON onSuccess, CB_ERR onError = nullptr);

    int timeout = 30000;

private:
    QNetworkAccessManager *networkAccessManager;
    QTimer *timer;
    CB_INT64_2 onProgress;
    CB_JSON onSuccess;
    CB onUploaded;
    CB_ERR onError;
};

#endif // HTTP_H
