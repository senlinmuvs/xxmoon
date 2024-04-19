#include "menumanager.h"
#include "com/const.h"
#include "com/global.h"
#include <QDebug>
#include <QDesktopServices>
#include <QWidget>
#include <QWindow>

MenuManager::MenuManager(QObject *parent) : QObject(parent) {
}

void MenuManager::init() {
    menuBar = new QMenuBar();
    QMenu *menu00 = menuBar->addMenu("&");
    QString act00name = "About &Xxmoon";
    QAction *act00 = menu00->addAction(act00name);

    QMenu* menu0 = new QMenu(trans->tr("File"));
    QMenu* menu1 = new QMenu(trans->tr("Edit"));
    QMenu* menu2 = new QMenu(trans->tr("Window"));
    QMenu* menu3 = new QMenu(trans->tr("Help"));

    menuBar->addMenu(menu0);
    menuBar->addMenu(menu1);
    menuBar->addMenu(menu2);
    menuBar->addMenu(menu3);

    QAction* act0 = new QAction(trans->tr("Open"), this);
    Qt::Modifier ctrlKey = Qt::CTRL;
    if(cfg->ctrl.toLower() == "meta") {
        ctrlKey = Qt::META;
    }
    act0->setShortcut(ctrlKey | Qt::Key_O);
    menu0->addAction(act0);

    //
    QAction* act1 = new QAction(trans->tr("Undo"), this);
    act1->setShortcut(ctrlKey | Qt::Key_Z);
    menu1->addAction(act1);

    QAction*  act2 = new QAction(trans->tr("Redo"), this);
    act2->setShortcut(ctrlKey | Qt::SHIFT | Qt::Key_Z);
    menu1->addAction(act2);
    menu1->addSeparator();

    QAction* act3 = new QAction(trans->tr("Copy"), this);
    act3->setShortcut(ctrlKey | Qt::Key_C);
    menu1->addAction(act3);

    QAction* act4 = new QAction(trans->tr("Paste"), this);
    act4->setShortcut(ctrlKey | Qt::Key_V);
    menu1->addAction(act4);

    QAction* act5 = new QAction(trans->tr("Cut"), this);
    act5->setShortcut(ctrlKey | Qt::Key_X);
    menu1->addAction(act5);

    QAction* act6 = new QAction(trans->tr("Select All"), this);
    act6->setShortcut(ctrlKey | Qt::Key_A);
    menu1->addAction(act6);

    //
    QAction* act7 = new QAction(trans->tr("Minizime"), this);
    act7->setShortcut(ctrlKey | Qt::Key_M);
    menu2->addAction(act7);

    QAction* act8 = new QAction(trans->tr("Zoom"), this);
//    act[8]->setShortcut(ctrlKey | Qt::Key_Z);
    menu2->addAction(act8);

    //
    QAction* act9 = new QAction(trans->tr("How to use ..."), this);
    act9->setShortcut(Qt::Key_F1);
    menu3->addAction(act9);

    // QAction* act10 = new QAction(trans->tr("Contact ..."), this);
    // menu3->addAction(act10);

    connect(act00,&QAction::triggered,this,&MenuManager::onAbout);
    connect(act0,&QAction::triggered,this,&MenuManager::onOpen);
    connect(act1,&QAction::triggered,this,&MenuManager::onUndo);
    connect(act2,&QAction::triggered,this,&MenuManager::onRedo);
    connect(act3,&QAction::triggered,this,&MenuManager::onCopy);
    connect(act4,&QAction::triggered,this,&MenuManager::onPaste);
    connect(act5,&QAction::triggered,this,&MenuManager::onCut);
    connect(act6,&QAction::triggered,this,&MenuManager::onSelectAll);
    connect(act7,&QAction::triggered,this,&MenuManager::onMinizime);
    connect(act8,&QAction::triggered,this,&MenuManager::onZoom);
    connect(act9,&QAction::triggered,this,&MenuManager::onHowToUse);
    // connect(act10,&QAction::triggered,this,&MenuManager::onContact);
}

void MenuManager::regReceiver(QObject* r) {
    receiver = r;
}

void MenuManager::onAbout(bool checked) {
    pushMsg(PUSH_OPEN_ABOUT, 0);
}
void MenuManager::onOpen(bool checked) {
    pushMsg(PUSH_OPENFILE, 0);
    qDebug() << "menu open" << receiver;
}

void MenuManager::onCopy(bool checked) {
    if(receiver == NULL) {
        lg->warn("onCopy receiver null");
    } else {
        QKeyEvent e(QEvent::KeyPress, Qt::Key_C, Qt::ControlModifier);
        QCoreApplication::sendEvent(receiver, &e);
        qDebug() << "menu copy" << receiver;
    }
}

void MenuManager::onPaste(bool checked) {
    if(receiver == NULL) {
        lg->warn("onPaste receiver null");
    } else {
        QKeyEvent e(QEvent::KeyPress, Qt::Key_V, Qt::ControlModifier);
        QCoreApplication::sendEvent(receiver, &e);
        qDebug() << "menu paste" << receiver;
    }
}

void MenuManager::onCut(bool checked) {
    if(receiver == NULL) {
        lg->warn("onCut receiver null");
    } else {
        QKeyEvent e(QEvent::KeyPress, Qt::Key_X, Qt::ControlModifier);
        QCoreApplication::sendEvent(receiver, &e);
        qDebug() << "menu cut" << receiver;
    }
}

void MenuManager::onUndo(bool checked) {
    if(receiver == NULL) {
        lg->warn("onUndo receiver null");
    } else {
        QKeyEvent e(QEvent::KeyPress, Qt::Key_Z, Qt::ControlModifier);
        QCoreApplication::sendEvent(receiver, &e);
        qDebug() << "menu undo" << receiver;
    }
}

void MenuManager::onRedo(bool checked) {
    if(receiver == NULL) {
        lg->warn("onRedo receiver null");
    } else {
        QKeyEvent e(QEvent::KeyPress, Qt::Key_Z, Qt::ControlModifier | Qt::ShiftModifier);
        QCoreApplication::sendEvent(receiver, &e);
        qDebug() << "menu redo" << receiver;
    }
}

void MenuManager::onSelectAll(bool checked) {
    if(receiver == NULL) {
        lg->warn("onSelectAll receiver null");
    } else {
        QKeyEvent e(QEvent::KeyPress, Qt::Key_A, Qt::ControlModifier);
        QCoreApplication::sendEvent(receiver, &e);
        qDebug() << "menu selectAll" << receiver;
    }
}
void MenuManager::onMinizime(bool checked) {
    QObject *qmlRoot = engine->rootObjects()[0];
    QWindow *w = qobject_cast<QWindow *>(qmlRoot);
    w->showMinimized();
}
void MenuManager::onZoom(bool checked) {
    QObject *qmlRoot = engine->rootObjects()[0];
    QWindow *w = qobject_cast<QWindow *>(qmlRoot);
    if (w->windowState() == Qt::WindowMaximized) {
        w->showNormal();
    } else {
        w->showMaximized();
    }
}

void MenuManager::onHowToUse(bool checked) {
    QDesktopServices::openUrl(QUrl(QString("https://github.com/senlinmuvs/xxmoon/wiki")));
}

// void MenuManager::onContact(bool checked) {
// }
