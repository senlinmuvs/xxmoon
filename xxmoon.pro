QT += widgets
QT += qml
QT += quick
QT += quickcontrols2
QT += sql

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        action/bookaction.cpp \
        action/collectaction.cpp \
        com/async.cpp \
        com/docparser.cpp \
        com/future.cpp \
        com/global.cpp \
        com/log.cpp \
        com/mypinyin.cpp \
        com/qaesencryption.cpp \
        com/runmain.cpp \
        com/sm.cpp \
        com/sqlite_manager.cpp \
        com/sslhelper.cpp \
        com/util.cpp \
        com/xm.cpp \
        db/basedao.cpp \
        db/coldao.cpp \
        db/envdao.cpp \
        db/notedao.cpp \
        db/pkdao.cpp \
        db/tagdao.cpp \
        db/workdao.cpp \
        hserver.cpp \
        menumanager.cpp \
        model/cfg.cpp \
        model/collect.cpp \
        model/note.cpp \
        model/pk.cpp \
        model/tag.cpp \
        model/work.cpp \
        app.cpp \
        l.cpp \
        main.cpp \
        timer.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

HEADERS += \
    action/bookaction.h \
    action/collectaction.h \
    com/async.h \
    com/const.h \
    com/docparser.h \
    com/future.h \
    com/global.h \
    com/httplib.h \
    com/log.h \
    com/mypinyin.h \
    com/qaesencryption.h \
    com/runmain.h \
    com/sm.h \
    com/sqlite_manager.h \
    com/sslhelper.h \
    com/util.h \
    com/xm.h \
    db/basedao.h \
    db/coldao.h \
    db/envdao.h \
    db/notedao.h \
    db/pkdao.h \
    db/tagdao.h \
    db/workdao.h \
    hserver.h \
    menumanager.h \
    model/cfg.h \
    model/collect.h \
    model/note.h \
    model/pk.h \
    model/tag.h \
    model/work.h \
    app.h \
    l.h \
    test.h \
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

    LIBS += -L$$PWD/libs/macos/ -lcrypto -lssl -lxxmoon
    INCLUDEPATH += /Volumes/D/github/c/openssl-1.1.1k/include
    INCLUDEPATH += $$PWD/libs/macos/

    QMAKE_TARGET_BUNDLE_PREFIX = com.xxmoon
#    mac_icon.files = $$files($$PWD/xxmoon/Images.xcassets/AppIcon.appiconset/icon*.png)
    QMAKE_BUNDLE_DATA += mac_icon
    QMAKE_INFO_PLIST=$$PWD/Info.plist
}
win32 {
    win32:RC_ICONS += assets/logo.ico
    include(D:\github\qt\QHotkey\qhotkey.pri)
    DEFINES += _WINSOCKAPI_
    LIBS += -lWs2_32
    LIBS += -L$$PWD/libs/ -lcrypto -lssl
    INCLUDEPATH += D:\github\c\openssl-1.1.1g\build_win32\out\include
}
unix:!macx {
    include(/home/sen/github/qt/QHotkey/qhotkey.pri)
}
include(libxxmoon.pri)
TRANSLATIONS = zh_CN.ts en_US.ts
