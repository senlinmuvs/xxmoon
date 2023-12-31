#ifndef CLIPBOARDUTIL_H
#define CLIPBOARDUTIL_H

#include <QImage>
#include <QString>
#include <QFile>

namespace ut {

    namespace cpb {
        extern QString getText();
        extern void setText(QString txt);
        extern QImage getImage();
        extern void setImage(QImage img);
        extern void clear();
    }

    namespace file {
        extern QString readFile(QString path);
        extern QStringList allLines(QString file);
        extern QString desktop(QString file);
        extern QString writeData(QString file, QByteArray data, QFile::Permissions perms = (QFile::ReadUser|QFile::WriteUser|QFile::ReadGroup|QFile::ReadOther));
        extern void writeText(QString file, QString text, QFile::Permissions perms = (QFile::ReadUser|QFile::WriteUser|QFile::ReadGroup|QFile::ReadOther));
        extern bool exists(QString file);
        extern void rm(QString file);
        extern void rename(QString srcFile, QString dstFile);
        extern QByteArray toByteArray(QString file);
        extern void registerFileRelation(const QString& className,const QString& appPath,const QString& ext,const QString& extDes);
        extern QString postfix(QString f);
        extern int postfixType(QString f);
        extern QString typeToPostfix(int t);
    }
    extern QString ipv4IntegerToString(quint32 ip);
    extern quint32 ipv4StringToInteger(const QString& ip);

    namespace str {
        extern QString sub(QString s, int from, int len);
        extern QString sub(QString s, int from);
        extern QString removePrefix(QString s, QString k);
        extern QVariantList replaceTag(QString txt,int fromIndex,QString srcTag1,QString srcTag2,
                                QString dstTag1,QString dstTag2,int mode = 0,
                                QString param = "", QString notContains = "",
                                QVariantList (*cb)(QString srcTag1, QString srcTag2, QString dstTag1, QString dstTag2, QString k, QString param) = nullptr);
        extern QString replaceAllTag(QString txt,QString srcTag1,QString srcTag2,QString dstTag1,QString dstTag2,int mode = 0,
                              QString param = "", QString notContains = "",
                              QVariantList (*cb)(QString srcTag1, QString srcTag2, QString dstTag1, QString dstTag2, QString k, QString param) = nullptr);
        extern QString mapToStr(QMap<QString, QString> map);
        extern QString mapToStr(QVariantMap map);
        extern QString listToStr(QStringList list);
        extern int findFrontLine(QString cont, uint n, uint from);
        extern QString frontLine(QString cont, uint n);
        extern QString fillTmpl(QString tmpl, QMap<QString, QString> m);
        extern std::tuple<QString, int, int> findByTag(QString src, QString tag1, QString tag2, int from = 0);
        extern QString randomStr(int n);
        extern char* strToChar(QString s);
        extern QString unescapedHtml(QString s);
        extern QString removeFirstLine(QString s);
        extern QString removeEndLine(QString s);
    }

    namespace time {
        extern int getYear();
        extern QString getYearStr();
        extern QString getCurrentTimeStr();
        extern uint getCurSeconds();
        extern qint64 getCurMills();
    }

    namespace img {
        extern QByteArray toByteArray(QString path, QString format = "PNG");
        extern QString reduceImage(QString src, QString target, uint qua, uint w, uint h, uint maxW = 0);
    }

    namespace sys {
        extern QString mac();
        extern QString iOPlatformUUID();
        extern QString getHardwareInfo(const QString& cmd);
        extern QString getLocalIP();
    }

    namespace byte {
        extern void writeUInt(QByteArray* a, uint n);
        extern void writeBool(QByteArray* arr, bool n);
        extern QByteArray removeBom(QByteArray ba);
    }
    namespace cipher {
        extern QByteArray encryptAES(QString k , const QByteArray& data);
        extern QByteArray decryptAES(QString k , const QByteArray& data);
        extern QString encryptTextAES(QString k , const QString& text);
        extern QString decryptTextAES(QString k, const QString& text);
    }
    namespace col {
        extern QVariantMap createMap(QString k1, QVariant v1);
        extern QVariantMap createMap(QString k1, QVariant v1, QString k2, QVariant v2);
        extern QVariantMap createMap(QString k1, QVariant v1, QString k2, QVariant v2, QString k3, QVariant v3);
        extern QVariantMap createMap(QString k1, QVariant v1, QString k2, QVariant v2, QString k3, QVariant v3, QString k4, QVariant v4);
    }
    namespace json {
        extern int getInt(QJsonObject jo, QString k, int def);
        extern uint getUInt(QJsonObject jo, QString k, uint def);
        extern double getDouble(QJsonObject jo, QString k, int def);
        extern qint64 getQint64(QJsonObject jo, QString k, qint64 def);
        extern QString getString(QJsonObject jo, QString k, QString def);
        extern bool getBool(QJsonObject jo, QString k, int def);
        extern QList<int> getIntList(QJsonObject jo, QString k);
        extern QJsonObject create(QString k1, QVariant v1);
        extern QJsonObject create(QString k1, QVariant v1, QString k2, QVariant v2);
        extern QJsonObject create(QString k1, QVariant v1, QString k2, QVariant v2, QString k3, QVariant v3);
        extern QJsonObject create(QString k1, QVariant v1, QString k2, QVariant v2, QString k3, QVariant v3, QString k4, QVariant v4);
    }
}
#endif // CLIPBOARDUTIL_H
