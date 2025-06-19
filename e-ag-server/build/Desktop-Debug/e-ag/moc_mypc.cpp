/****************************************************************************
** Meta object code from reading C++ file 'mypc.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../e-ag/mypc.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mypc.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyPc_t {
    QByteArrayData data[54];
    char stringdata0[753];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyPc_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyPc_t qt_meta_stringdata_MyPc = {
    {
QT_MOC_LITERAL(0, 0, 4), // "MyPc"
QT_MOC_LITERAL(1, 5, 13), // "pcClickSignal"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 3), // "mac"
QT_MOC_LITERAL(4, 24, 18), // "pcRightClickSignal"
QT_MOC_LITERAL(5, 43, 13), // "pcListeSignal"
QT_MOC_LITERAL(6, 57, 12), // "pcHideSignal"
QT_MOC_LITERAL(7, 70, 4), // "_mac"
QT_MOC_LITERAL(8, 75, 13), // "pcCloseSignal"
QT_MOC_LITERAL(9, 89, 2), // "ip"
QT_MOC_LITERAL(10, 92, 18), // "pcListeStateSignal"
QT_MOC_LITERAL(11, 111, 22), // "pcTcpPortControlSignal"
QT_MOC_LITERAL(12, 134, 22), // "pcSshPortControlSignal"
QT_MOC_LITERAL(13, 157, 22), // "pcVncPortControlSignal"
QT_MOC_LITERAL(14, 180, 23), // "pcXrdpPortControlSignal"
QT_MOC_LITERAL(15, 204, 25), // "pcKilitStateControlSignal"
QT_MOC_LITERAL(16, 230, 11), // "_kilitstate"
QT_MOC_LITERAL(17, 242, 35), // "pcKilitTransparanStateControl..."
QT_MOC_LITERAL(18, 278, 21), // "_transparankilitstate"
QT_MOC_LITERAL(19, 300, 24), // "pcIconStateControlSignal"
QT_MOC_LITERAL(20, 325, 10), // "_iconstate"
QT_MOC_LITERAL(21, 336, 12), // "pcMenuSignal"
QT_MOC_LITERAL(22, 349, 5), // "_slot"
QT_MOC_LITERAL(23, 355, 7), // "setSize"
QT_MOC_LITERAL(24, 363, 2), // "_w"
QT_MOC_LITERAL(25, 366, 2), // "_h"
QT_MOC_LITERAL(26, 369, 5), // "_font"
QT_MOC_LITERAL(27, 375, 7), // "setUser"
QT_MOC_LITERAL(28, 383, 3), // "_os"
QT_MOC_LITERAL(29, 387, 11), // "setHostname"
QT_MOC_LITERAL(30, 399, 9), // "_hostname"
QT_MOC_LITERAL(31, 409, 20), // "setKilitControlState"
QT_MOC_LITERAL(32, 430, 5), // "state"
QT_MOC_LITERAL(33, 436, 30), // "setKilitTransparanControlState"
QT_MOC_LITERAL(34, 467, 19), // "setIconControlState"
QT_MOC_LITERAL(35, 487, 26), // "timertcpConnectControlSlot"
QT_MOC_LITERAL(36, 514, 15), // "setConnectState"
QT_MOC_LITERAL(37, 530, 20), // "setCommandButonState"
QT_MOC_LITERAL(38, 551, 11), // "setSshState"
QT_MOC_LITERAL(39, 563, 11), // "setVncState"
QT_MOC_LITERAL(40, 575, 12), // "setXrdpState"
QT_MOC_LITERAL(41, 588, 15), // "setCommandState"
QT_MOC_LITERAL(42, 604, 8), // "_command"
QT_MOC_LITERAL(43, 613, 14), // "_commandDetail"
QT_MOC_LITERAL(44, 628, 13), // "_commandState"
QT_MOC_LITERAL(45, 642, 14), // "slotMouseClick"
QT_MOC_LITERAL(46, 657, 20), // "slotMouseDoubleClick"
QT_MOC_LITERAL(47, 678, 12), // "slotSelectPc"
QT_MOC_LITERAL(48, 691, 14), // "slotUnselectPc"
QT_MOC_LITERAL(49, 706, 10), // "slothidePc"
QT_MOC_LITERAL(50, 717, 15), // "getIpPortStatus"
QT_MOC_LITERAL(51, 733, 3), // "ip_"
QT_MOC_LITERAL(52, 737, 4), // "port"
QT_MOC_LITERAL(53, 742, 10) // "slotPcAyar"

    },
    "MyPc\0pcClickSignal\0\0mac\0pcRightClickSignal\0"
    "pcListeSignal\0pcHideSignal\0_mac\0"
    "pcCloseSignal\0ip\0pcListeStateSignal\0"
    "pcTcpPortControlSignal\0pcSshPortControlSignal\0"
    "pcVncPortControlSignal\0pcXrdpPortControlSignal\0"
    "pcKilitStateControlSignal\0_kilitstate\0"
    "pcKilitTransparanStateControlSignal\0"
    "_transparankilitstate\0pcIconStateControlSignal\0"
    "_iconstate\0pcMenuSignal\0_slot\0setSize\0"
    "_w\0_h\0_font\0setUser\0_os\0setHostname\0"
    "_hostname\0setKilitControlState\0state\0"
    "setKilitTransparanControlState\0"
    "setIconControlState\0timertcpConnectControlSlot\0"
    "setConnectState\0setCommandButonState\0"
    "setSshState\0setVncState\0setXrdpState\0"
    "setCommandState\0_command\0_commandDetail\0"
    "_commandState\0slotMouseClick\0"
    "slotMouseDoubleClick\0slotSelectPc\0"
    "slotUnselectPc\0slothidePc\0getIpPortStatus\0"
    "ip_\0port\0slotPcAyar"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyPc[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      14,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  184,    2, 0x06 /* Public */,
       4,    0,  187,    2, 0x06 /* Public */,
       5,    0,  188,    2, 0x06 /* Public */,
       6,    1,  189,    2, 0x06 /* Public */,
       8,    2,  192,    2, 0x06 /* Public */,
      10,    0,  197,    2, 0x06 /* Public */,
      11,    2,  198,    2, 0x06 /* Public */,
      12,    2,  203,    2, 0x06 /* Public */,
      13,    2,  208,    2, 0x06 /* Public */,
      14,    2,  213,    2, 0x06 /* Public */,
      15,    3,  218,    2, 0x06 /* Public */,
      17,    3,  225,    2, 0x06 /* Public */,
      19,    3,  232,    2, 0x06 /* Public */,
      21,    3,  239,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      23,    3,  246,    2, 0x0a /* Public */,
      27,    1,  253,    2, 0x0a /* Public */,
      29,    1,  256,    2, 0x0a /* Public */,
      31,    1,  259,    2, 0x0a /* Public */,
      33,    1,  262,    2, 0x0a /* Public */,
      34,    1,  265,    2, 0x0a /* Public */,
      35,    0,  268,    2, 0x0a /* Public */,
      36,    1,  269,    2, 0x0a /* Public */,
      37,    1,  272,    2, 0x0a /* Public */,
      38,    1,  275,    2, 0x0a /* Public */,
      39,    1,  278,    2, 0x0a /* Public */,
      40,    1,  281,    2, 0x0a /* Public */,
      41,    3,  284,    2, 0x0a /* Public */,
      45,    0,  291,    2, 0x0a /* Public */,
      46,    0,  292,    2, 0x0a /* Public */,
      47,    0,  293,    2, 0x0a /* Public */,
      48,    0,  294,    2, 0x0a /* Public */,
      49,    0,  295,    2, 0x0a /* Public */,
      50,    2,  296,    2, 0x08 /* Private */,
      53,    0,  301,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    9,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    3,    9,   16,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    3,    9,   18,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    3,    9,   20,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    9,   22,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString,   24,   25,   26,
    QMetaType::Void, QMetaType::QString,   28,
    QMetaType::Void, QMetaType::QString,   30,
    QMetaType::Void, QMetaType::Bool,   32,
    QMetaType::Void, QMetaType::Bool,   32,
    QMetaType::Void, QMetaType::Bool,   32,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   32,
    QMetaType::Void, QMetaType::Bool,   32,
    QMetaType::Void, QMetaType::Bool,   32,
    QMetaType::Void, QMetaType::Bool,   32,
    QMetaType::Void, QMetaType::Bool,   32,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   42,   43,   44,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString, QMetaType::QString,   51,   52,
    QMetaType::Void,

       0        // eod
};

