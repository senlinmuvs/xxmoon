HEADERS += $$files($$PWD/*.h, true)
SOURCES += $$files($$PWD/*.cpp, true)
SOURCES += $$files($$PWD/*.mm, true)

EXCLUDE_HEADERS += $$files($$PWD/build/*.h, true)
EXCLUDE_SOURCES1 += $$files($$PWD/build/*.cpp, true)
EXCLUDE_SOURCES2 += $$files($$PWD/moc_*.cpp)
HEADERS -= $$EXCLUDE_HEADERS
SOURCES -= $$EXCLUDE_SOURCES1
SOURCES -= $$EXCLUDE_SOURCES2
SOURCES -= $$files($$PWD/main.cpp)

INCLUDEPATH += $$PWD/../xxmoon

macx {
    LIBS += -framework Foundation
    LIBS += -framework Cocoa
    include(/Volumes/D/github/qt/QHotkey/qhotkey.pri)

    LIBS += -L$$PWD/libs/mac/ -lcrypto -lssl -lxxmoon
    INCLUDEPATH += /Volumes/D/github/c/openssl-1.1.1k/include
    INCLUDEPATH += $$PWD/libs/mac/
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
