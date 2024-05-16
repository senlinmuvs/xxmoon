#ifndef DOCPARSER_H
#define DOCPARSER_H

#include <QVariantList>

class DocParser {

public:
    static const int TY_TEXT = 1;
    static const int TY_QUOTE = 2;
    static const int TY_IMG = 3;
    static const int TY_CODE = 4;
    static const int TY_TITLE1 = 5;
    static const int TY_TITLE2 = 6;
    static const int TY_TITLE3 = 7;
    static const int TY_B = 8;
    static const int TY_HTTP = 9;
    static const int TY_HTTPS = 10;
    static const int TY_FTP = 11;
    static const int TY_FILE = 12;
    static const int TY_REF = 13;
    static const int TY_COLOR = 14;
    static const int TY_TABLE = 15;
    static const int TY_FOOTNOTE = 16;

    class DocTag {
    public:
        int ty = 0;
        QString tag0 = "";
        QString tag1 = "";

        explicit DocTag();
        explicit DocTag(int ty) {
            this->ty = ty;
            this->tag0 = "";
            this->tag1 = "";
        }
        explicit DocTag(int ty, const QString& tag0, const QString& tag1) {
            this->ty = ty;
            this->tag0 = tag0;
            this->tag1 = tag1;
        }
        static DocTag& create(int ty) {
            static DocTag dt(ty);
            if(ty == TY_TEXT) {
                dt = DocTag(ty, "", "");
            } else if(ty == TY_QUOTE) {
                dt = DocTag(ty, "```\n", "\n```");
            } else if(ty == TY_CODE) {
                dt = DocTag(ty, "```", "\n```");
            } else if(ty == TY_IMG) {
                dt = DocTag(ty, "!(", ")\n");
            }
            return dt;
        }
    };
    class Doc {
    public:
        int ty;
        QString cont = "";

        explicit Doc():ty(0), cont(""){};
        explicit Doc(int ty, const QString& cont):ty(ty), cont(cont) {}
        QString toString() {
            return "ty:"+QString::number(ty) + ", cont:" + cont;
        }
    };

    QList<DocTag> tags;

public:
    DocParser();

    QString parseHtml(QString s, uint maxWidth = 0);
    QStringList parseQML(QString s, uint maxWidth = 0);

private:
    QString txtKeepPre(QString s);
    QString filterQml(QString s);
    QString filterHtml(QString s);
    QString doESC(QString s);
    QString parseTxtHtml(QString s, uint maxWidth = 0);
    QString parseImgHtml(QString s, uint maxWidth = 0);
    QString parseQuoteHtml(QString s, uint maxWidth = 0);
    QString parseCodeHtml(QString s, uint maxWidth = 0);
    QStringList parse0(bool qml, QString s, uint maxWidth = 0);
    void addQmlList(QStringList& l, Doc& doc, uint maxWidth = 0);
    void addHtmlList(QStringList& l, Doc& doc, uint maxWidth = 0);
};

#endif // DOCPARSER_H