void MyPc::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyPc *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->pcClickSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->pcRightClickSignal(); break;
        case 2: _t->pcListeSignal(); break;
        case 3: _t->pcHideSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->pcCloseSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->pcListeStateSignal(); break;
        case 6: _t->pcTcpPortControlSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->pcSshPortControlSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->pcVncPortControlSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: _t->pcXrdpPortControlSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 10: _t->pcKilitStateControlSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 11: _t->pcKilitTransparanStateControlSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 12: _t->pcIconStateControlSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 13: _t->pcMenuSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 14: _t->setSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 15: _t->setUser((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: _t->setHostname((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: _t->setKilitControlState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->setKilitTransparanControlState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: _t->setIconControlState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: _t->timertcpConnectControlSlot(); break;
        case 21: _t->setConnectState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->setCommandButonState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->setSshState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->setVncState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: _t->setXrdpState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: _t->setCommandState((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 27: _t->slotMouseClick(); break;
        case 28: _t->slotMouseDoubleClick(); break;
        case 29: _t->slotSelectPc(); break;
        case 30: _t->slotUnselectPc(); break;
        case 31: _t->slothidePc(); break;
        case 32: { QString _r = _t->getIpPortStatus((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 33: _t->slotPcAyar(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyPc::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyPc::pcClickSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MyPc::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyPc::pcRightClickSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MyPc::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyPc::pcListeSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MyPc::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyPc::pcHideSignal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MyPc::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyPc::pcCloseSignal)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MyPc::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyPc::pcListeStateSignal)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MyPc::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyPc::pcTcpPortControlSignal)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (MyPc::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyPc::pcSshPortControlSignal)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (MyPc::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyPc::pcVncPortControlSignal)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (MyPc::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyPc::pcXrdpPortControlSignal)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (MyPc::*)(QString , QString , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyPc::pcKilitStateControlSignal)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (MyPc::*)(QString , QString , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyPc::pcKilitTransparanStateControlSignal)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (MyPc::*)(QString , QString , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyPc::pcIconStateControlSignal)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (MyPc::*)(QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyPc::pcMenuSignal)) {
                *result = 13;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyPc::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_MyPc.data,
    qt_meta_data_MyPc,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyPc::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyPc::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyPc.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MyPc::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 34)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 34;
    }
    return _id;
}

// SIGNAL 0
void MyPc::pcClickSignal(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyPc::pcRightClickSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MyPc::pcListeSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MyPc::pcHideSignal(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MyPc::pcCloseSignal(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MyPc::pcListeStateSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MyPc::pcTcpPortControlSignal(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MyPc::pcSshPortControlSignal(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MyPc::pcVncPortControlSignal(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void MyPc::pcXrdpPortControlSignal(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void MyPc::pcKilitStateControlSignal(QString _t1, QString _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void MyPc::pcKilitTransparanStateControlSignal(QString _t1, QString _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void MyPc::pcIconStateControlSignal(QString _t1, QString _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void MyPc::pcMenuSignal(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
