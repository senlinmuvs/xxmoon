#ifndef MAC_H
#define MAC_H
#include <QWindow>

class Mac {

public:
    Mac();
    ~Mac();

    void initWindow(QWindow* w);
    void notification(QString title, QString text);
    bool existsAllowedURL();
    void loadBookmarks();
    QString openSelectFile();
    void alert(QString tip1, QString tip2);
    void close();
};

#endif // MAC_H
