macx {
    INCLUDEPATH += $$PWD/libs/mac/
    LIBS += -L$$PWD/libs/mac/ -lxxmoon
}
win32 {
    INCLUDEPATH += $$PWD/libs/win/
    LIBS += -L$$PWD/libs/win -lxxmoon
}
