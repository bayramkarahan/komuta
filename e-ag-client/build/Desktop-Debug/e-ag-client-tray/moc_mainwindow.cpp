/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../e-ag-client-tray/mainwindow.h"
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
    QByteArrayData data[27];
    char stringdata0[317];
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
QT_MOC_LITERAL(3, 30, 16), // "udpServerGetSlot"
QT_MOC_LITERAL(4, 47, 17), // "networkProfilLoad"
QT_MOC_LITERAL(5, 65, 21), // "tcpMessageControlSlot"
QT_MOC_LITERAL(6, 87, 5), // "_data"
QT_MOC_LITERAL(7, 93, 12), // "WidgetClosed"
QT_MOC_LITERAL(8, 106, 13), // "iconActivated"
QT_MOC_LITERAL(9, 120, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(10, 154, 5), // "gizle"
QT_MOC_LITERAL(11, 160, 12), // "myMessageBox"
QT_MOC_LITERAL(12, 173, 6), // "baslik"
QT_MOC_LITERAL(13, 180, 5), // "mesaj"
QT_MOC_LITERAL(14, 186, 4), // "evet"
QT_MOC_LITERAL(15, 191, 5), // "hayir"
QT_MOC_LITERAL(16, 197, 5), // "tamam"
QT_MOC_LITERAL(17, 203, 17), // "QMessageBox::Icon"
QT_MOC_LITERAL(18, 221, 4), // "icon"
QT_MOC_LITERAL(19, 226, 24), // "hostAddressMacButtonSlot"
QT_MOC_LITERAL(20, 251, 10), // "widgetShow"
QT_MOC_LITERAL(21, 262, 14), // "getSessionInfo"
QT_MOC_LITERAL(22, 277, 2), // "id"
QT_MOC_LITERAL(23, 280, 9), // "parametre"
QT_MOC_LITERAL(24, 290, 9), // "getSeatId"
QT_MOC_LITERAL(25, 300, 12), // "stringToBool"
QT_MOC_LITERAL(26, 313, 3) // "str"

    },
    "MainWindow\0udpConsoleGetSlot\0\0"
    "udpServerGetSlot\0networkProfilLoad\0"
    "tcpMessageControlSlot\0_data\0WidgetClosed\0"
    "iconActivated\0QSystemTrayIcon::ActivationReason\0"
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
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a /* Public */,
       3,    0,   80,    2, 0x0a /* Public */,
       4,    0,   81,    2, 0x0a /* Public */,
       5,    1,   82,    2, 0x0a /* Public */,
       7,    0,   85,    2, 0x0a /* Public */,
       8,    1,   86,    2, 0x0a /* Public */,
      10,    0,   89,    2, 0x0a /* Public */,
      11,    6,   90,    2, 0x0a /* Public */,
      19,    0,  103,    2, 0x0a /* Public */,
      20,    0,  104,    2, 0x0a /* Public */,
      21,    2,  105,    2, 0x0a /* Public */,
      24,    0,  110,    2, 0x0a /* Public */,
      25,    1,  111,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, 0x80000000 | 17,   12,   13,   14,   15,   16,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString, QMetaType::QString,   22,   23,
    QMetaType::QString,
    QMetaType::Bool, QMetaType::QString,   26,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->udpConsoleGetSlot(); break;
        case 1: _t->udpServerGetSlot(); break;
        case 2: _t->networkProfilLoad(); break;
        case 3: _t->tcpMessageControlSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->WidgetClosed(); break;
        case 5: _t->iconActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 6: _t->gizle(); break;
        case 7: { QString _r = _t->myMessageBox((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QMessageBox::Icon(*)>(_a[6])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->hostAddressMacButtonSlot(); break;
        case 9: _t->widgetShow(); break;
        case 10: { QString _r = _t->getSessionInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 11: { QString _r = _t->getSeatId();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 12: { bool _r = _t->stringToBool((*reinterpret_cast< const QString(*)>(_a[1])));
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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
