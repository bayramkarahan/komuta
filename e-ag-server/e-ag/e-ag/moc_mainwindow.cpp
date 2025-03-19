/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mainwindow.h"
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
    QByteArrayData data[161];
    char stringdata0[2155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 8), // "slotVnc0"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 8), // "slotVnc1"
QT_MOC_LITERAL(4, 30, 8), // "slotVnc2"
QT_MOC_LITERAL(5, 39, 6), // "pcMenu"
QT_MOC_LITERAL(6, 46, 8), // "singlepc"
QT_MOC_LITERAL(7, 55, 7), // "readArp"
QT_MOC_LITERAL(8, 63, 19), // "udpSocketServerRead"
QT_MOC_LITERAL(9, 83, 15), // "getIpPortStatus"
QT_MOC_LITERAL(10, 99, 7), // "service"
QT_MOC_LITERAL(11, 107, 11), // "udpSendData"
QT_MOC_LITERAL(12, 119, 9), // "_mesajTur"
QT_MOC_LITERAL(13, 129, 6), // "_mesaj"
QT_MOC_LITERAL(14, 136, 3), // "_ip"
QT_MOC_LITERAL(15, 140, 13), // "layoutTemizle"
QT_MOC_LITERAL(16, 154, 16), // "pcListeStateSlot"
QT_MOC_LITERAL(17, 171, 11), // "newPcDetect"
QT_MOC_LITERAL(18, 183, 16), // "sshCommandWidget"
QT_MOC_LITERAL(19, 200, 8), // "QWidget*"
QT_MOC_LITERAL(20, 209, 12), // "sliderWidget"
QT_MOC_LITERAL(21, 222, 12), // "sshScpWidget"
QT_MOC_LITERAL(22, 235, 11), // "videoWidget"
QT_MOC_LITERAL(23, 247, 12), // "duyuruWidget"
QT_MOC_LITERAL(24, 260, 13), // "ayarlarWidget"
QT_MOC_LITERAL(25, 274, 12), // "volumeWidget"
QT_MOC_LITERAL(26, 287, 11), // "ekranWidget"
QT_MOC_LITERAL(27, 299, 11), // "kilitWidget"
QT_MOC_LITERAL(28, 311, 21), // "kilittransparanWidget"
QT_MOC_LITERAL(29, 333, 9), // "rdpWidget"
QT_MOC_LITERAL(30, 343, 20), // "poweroffrebootWidget"
QT_MOC_LITERAL(31, 364, 12), // "logoutWidget"
QT_MOC_LITERAL(32, 377, 14), // "agProfilWidget"
QT_MOC_LITERAL(33, 392, 13), // "temelIslemler"
QT_MOC_LITERAL(34, 406, 14), // "languageWidget"
QT_MOC_LITERAL(35, 421, 13), // "macListWidget"
QT_MOC_LITERAL(36, 435, 12), // "webBlockSlot"
QT_MOC_LITERAL(37, 448, 7), // "wolSlot"
QT_MOC_LITERAL(38, 456, 14), // "hideShowPcSlot"
QT_MOC_LITERAL(39, 471, 12), // "updateSlider"
QT_MOC_LITERAL(40, 484, 3), // "val"
QT_MOC_LITERAL(41, 488, 3), // "ip_"
QT_MOC_LITERAL(42, 492, 4), // "port"
QT_MOC_LITERAL(43, 497, 17), // "slotServisControl"
QT_MOC_LITERAL(44, 515, 17), // "acountButtonSlot1"
QT_MOC_LITERAL(45, 533, 17), // "acountButtonSlot2"
QT_MOC_LITERAL(46, 551, 16), // "acountButtonSlot"
QT_MOC_LITERAL(47, 568, 10), // "selectSlot"
QT_MOC_LITERAL(48, 579, 12), // "terminalSlot"
QT_MOC_LITERAL(49, 592, 14), // "vncDisplaySlot"
QT_MOC_LITERAL(50, 607, 26), // "pcTcpPortControlSignalSlot"
QT_MOC_LITERAL(51, 634, 4), // "_mac"
QT_MOC_LITERAL(52, 639, 26), // "pcSshPortControlSignalSlot"
QT_MOC_LITERAL(53, 666, 26), // "pcVncPortControlSignalSlot"
QT_MOC_LITERAL(54, 693, 26), // "pcFtpPortControlSignalSlot"
QT_MOC_LITERAL(55, 720, 29), // "pcKilitStateControlSignalSlot"
QT_MOC_LITERAL(56, 750, 10), // "kilitstate"
QT_MOC_LITERAL(57, 761, 39), // "pcKilitTransparanStateControl..."
QT_MOC_LITERAL(58, 801, 20), // "transparankilitstate"
QT_MOC_LITERAL(59, 822, 28), // "pcIconStateControlSignalSlot"
QT_MOC_LITERAL(60, 851, 9), // "iconstate"
QT_MOC_LITERAL(61, 861, 16), // "pcMenuSignalSlot"
QT_MOC_LITERAL(62, 878, 5), // "_slot"
QT_MOC_LITERAL(63, 884, 17), // "cellDoubleClicked"
QT_MOC_LITERAL(64, 902, 4), // "iRow"
QT_MOC_LITERAL(65, 907, 7), // "iColumn"
QT_MOC_LITERAL(66, 915, 25), // "webTableCellDoubleClicked"
QT_MOC_LITERAL(67, 941, 10), // "acountLoad"
QT_MOC_LITERAL(68, 952, 8), // "selectPc"
QT_MOC_LITERAL(69, 961, 15), // "printButtonSlot"
QT_MOC_LITERAL(70, 977, 21), // "macListSaveButtonSlot"
QT_MOC_LITERAL(71, 999, 20), // "ftpConnectButtonSlot"
QT_MOC_LITERAL(72, 1020, 24), // "hostAddressMacButtonSlot"
QT_MOC_LITERAL(73, 1045, 11), // "pcListeSlot"
QT_MOC_LITERAL(74, 1057, 13), // "hostListReset"
QT_MOC_LITERAL(75, 1071, 11), // "arpListInit"
QT_MOC_LITERAL(76, 1083, 17), // "sshCommandAllSlot"
QT_MOC_LITERAL(77, 1101, 3), // "kmt"
QT_MOC_LITERAL(78, 1105, 18), // "sshFileCopyAllSlot"
QT_MOC_LITERAL(79, 1124, 11), // "_sourcePath"
QT_MOC_LITERAL(80, 1136, 11), // "_targetPath"
QT_MOC_LITERAL(81, 1148, 21), // "sshSelectFileCopySlot"
QT_MOC_LITERAL(82, 1170, 18), // "selectFileCopySlot"
QT_MOC_LITERAL(83, 1189, 10), // "_mesajtype"
QT_MOC_LITERAL(84, 1200, 22), // "sshSelectPcCommandSlot"
QT_MOC_LITERAL(85, 1223, 14), // "sshCommandSlot"
QT_MOC_LITERAL(86, 1238, 19), // "pcListeGuncelleSlot"
QT_MOC_LITERAL(87, 1258, 13), // "_ColumnSayisi"
QT_MOC_LITERAL(88, 1272, 3), // "pcw"
QT_MOC_LITERAL(89, 1276, 3), // "pch"
QT_MOC_LITERAL(90, 1280, 17), // "bilgiAlButtonSlot"
QT_MOC_LITERAL(91, 1298, 20), // "ayarKaydetButtonSlot"
QT_MOC_LITERAL(92, 1319, 9), // "mesajSlot"
QT_MOC_LITERAL(93, 1329, 3), // "msg"
QT_MOC_LITERAL(94, 1333, 16), // "listRemoveToList"
QT_MOC_LITERAL(95, 1350, 10), // "sourceList"
QT_MOC_LITERAL(96, 1361, 10), // "removeList"
QT_MOC_LITERAL(97, 1372, 9), // "dataIndex"
QT_MOC_LITERAL(98, 1382, 10), // "listToFile"
QT_MOC_LITERAL(99, 1393, 4), // "list"
QT_MOC_LITERAL(100, 1398, 8), // "filename"
QT_MOC_LITERAL(101, 1407, 10), // "fileToList"
QT_MOC_LITERAL(102, 1418, 4), // "path"
QT_MOC_LITERAL(103, 1423, 11), // "listGetLine"
QT_MOC_LITERAL(104, 1435, 4), // "data"
QT_MOC_LITERAL(105, 1440, 10), // "listRemove"
QT_MOC_LITERAL(106, 1451, 11), // "listReplace"
QT_MOC_LITERAL(107, 1463, 7), // "oldData"
QT_MOC_LITERAL(108, 1471, 7), // "newData"
QT_MOC_LITERAL(109, 1479, 5), // "index"
QT_MOC_LITERAL(110, 1485, 9), // "listMerge"
QT_MOC_LITERAL(111, 1495, 5), // "list1"
QT_MOC_LITERAL(112, 1501, 5), // "list2"
QT_MOC_LITERAL(113, 1507, 11), // "listGetList"
QT_MOC_LITERAL(114, 1519, 8), // "listSort"
QT_MOC_LITERAL(115, 1528, 11), // "getMacForIP"
QT_MOC_LITERAL(116, 1540, 9), // "ipAddress"
QT_MOC_LITERAL(117, 1550, 21), // "sendBroadcastDatagram"
QT_MOC_LITERAL(118, 1572, 11), // "pcClickSlot"
QT_MOC_LITERAL(119, 1584, 13), // "slotWakeOnLan"
QT_MOC_LITERAL(120, 1598, 7), // "slotVnc"
QT_MOC_LITERAL(121, 1606, 4), // "_dsp"
QT_MOC_LITERAL(122, 1611, 11), // "slotVncFlip"
QT_MOC_LITERAL(123, 1623, 5), // "scale"
QT_MOC_LITERAL(124, 1629, 9), // "viewState"
QT_MOC_LITERAL(125, 1639, 15), // "slotVncFlipStop"
QT_MOC_LITERAL(126, 1655, 14), // "slotVncFlipAll"
QT_MOC_LITERAL(127, 1670, 18), // "slotVncFlipAllStop"
QT_MOC_LITERAL(128, 1689, 7), // "slotRdp"
QT_MOC_LITERAL(129, 1697, 7), // "slotFtp"
QT_MOC_LITERAL(130, 1705, 9), // "slotKilit"
QT_MOC_LITERAL(131, 1715, 12), // "slotKilitAll"
QT_MOC_LITERAL(132, 1728, 19), // "slotTransparanKilit"
QT_MOC_LITERAL(133, 1748, 22), // "slotTransparanKilitAll"
QT_MOC_LITERAL(134, 1771, 11), // "slotKilitAc"
QT_MOC_LITERAL(135, 1783, 21), // "slotTransparanKilitAc"
QT_MOC_LITERAL(136, 1805, 14), // "slotKilitAcAll"
QT_MOC_LITERAL(137, 1820, 24), // "slotTransparanKilitAcAll"
QT_MOC_LITERAL(138, 1845, 8), // "slotHide"
QT_MOC_LITERAL(139, 1854, 9), // "slotLogin"
QT_MOC_LITERAL(140, 1864, 10), // "slotLogout"
QT_MOC_LITERAL(141, 1875, 13), // "slotLogoutAll"
QT_MOC_LITERAL(142, 1889, 12), // "slotLoginAll"
QT_MOC_LITERAL(143, 1902, 10), // "slotReboot"
QT_MOC_LITERAL(144, 1913, 13), // "slotRebootAll"
QT_MOC_LITERAL(145, 1927, 12), // "slotPowerOff"
QT_MOC_LITERAL(146, 1940, 15), // "slotPowerOffAll"
QT_MOC_LITERAL(147, 1956, 17), // "slotSelectPcMesaj"
QT_MOC_LITERAL(148, 1974, 4), // "_msg"
QT_MOC_LITERAL(149, 1979, 11), // "slotCommand"
QT_MOC_LITERAL(150, 1991, 4), // "_kmt"
QT_MOC_LITERAL(151, 1996, 19), // "slotPcCommandSelect"
QT_MOC_LITERAL(152, 2016, 17), // "slotSelectCommand"
QT_MOC_LITERAL(153, 2034, 11), // "_runSession"
QT_MOC_LITERAL(154, 2046, 16), // "slotPcCommandAll"
QT_MOC_LITERAL(155, 2063, 8), // "vncState"
QT_MOC_LITERAL(156, 2072, 8), // "ftpState"
QT_MOC_LITERAL(157, 2081, 13), // "slotEkranIzle"
QT_MOC_LITERAL(158, 2095, 19), // "slotEkranIzleDurdur"
QT_MOC_LITERAL(159, 2115, 16), // "slotEkranIzleAll"
QT_MOC_LITERAL(160, 2132, 22) // "slotEkranIzleAllDurdur"

    },
    "MainWindow\0slotVnc0\0\0slotVnc1\0slotVnc2\0"
    "pcMenu\0singlepc\0readArp\0udpSocketServerRead\0"
    "getIpPortStatus\0service\0udpSendData\0"
    "_mesajTur\0_mesaj\0_ip\0layoutTemizle\0"
    "pcListeStateSlot\0newPcDetect\0"
    "sshCommandWidget\0QWidget*\0sliderWidget\0"
    "sshScpWidget\0videoWidget\0duyuruWidget\0"
    "ayarlarWidget\0volumeWidget\0ekranWidget\0"
    "kilitWidget\0kilittransparanWidget\0"
    "rdpWidget\0poweroffrebootWidget\0"
    "logoutWidget\0agProfilWidget\0temelIslemler\0"
    "languageWidget\0macListWidget\0webBlockSlot\0"
    "wolSlot\0hideShowPcSlot\0updateSlider\0"
    "val\0ip_\0port\0slotServisControl\0"
    "acountButtonSlot1\0acountButtonSlot2\0"
    "acountButtonSlot\0selectSlot\0terminalSlot\0"
    "vncDisplaySlot\0pcTcpPortControlSignalSlot\0"
    "_mac\0pcSshPortControlSignalSlot\0"
    "pcVncPortControlSignalSlot\0"
    "pcFtpPortControlSignalSlot\0"
    "pcKilitStateControlSignalSlot\0kilitstate\0"
    "pcKilitTransparanStateControlSignalSlot\0"
    "transparankilitstate\0pcIconStateControlSignalSlot\0"
    "iconstate\0pcMenuSignalSlot\0_slot\0"
    "cellDoubleClicked\0iRow\0iColumn\0"
    "webTableCellDoubleClicked\0acountLoad\0"
    "selectPc\0printButtonSlot\0macListSaveButtonSlot\0"
    "ftpConnectButtonSlot\0hostAddressMacButtonSlot\0"
    "pcListeSlot\0hostListReset\0arpListInit\0"
    "sshCommandAllSlot\0kmt\0sshFileCopyAllSlot\0"
    "_sourcePath\0_targetPath\0sshSelectFileCopySlot\0"
    "selectFileCopySlot\0_mesajtype\0"
    "sshSelectPcCommandSlot\0sshCommandSlot\0"
    "pcListeGuncelleSlot\0_ColumnSayisi\0pcw\0"
    "pch\0bilgiAlButtonSlot\0ayarKaydetButtonSlot\0"
    "mesajSlot\0msg\0listRemoveToList\0"
    "sourceList\0removeList\0dataIndex\0"
    "listToFile\0list\0filename\0fileToList\0"
    "path\0listGetLine\0data\0listRemove\0"
    "listReplace\0oldData\0newData\0index\0"
    "listMerge\0list1\0list2\0listGetList\0"
    "listSort\0getMacForIP\0ipAddress\0"
    "sendBroadcastDatagram\0pcClickSlot\0"
    "slotWakeOnLan\0slotVnc\0_dsp\0slotVncFlip\0"
    "scale\0viewState\0slotVncFlipStop\0"
    "slotVncFlipAll\0slotVncFlipAllStop\0"
    "slotRdp\0slotFtp\0slotKilit\0slotKilitAll\0"
    "slotTransparanKilit\0slotTransparanKilitAll\0"
    "slotKilitAc\0slotTransparanKilitAc\0"
    "slotKilitAcAll\0slotTransparanKilitAcAll\0"
    "slotHide\0slotLogin\0slotLogout\0"
    "slotLogoutAll\0slotLoginAll\0slotReboot\0"
    "slotRebootAll\0slotPowerOff\0slotPowerOffAll\0"
    "slotSelectPcMesaj\0_msg\0slotCommand\0"
    "_kmt\0slotPcCommandSelect\0slotSelectCommand\0"
    "_runSession\0slotPcCommandAll\0vncState\0"
    "ftpState\0slotEkranIzle\0slotEkranIzleDurdur\0"
    "slotEkranIzleAll\0slotEkranIzleAllDurdur"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
     117,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  599,    2, 0x0a /* Public */,
       3,    0,  600,    2, 0x0a /* Public */,
       4,    0,  601,    2, 0x0a /* Public */,
       5,    1,  602,    2, 0x08 /* Private */,
       7,    0,  605,    2, 0x08 /* Private */,
       8,    0,  606,    2, 0x08 /* Private */,
       9,    1,  607,    2, 0x08 /* Private */,
      11,    3,  610,    2, 0x08 /* Private */,
      15,    0,  617,    2, 0x08 /* Private */,
      16,    0,  618,    2, 0x08 /* Private */,
      17,    0,  619,    2, 0x08 /* Private */,
      18,    0,  620,    2, 0x08 /* Private */,
      20,    0,  621,    2, 0x08 /* Private */,
      21,    0,  622,    2, 0x08 /* Private */,
      22,    0,  623,    2, 0x08 /* Private */,
      23,    0,  624,    2, 0x08 /* Private */,
      24,    0,  625,    2, 0x08 /* Private */,
      25,    0,  626,    2, 0x08 /* Private */,
      26,    0,  627,    2, 0x08 /* Private */,
      27,    0,  628,    2, 0x08 /* Private */,
      28,    0,  629,    2, 0x08 /* Private */,
      29,    0,  630,    2, 0x08 /* Private */,
      30,    0,  631,    2, 0x08 /* Private */,
      31,    0,  632,    2, 0x08 /* Private */,
      32,    0,  633,    2, 0x08 /* Private */,
      33,    0,  634,    2, 0x08 /* Private */,
      34,    0,  635,    2, 0x08 /* Private */,
      35,    0,  636,    2, 0x08 /* Private */,
      36,    0,  637,    2, 0x08 /* Private */,
      37,    0,  638,    2, 0x08 /* Private */,
      38,    0,  639,    2, 0x08 /* Private */,
      39,    1,  640,    2, 0x08 /* Private */,
       9,    2,  643,    2, 0x08 /* Private */,
      43,    0,  648,    2, 0x08 /* Private */,
      44,    0,  649,    2, 0x08 /* Private */,
      45,    0,  650,    2, 0x08 /* Private */,
      46,    0,  651,    2, 0x08 /* Private */,
      47,    0,  652,    2, 0x08 /* Private */,
      48,    0,  653,    2, 0x08 /* Private */,
      49,    0,  654,    2, 0x08 /* Private */,
      50,    2,  655,    2, 0x08 /* Private */,
      52,    2,  660,    2, 0x08 /* Private */,
      53,    2,  665,    2, 0x08 /* Private */,
      54,    2,  670,    2, 0x08 /* Private */,
      55,    3,  675,    2, 0x08 /* Private */,
      57,    3,  682,    2, 0x08 /* Private */,
      59,    3,  689,    2, 0x08 /* Private */,
      61,    3,  696,    2, 0x08 /* Private */,
      63,    2,  703,    2, 0x08 /* Private */,
      66,    2,  708,    2, 0x08 /* Private */,
      67,    0,  713,    2, 0x08 /* Private */,
      68,    0,  714,    2, 0x08 /* Private */,
      69,    0,  715,    2, 0x08 /* Private */,
      70,    0,  716,    2, 0x08 /* Private */,
      71,    0,  717,    2, 0x08 /* Private */,
      72,    0,  718,    2, 0x08 /* Private */,
      73,    0,  719,    2, 0x08 /* Private */,
      74,    0,  720,    2, 0x08 /* Private */,
      75,    0,  721,    2, 0x08 /* Private */,
      76,    1,  722,    2, 0x08 /* Private */,
      78,    2,  725,    2, 0x08 /* Private */,
      81,    2,  730,    2, 0x08 /* Private */,
      82,    4,  735,    2, 0x08 /* Private */,
      84,    1,  744,    2, 0x08 /* Private */,
      85,    2,  747,    2, 0x08 /* Private */,
      86,    3,  752,    2, 0x08 /* Private */,
      90,    0,  759,    2, 0x08 /* Private */,
      91,    0,  760,    2, 0x08 /* Private */,
      92,    1,  761,    2, 0x08 /* Private */,
      94,    3,  764,    2, 0x08 /* Private */,
      98,    2,  771,    2, 0x08 /* Private */,
     101,    2,  776,    2, 0x08 /* Private */,
     103,    2,  781,    2, 0x08 /* Private */,
     105,    2,  786,    2, 0x08 /* Private */,
     106,    4,  791,    2, 0x08 /* Private */,
     110,    3,  800,    2, 0x08 /* Private */,
     113,    3,  807,    2, 0x08 /* Private */,
     114,    2,  814,    2, 0x08 /* Private */,
     115,    1,  819,    2, 0x08 /* Private */,
     117,    0,  822,    2, 0x08 /* Private */,
     118,    1,  823,    2, 0x08 /* Private */,
     119,    2,  826,    2, 0x08 /* Private */,
     120,    1,  831,    2, 0x08 /* Private */,
     122,    2,  834,    2, 0x08 /* Private */,
     125,    0,  839,    2, 0x08 /* Private */,
     126,    2,  840,    2, 0x08 /* Private */,
     127,    0,  845,    2, 0x08 /* Private */,
     128,    0,  846,    2, 0x08 /* Private */,
     129,    0,  847,    2, 0x08 /* Private */,
     130,    0,  848,    2, 0x08 /* Private */,
     131,    0,  849,    2, 0x08 /* Private */,
     132,    0,  850,    2, 0x08 /* Private */,
     133,    0,  851,    2, 0x08 /* Private */,
     134,    0,  852,    2, 0x08 /* Private */,
     135,    0,  853,    2, 0x08 /* Private */,
     136,    0,  854,    2, 0x08 /* Private */,
     137,    0,  855,    2, 0x08 /* Private */,
     138,    0,  856,    2, 0x08 /* Private */,
     139,    0,  857,    2, 0x08 /* Private */,
     140,    0,  858,    2, 0x08 /* Private */,
     141,    0,  859,    2, 0x08 /* Private */,
     142,    0,  860,    2, 0x08 /* Private */,
     143,    0,  861,    2, 0x08 /* Private */,
     144,    0,  862,    2, 0x08 /* Private */,
     145,    0,  863,    2, 0x08 /* Private */,
     146,    0,  864,    2, 0x08 /* Private */,
     147,    1,  865,    2, 0x08 /* Private */,
     149,    1,  868,    2, 0x08 /* Private */,
     151,    1,  871,    2, 0x08 /* Private */,
     152,    2,  874,    2, 0x08 /* Private */,
     154,    1,  879,    2, 0x08 /* Private */,
     155,    1,  882,    2, 0x08 /* Private */,
     156,    1,  885,    2, 0x08 /* Private */,
     157,    0,  888,    2, 0x08 /* Private */,
     158,    0,  889,    2, 0x08 /* Private */,
     159,    0,  890,    2, 0x08 /* Private */,
     160,    0,  891,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::QStringList,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   12,   13,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 19,
    0x80000000 | 19,
    0x80000000 | 19,
    0x80000000 | 19,
    0x80000000 | 19,
    0x80000000 | 19,
    0x80000000 | 19,
    0x80000000 | 19,
    0x80000000 | 19,
    0x80000000 | 19,
    0x80000000 | 19,
    0x80000000 | 19,
    0x80000000 | 19,
    0x80000000 | 19,
    0x80000000 | 19,
    0x80000000 | 19,
    0x80000000 | 19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   40,
    QMetaType::QString, QMetaType::QString, QMetaType::QString,   41,   42,
    QMetaType::Void,
    0x80000000 | 19,
    0x80000000 | 19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   51,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   51,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   51,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   51,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,   51,   14,   56,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,   51,   14,   58,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,   51,   14,   60,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   51,   14,   62,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   64,   65,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   64,   65,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QStringList,
    QMetaType::Void, QMetaType::QString,   77,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   79,   80,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   79,   80,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   83,   14,   79,   80,
    QMetaType::Void, QMetaType::QString,   77,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   77,   14,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   87,   88,   89,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   93,
    QMetaType::QStringList, QMetaType::QStringList, QMetaType::QStringList, QMetaType::Int,   95,   96,   97,
    QMetaType::Void, QMetaType::QStringList, QMetaType::QString,   99,  100,
    QMetaType::QStringList, QMetaType::QString, QMetaType::QString,  100,  102,
    QMetaType::QString, QMetaType::QStringList, QMetaType::QString,   99,  104,
    QMetaType::QStringList, QMetaType::QStringList, QMetaType::QString,   99,  104,
    QMetaType::QStringList, QMetaType::QStringList, QMetaType::QString, QMetaType::QString, QMetaType::Int,   99,  107,  108,  109,
    QMetaType::QStringList, QMetaType::QStringList, QMetaType::QStringList, QMetaType::Int,  111,  112,   97,
    QMetaType::QStringList, QMetaType::QStringList, QMetaType::QString, QMetaType::Int,   99,  104,  109,
    QMetaType::QStringList, QMetaType::QStringList, QMetaType::Int,   99,   97,
    QMetaType::QString, QMetaType::QString,  116,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   51,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   14,   51,
    QMetaType::Void, QMetaType::QString,  121,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  123,  124,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  123,  124,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  148,
    QMetaType::Void, QMetaType::QString,  150,
    QMetaType::Void, QMetaType::QString,  150,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  153,  150,
    QMetaType::Void, QMetaType::QString,  150,
    QMetaType::Bool, QMetaType::QString,   51,
    QMetaType::Bool, QMetaType::QString,   51,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->slotVnc0(); break;
        case 1: _t->slotVnc1(); break;
        case 2: _t->slotVnc2(); break;
        case 3: _t->pcMenu((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: { QStringList _r = _t->readArp();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->udpSocketServerRead(); break;
        case 6: { QString _r = _t->getIpPortStatus((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->udpSendData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 8: _t->layoutTemizle(); break;
        case 9: _t->pcListeStateSlot(); break;
        case 10: _t->newPcDetect(); break;
        case 11: { QWidget* _r = _t->sshCommandWidget();
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = std::move(_r); }  break;
        case 12: { QWidget* _r = _t->sliderWidget();
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = std::move(_r); }  break;
        case 13: { QWidget* _r = _t->sshScpWidget();
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = std::move(_r); }  break;
        case 14: { QWidget* _r = _t->videoWidget();
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = std::move(_r); }  break;
        case 15: { QWidget* _r = _t->duyuruWidget();
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = std::move(_r); }  break;
        case 16: { QWidget* _r = _t->ayarlarWidget();
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = std::move(_r); }  break;
        case 17: { QWidget* _r = _t->volumeWidget();
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = std::move(_r); }  break;
        case 18: { QWidget* _r = _t->ekranWidget();
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = std::move(_r); }  break;
        case 19: { QWidget* _r = _t->kilitWidget();
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = std::move(_r); }  break;
        case 20: { QWidget* _r = _t->kilittransparanWidget();
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = std::move(_r); }  break;
        case 21: { QWidget* _r = _t->rdpWidget();
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = std::move(_r); }  break;
        case 22: { QWidget* _r = _t->poweroffrebootWidget();
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = std::move(_r); }  break;
        case 23: { QWidget* _r = _t->logoutWidget();
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = std::move(_r); }  break;
        case 24: { QWidget* _r = _t->agProfilWidget();
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = std::move(_r); }  break;
        case 25: { QWidget* _r = _t->temelIslemler();
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = std::move(_r); }  break;
        case 26: { QWidget* _r = _t->languageWidget();
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = std::move(_r); }  break;
        case 27: { QWidget* _r = _t->macListWidget();
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = std::move(_r); }  break;
        case 28: _t->webBlockSlot(); break;
        case 29: _t->wolSlot(); break;
        case 30: _t->hideShowPcSlot(); break;
        case 31: _t->updateSlider((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: { QString _r = _t->getIpPortStatus((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 33: _t->slotServisControl(); break;
        case 34: { QWidget* _r = _t->acountButtonSlot1();
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = std::move(_r); }  break;
        case 35: { QWidget* _r = _t->acountButtonSlot2();
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = std::move(_r); }  break;
        case 36: _t->acountButtonSlot(); break;
        case 37: _t->selectSlot(); break;
        case 38: _t->terminalSlot(); break;
        case 39: _t->vncDisplaySlot(); break;
        case 40: _t->pcTcpPortControlSignalSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 41: _t->pcSshPortControlSignalSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 42: _t->pcVncPortControlSignalSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 43: _t->pcFtpPortControlSignalSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 44: _t->pcKilitStateControlSignalSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 45: _t->pcKilitTransparanStateControlSignalSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 46: _t->pcIconStateControlSignalSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 47: _t->pcMenuSignalSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 48: _t->cellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 49: _t->webTableCellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 50: _t->acountLoad(); break;
        case 51: _t->selectPc(); break;
        case 52: _t->printButtonSlot(); break;
        case 53: _t->macListSaveButtonSlot(); break;
        case 54: _t->ftpConnectButtonSlot(); break;
        case 55: _t->hostAddressMacButtonSlot(); break;
        case 56: _t->pcListeSlot(); break;
        case 57: _t->hostListReset(); break;
        case 58: { QStringList _r = _t->arpListInit();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 59: _t->sshCommandAllSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 60: _t->sshFileCopyAllSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 61: _t->sshSelectFileCopySlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 62: _t->selectFileCopySlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 63: _t->sshSelectPcCommandSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 64: _t->sshCommandSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 65: _t->pcListeGuncelleSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 66: _t->bilgiAlButtonSlot(); break;
        case 67: _t->ayarKaydetButtonSlot(); break;
        case 68: _t->mesajSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 69: { QStringList _r = _t->listRemoveToList((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 70: _t->listToFile((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 71: { QStringList _r = _t->fileToList((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 72: { QString _r = _t->listGetLine((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 73: { QStringList _r = _t->listRemove((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 74: { QStringList _r = _t->listReplace((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 75: { QStringList _r = _t->listMerge((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 76: { QStringList _r = _t->listGetList((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 77: { QStringList _r = _t->listSort((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 78: { QString _r = _t->getMacForIP((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 79: _t->sendBroadcastDatagram(); break;
        case 80: _t->pcClickSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 81: _t->slotWakeOnLan((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 82: _t->slotVnc((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 83: _t->slotVncFlip((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 84: _t->slotVncFlipStop(); break;
        case 85: _t->slotVncFlipAll((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 86: _t->slotVncFlipAllStop(); break;
        case 87: _t->slotRdp(); break;
        case 88: _t->slotFtp(); break;
        case 89: _t->slotKilit(); break;
        case 90: _t->slotKilitAll(); break;
        case 91: _t->slotTransparanKilit(); break;
        case 92: _t->slotTransparanKilitAll(); break;
        case 93: _t->slotKilitAc(); break;
        case 94: _t->slotTransparanKilitAc(); break;
        case 95: _t->slotKilitAcAll(); break;
        case 96: _t->slotTransparanKilitAcAll(); break;
        case 97: _t->slotHide(); break;
        case 98: _t->slotLogin(); break;
        case 99: _t->slotLogout(); break;
        case 100: _t->slotLogoutAll(); break;
        case 101: _t->slotLoginAll(); break;
        case 102: _t->slotReboot(); break;
        case 103: _t->slotRebootAll(); break;
        case 104: _t->slotPowerOff(); break;
        case 105: _t->slotPowerOffAll(); break;
        case 106: _t->slotSelectPcMesaj((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 107: _t->slotCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 108: _t->slotPcCommandSelect((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 109: _t->slotSelectCommand((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 110: _t->slotPcCommandAll((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 111: { bool _r = _t->vncState((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 112: { bool _r = _t->ftpState((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 113: _t->slotEkranIzle(); break;
        case 114: _t->slotEkranIzleDurdur(); break;
        case 115: _t->slotEkranIzleAll(); break;
        case 116: _t->slotEkranIzleAllDurdur(); break;
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
        if (_id < 117)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 117;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 117)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 117;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
