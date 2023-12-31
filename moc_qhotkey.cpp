/****************************************************************************
** Meta object code from reading C++ file 'qhotkey.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../github/qt/QHotkey/QHotkey/qhotkey.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qhotkey.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QHotkey_t {
    QByteArrayData data[18];
    char stringdata0[224];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QHotkey_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QHotkey_t qt_meta_stringdata_QHotkey = {
    {
QT_MOC_LITERAL(0, 0, 7), // "QHotkey"
QT_MOC_LITERAL(1, 8, 9), // "activated"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 8), // "released"
QT_MOC_LITERAL(4, 28, 17), // "registeredChanged"
QT_MOC_LITERAL(5, 46, 10), // "registered"
QT_MOC_LITERAL(6, 57, 13), // "setRegistered"
QT_MOC_LITERAL(7, 71, 11), // "setShortcut"
QT_MOC_LITERAL(8, 83, 8), // "shortcut"
QT_MOC_LITERAL(9, 92, 12), // "autoRegister"
QT_MOC_LITERAL(10, 105, 7), // "Qt::Key"
QT_MOC_LITERAL(11, 113, 7), // "keyCode"
QT_MOC_LITERAL(12, 121, 21), // "Qt::KeyboardModifiers"
QT_MOC_LITERAL(13, 143, 9), // "modifiers"
QT_MOC_LITERAL(14, 153, 13), // "resetShortcut"
QT_MOC_LITERAL(15, 167, 17), // "setNativeShortcut"
QT_MOC_LITERAL(16, 185, 23), // "QHotkey::NativeShortcut"
QT_MOC_LITERAL(17, 209, 14) // "nativeShortcut"

    },
    "QHotkey\0activated\0\0released\0"
    "registeredChanged\0registered\0setRegistered\0"
    "setShortcut\0shortcut\0autoRegister\0"
    "Qt::Key\0keyCode\0Qt::KeyboardModifiers\0"
    "modifiers\0resetShortcut\0setNativeShortcut\0"
    "QHotkey::NativeShortcut\0nativeShortcut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QHotkey[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       2,  106, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    1,   71,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   74,    2, 0x0a /* Public */,
       7,    2,   77,    2, 0x0a /* Public */,
       7,    1,   82,    2, 0x2a /* Public | MethodCloned */,
       7,    3,   85,    2, 0x0a /* Public */,
       7,    2,   92,    2, 0x2a /* Public | MethodCloned */,
      14,    0,   97,    2, 0x0a /* Public */,
      15,    2,   98,    2, 0x0a /* Public */,
      15,    1,  103,    2, 0x2a /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    5,

 // slots: parameters
    QMetaType::Bool, QMetaType::Bool,    5,
    QMetaType::Bool, QMetaType::QKeySequence, QMetaType::Bool,    8,    9,
    QMetaType::Bool, QMetaType::QKeySequence,    8,
    QMetaType::Bool, 0x80000000 | 10, 0x80000000 | 12, QMetaType::Bool,   11,   13,    9,
    QMetaType::Bool, 0x80000000 | 10, 0x80000000 | 12,   11,   13,
    QMetaType::Bool,
    QMetaType::Bool, 0x80000000 | 16, QMetaType::Bool,   17,    9,
    QMetaType::Bool, 0x80000000 | 16,   17,

 // properties: name, type, flags
       5, QMetaType::Bool, 0x00495103,
       8, QMetaType::QKeySequence, 0x00095107,

 // properties: notify_signal_id
       2,
       0,

       0        // eod
};

void QHotkey::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QHotkey *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->activated(QPrivateSignal()); break;
        case 1: _t->released(QPrivateSignal()); break;
        case 2: _t->registeredChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: { bool _r = _t->setRegistered((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { bool _r = _t->setShortcut((*reinterpret_cast< const QKeySequence(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: { bool _r = _t->setShortcut((*reinterpret_cast< const QKeySequence(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: { bool _r = _t->setShortcut((*reinterpret_cast< Qt::Key(*)>(_a[1])),(*reinterpret_cast< Qt::KeyboardModifiers(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->setShortcut((*reinterpret_cast< Qt::Key(*)>(_a[1])),(*reinterpret_cast< Qt::KeyboardModifiers(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->resetShortcut();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->setNativeShortcut((*reinterpret_cast< QHotkey::NativeShortcut(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->setNativeShortcut((*reinterpret_cast< QHotkey::NativeShortcut(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QHotkey::NativeShortcut >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QHotkey::NativeShortcut >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QHotkey::*)(QPrivateSignal);
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QHotkey::activated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QHotkey::*)(QPrivateSignal);
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QHotkey::released)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QHotkey::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QHotkey::registeredChanged)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QHotkey *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->isRegistered(); break;
        case 1: *reinterpret_cast< QKeySequence*>(_v) = _t->shortcut(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QHotkey *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setRegistered(*reinterpret_cast< bool*>(_v)); break;
        case 1: _t->setShortcut(*reinterpret_cast< QKeySequence*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
        QHotkey *_t = static_cast<QHotkey *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 1: _t->resetShortcut(); break;
        default: break;
        }
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject QHotkey::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QHotkey.data,
    qt_meta_data_QHotkey,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QHotkey::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QHotkey::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QHotkey.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QHotkey::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QHotkey::activated(QPrivateSignal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QHotkey::released(QPrivateSignal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QHotkey::registeredChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
