/****************************************************************************
** Meta object code from reading C++ file 'app.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "app.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'app.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_App_t {
    QByteArrayData data[110];
    char stringdata0[929];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_App_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_App_t qt_meta_stringdata_App = {
    {
QT_MOC_LITERAL(0, 0, 3), // "App"
QT_MOC_LITERAL(1, 4, 11), // "getPlatform"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 9), // "getDeploy"
QT_MOC_LITERAL(4, 27, 13), // "getComputerID"
QT_MOC_LITERAL(5, 41, 11), // "isActivated"
QT_MOC_LITERAL(6, 53, 9), // "getCfgVal"
QT_MOC_LITERAL(7, 63, 1), // "k"
QT_MOC_LITERAL(8, 65, 7), // "getCtrl"
QT_MOC_LITERAL(9, 73, 6), // "import"
QT_MOC_LITERAL(10, 80, 4), // "path"
QT_MOC_LITERAL(11, 85, 3), // "obj"
QT_MOC_LITERAL(12, 89, 11), // "checkImport"
QT_MOC_LITERAL(13, 101, 11), // "checkExport"
QT_MOC_LITERAL(14, 113, 11), // "getLastPath"
QT_MOC_LITERAL(15, 125, 7), // "tagList"
QT_MOC_LITERAL(16, 133, 6), // "target"
QT_MOC_LITERAL(17, 140, 6), // "addTag"
QT_MOC_LITERAL(18, 147, 3), // "tag"
QT_MOC_LITERAL(19, 151, 6), // "delTag"
QT_MOC_LITERAL(20, 158, 3), // "tid"
QT_MOC_LITERAL(21, 162, 10), // "getTagById"
QT_MOC_LITERAL(22, 173, 2), // "id"
QT_MOC_LITERAL(23, 176, 4), // "cbid"
QT_MOC_LITERAL(24, 181, 3), // "set"
QT_MOC_LITERAL(25, 185, 1), // "v"
QT_MOC_LITERAL(26, 187, 4), // "init"
QT_MOC_LITERAL(27, 192, 8), // "setLocal"
QT_MOC_LITERAL(28, 201, 7), // "encrypt"
QT_MOC_LITERAL(29, 209, 9), // "listWidth"
QT_MOC_LITERAL(30, 219, 7), // "decrypt"
QT_MOC_LITERAL(31, 227, 22), // "ensureEncryptOrDecrypt"
QT_MOC_LITERAL(32, 250, 4), // "cont"
QT_MOC_LITERAL(33, 255, 7), // "genFile"
QT_MOC_LITERAL(34, 263, 8), // "fileType"
QT_MOC_LITERAL(35, 272, 4), // "type"
QT_MOC_LITERAL(36, 277, 3), // "gid"
QT_MOC_LITERAL(37, 281, 5), // "batch"
QT_MOC_LITERAL(38, 287, 3), // "pwd"
QT_MOC_LITERAL(39, 291, 14), // "deleteFromSite"
QT_MOC_LITERAL(40, 306, 13), // "getFilesInDir"
QT_MOC_LITERAL(41, 320, 3), // "dir"
QT_MOC_LITERAL(42, 324, 14), // "openInExternal"
QT_MOC_LITERAL(43, 339, 3), // "img"
QT_MOC_LITERAL(44, 343, 7), // "openDir"
QT_MOC_LITERAL(45, 351, 5), // "close"
QT_MOC_LITERAL(46, 357, 1), // "r"
QT_MOC_LITERAL(47, 359, 12), // "checkTmpFile"
QT_MOC_LITERAL(48, 372, 9), // "plainText"
QT_MOC_LITERAL(49, 382, 4), // "html"
QT_MOC_LITERAL(50, 387, 9), // "checkAuth"
QT_MOC_LITERAL(51, 397, 4), // "auth"
QT_MOC_LITERAL(52, 402, 4), // "save"
QT_MOC_LITERAL(53, 407, 6), // "getCfg"
QT_MOC_LITERAL(54, 414, 10), // "getKeyName"
QT_MOC_LITERAL(55, 425, 3), // "key"
QT_MOC_LITERAL(56, 429, 9), // "modifiers"
QT_MOC_LITERAL(57, 439, 6), // "setCfg"
QT_MOC_LITERAL(58, 446, 10), // "openXMFile"
QT_MOC_LITERAL(59, 457, 4), // "file"
QT_MOC_LITERAL(60, 462, 8), // "importXM"
QT_MOC_LITERAL(61, 471, 6), // "pkdata"
QT_MOC_LITERAL(62, 478, 4), // "copy"
QT_MOC_LITERAL(63, 483, 1), // "s"
QT_MOC_LITERAL(64, 485, 10), // "getVersion"
QT_MOC_LITERAL(65, 496, 9), // "getUIData"
QT_MOC_LITERAL(66, 506, 7), // "copyImg"
QT_MOC_LITERAL(67, 514, 12), // "enableServer"
QT_MOC_LITERAL(68, 527, 13), // "disableServer"
QT_MOC_LITERAL(69, 541, 9), // "genQRCode"
QT_MOC_LITERAL(70, 551, 7), // "devices"
QT_MOC_LITERAL(71, 559, 6), // "delDev"
QT_MOC_LITERAL(72, 566, 3), // "dev"
QT_MOC_LITERAL(73, 570, 11), // "sendToPhone"
QT_MOC_LITERAL(74, 582, 2), // "ty"
QT_MOC_LITERAL(75, 585, 12), // "getCurQRCode"
QT_MOC_LITERAL(76, 598, 7), // "genCert"
QT_MOC_LITERAL(77, 606, 5), // "force"
QT_MOC_LITERAL(78, 612, 2), // "al"
QT_MOC_LITERAL(79, 615, 15), // "regMenuReceiver"
QT_MOC_LITERAL(80, 631, 1), // "o"
QT_MOC_LITERAL(81, 633, 11), // "triggerMenu"
QT_MOC_LITERAL(82, 645, 3), // "act"
QT_MOC_LITERAL(83, 649, 16), // "existsAllowedURL"
QT_MOC_LITERAL(84, 666, 11), // "alertMacTip"
QT_MOC_LITERAL(85, 678, 4), // "tip1"
QT_MOC_LITERAL(86, 683, 4), // "tip2"
QT_MOC_LITERAL(87, 688, 13), // "selectDataDir"
QT_MOC_LITERAL(88, 702, 2), // "pk"
QT_MOC_LITERAL(89, 705, 8), // "setUIVal"
QT_MOC_LITERAL(90, 714, 8), // "getUIVal"
QT_MOC_LITERAL(91, 723, 4), // "test"
QT_MOC_LITERAL(92, 728, 7), // "calLine"
QT_MOC_LITERAL(93, 736, 3), // "txt"
QT_MOC_LITERAL(94, 740, 5), // "index"
QT_MOC_LITERAL(95, 746, 9), // "existFile"
QT_MOC_LITERAL(96, 756, 8), // "pageSize"
QT_MOC_LITERAL(97, 765, 4), // "tag1"
QT_MOC_LITERAL(98, 770, 4), // "tag2"
QT_MOC_LITERAL(99, 775, 6), // "maxTag"
QT_MOC_LITERAL(100, 782, 7), // "dataDir"
QT_MOC_LITERAL(101, 790, 7), // "baseDir"
QT_MOC_LITERAL(102, 798, 6), // "imgDir"
QT_MOC_LITERAL(103, 805, 7), // "fileDir"
QT_MOC_LITERAL(104, 813, 15), // "ENV_K_LAST_SORT"
QT_MOC_LITERAL(105, 829, 20), // "ENV_K_LAST_VIEW_TYPE"
QT_MOC_LITERAL(106, 850, 13), // "ENV_K_LAST_WH"
QT_MOC_LITERAL(107, 864, 29), // "ENV_K_LAST_COLLECT_LEFT_WIDTH"
QT_MOC_LITERAL(108, 894, 26), // "ENV_K_LAST_BOOK_LEFT_WIDTH"
QT_MOC_LITERAL(109, 921, 7) // "cfgFile"

    },
    "App\0getPlatform\0\0getDeploy\0getComputerID\0"
    "isActivated\0getCfgVal\0k\0getCtrl\0import\0"
    "path\0obj\0checkImport\0checkExport\0"
    "getLastPath\0tagList\0target\0addTag\0tag\0"
    "delTag\0tid\0getTagById\0id\0cbid\0set\0v\0"
    "init\0setLocal\0encrypt\0listWidth\0decrypt\0"
    "ensureEncryptOrDecrypt\0cont\0genFile\0"
    "fileType\0type\0gid\0batch\0pwd\0deleteFromSite\0"
    "getFilesInDir\0dir\0openInExternal\0img\0"
    "openDir\0close\0r\0checkTmpFile\0plainText\0"
    "html\0checkAuth\0auth\0save\0getCfg\0"
    "getKeyName\0key\0modifiers\0setCfg\0"
    "openXMFile\0file\0importXM\0pkdata\0copy\0"
    "s\0getVersion\0getUIData\0copyImg\0"
    "enableServer\0disableServer\0genQRCode\0"
    "devices\0delDev\0dev\0sendToPhone\0ty\0"
    "getCurQRCode\0genCert\0force\0al\0"
    "regMenuReceiver\0o\0triggerMenu\0act\0"
    "existsAllowedURL\0alertMacTip\0tip1\0"
    "tip2\0selectDataDir\0pk\0setUIVal\0getUIVal\0"
    "test\0calLine\0txt\0index\0existFile\0"
    "pageSize\0tag1\0tag2\0maxTag\0dataDir\0"
    "baseDir\0imgDir\0fileDir\0ENV_K_LAST_SORT\0"
    "ENV_K_LAST_VIEW_TYPE\0ENV_K_LAST_WH\0"
    "ENV_K_LAST_COLLECT_LEFT_WIDTH\0"
    "ENV_K_LAST_BOOK_LEFT_WIDTH\0cfgFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_App[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      67,   14, // methods
      14,  604, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    0,  349,    2, 0x02 /* Public */,
       3,    0,  350,    2, 0x02 /* Public */,
       4,    0,  351,    2, 0x02 /* Public */,
       5,    0,  352,    2, 0x02 /* Public */,
       6,    1,  353,    2, 0x02 /* Public */,
       8,    0,  356,    2, 0x02 /* Public */,
       9,    2,  357,    2, 0x02 /* Public */,
      12,    0,  362,    2, 0x02 /* Public */,
      13,    0,  363,    2, 0x02 /* Public */,
      14,    1,  364,    2, 0x02 /* Public */,
      15,    3,  367,    2, 0x02 /* Public */,
      17,    2,  374,    2, 0x02 /* Public */,
      19,    2,  379,    2, 0x02 /* Public */,
      21,    2,  384,    2, 0x02 /* Public */,
      24,    3,  389,    2, 0x02 /* Public */,
      24,    2,  396,    2, 0x22 /* Public | MethodCloned */,
      27,    2,  401,    2, 0x02 /* Public */,
      28,    4,  406,    2, 0x02 /* Public */,
      30,    4,  415,    2, 0x02 /* Public */,
      31,    3,  424,    2, 0x02 /* Public */,
      33,    6,  431,    2, 0x02 /* Public */,
      33,    5,  444,    2, 0x22 /* Public | MethodCloned */,
      33,    4,  455,    2, 0x22 /* Public | MethodCloned */,
      39,    2,  464,    2, 0x02 /* Public */,
      39,    1,  469,    2, 0x22 /* Public | MethodCloned */,
      40,    1,  472,    2, 0x02 /* Public */,
      42,    3,  475,    2, 0x02 /* Public */,
      42,    2,  482,    2, 0x22 /* Public | MethodCloned */,
      42,    1,  487,    2, 0x22 /* Public | MethodCloned */,
      42,    0,  490,    2, 0x22 /* Public | MethodCloned */,
      44,    1,  491,    2, 0x02 /* Public */,
      45,    1,  494,    2, 0x02 /* Public */,
      45,    0,  497,    2, 0x22 /* Public | MethodCloned */,
      47,    0,  498,    2, 0x02 /* Public */,
      48,    2,  499,    2, 0x02 /* Public */,
      50,    2,  504,    2, 0x02 /* Public */,
      53,    1,  509,    2, 0x02 /* Public */,
      54,    2,  512,    2, 0x02 /* Public */,
      57,    2,  517,    2, 0x02 /* Public */,
      58,    3,  522,    2, 0x02 /* Public */,
      60,    1,  529,    2, 0x02 /* Public */,
      62,    1,  532,    2, 0x02 /* Public */,
      64,    0,  535,    2, 0x02 /* Public */,
      65,    0,  536,    2, 0x02 /* Public */,
      66,    1,  537,    2, 0x02 /* Public */,
      67,    0,  540,    2, 0x02 /* Public */,
      68,    0,  541,    2, 0x02 /* Public */,
      69,    1,  542,    2, 0x02 /* Public */,
      70,    1,  545,    2, 0x02 /* Public */,
      71,    2,  548,    2, 0x02 /* Public */,
      73,    3,  553,    2, 0x02 /* Public */,
      75,    1,  560,    2, 0x02 /* Public */,
      76,    2,  563,    2, 0x02 /* Public */,
      76,    1,  568,    2, 0x22 /* Public | MethodCloned */,
      76,    0,  571,    2, 0x22 /* Public | MethodCloned */,
      79,    1,  572,    2, 0x02 /* Public */,
      81,    1,  575,    2, 0x02 /* Public */,
      83,    0,  578,    2, 0x02 /* Public */,
      84,    2,  579,    2, 0x02 /* Public */,
      87,    0,  584,    2, 0x02 /* Public */,
      26,    0,  585,    2, 0x02 /* Public */,
      88,    0,  586,    2, 0x02 /* Public */,
      89,    2,  587,    2, 0x02 /* Public */,
      90,    1,  592,    2, 0x02 /* Public */,
      91,    0,  595,    2, 0x02 /* Public */,
      92,    2,  596,    2, 0x02 /* Public */,
      95,    1,  601,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::QString,
    QMetaType::Bool,
    QMetaType::QString, QMetaType::QString,    7,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString, QMetaType::QObjectStar,   10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QObjectStar,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::UInt, QMetaType::QObjectStar,    7,   16,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::QObjectStar,   18,   11,
    QMetaType::Void, QMetaType::UInt, QMetaType::QObjectStar,   20,   11,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt,   22,   23,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    7,   25,   26,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,   25,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,   25,
    QMetaType::Void, QMetaType::UInt, QMetaType::QString, QMetaType::UInt, QMetaType::UInt,   22,    7,   29,   23,
    QMetaType::Void, QMetaType::UInt, QMetaType::QString, QMetaType::UInt, QMetaType::UInt,   22,    7,   29,   23,
    QMetaType::Void, QMetaType::UInt, QMetaType::QString, QMetaType::UInt,   22,   32,   23,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt, QMetaType::Bool, QMetaType::QString,   34,   35,   36,   22,   37,   38,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt, QMetaType::Bool,   34,   35,   36,   22,   37,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt,   34,   35,   36,   22,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt,   22,   35,
    QMetaType::Void, QMetaType::UInt,   22,
    QMetaType::QStringList, QMetaType::QString,   41,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::UInt,   35,   43,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   35,   43,
    QMetaType::Void, QMetaType::Int,   35,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::Int,   46,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::UInt,   49,   23,
    QMetaType::Bool, QMetaType::QString, QMetaType::Bool,   51,   52,
    QMetaType::Void, QMetaType::QObjectStar,   11,
    QMetaType::QString, QMetaType::Int, QMetaType::Int,   55,   56,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,   25,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::UInt,   59,   38,   23,
    QMetaType::Void, QMetaType::QVariantMap,   61,
    QMetaType::Void, QMetaType::QString,   63,
    QMetaType::QString,
    QMetaType::QVariantMap,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   72,   23,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   74,   22,   23,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool,   77,   78,
    QMetaType::Void, QMetaType::Bool,   77,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QObjectStar,   80,
    QMetaType::Void, QMetaType::Int,   82,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   85,   86,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt, QMetaType::QString,    7,   25,
    QMetaType::QString, QMetaType::UInt,    7,
    QMetaType::QString,
    QMetaType::UInt, QMetaType::QString, QMetaType::Int,   93,   94,
    QMetaType::Bool, QMetaType::QString,   59,

 // properties: name, type, flags
      96, QMetaType::UInt, 0x00095401,
      97, QMetaType::QString, 0x00095401,
      98, QMetaType::QString, 0x00095401,
      99, QMetaType::UInt, 0x00095401,
     100, QMetaType::QString, 0x00095401,
     101, QMetaType::QString, 0x00095401,
     102, QMetaType::QString, 0x00095401,
     103, QMetaType::QString, 0x00095401,
     104, QMetaType::QString, 0x00095401,
     105, QMetaType::QString, 0x00095401,
     106, QMetaType::QString, 0x00095401,
     107, QMetaType::QString, 0x00095401,
     108, QMetaType::QString, 0x00095401,
     109, QMetaType::QString, 0x00095401,

       0        // eod
};

