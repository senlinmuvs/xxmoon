#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <QMenuBar>
#include <QObject>

class MenuManager: public QObject {
    Q_OBJECT
private:
    QMenuBar* menuBar;
    QObject* receiver;

public:
    explicit MenuManager(QObject *parent = nullptr);
    void init();
    void regReceiver(QObject* r);

public slots:
    void onAbout(bool checked = false);
    void onOpen(bool checked = false);
    void onCopy(bool checked = false);
    void onPaste(bool checked = false);
    void onCut(bool checked = false);
    void onUndo(bool checked = false);
    void onRedo(bool checked = false);
    void onSelectAll(bool checked = false);
    void onMinizime(bool checked = false);
    void onZoom(bool checked = false);
    void onHowToUse(bool checked = false);
    void onContact(bool checked = false);
};

#endif // MENUMANAGER_H
