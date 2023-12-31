#include "xm.h"
#include "com/util.h"
#include "com/global.h"

#include <QUuid>

XM::XM() {

}

//==============header==============
//int 32 bytes uuid
//int 4 byte 加密
//int 4 bytes 图片数
//int 4 bytes 主图长度
//int 4 bytes 第1张图片长度
//int 4 bytes 第2张图片长度
//int 4 bytes 第n张图片长度
//=============imgs=================
//1byte格式+主图数据
//1byte格式+第1张图片数据
//1byte格式+第2张图片数据
//1byte格式+第n张图片数据
//=============cont=================
//剩下为内容
QString XM::createXMFile(QString name, QString mainImg, QString& cont, QString pwd) {
    qint64 t1 = QDateTime::currentDateTime().currentMSecsSinceEpoch();
    //
    bool encrypt = pwd.length() > 0;
    //
    QFileInfo mainImgFile(cfg->imgDir + "/" + mainImg);
    qint64 mainImgLen = 0;
    if(mainImgFile.isFile()) {
       mainImgLen = mainImgFile.size();
    }
    //
    QString file = cfg->fileDir + "/" + name + "_" + ut::time::getCurrentTimeStr() + ".xm";

    QStringList refs;
    if(mainImgLen > 0) {
        refs.append(mainImg);
    }
    QStringList imgs = extractImgsAsList(cont);
    if(!imgs.isEmpty()) {
        refs.append(imgs);
    }
    if(lg->isDebug()) {
        lg->trace(QString("extract refs %1 %2 imgs %3 %4")
                   .arg(refs.length()).arg(ut::str::listToStr(refs))
                   .arg(imgs.length()).arg(ut::str::listToStr(imgs)));
    }
    int dupn = refs.removeDuplicates();
    if(lg->isDebug()) {
        lg->debug(QString("createXMFile %1 cont %2 %3 mainImg %4 refs %5 remove dups %6")
                   .arg(file).arg(cont.length())
                   .arg(cont.mid(0, 30))
                   .arg(mainImgFile.filePath())
                   .arg(refs.length())
                   .arg(dupn));
    }
    uint imgCount = refs.length();
    //=============header=============
    QByteArray *data = new QByteArray();
    //uuid
    QString uuid = QUuid::createUuid().toString(QUuid::Id128);
    data->append(uuid.toUtf8());
    //是否加密
    ut::byte::writeUInt(data, encrypt);
    //图片数
    ut::byte::writeUInt(data, imgCount);
    if(lg->isDebug()) {
        lg->debug(QString("createXMFile imgCount %1").arg(imgCount));
    }
    //所有图片长度
    int x = 0;
    if(mainImgLen == 0) {
        ut::byte::writeUInt(data, 0);
        x = 1;
        if(lg->isDebug()) {
            lg->debug(QString("createXMFile img%1 len %2").arg(0).arg(0));
        }
    }
    for(int i = 0; i < refs.size(); i++) {
        QString img = refs.at(i);
        QFileInfo f(cfg->imgDir + "/" + img);
        ut::byte::writeUInt(data, f.size());
        if(lg->isDebug()){
            lg->debug(QString("createXMFile img%1 len %2 %3").arg(i+x).arg(f.size()).arg(img));
        }
    }
    //=============imgs==============
    //所有图片数据
    QMap<uint, std::tuple<QString,QString>> imgWHMap;
    for(int i = 0; i < refs.size(); i++) {
        QString img = refs.at(i);
        int ty = ut::file::postfixType(img);
        data->append((char)ty);
        QByteArray ba = ut::file::toByteArray(cfg->imgDir + "/" + img);
        data->append(ba);

        std::tuple<uint,uint> tp = getWHFromFileName(img);
        QString wh_ = QString("%1.%2").arg(get<0>(tp)).arg(get<1>(tp));
        QString postfix = ut::file::postfix(img);;
        imgWHMap.insert(i, {wh_, postfix});
    }
    //=============cont==============
    //内容
    //替换内容里的引用链接
    for(int i = 0; i < refs.size(); i++) {
        QString ref = refs.at(i);
        std::tuple<QString,QString> tp = imgWHMap.value(i);
        QString wh = get<0>(tp);
        QString postfix = get<1>(tp);
        cont.replace(ref, QString("tmp/%1/%2.%3%4").arg(uuid).arg(i).arg(wh).arg(postfix));
    }
    data->append(cont.toUtf8());
    if(lg->isDebug()) {
        lg->debug(QString("createXMFile cont len %1").arg(cont.length()));
    }
    /////////////////////////////////
    QByteArray compressed = qCompress(*data, 9);
//    QByteArray compressed = *data;

    QString err = ut::file::writeData(file, compressed);
    if(err.length() > 0) {
        lg->error(QString("writeData error %1 %2").arg(err).arg(file));
    }

    qint64 t2 = QDateTime::currentDateTime().currentMSecsSinceEpoch();
    if(lg->isDebug()){
        lg->debug(QString("createXMFile finished data len %1 compressed %2 file %3 in %4 ms")
                   .arg(data->length()).arg(compressed.length()).arg(file).arg(t2-t1));
    }
    delete data;
    return file;
}
PK* XM::openFile(QString file, QString pwd) {
    if(lg->isDebug()) {
        lg->debug(QString("openFile %1").arg(file));
    }
    QByteArray data = ut::file::toByteArray(file);
    try {
        data = qUncompress(data);
    } catch(...) {
        lg->error(QString("openFile error %1").arg(file));
        return NULL;
    }
    if(data.size() <= 4) {
        lg->error(QString("openFile file error len %1").arg(data.size()));
        return NULL;
    }
    //
    bool ok;
    QString uuid = data.mid(0, 32);
    uint jm = data.mid(32, 4).toHex().toUInt(&ok, 16);
    uint imgCount = data.mid(36, 4).toHex().toUInt(&ok, 16);
    if(imgCount > MAX_XM_IMG_COUNT) {
        lg->error(QString("openFile file error imgCount %1").arg(imgCount));
        return NULL;
    }
    uint mainImgLen = data.mid(40, 4).toHex().toUInt(&ok, 16);
    if(lg->isDebug()){
        lg->debug(QString("data len %1 imgCount %2 mainImgLen %3")
                   .arg(data.size()).arg(imgCount).arg(mainImgLen));
    }
    if(mainImgLen > SIZE_1G) {
        lg->error(QString("openFile file error mainImgLen %1").arg(mainImgLen));
        return NULL;
    }
    QList<uint> imgLens;
    uint x = 0;
    if(mainImgLen > 0) {
        imgLens << mainImgLen;
        x = 1;
    }
    uint headerLen = 44;
    for(uint i = 0; i < imgCount-x; i++) {
        uint imgLen = data.mid(headerLen, 4).toHex().toUInt(&ok, 16);
        if(imgLen > SIZE_1G) {
            lg->error(QString("openFile file error imgLen %1").arg(imgLen));
            return NULL;
        }
        imgLens << imgLen;
        if(lg->isDebug()) {
            lg->debug(QString("img%1 len %2").arg(i).arg(imgLen));
        }
        headerLen += 4;
    }
    //
    QString imgFilePath;
    QString mainImgName;
    uint from = headerLen;
    if(imgLens.size() > 0) {
        imgFilePath = "/tmp/" + uuid;
        QString path = cfg->imgDir + imgFilePath;
        QDir dir(path);
        if(!dir.exists()) {
            lg->debug(QString("mkpath %1").arg(path));
            if(!dir.mkpath(path)) {
                lg->error(QString("mkpath err %1").arg(path));
            }
        }
        for(int i = 0; i < imgLens.size(); i++) {
            uint imgLen = imgLens.at(i);
            if(imgLen > 0) {
                QByteArray imgData = data.mid(from, imgLen+1);
                char ty = imgData.at(0);
                QString postfix = ut::file::typeToPostfix((int)ty);
//                qDebug() << "::::::::::::" << ty << postfix;
                imgData = imgData.mid(1);
                if(i == 0) {
                    if(pwd.length() > 0) {
                        uint imgDataLen = imgData.length();
                        imgData = ut::cipher::decryptAES(pwd, imgData);
                        if(lg->isDebug()){
                            lg->debug(QString("mainImg decrptyAES pwd len %1 imgDat len %2 -> %3")
                                       .arg(pwd.length()).arg(imgDataLen).arg(imgData.length()));
                        }
                    }
                }
                //
                QImage *qimg = new QImage();
                qimg->loadFromData(imgData);
                if(qimg->width() > 0 && qimg->height() > 0){
                    if(i == 0) {
                        mainImgName = QString("%1.%2.%3%4").arg(i).arg(qimg->width()).arg(qimg->height()).arg(postfix);
                    }
                    //
                    QString file = QString("%1/%2.%3.%4%5").arg(path).arg(i).arg(qimg->width()).arg(qimg->height()).arg(postfix);
                    QFileInfo f(file);
                    if(!f.exists()) {
                        if(lg->isDebug()) {
                            lg->debug(QString("img%1 len %2/%3 file %4")
                                       .arg(i).arg(imgData.size()).arg(imgLen).arg(file));
                        }
                        QString err = ut::file::writeData(file, imgData);
                        if(err.length() > 0) {
                            lg->error(QString("openFile write file err %1 file %2").arg(err).arg(file));
                        }
                    }
                }
                from += imgLen+1;
            }
        }
    }
    //
    QString cont = data.mid(from);
    uint contLen = cont.length();
    if(pwd.length() > 0) {
        cont = ut::cipher::decryptTextAES(pwd, cont);
    }
    if(lg->isDebug()) {
        lg->debug(QString("pwd len %1 cont len %2 -> %3").arg(pwd.length()).arg(contLen).arg(cont.length()));
    }
    //
    PK *pk = new PK();
    pk->img = mainImgLen > 0 ? imgFilePath + "/" + mainImgName : "";
    pk->cont = cont;
    pk->uuid = uuid;
    pk->file = file;
    pk->jm = pwd.length() > 0 ? false : jm;
    return pk;
}