void App::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<App *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->getPlatform();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: { int _r = _t->getDeploy();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 2: { QString _r = _t->getComputerID();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 3: { bool _r = _t->isActivated();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { QString _r = _t->getCfgVal((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 5: { QString _r = _t->getCtrl();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->import((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2]))); break;
        case 7: _t->checkImport(); break;
        case 8: _t->checkExport(); break;
        case 9: _t->getLastPath((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 10: _t->tagList((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< QObject*(*)>(_a[3]))); break;
        case 11: _t->addTag((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2]))); break;
        case 12: _t->delTag((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2]))); break;
        case 13: _t->getTagById((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 14: _t->set((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 15: _t->set((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 16: _t->setLocal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 17: _t->encrypt((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4]))); break;
        case 18: _t->decrypt((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4]))); break;
        case 19: _t->ensureEncryptOrDecrypt((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 20: _t->genFile((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6]))); break;
        case 21: _t->genFile((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 22: _t->genFile((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4]))); break;
        case 23: _t->deleteFromSite((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 24: _t->deleteFromSite((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 25: { QStringList _r = _t->getFilesInDir((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 26: _t->openInExternal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 27: _t->openInExternal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 28: _t->openInExternal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->openInExternal(); break;
        case 30: _t->openDir((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 31: _t->close((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->close(); break;
        case 33: _t->checkTmpFile(); break;
        case 34: _t->plainText((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 35: { bool _r = _t->checkAuth((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 36: _t->getCfg((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 37: { QString _r = _t->getKeyName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 38: _t->setCfg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 39: _t->openXMFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 40: _t->importXM((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 41: _t->copy((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 42: { QString _r = _t->getVersion();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 43: { QVariantMap _r = _t->getUIData();
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 44: _t->copyImg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 45: _t->enableServer(); break;
        case 46: _t->disableServer(); break;
        case 47: _t->genQRCode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 48: _t->devices((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 49: _t->delDev((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 50: _t->sendToPhone((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 51: _t->getCurQRCode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 52: _t->genCert((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 53: _t->genCert((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 54: _t->genCert(); break;
        case 55: _t->regMenuReceiver((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 56: _t->triggerMenu((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 57: { bool _r = _t->existsAllowedURL();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 58: _t->alertMacTip((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 59: { QString _r = _t->selectDataDir();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 60: _t->init(); break;
        case 61: _t->pk(); break;
        case 62: _t->setUIVal((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 63: { QString _r = _t->getUIVal((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 64: { QString _r = _t->test();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 65: { uint _r = _t->calLine((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 66: { bool _r = _t->existFile((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<App *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< uint*>(_v) = _t->getPageSize(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->getTag1(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->getTag2(); break;
        case 3: *reinterpret_cast< uint*>(_v) = _t->getMaxTag(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->getDataDir(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->getBaseDir(); break;
        case 6: *reinterpret_cast< QString*>(_v) = _t->getImgDir(); break;
        case 7: *reinterpret_cast< QString*>(_v) = _t->getFileDir(); break;
        case 8: *reinterpret_cast< QString*>(_v) = _t->getENV_K_LAST_SORT(); break;
        case 9: *reinterpret_cast< QString*>(_v) = _t->getLAST_VIEW_TYPE(); break;
        case 10: *reinterpret_cast< QString*>(_v) = _t->getLAST_WH(); break;
        case 11: *reinterpret_cast< QString*>(_v) = _t->getLAST_COLLECT_LEFT_WIDTH(); break;
        case 12: *reinterpret_cast< QString*>(_v) = _t->getLAST_BOOK_LEFT_WIDTH(); break;
        case 13: *reinterpret_cast< QString*>(_v) = _t->getCfgFile(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject App::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_App.data,
    qt_meta_data_App,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *App::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *App::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_App.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int App::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 67)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 67;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 67)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 67;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 14;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
