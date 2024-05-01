#include "qaesencryption.h"
#include "util.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QBuffer>
#include <QClipboard>
#include <QDateTime>
#include <QGuiApplication>
#include <QStandardPaths>
#include <QThread>
#include <QDebug>
#include <QNetworkInterface>
#include <QProcess>
#include <QSettings>
#include <QCryptographicHash>
#include <QImageWriter>

using namespace std;

namespace ut {

    namespace cpb {
        ///clipboard
        QString getText() {
            QClipboard *board = QGuiApplication::clipboard();
            QString str = board->text();
            return str.trimmed();
        }

        void setText(QString txt) {
            QClipboard *board = QGuiApplication::clipboard();
            board->setText(txt);
        }

        QImage getImage() {
            QClipboard *board = QGuiApplication::clipboard();
            QImage img = board->image();
            return img;
        }

        void setImage(QImage img) {
            QClipboard *board = QGuiApplication::clipboard();
            board->setImage(img);
        }

        void clear() {
            QClipboard *board = QGuiApplication::clipboard();
            board->clear();
        }
    }

    ///file
    namespace file {
        QString readFile(QString path) {
            QFile file(path);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                in.setEncoding(QStringConverter::Utf8);
                auto cont = in.readAll();
                file.close();
                return QString(cont);
            }
            return "";
        }
        QStringList allLines(QString file) {
            QString cont = readFile(file);
            QStringList arr;
            if(cont.length() > 0) {
                arr = cont.split("\n");
            }
            return arr;
        }
        QString desktop(QString file) {
            return QString("%1/"+file).arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
        }
        QString writeData(QString file, QByteArray data, QFile::Permissions perms) {
            QFile f(file);
            bool b = f.open(QIODevice::WriteOnly);
            QString err;
            if(b) {
                f.write(data);
                f.setPermissions(perms);
                f.close();
            } else {
                err = f.errorString();
            }
            return err;
        }
        void writeText(QString file, QString text, QFile::Permissions perms) {
            QString err = writeData(file, text.toUtf8(), perms);
            if(!err.isEmpty()) {
                qDebug() << "writeText" << file << perms << err;
            }
        }
        bool exists(QString file) {
            QFile f(file);
            return f.exists();
        }
        void rm(QString file) {
            QFile f(file);
            f.remove();
        }
        void rename(QString srcFile, QString dstFile) {
            QFile f(srcFile);
            f.rename(dstFile);
        }
        QByteArray toByteArray(QString file) {
            QFile f(file);
            QByteArray data;
            if(f.open(QIODevice::ReadOnly)){
                data = f.readAll();
                f.close();
            }
            return data;
        }
        /*******************************************************************
        * 注册文件关联
        * className    // 自定义的类别
        * appPath      // 关联的程序目录
        * ext          // 关联的文件类型
        * extDes       // 该文件类型描述
        *******************************************************************/
        void registerFileRelation(const QString& className,const QString& appPath,const QString& ext,const QString& extDes) {
#ifdef Q_OS_WIN
            //要添加的顶层目录
            QString baseUrl("HKEY_CURRENT_USER\\Software\\Classes");
            QSettings settingClasses(baseUrl,QSettings::NativeFormat);
            //在...Classes\类别下创建一个新的类别，并设置该类别打开文件时的调用参数
            settingClasses.setValue("/" + className + "/Shell/Open/Command/.","\"" + appPath + "\" \"%1\"");
            //文件类型描述
            settingClasses.setValue("/" + className + "/.",extDes);
            //设置该类别的默认图标默认图标
            settingClasses.setValue("/" + className + "/DefaultIcon/.",appPath + ",0");
            //关联ext和类别
            settingClasses.setValue("/" + ext + "/OpenWithProgIds/" + className,"");
            //立即保存该修改
            settingClasses.sync();
#endif
        }
        QString postfix(QString f) {
            return f.mid(f.lastIndexOf("."));
        }
        int postfixType(QString f) {
            QString hz = postfix(f);
            if(hz == ".png") {
                return 0;
            } else if(hz == ".jpg") {
                return 1;
            } else if(hz == ".jpeg") {
                return 2;
            } else if(hz == ".bmp") {
                return 3;
            } else if(hz == ".gif") {
                return 4;
            } else if(hz == ".webp") {
                return 5;
            } else if(hz == ".mp4") {
                return 6;
            } else {
                return -1;
            }
        }
        QString typeToPostfix(int t) {
            if(t == 0) {
                return ".png";
            } else if(t == 1) {
                return ".jpg";
            } else if(t == 2) {
                return ".jpeg";
            } else if(t == 3) {
                return ".bmp";
            } else if(t == 4) {
                return ".gif";
            } else if(t == 5) {
                return ".webp";
            } else if(t == 6) {
                return ".mp4";
            } else {
                return ".png";
            }
        }
    }

    ///string
    namespace str {
        QString removePrefix(QString s, QString k) {
            if(s.startsWith(k)) {
                s = s.mid(k.length());
            }
            return s;
        }
        QVariantList replaceTag(QString txt,int fromIndex,QString srcTag1,QString srcTag2,
                                QString dstTag1,QString dstTag2,int mode, QString param, QString notContains,
                                QVariantList (*cb)(QString srcTag1, QString srcTag2, QString dstTag1, QString dstTag2, QString k,QString param)) {
            QString s = "";
            bool pendingSrcTag1 = false;
            int srcTag1Index = -1;
            int srcTag2Index = -1;
            for(int i = fromIndex; i < txt.length(); i++) {
                s += txt[i];
                if(srcTag2Index > 0) {
                  break;
                }
                if(srcTag1Index > 0) {
                      if(s.endsWith(srcTag2)) {
                          //当完全匹配到srcTag2时，如果前面没有字符了或者前面不是转义字符时才确定匹配
                          int x = i - srcTag2.length();
                          if(x < 0 || txt[x] != '`') {
                              srcTag2Index = i+1;
                          }
                      }
                } else {
                  if(pendingSrcTag1) {
                      if(s.endsWith(srcTag1)) {
                          s = "";
                      } else {
                          if(i-s.length()-1>=0) {
                              int x = i-srcTag1.length()-1;
                              int y = i-srcTag1.length();
                              if(txt[x] != txt[y]) {
                                  srcTag1Index = i;
                              } else {
                                  pendingSrcTag1 = false;
                              }
                          } else {
                              srcTag1Index = i;
                          }
                          s = "";
                      }
                  } else {
                      if(srcTag1.startsWith(s)) {
                          if(srcTag1 == s) {
                              if(mode == 0){
                                //当完全匹配到srcTag1时，如果前面没有字符或者是\n或>时才进一步确定srcTag1是要找的
                                int x = i - srcTag1.length();
                                // log(i, x, txt[x]);
                                if(x < 0 || txt[x] == '\n' || txt[x] == '>') {
                                    if(txt[x] != '`') {
                                        pendingSrcTag1 = true;
                                    }
//                                    qDebug() << ">>>>>>>>>>>" << x << txt[x];
                                }
                              } else {
                                //当完全匹配到srcTag1时，如果前面字符不是转义字符时才进一步确定srcTag1是要找的
                                int x = i - srcTag1.length();
                                if(x < 0 || txt[x] != '`') {
                                    pendingSrcTag1 = true;
                                }
                              }
                          }
                      } else {
                          s = "";
                      }
                  }
                }
             }
//            qDebug() << srcTag1Index << srcTag2Index;
            if(srcTag1Index < 0 || srcTag2Index < 0) {
                return {txt, -1};
            }
            QString k = txt.mid(srcTag1Index, srcTag2Index-srcTag2.length()-srcTag1Index);
            if(notContains != "" && k.contains(notContains)) {
                return {txt, -1};
            }
            if(cb != nullptr) {
                QVariantList arr = cb(srcTag1, srcTag2, dstTag1, dstTag2, k, param);
                if(arr.length() > 0) {
                   QString newK = arr[0].toString();
                   if(k != newK) {
                      txt = txt.replace(txt.indexOf(k), k.size(), newK);
                      int off = newK.length() - k.length();
                      srcTag2Index += off;
                   }
                   for(int i = 0; i < arr.length(); i++) {
                      QString param = arr[i].toString();
                      QString paramTemplate = QString("{%1}").arg(i);
                      dstTag1 = dstTag1.replace(paramTemplate, param);
                      dstTag2 = dstTag2.replace(paramTemplate, param);
//                      qDebug() << param << paramTemplate << dstTag1 << dstTag2;
                   }
                }
            }
            txt = txt.insert(srcTag1Index, dstTag1);
            txt = txt.insert(srcTag2Index+dstTag1.length(), dstTag2);
            txt = txt.remove(srcTag1Index-srcTag1.length(), srcTag1.length());
            int x = srcTag2Index+dstTag1.length()-srcTag1.length()-srcTag2.length();
            txt = txt.remove(x, srcTag2.length());
            int endIndex = x + dstTag2.length();
            // log(oldTxt.substring(fromIndex), txt, endIndex);
            return {txt, endIndex};
        }
        QString replaceAllTag(QString txt,QString srcTag1,QString srcTag2,QString dstTag1,QString dstTag2,int mode, QString param, QString notContains,
                              QVariantList (*cb)(QString srcTag1, QString srcTag2, QString dstTag1, QString dstTag2, QString k, QString param)) {
            int from = 0;
            while(true) {
                if(from < 0 || from >= txt.length()-1) {
                    break;
                }
                QVariantList m = replaceTag(txt,from, srcTag1,srcTag2,dstTag1,dstTag2,mode,param,notContains,cb);
                txt = m[0].toString();
                from = m[1].toInt();
            }
            return txt;
        }
        QString mapToStr(QMap<QString, QString> map) {
            QString s;
            QMapIterator<QString, QString> it(map);
            while (it.hasNext()) {
                it.next();
                s += it.key() + " = " + it.value() + ", ";
            }
            if(s.length() > 0) {
                s = s.mid(0, s.length()-2);
            }
            s = "["+s+"]";
            return s;
        }
        QString mapToStr(QVariantMap map) {
            QString s;
            QMapIterator<QString, QVariant> it(map);
            while (it.hasNext()) {
                it.next();
                QVariant var = it.value();
                QString v = "";
                if(v.isNull()) {
                    v = "null";
                } else {
                    if(var.type() == QVariant::Type::String) {
                        v = "\""+var.toString()+"\"";
                    } else {
                        v = var.toString();
                    }
                }
                s += it.key() + "=" + v + ", ";
            }
            if(s.length() > 0) {
                s = s.mid(0, s.length()-2);
            }
            s = "["+s+"]";
            return s;
        }
        //找到cont的from位置开始的前n行
        int findFrontLine(QString cont, uint n, uint from) {
            uint line = 0;
            int j = from;
            for(; j >= 0; j--) {
                if(cont.at(j) == '\n') {
                    line++;
                    if(line >= n) {
                        break;
                    }
                }
            }
            return j;
        }
        //取cont的前n行
        QString frontLine(QString cont, uint n) {
            uint line = 0;
            for(int i = 0; i < cont.length(); i++){
                if(cont.at(i) == '\n') {
                    line++;
                    if(line >= n) {
                        return cont.mid(0, i);
                    }
                }
            }
            return cont;
        }
        QString listToStr(QStringList list) {
            QString s = "";
            for(int i = 0; i < list.size(); i++) {
                s += list.at(i) + ",";
            }
            if(!s.isEmpty()) {
                s = "[" + s.mid(0, s.length()-1) + "]";
            }
            return s;
        }
        QString fillTmpl(QString tmpl, QMap<QString, QString> m) {
            for(QString e:m.keys()) {
                QString v = m.value(e);
                QString x = "${"+e+"}";
                int fromI = 0;
                while(fromI >= 0 && fromI < tmpl.length()) {
                    int ind = tmpl.indexOf(x, fromI);
                    if(ind >= 0) {
                        tmpl = tmpl.replace(ind, x.length(), v);
                    }
                    fromI = ind;
                }
            }
            return tmpl;
        }
        std::tuple<QString, int, int> findByTag(QString src, QString tag1, QString tag2, int from) {
            int i0 = src.indexOf(tag1, from);
            int i1 = src.indexOf(tag2, i0);
            if(i0 >= 0 && i1 >= 0) {
                return make_tuple(src.mid(i0+tag1.length(), i1-i0-tag1.length()), i0, i1);
            }
            return make_tuple("", -1, -1);
        }

        QString randomStr(int n) {
            srand(QDateTime::currentMSecsSinceEpoch());
            const char ch[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
            int size = sizeof(ch);
            char* str = new char[n + 1];
            int num = 0;
            for (int i = 0; i < n; ++i) {
                num = rand() % (size - 1);
                str[i] = ch[num];
            }
            str[n] = '\0';
            return QString(str);
        }
        QString unescapedHtml(QString s) {
            return s.replace("&nbsp;"," ")
                    .replace("&quot;", "\"")
                    .replace("&lt;", "<")
                    .replace("&amp;", "&")
                    .replace("&gt;", ">");
        }
        QString removeFirstLine(QString s) {
            int i = s.indexOf("\n");
            if(i >= 0) {
                return s.mid(i+1);
            }
            return s;
        }
        QString removeEndLine(QString s) {
            int endIndex = -1;
            uint c = 0;
            uint n = s.endsWith("\n") ? 2 : 1;
            for(uint i = s.length()-1; i >= 0; i--) {
                if(s.at(i) == '\n') {
                    c++;
                }
                if(c == n) {
                    endIndex = i;
                    break;
                }
            }
            if(endIndex >= 0) {
                return s.mid(0, endIndex);
            }
            return s;
        }
    }

    ///ip
    QString ipv4IntegerToString(quint32 ip) {
        return QString("%1.%2.%3.%4")
                .arg((ip >> 24) & 0xFF)
                .arg((ip >> 16) & 0xFF)
                .arg((ip >> 8) & 0xFF)
                .arg(ip & 0xFF);
    }

    quint32 ipv4StringToInteger(const QString& ip) {
        QStringList ips = ip.split(".");
        if(ips.size() == 4){
            return ips.at(3).toUInt()
                    | ips.at(2).toUInt() << 8
                    | ips.at(1).toUInt() << 16
                    | ips.at(0).toUInt() << 24;
        }
        return 0;
    }

    ///time
    namespace time {
        int getYear() {
            return QDate::currentDate().year();
        }
        QString getYearStr() {
            return QString::number(getYear());
        }
        QString getCurrentTimeStr() {
            QDateTime dt = QDateTime::currentDateTime();
            return dt.toString("yyyyMMddhhmmss.zzz");
        }
        uint getCurSeconds() {
            return QDateTime::currentDateTime().toSecsSinceEpoch();
        }
        qint64 getCurMills() {
            return QDateTime::currentDateTime().toMSecsSinceEpoch();
        }
    }

    namespace img {
        QByteArray toByteArray(QString file, QString format) {
            QImage image(file);
            QByteArray ba;
            QBuffer buffer(&ba);
            buffer.open(QIODevice::WriteOnly);
            image.save(&buffer, format.toStdString().c_str());
            return ba;
        }
        QString reduceImage(QString src, QString target, uint qua, uint w, uint h, uint maxW) {
            QImage image(src);
            uint w_ = image.width();
            uint h_ = image.height();
            if(maxW > 0) {
                w = std::min(maxW, w_);
                h = w;
            }
            if(w>0 && h>0 && w_ > w && h_ > h) {
                image = image.scaled(w, h, Qt::KeepAspectRatio);
            }
            QImageWriter writer(target, "jpeg");
//            if (writer.supportsOption(QImageIOHandler::Description)) {
//                writer.setText("Author", "Mr Wang");
//                writer.setText("Description", "Qter");
//            }
            writer.setQuality(qua);
            if (writer.canWrite() && writer.write(image)) {
                return "";
            }
//            QImageWriter::ImageWriterError error = writer.error();
            QString strError = writer.errorString();
            return strError;
        }
    }

    namespace sys {
        QString mac() {
            QString strMac;
            QList<QNetworkInterface> netList = QNetworkInterface::allInterfaces();
            foreach(QNetworkInterface item, netList) {
                if((QNetworkInterface::IsUp & item.flags()) && (QNetworkInterface::IsRunning & item.flags())) {
                    if(strMac.isEmpty() || strMac < item.hardwareAddress()) {
                        strMac = item.hardwareAddress();
                    }
                }
            }
            return strMac;
        }
        /**
         * 获取cpu名称：wmic cpu get Name
         * 获取cpu核心数：wmic cpu get NumberOfCores
         * 获取cpu线程数：wmic cpu get NumberOfLogicalProcessors
         * 查询cpu序列号：wmic cpu get processorid
         * 查询主板序列号：wmic baseboard get serialnumber
         * 查询BIOS序列号：wmic bios get serialnumber
         * 查看硬盘：wmic diskdrive get serialnumber
         * @brief getHardwareInfo
         * @param cmd
         * @return
         */
        QString getHardwareInfo(const QString& cmd) {
            QProcess p;
            p.start(cmd);
            p.waitForFinished();
            QString result = QString::fromLocal8Bit(p.readAllStandardOutput());
            QStringList list = cmd.split(" ");
            result = result.remove(list.last(), Qt::CaseInsensitive);
            result = result.replace("\r", "");
            result = result.replace("\n", "");
            result = result.simplified();
            return result;
        }
        QString iOPlatformUUID() {
            QString result = "";
#ifdef Q_OS_MAC
            QProcess proc;
            QStringList args;
            args << "-c" << "ioreg -rd1 -c IOPlatformExpertDevice | awk -F\\\" '/IOPlatformUUID/ { print $(NF-1); }'";
            proc.start( "/bin/bash", args);
            proc.waitForFinished();
            QString uID = proc.readAll();
            result = uID.mid(0, uID.length()-1);
#endif
#ifdef Q_OS_WIN
            result = getHardwareInfo("wmic baseboard get serialnumber");
#endif
            return result;
        }
        QString getLocalIP() {
            const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
            for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
                if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost) {
                     return address.toString();
                }
            }
            return "";
        }
    }

    namespace byte {
        void writeUInt(QByteArray* arr, uint n) {
            char a = (n >> 24) & 0XFF;
            char b = (n >> 16) & 0XFF;
            char c = (n >> 8) & 0XFF;
            char d = n & 0XFF;
            arr->append(a);
            arr->append(b);
            arr->append(c);
            arr->append(d);
        }
        void writeBool(QByteArray* arr, bool n) {
            char a = n ? 1 : 0;
            arr->append(a);
        }
        QByteArray removeBom(QByteArray ba) {
            QByteArray newBa;
            for(int i = 0; i < ba.size();) {
                if(ba.at(i) == (char)0xEF &&
                        ba.at(i+1) == (char)0xBB &&
                        ba.at(i+2) == (char)0xBF) {
                    i += 3;
                } else {
                    newBa.append(ba.at(i));
                    i++;
                }
            }
            return newBa;
        }
    }

    namespace cipher {
        QByteArray encryptAES(QString k, const QByteArray& data) {
            if(data.length() <= 0){
                return data;
            }
            QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
            QString iv = k;
            QByteArray hashKey = QCryptographicHash::hash(k.toLocal8Bit(), QCryptographicHash::Sha256);
            QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);
            QByteArray encodeText = encryption.encode(data, hashKey, hashIV);
            return encodeText;
        }
        QByteArray decryptAES(QString k, const QByteArray& data) {
            if(data.length() <= 0){
                return data;
            }
            QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
            QString iv = k;
            QByteArray hashKey = QCryptographicHash::hash(k.toLocal8Bit(), QCryptographicHash::Sha256);
            QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);
            QByteArray decodeText = encryption.decode(data, hashKey, hashIV);
            return encryption.removePadding(decodeText);
        }
        QString encryptTextAES(QString k , const QString& text) {
            QByteArray ba;
            ba.append(text.toUtf8());
            return encryptAES(k, ba).toBase64();
        }
        QString decryptTextAES(QString k, const QString& text) {
            QByteArray ba;
            ba.append(text.toUtf8());
            return QString(decryptAES(k, QByteArray::fromBase64(ba)));
        }
    }
    namespace col {
        QVariantMap createMap(QString k1, QVariant v1) {
            QVariantMap m;
            m.insert(k1, v1);
            return m;
        }
        QVariantMap createMap(QString k1, QVariant v1, QString k2, QVariant v2) {
            QVariantMap m;
            m.insert(k1, v1);
            m.insert(k2, v2);
            return m;
        }
        QVariantMap createMap(QString k1, QVariant v1, QString k2, QVariant v2, QString k3, QVariant v3) {
            QVariantMap m;
            m.insert(k1, v1);
            m.insert(k2, v2);
            m.insert(k3, v3);
            return m;
        }
        QVariantMap createMap(QString k1, QVariant v1, QString k2, QVariant v2, QString k3, QVariant v3, QString k4, QVariant v4) {
            QVariantMap m;
            m.insert(k1, v1);
            m.insert(k2, v2);
            m.insert(k3, v3);
            m.insert(k4, v4);
            return m;
        }
    }
    namespace json {
        bool getBool(QJsonObject jo, QString k, int def) {
            QJsonValue jv = jo.value(k);
            if(jv.isNull()) {
                return def;
            }
            return jv.toBool(def);
        }
        int getInt(QJsonObject jo, QString k, int def) {
            QJsonValue jv = jo.value(k);
            if(jv.isNull()) {
                return def;
            }
            bool ok;
            int v = jv.toVariant().toInt(&ok);
            if(ok) {
                return v;
            } else {
                return def;
            }
        }
        uint getUInt(QJsonObject jo, QString k, uint def) {
            QJsonValue jv = jo.value(k);
            if(jv.isNull()) {
                return def;
            }
            bool ok;
            uint v = jv.toVariant().toUInt(&ok);
            if(ok) {
                return v;
            } else {
                return def;
            }
        }
        double getDouble(QJsonObject jo, QString k, int def) {
            QJsonValue jv = jo.value(k);
            if(jv.isNull()) {
                return def;
            }
            bool ok;
            double v = jv.toVariant().toDouble(&ok);
            if(ok) {
                return v;
            } else {
                return def;
            }
        }
        qint64 getQint64(QJsonObject jo, QString k, qint64 def) {
            QJsonValue jv = jo.value(k);
            if(jv.isNull()) {
                return def;
            }
            bool ok;
            qint64 v = jv.toVariant().toLongLong(&ok);
            if(ok) {
                return v;
            } else {
                return def;
            }
        }
        QString getString(QJsonObject jo, QString k, QString def) {
            QJsonValue jv = jo.value(k);
            if(jv.isNull()) {
                return def;
            }
            return jv.toVariant().toString();
        }
        QList<int> getIntList(QJsonObject jo, QString k) {
            QList<int> list;
            QJsonValue jv = jo.value(k);
            if(jv.isNull()) {
                return list;
            }
            QJsonArray ja = jv.toArray();
            for(const QJsonValue& ajv : ja) {
                list.append(ajv.toInt());
            }
            return list;
        }
        QJsonObject create(QString k1, QVariant v1) {
            return QJsonObject::fromVariantMap(col::createMap(k1, v1));
        }
        QJsonObject create(QString k1, QVariant v1, QString k2, QVariant v2) {
            return QJsonObject::fromVariantMap(col::createMap(k1, v1, k2, v2));
        }
        QJsonObject create(QString k1, QVariant v1, QString k2, QVariant v2, QString k3, QVariant v3) {
            return QJsonObject::fromVariantMap(col::createMap(k1, v1, k2, v2, k3, v3));
        }
        QJsonObject create(QString k1, QVariant v1, QString k2, QVariant v2, QString k3, QVariant v3, QString k4, QVariant v4) {
            return QJsonObject::fromVariantMap(col::createMap(k1, v1, k2, v2, k3, v3, k4, v4));
        }
        QJsonDocument parseJsonDoc(const QByteArray& d) {
            QJsonParseError jsonError;
            QJsonDocument document = QJsonDocument::fromJson(d, &jsonError);
            if(document.isNull() || (jsonError.error != QJsonParseError::NoError)) {
                qDebug() << QString("parseJsonDoc error document.isNull() %1 json error %2")
                                    .arg(document.isNull()).arg(jsonError.error);
            }
            return document;
        }
        QJsonObject parseJson(const QByteArray& d) {
            QJsonDocument doc = parseJsonDoc(d);
            if(!doc.isNull() && doc.isObject()) {
                return doc.object();
            }
            return QJsonObject();
        }
        QJsonArray parseJsonArr(const QByteArray& d) {
            QJsonDocument doc = parseJsonDoc(d);
            if(!doc.isNull() && doc.isArray()) {
                return doc.array();
            }
            return QJsonArray();
        }
        QString toString(const QJsonObject& jo) {
            QJsonDocument jsonDocument(jo);
            return jsonDocument.toJson(QJsonDocument::Compact);
        }
    }
}
