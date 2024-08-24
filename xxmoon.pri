HEADERS += $$files($$PWD/*.h, true)
SOURCES += $$files($$PWD/*.cpp, true)

EXCLUDE_HEADERS += $$files($$PWD/build/*.h, true)
EXCLUDE_SOURCES1 += $$files($$PWD/build/*.cpp, true)
EXCLUDE_SOURCES2 += $$files($$PWD/moc_*.cpp)
HEADERS -= $$EXCLUDE_HEADERS
SOURCES -= $$EXCLUDE_SOURCES1
SOURCES -= $$EXCLUDE_SOURCES2
SOURCES -= $$files($$PWD/main.cpp)

INCLUDEPATH += $$PWD/../xxmoon

macx {
    SOURCES += $$files($$PWD/*.mm, true)

    LIBS += -framework Foundation
    LIBS += -framework Cocoa
    include(/Volumes/D/github/qt/QHotkey/qhotkey.pri)

    LIBS += -L$$PWD/libs/mac/ -lcrypto -lssl -lxxmoon
    INCLUDEPATH += /Volumes/D/github/c/openssl-1.1.1k/include
    INCLUDEPATH += $$PWD/libs/mac/
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
