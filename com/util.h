#ifndef CLIPBOARDUTIL_H
#define CLIPBOARDUTIL_H

#include <QImage>
#include <QString>
#include <QFile>

namespace ut {

    namespace cpb {
        QString getText();
        void setText(QString txt);
        QImage getImage();
        void setImage(QImage img);
        void clear();
    }

    namespace file {
        QString readFile(QString path);
        QStringList allLines(QString file);
        QString desktop(QString file);
        QString writeData(QString file, QByteArray data, QFile::Permissions perms = (QFile::ReadUser|QFile::WriteUser|QFile::ReadGroup|QFile::ReadOther));
        void writeText(QString file, QString text, QFile::Permissions perms = (QFile::ReadUser|QFile::WriteUser|QFile::ReadGroup|QFile::ReadOther));
        bool exists(QString file);
        void rm(QString file);
        void rename(QString srcFile, QString dstFile);
        QByteArray toByteArray(QString file);
        void registerFileRelation(const QString& className,const QString& appPath,const QString& ext,const QString& extDes);
        QString postfix(QString f);
        int postfixType(QString f);
        QString typeToPostfix(int t);
        QList<uint> count(QString path);
    }
    QString ipv4IntegerToString(quint32 ip);
    quint32 ipv4StringToInteger(const QString& ip);

    namespace str {
        QString sub(QString s, int from, int len);
        QString sub(QString s, int from);
        QString removePrefix(QString s, QString k);
        QVariantList replaceTag(QString txt,int fromIndex,QString srcTag1,QString srcTag2,
                                QString dstTag1,QString dstTag2,int mode = 0,
                                QString param = "", QString notContains = "",
                                QVariantList (*cb)(const QString& srcTag1, const QString& srcTag2, const QString& dstTag1, const QString& dstTag2, QString& k, const QString& param) = nullptr);
        QString replaceAllTag(QString txt,QString srcTag1,QString srcTag2,QString dstTag1,QString dstTag2,int mode = 0,
                              QString param = "", QString notContains = "",
                              QVariantList (*cb)(const QString& srcTag1, const QString& srcTag2, const QString& dstTag1, const QString& dstTag2, QString k, const QString& param) = nullptr);
        QString mapToStr(QMap<QString, QString> map);
        QString mapToStr(QVariantMap map);
        QString listToStr(QStringList list);
        int findFrontLine(QString cont, uint n, uint from);
        QString frontLine(QString cont, uint n);
        QString fillTmpl(QString tmpl, QMap<QString, QString> m);
        std::tuple<QString, int, int> findByTag(QString src, QString tag1, QString tag2, int from = 0);
        QString randomStr(int n);
        QString& unescapedHtml(QString& s);
        QString removeFirstLine(const QString& s);
        QString removeEndLine(const QString& s);
        QString getEndLine(const QString& s);
        bool isChinese(QChar ch);
        QString substrUniformWidth(const QString &s, int from, int len);
    }

    namespace time {
        int getYear();
        QString getYearStr();
        QString getCurrentTimeStr(QString format = "yyyyMMddhhmmss.zzz");
        uint getCurSeconds();
        qint64 getCurMills();
        QString toString(qint64 mills, QString format = "yyyy/MM/dd hh:mm:ss");
    }

    namespace img {
        QByteArray toByteArray(QString path, QString format = "PNG");
        QString reduceImage(QString src, QString target, uint qua, uint w, uint h, uint maxW = 0);
    }

    namespace sys {
        QString mac();
        QString iOPlatformUUID();
        QString getHardwareInfo(const QString& cmd);
        QString getLocalIP();
    }

    namespace byte {
        void writeUInt(QByteArray* a, uint n);
        void writeBool(QByteArray* arr, bool n);
        QByteArray removeBom(QByteArray ba);
    }
    namespace cipher {
        QByteArray encryptAES(QString k , const QByteArray& data);
        QByteArray decryptAES(QString k , const QByteArray& data);
        QString encryptTextAES(QString k , const QString& text);
        QString decryptTextAES(QString k, const QString& text);
    }
    namespace col {
        QVariantMap createMap(QString k1, QVariant v1);
        QVariantMap createMap(QString k1, QVariant v1, QString k2, QVariant v2);
        QVariantMap createMap(QString k1, QVariant v1, QString k2, QVariant v2, QString k3, QVariant v3);
        QVariantMap createMap(QString k1, QVariant v1, QString k2, QVariant v2, QString k3, QVariant v3, QString k4, QVariant v4);
    }
    namespace json {
        int getInt(QJsonObject jo, QString k, int def);
        uint getUInt(QJsonObject jo, QString k, uint def);
        double getDouble(QJsonObject jo, QString k, int def);
        qint64 getQint64(QJsonObject jo, QString k, qint64 def);
        QString getString(QJsonObject jo, QString k, QString def);
        bool getBool(QJsonObject jo, QString k, int def);
        QList<int> getIntList(QJsonObject jo, QString k);
        QJsonObject create(QString k1, QVariant v1);
        QJsonObject create(QString k1, QVariant v1, QString k2, QVariant v2);
        QJsonObject create(QString k1, QVariant v1, QString k2, QVariant v2, QString k3, QVariant v3);
        QJsonObject create(QString k1, QVariant v1, QString k2, QVariant v2, QString k3, QVariant v3, QString k4, QVariant v4);
        QJsonDocument parseJsonDoc(const QByteArray& d);
        QJsonObject parseJson(const QByteArray& d);
        QJsonArray parseJsonArr(const QByteArray& d);
        QString toString(const QJsonObject& jo);
    }
}
#endif // CLIPBOARDUTIL_H
