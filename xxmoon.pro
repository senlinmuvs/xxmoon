QT += widgets
QT += qml
QT += quick
QT += quickcontrols2
QT += sql
QT += network

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        action/bookaction.cpp \
        action/xmaction.cpp \
        com/async.cpp \
        com/docparser.cpp \
        com/filequeue.cpp \
        com/future.cpp \
        com/global.cpp \
        com/http.cpp \
        com/log.cpp \
        com/mypinyin.cpp \
        com/qaesencryption.cpp \
        com/runmain.cpp \
        com/script.cpp \
        com/sm.cpp \
        com/sqlite_manager.cpp \
        com/sslhelper.cpp \
        com/sync.cpp \
        com/trans.cpp \
        com/util.cpp \
        com/xm_format.cpp \
        db/basedao.cpp \
        db/categorydao.cpp \
        db/envdao.cpp \
        db/notedao.cpp \
        db/tagdao.cpp \
        db/tasklogdao.cpp \
        db/workdao.cpp \
        db/xmdao.cpp \
        hserver.cpp \
        menumanager.cpp \
        model/category.cpp \
        model/cfg.cpp \
        model/note.cpp \
        model/tag.cpp \
        model/tasklog.cpp \
        model/work.cpp \
        app.cpp \
        l.cpp \
        main.cpp \
        model/xm.cpp \
        timer.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

HEADERS += \
    action/bookaction.h \
    action/xmaction.h \
    com/async.h \
    com/const.h \
    com/docparser.h \
    com/filequeue.h \
    com/future.h \
    com/global.h \
    com/http.h \
    com/httplib.h \
    com/log.h \
    com/mypinyin.h \
    com/qaesencryption.h \
    com/runmain.h \
    com/script.h \
    com/sm.h \
    com/sqlite_manager.h \
    com/sslhelper.h \
    com/sync.h \
    com/trans.h \
    com/util.h \
    com/xm_format.h \
    db/basedao.h \
    db/categorydao.h \
    db/envdao.h \
    db/notedao.h \
    db/tagdao.h \
    db/tasklogdao.h \
    db/workdao.h \
    db/xmdao.h \
    hserver.h \
    menumanager.h \
    model/category.h \
    model/cfg.h \
    model/note.h \
    model/tag.h \
    model/tasklog.h \
    model/work.h \
    app.h \
    l.h \
    model/xm.h \
    timer.h

TARGET = xxmoon

macx {
    HEADERS += \
        com/mac.h
    OBJECTIVE_SOURCES += \
        com/mac.mm
    LIBS += -framework Foundation
    LIBS += -framework Cocoa
    ICON = assets/logo.icns
    include(/Volumes/D/github/qt/QHotkey/qhotkey.pri)

    LIBS += -L$$PWD/libs/mac/ -lcrypto -lssl -lxxmoon
    INCLUDEPATH += /Volumes/D/github/c/openssl-1.1.1k/include
    INCLUDEPATH += $$PWD/libs/mac/

    QMAKE_TARGET_BUNDLE_PREFIX = com.xxmoon
#    mac_icon.files = $$files($$PWD/xxmoon/Images.xcassets/AppIcon.appiconset/icon*.png)
    QMAKE_BUNDLE_DATA += mac_icon
    QMAKE_INFO_PLIST=$$PWD/Info.plist
}
win32 {
    win32:RC_ICONS += assets/logo.ico
    include(E:\code\qt\os\QHotkey\qhotkey.pri)
    DEFINES += _WINSOCKAPI_
    LIBS += -lWs2_32
    LIBS += -L$$PWD\libs\win\ -lcrypto -lssl
    INCLUDEPATH += $$PWD\libs\win\include
}
unix:!macx {
    include(/home/sen/github/qt/QHotkey/qhotkey.pri)
}
include(libxxmoon.pri)

DISTFILES += \
    xxmoon.pri
