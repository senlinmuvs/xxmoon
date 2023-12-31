/****************************************************************************
** Meta object code from reading C++ file 'bookaction.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "action/bookaction.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bookaction.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BookAction_t {
    QByteArrayData data[30];
    char stringdata0[216];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BookAction_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BookAction_t qt_meta_stringdata_BookAction = {
    {
QT_MOC_LITERAL(0, 0, 10), // "BookAction"
QT_MOC_LITERAL(1, 11, 11), // "getWorkList"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 1), // "k"
QT_MOC_LITERAL(4, 26, 8), // "fromTime"
QT_MOC_LITERAL(5, 35, 3), // "obj"
QT_MOC_LITERAL(6, 39, 7), // "addWork"
QT_MOC_LITERAL(7, 47, 4), // "name"
QT_MOC_LITERAL(8, 52, 6), // "author"
QT_MOC_LITERAL(9, 59, 4), // "time"
QT_MOC_LITERAL(10, 64, 10), // "updateWork"
QT_MOC_LITERAL(11, 75, 3), // "bid"
QT_MOC_LITERAL(12, 79, 7), // "delWork"
QT_MOC_LITERAL(13, 87, 2), // "id"
QT_MOC_LITERAL(14, 90, 4), // "cbid"
QT_MOC_LITERAL(15, 95, 11), // "getNoteList"
QT_MOC_LITERAL(16, 107, 3), // "wid"
QT_MOC_LITERAL(17, 111, 4), // "page"
QT_MOC_LITERAL(18, 116, 4), // "sort"
QT_MOC_LITERAL(19, 121, 9), // "listWidth"
QT_MOC_LITERAL(20, 131, 7), // "addNote"
QT_MOC_LITERAL(21, 139, 4), // "cont"
QT_MOC_LITERAL(22, 144, 4), // "pos0"
QT_MOC_LITERAL(23, 149, 4), // "pos1"
QT_MOC_LITERAL(24, 154, 10), // "updateNote"
QT_MOC_LITERAL(25, 165, 11), // "bklistWidth"
QT_MOC_LITERAL(26, 177, 14), // "updateNoteTags"
QT_MOC_LITERAL(27, 192, 4), // "tags"
QT_MOC_LITERAL(28, 197, 10), // "deleteNote"
QT_MOC_LITERAL(29, 208, 7) // "getNote"

    },
    "BookAction\0getWorkList\0\0k\0fromTime\0"
    "obj\0addWork\0name\0author\0time\0updateWork\0"
    "bid\0delWork\0id\0cbid\0getNoteList\0wid\0"
    "page\0sort\0listWidth\0addNote\0cont\0pos0\0"
    "pos1\0updateNote\0bklistWidth\0updateNoteTags\0"
    "tags\0deleteNote\0getNote"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BookAction[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    3,   64,    2, 0x02 /* Public */,
       6,    4,   71,    2, 0x02 /* Public */,
      10,    5,   80,    2, 0x02 /* Public */,
      12,    2,   91,    2, 0x02 /* Public */,
      15,    6,   96,    2, 0x02 /* Public */,
      20,    6,  109,    2, 0x02 /* Public */,
      24,    6,  122,    2, 0x02 /* Public */,
      26,    3,  135,    2, 0x02 /* Public */,
      28,    2,  142,    2, 0x02 /* Public */,
      29,    2,  147,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::ULong, QMetaType::QObjectStar,    3,    4,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::UInt, QMetaType::QObjectStar,    7,    8,    9,    5,
    QMetaType::Void, QMetaType::UInt, QMetaType::QString, QMetaType::QString, QMetaType::UInt, QMetaType::QObjectStar,   11,    7,    8,    9,    5,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt,   13,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::UInt, QMetaType::UInt, QMetaType::QString, QMetaType::UInt, QMetaType::QObjectStar,    3,   16,   17,   18,   19,    5,
    QMetaType::Void, QMetaType::UInt, QMetaType::QString, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt,   16,   21,   22,   23,   19,   14,
    QMetaType::Void, QMetaType::UInt, QMetaType::QString, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt,   13,   21,   22,   23,   25,   14,
    QMetaType::Void, QMetaType::UInt, QMetaType::QString, QMetaType::UInt,   13,   27,   14,
    QMetaType::Void, QMetaType::UInt, QMetaType::QObjectStar,   13,    5,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt,   13,   14,

       0        // eod
};

void BookAction::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BookAction *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getWorkList((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< ulong(*)>(_a[2])),(*reinterpret_cast< QObject*(*)>(_a[3]))); break;
        case 1: _t->addWork((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])),(*reinterpret_cast< QObject*(*)>(_a[4]))); break;
        case 2: _t->updateWork((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4])),(*reinterpret_cast< QObject*(*)>(_a[5]))); break;
        case 3: _t->delWork((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 4: _t->getNoteList((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< uint(*)>(_a[5])),(*reinterpret_cast< QObject*(*)>(_a[6]))); break;
        case 5: _t->addNote((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4])),(*reinterpret_cast< uint(*)>(_a[5])),(*reinterpret_cast< uint(*)>(_a[6]))); break;
        case 6: _t->updateNote((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4])),(*reinterpret_cast< uint(*)>(_a[5])),(*reinterpret_cast< uint(*)>(_a[6]))); break;
        case 7: _t->updateNoteTags((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 8: _t->deleteNote((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2]))); break;
        case 9: _t->getNote((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BookAction::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_BookAction.data,
    qt_meta_data_BookAction,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BookAction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BookAction::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BookAction.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BookAction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
