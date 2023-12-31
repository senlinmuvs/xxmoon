/****************************************************************************
** Meta object code from reading C++ file 'l.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "l.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'l.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_L_t {
    QByteArrayData data[10];
    char stringdata0[51];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_L_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_L_t qt_meta_stringdata_L = {
    {
QT_MOC_LITERAL(0, 0, 1), // "L"
QT_MOC_LITERAL(1, 2, 7), // "isDebug"
QT_MOC_LITERAL(2, 10, 0), // ""
QT_MOC_LITERAL(3, 11, 7), // "isTrace"
QT_MOC_LITERAL(4, 19, 5), // "trace"
QT_MOC_LITERAL(5, 25, 3), // "msg"
QT_MOC_LITERAL(6, 29, 5), // "debug"
QT_MOC_LITERAL(7, 35, 4), // "info"
QT_MOC_LITERAL(8, 40, 4), // "warn"
QT_MOC_LITERAL(9, 45, 5) // "error"

    },
    "L\0isDebug\0\0isTrace\0trace\0msg\0debug\0"
    "info\0warn\0error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_L[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x02 /* Public */,
       3,    0,   50,    2, 0x02 /* Public */,
       4,    1,   51,    2, 0x02 /* Public */,
       6,    1,   54,    2, 0x02 /* Public */,
       7,    1,   57,    2, 0x02 /* Public */,
       8,    1,   60,    2, 0x02 /* Public */,
       9,    1,   63,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,

       0        // eod
};

void L::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<L *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->isDebug();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: { bool _r = _t->isTrace();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->trace((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->debug((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->info((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->warn((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject L::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_L.data,
    qt_meta_data_L,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *L::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *L::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_L.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int L::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
