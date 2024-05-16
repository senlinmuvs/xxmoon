#ifndef TEST_H
#define TEST_H

#include <QString>
#include <QList>
#include <QDebug>
#include <QClipboard>
#include <QTimer>
#include <com/http.h>
#include "com/util.h"
#include "com/global.h"
#include "com/docparser.h"
#include "libxxmoon.h"

void test1() {
    qDebug() << "------------------------- TEST1 START -------------------------";
    QString s = ut::file::readFile("/Volumes/D/x.txt");
//    qDebug() << s;
    QList<DocParser::DocTag> tags;
    tags << DocParser::DocTag::create(DocParser::TY_QUOTE);
    tags << DocParser::DocTag::create(DocParser::TY_IMG);
    QList<QString> l;
    int start = 0;
    while(true) {
        int i0 = -1;
        int i1 = -1;
        int tagsIndex = 0;
        for(int i = 0; i < tags.size(); i++) {
            DocParser::DocTag dt = tags.at(i);
            int i0_ = s.indexOf(dt.tag0, start);
            if(i0_ >= 0) {
                int i1_ = s.indexOf(dt.tag1, i0_+dt.tag0.size());
                if(i1_ >= 0) {
                    if((i0 < 0 || i0_ < i0) && (i1 < 0 || i1_ < i1)) {
                        i0 = i0_;
                        i1 = i1_;
                        tagsIndex = i;
                    }
                }
            }
        }

//        DocParser::DocTag textDocTag = DocParser::DocTag(DocParser::TY_TEXT);
//        if(i0 >= 0 && i1 >= 0) {
//            if(i0 > start) {
//                l << DocParser::Doc(textDocTag.ty, s.mid(start, i0-start)).parse();
//            }
//            //
//            DocParser::DocTag dt = tags.at(tagsIndex);
//            int tag0Len = dt.tag0.length();
//            int tag1Len = dt.tag1.length();
//            if(i1 > i0+tag0Len) {
//                l << DocParser::Doc(dt.ty,s.mid(i0+tag0Len, i1-i0-tag0Len)).parse();
//            }
//            //
//            if(i1 + tag1Len > start) {
//                start = i1 + tag1Len;
//            }
//            qDebug() << start << i0 << i1;
//        } else {
//            if(s.size()-1 > start) {
//                l << DocParser::Doc(textDocTag.ty,s.right(s.size() - start)).parse();
//            }
//            break;
//        }
    }
    //
    for(QString s:l) {
        qDebug() << s;
    }
    qDebug() << "------------------------- TEST1 END -------------------------";
}

void test2() {
    qDebug() << "------------------------- TEST2 START -------------------------";
    QString s = ut::file::readFile("/Volumes/D/x.txt");
    DocParser dp;
    QStringList l = dp.parseQML(s);
    for(QString s : l) {
        qDebug() << s;
    }
    qDebug() << "------------------------- TEST2 END -------------------------";
}

void test3() {
    qDebug() << "------------------------- TEST3 START -----------------------";
    QString img = "x.gifx";
    int ty = ut::file::postfixType(img);
    QByteArray ba;
    char c = (char)ty;
    ba.append(c);
    int ty_ = (int)ba.at(0);
    qDebug() << ty << "|" << ty_ << ba.size();
    qDebug() << "------------------------- TEST3 END -------------------------";
}

void test4() {
    qDebug() << "------------------------- TEST3 START -----------------------";
    QString img = "20210215224724.361.1920.1080.png";
    std::tuple<uint, uint> tp = getWHFromFileName(img);
    qDebug() << get<0>(tp) << get<1>(tp);
    qDebug() << "------------------------- TEST3 END -------------------------";
}

