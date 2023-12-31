macx {
    INCLUDEPATH += $$PWD/libs/macos/
    LIBS += -L$$PWD/libs/macos/ -lxxmoon
}
win32 {
    INCLUDEPATH += $$PWD/libs/
    LIBS += -L$$PWD/libs/ -lxxmoon
}
