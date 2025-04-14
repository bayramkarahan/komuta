/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[26];
    char stringdata0[300];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 17), // "udpConsoleGetSlot"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 17), // "networkProfilLoad"
QT_MOC_LITERAL(4, 48, 21), // "tcpMessageControlSlot"
QT_MOC_LITERAL(5, 70, 5), // "_data"
QT_MOC_LITERAL(6, 76, 12), // "WidgetClosed"
QT_MOC_LITERAL(7, 89, 13), // "iconActivated"
QT_MOC_LITERAL(8, 103, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(9, 137, 5), // "gizle"
QT_MOC_LITERAL(10, 143, 12), // "myMessageBox"
QT_MOC_LITERAL(11, 156, 6), // "baslik"
QT_MOC_LITERAL(12, 163, 5), // "mesaj"
QT_MOC_LITERAL(13, 169, 4), // "evet"
QT_MOC_LITERAL(14, 174, 5), // "hayir"
QT_MOC_LITERAL(15, 180, 5), // "tamam"
QT_MOC_LITERAL(16, 186, 17), // "QMessageBox::Icon"
QT_MOC_LITERAL(17, 204, 4), // "icon"
QT_MOC_LITERAL(18, 209, 24), // "hostAddressMacButtonSlot"
QT_MOC_LITERAL(19, 234, 10), // "widgetShow"
QT_MOC_LITERAL(20, 245, 14), // "getSessionInfo"
QT_MOC_LITERAL(21, 260, 2), // "id"
QT_MOC_LITERAL(22, 263, 9), // "parametre"
QT_MOC_LITERAL(23, 273, 9), // "getSeatId"
QT_MOC_LITERAL(24, 283, 12), // "stringToBool"
QT_MOC_LITERAL(25, 296, 3) // "str"

    },
    "MainWindow\0udpConsoleGetSlot\0\0"
    "networkProfilLoad\0tcpMessageControlSlot\0"
    "_data\0WidgetClosed\0iconActivated\0"
    "QSystemTrayIcon::ActivationReason\0"
    "gizle\0myMessageBox\0baslik\0mesaj\0evet\0"
    "hayir\0tamam\0QMessageBox::Icon\0icon\0"
    "hostAddressMacButtonSlot\0widgetShow\0"
    "getSessionInfo\0id\0parametre\0getSeatId\0"
    "stringToBool\0str"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x0a /* Public */,
       3,    0,   75,    2, 0x0a /* Public */,
       4,    1,   76,    2, 0x0a /* Public */,
       6,    0,   79,    2, 0x0a /* Public */,
       7,    1,   80,    2, 0x0a /* Public */,
       9,    0,   83,    2, 0x0a /* Public */,
      10,    6,   84,    2, 0x0a /* Public */,
      18,    0,   97,    2, 0x0a /* Public */,
      19,    0,   98,    2, 0x0a /* Public */,
      20,    2,   99,    2, 0x0a /* Public */,
      23,    0,  104,    2, 0x0a /* Public */,
      24,    1,  105,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, 0x80000000 | 16,   11,   12,   13,   14,   15,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString, QMetaType::QString,   21,   22,
    QMetaType::QString,
    QMetaType::Bool, QMetaType::QString,   25,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->udpConsoleGetSlot(); break;
        case 1: _t->networkProfilLoad(); break;
        case 2: _t->tcpMessageControlSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->WidgetClosed(); break;
        case 4: _t->iconActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 5: _t->gizle(); break;
        case 6: { QString _r = _t->myMessageBox((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QMessageBox::Icon(*)>(_a[6])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->hostAddressMacButtonSlot(); break;
        case 8: _t->widgetShow(); break;
        case 9: { QString _r = _t->getSessionInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 10: { QString _r = _t->getSeatId();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 11: { bool _r = _t->stringToBool((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