void test5() {
    qDebug() << "------------------------- TEST 5 START -----------------------";
    // QString src = ut::file::readFile("/Users/sen/Desktop/src.txt");
    QString src = "//aaa";
    QString code = "java";
    qDebug() << src.toUtf8().data();
    qDebug() << "-------------------------------------------------------------";
    QString x = Highlight(src.toUtf8().data(), code.toUtf8().data());
    ut::file::writeText("/Users/sen/Desktop/code_java.html", x);
    qDebug() << x;
    qDebug() << "------------------------- TEST 5 END -------------------------";
}
void test6() {
    qDebug() << "------------------------- TEST 6 START -----------------------";
//    doc_parser->test();
    QString s = "````\nx`````\n";
    qDebug() << s;
//    s = ut::str::replaceAllTag(s, "`# ","\n", "# ", "\n");
//    s = s.replace("``", "`");
//    s = ut::str::replaceAllTag(s, "`","\n", "", "\n");
    s = ut::str::replaceAllTag(s, "```","```\n", "<", ">");
    qDebug() << s;
    qDebug() << "------------------------- TEST 6 END -------------------------";
}
void test7() {
    qDebug() << "------------------------- TEST 7 START -----------------------";
    QString cont = ut::file::readFile("/Users/sen/Desktop/x");
//    qDebug() << cont.toUtf8().data();
    QString html = doc_parser->parseHtml(cont, 600);
    qDebug() << html.toUtf8().data();
    qDebug() << "-------------------------------------";
    QStringList qmls = doc_parser->parseQML(cont, 600);
    for(int i = 0; i < qmls.length(); i++) {
        qDebug() << qmls.at(i).toUtf8().data();
    }
    qDebug() << "------------------------- TEST 7 END -------------------------";
}
void test8() {
    qDebug() << "------------------------- TEST 8 Start -------------------------";
    QString param = QString::number(800);
//    QString s = "**a\nx**";
//    QString s = "**a**";
//    s = ut::str::replaceAllTag(s, "**","**", "<b>", "</b>", 1, param, "\n", eachTag_);

//    QString s = "@#a@";
    QString s = "**a\nb**";
    s = ut::str::replaceAllTag(s, "**","**", "<b>", "</b>", 1, param, "\n", nullptr);
    qDebug() << s;
    qDebug() << "------------------------- TEST 8 END -------------------------";
}
void test9() {
    qDebug() << "------------------------- TEST 9 Start -------------------------";
    QString s = "# a\n```\nb\n```";
//    QString s = "a\nhttp://b";
//    QString html = doc_parser->parseHtml(s, 600);
//    qDebug() << html.toUtf8().data();
    QStringList qmls = doc_parser->parseQML(s, 600);
    for(int i = 0; i < qmls.length(); i++) {
        qDebug() << qmls.at(i).toUtf8().data();
    }
    qDebug() << "------------------------- TEST 9 END -------------------------";
}

void test10() {
    qDebug() << "------------------------- TEST 10 Start -------------------------";
    QString cont = ut::file::readFile("/Users/sen/Desktop/cont.txt");
    QStringList list = extractImgsAsList(cont);
    qDebug() << list;
    qDebug() << "------------------------- TEST 10 END -------------------------";
}

void test11() {
    qDebug() << "------------------------- TEST 11 Start -------------------------";
    QClipboard *board = QGuiApplication::clipboard();
    QObject::connect(board, &QClipboard::dataChanged, a, [=](){
        static bool finished = true;

        qDebug() << "datachanged:" <<  board->text();

        if(board->text() == "" || finished == false) {
            return;
        }

        QString text = board->text();
        text = text.replace("\n", "\t");

        qDebug() << "new text:" << text;

        finished = false;
        board->setText(text);
        finished = true;
    }, Qt::DirectConnection);
    qDebug() << "------------------------- TEST 11 End ----------------------------";
}

