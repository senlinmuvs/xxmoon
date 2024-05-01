#include "http.h"
#include "com/util.h"

#include <QFile>
#include <QFileInfo>
#include <QHttpPart>
#include <QUrlQuery>

Http::Http(QObject *parent) :QObject(parent), networkAccessManager(new QNetworkAccessManager(this)) {
}

void Http::upload(const QString &url, const QMap<QString, QString>& params, const QString &filePath, CB onUploaded, CB_INT64_2 onProgress, CB_ERR onError) {
    this->upload(url, params, QStringList() << filePath, onUploaded, onProgress, onError);
}
void Http::upload(const QString &url, const QMap<QString, QString>& params, const QStringList &filePaths, CB onUploaded, CB_INT64_2 onProgress, CB_ERR onError) {
    this->onUploaded = onUploaded;
    this->onProgress = onProgress;
    this->onError = onError;

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType, this);
    QMapIterator<QString, QString> i(params);
    while (i.hasNext()) {
        i.next();
        QHttpPart textPart;
        textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"" + i.key() + "\""));
        textPart.setBody(i.value().toUtf8());
        multiPart->append(textPart);
    }

    for(const QString &filePath : filePaths) {
        QFile *file = new QFile(filePath, multiPart);
        if (!file->open(QIODevice::ReadOnly)) {
            qDebug() << "Unable to open the file:" << filePath;
            continue;
        }
        QHttpPart filePart;
        filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/octet-stream"));
        filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"files\"; filename=\"" + QFileInfo(filePath).fileName() + "\""));
        filePart.setBodyDevice(file);
        file->setParent(multiPart);
        multiPart->append(filePart);
    }

    QNetworkReply *reply = networkAccessManager->post(QNetworkRequest(url), multiPart);
    multiPart->setParent(reply);

    connect(reply, &QNetworkReply::sslErrors, this, [reply](const QList<QSslError> &errors) {
        for (const QSslError &error : errors) {
            // qDebug() << "ssl err" << error.error();
            if (error.error() == QSslError::SelfSignedCertificate || error.error() == QSslError::HostNameMismatch) {
                reply->ignoreSslErrors();
            }
        }
    });
    connect(reply, &QNetworkReply::errorOccurred, this, [this, reply](QNetworkReply::NetworkError err) {
        if(this->onError) {
            this->onError(err);
        }
        reply->deleteLater();
    });
    connect(reply, &QNetworkReply::uploadProgress, this, [this](qint64 sent, qint64 total){
        if(this->onProgress) {
            this->onProgress(sent, total);
        }
    });
    connect(reply, &QNetworkReply::finished, this, [this, reply]{
        if(this->onUploaded) {
            this->onUploaded();
        }
        reply->deleteLater();
    });
}

void Http::get(const QString &url, CB_JSON onSuccess, CB_ERR onError) {
    this->onSuccess = onSuccess;
    this->onError = onError;
    QNetworkReply *reply = networkAccessManager->get(QNetworkRequest(url));

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray resp = reply->readAll();
            QJsonObject jo = ut::json::parseJson(resp);
            if(this->onSuccess) {
                this->onSuccess(jo);
            }
        } else {
            if(this->onError) {
                this->onError(reply->error());
            }
        }
        reply->deleteLater();
    });
}

void Http::post(const QString &url, const QMap<QString, QString>& params, CB_JSON onSuccess, CB_ERR onError) {
    this->onSuccess = onSuccess;
    this->onError = onError;
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QUrlQuery urlQuery;
    QMap<QString, QString>::const_iterator it;
    for (it = params.constBegin(); it != params.constEnd(); ++it) {
        const QString& key = it.key();
        const QString& value = it.value();
        QByteArray encodedValue = QUrl::toPercentEncoding(value);
        QString encodedString = QString::fromUtf8(encodedValue);
        urlQuery.addQueryItem(key, encodedString);
    }
    QByteArray postData = urlQuery.query(QUrl::FullyEncoded).toUtf8();
    QNetworkReply *reply = networkAccessManager->post(request, postData);
    connect(reply, &QNetworkReply::sslErrors, this, [reply](const QList<QSslError> &errors) {
        for (const QSslError &error : errors) {
            // qDebug() << "ssl err" << error.error();
            if (error.error() == QSslError::SelfSignedCertificate || error.error() == QSslError::HostNameMismatch) {
                reply->ignoreSslErrors();
            }
        }
    });
    connect(reply, &QNetworkReply::errorOccurred, this, [this, reply](QNetworkReply::NetworkError err){
        if(this->onError) {
            this->onError(err);
        }
        reply->deleteLater();
    });
    connect(reply, &QNetworkReply::finished, this, [this, reply](){
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray resp = reply->readAll();
            QJsonObject jo = ut::json::parseJson(resp);
            if(this->onSuccess) {
                this->onSuccess(jo);
            }
        } else {
            if(this->onError) {
                this->onError(reply->error());
            }
        }
        reply->deleteLater();
    });
}