void test12() {
    qDebug() << "------------------------- TEST 12 Start ----------------------------";
    DB_Async->exe("test1", []{
        qDebug() << "test1 task doing";
    });
    DB_Async->exe("test2", []{
        qDebug() << "test2 task doing";
    });
    DB_Async->exe("test3", []{
        qDebug() << "test3 task doing";
    });
    DB_Async->exe("test4", []{
        lg->debug("test4 task doing");
        QThread::msleep(2000);
        lg->debug("test4 task end");
    });
    DB_Async->exe("test5", []{
        qDebug() << "test5 task doing";
    });
    qDebug() << "------------------------- TEST 12 End ------------------------------";
}
void test13() {
    qDebug() << "------------------------- TEST 13 Start ----------------------------";
    QMap<QString, QString> params;
    params["path"] = "";
    params["cid"] = "0";
    params["user"] = "xxmoon";
    params["pwd"] = "12345";
    Http *http = new Http();
    http->upload("https://localhost/upfile", params, "/Volumes/MD/CodeCharts12.pdf", [http]{
            qDebug() << "done";
            http->deleteLater();
        }, [](qint64 s, qint64 t){
            qDebug() << ">" << s << t;
        });
    qDebug() << "------------------------- TEST 13 End ------------------------------";
}
void test14() {
    qDebug() << "------------------------- TEST 14 Start ----------------------------";
    QMap<QString, QString> params;
    params["path"] = "";
    params["cid"] = "0";
    params["user"] = "xxmoon";
    params["pwd"] = "12345";
    QString file = "/Volumes/MD/pobi.png";
    QEventLoop loop;
    Http http;
    http.upload("https://localhost/upfile", params, file, [file, &loop]{
        qDebug() << "done" << file;
        loop.quit();
        qDebug() << "done>>>>>>>>>";
    }, [](qint64 s, qint64 t) {
        qDebug() << ">" << s << t;
    });
    loop.exec();
    qDebug() << "------------------------- TEST 14 End ------------------------------";
}

void test15() {
    qDebug() << "------------------------- TEST 15 Start ----------------------------";
    QEventLoop eventLoop;
    QTimer::singleShot(3000, &eventLoop, [&eventLoop]{
        eventLoop.quit();
    });
    // QTimer::singleShot(3000, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();
    qDebug() << "Event loop finished. Continuing execution...";
    qDebug() << "------------------------- TEST 15 End ------------------------------";
}

void test16() {
    qDebug() << "------------------------- TEST 16 Start ----------------------------";
    QMap<QString, QString> params;
    QEventLoop loop;
    Http http;
    http.timeout = 2000;
    qDebug() << "post timeout" << http.timeout;
    http.post("https://localhost/test", params, [&](QJsonObject& jo){
        qDebug() << "resp" << jo;
        loop.quit();
    }, [&](QNetworkReply::NetworkError err){
        qDebug() << "err" << err;
        loop.quit();
    });
    loop.exec();
    qDebug() << "------------------------- TEST 16 End ------------------------------";
}

void test17() {
    qDebug() << "------------------------- TEST 17 Start -------------------------";
    // QString s = ut::file::readFile("/Users/sen/Desktop/x.txt");
    // QString s = "```\na\n```\n# c\n\n\n# b";
    // QString s = "```\na\n```\n# c\n\n# b";
    QString s = "a\nhttp://b";
    // QString s = "# a\n\n```\nb\n```";
    // QString s = "```\na\n```\nb";
    // QString s = "```\na\n```\nb\n```\nc\n```";
    // QString s = "hello world!";
    // QString s = "```\na\n```b";
    // QString h = doc_parser->parseHtml(s, 600);
    // qDebug() << h.toUtf8().data();
    // ut::file::writeText("/Users/sen/Desktop/x.html", h);
    // qDebug() << QString("-----------------------------------------------------------------").toUtf8().data();
    //
    QStringList qmls = doc_parser->parseQML(s, 600);
    for(int i = 0; i < qmls.length(); i++) {
        qDebug() << qmls.at(i).toUtf8().data();
    }
    qDebug() << "------------------------- TEST 17 END -------------------------";
}
#endif // TEST_H
