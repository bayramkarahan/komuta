/*****************************************************************************
 *   Copyright (C) 2020 by Bayram KARAHAN                                    *
 *   <bayramk@gmail.com>                                                     *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 3 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .          *
 *****************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QList>
#include <QMainWindow>
#include<QTableWidget>
#include<QPushButton>
#include<QDebug>
#include<QTimer>
#include<QProgressBar>
#include<QLabel>
#include<QLineEdit>
#include<QGridLayout>
#include<QFileDialog>
#include<QTextEdit>
#include <QMessageBox>
#include <QMetaType>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>
#include<QComboBox>
#include<QTextBrowser>
#include<QPlainTextEdit>
#include<QUdpSocket>
#include<QMenu>
#include <QStyle>
#include<mypc.h>
#include<QPalette>
#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <QVBoxLayout>
#include<QDialogButtonBox>
#include <QPrinter>
#include<QPrintDialog>
#include<QProcess>
#include<QTabWidget>
#include<QScrollArea>
#include<QStatusBar>
#include<pcdata.h>
#include<QRadioButton>
#include<QButtonGroup>
#include <QRubberBand>
#include "scdimgclient.h"
#include<QInputDialog>
#include <gst/gst.h>
#include <iostream>
#include<Database.h>
#include<qtermwidget5/qtermwidget.h>
#include<CustomInputDialog.h>
namespace Ui {
class MainWindow;
}
class PcRecord
{
public:
    QString ip;
    QString mac;
    QString name;
    QString vncPort;
    QString hostname;
    bool pcState;
    bool sshState;
    bool ftpState;
    bool vncState;
    bool connectState;
    bool visibleState;
};

class IpMac
{
public:
    QString ip;
    QString mac;
    QString broadcast;

};

class NetProfil
{
public:
    QString networkIndex;
    bool selectedNetworkProfil;
    QString networkName;
    QString serverAddress;
    QString networkBroadCastAddress;
    QString networkTcpPort;
    QString ftpPort;
    QString rootPath;
    QString language;
    bool lockScreenState;
    bool webblockState;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool mouseClickState=false;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
      QString _display="2";
      QPoint origin;
      QRubberBand *rubberBand;
      QList<IpMac> interfaceList;
      QList<NetProfil> NetProfilList;

 signals:

protected:
     void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
     void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
     void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
     void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
     void paintEvent(QPaintEvent* event);
 public slots:
     void slotVnc0();
     void slotVnc1();
     void slotVnc2();
     static  bool karsilastirMyPc(const MyPc *mypc1, const MyPc *mypc2);
     void networkProfilLoad();
     QString getSeatId();
     QString getSessionInfo(QString id, QString parametre);
private slots:
     QString getActiveUserName();
     void pcMenu(bool singlepc);
     QStringList readArp();
     void udpSocketServerRead();
     QString getIpPortStatus(QString service);
     void udpSendData(QString _mesajTur,QString _mesaj,QString _ip);
     void pcDetect();
     QWidget *commandWidget();
     QWidget *sliderWidget();

     QWidget *fileWidget();
     QWidget *videoWidget();
     QWidget *messageWidget();
     QWidget *settingsWidget();
     QWidget* volumeWidget();

    QWidget *ekranWidget();
    QWidget *kilitWidget();
    QWidget *kilittransparanWidget();
    QWidget *rdpWidget();
    QWidget *poweroffrebootWidget();
    QWidget *logoutWidget();


    QWidget *baseWidget();
    QWidget *languageWidget();
    QWidget *HostListWidget();
    void webBlockWidget();
    void wolWidget();
    void hideShowPcSlot();
    void networkProfil();
    void updateSlider(int val);
    QString getIpPortStatus(QString ip_,QString port);

    void selectSlot();

    void vncDisplaySlot();


    void selectPc();
    void hostAddressMacButtonSlot();
     void selectFileCopySlot(QString _mesajtype,QString _ip,QString _sourcePath, QString _targetPath);

    void pcListeGuncelleSlotnew(QString mission);
    void pcHideSignalSlot(QString _mac);

    void bilgiAlButtonSlot();

    void pcRightClickSignalSlot();
    void mesajSlot(QString msg);


QString getMacForIP(QString ipAddress);

    void pcClickSlot(QString _mac);
    void slotWakeOnLan(QString _ip,QString _mac);

    void slotVnc(QString _dsp);
    void slotVncFlip(QString scale,QString viewState);
    void slotVncFlipStop();
    void slotVncFlipAll(QString scale,QString viewState);
    void slotVncFlipAllStop();
    void slotRdp();
    void slotTerminal();
    void slotKilit();
    void slotTransparanKilit();
    void slotKilitAc();
    void slotTransparanKilitAc();
    void slotLogin();
    void slotLogout();
    void slotLogoutAll();

    void slotReboot();
    void slotRebootAll();
    void slotPowerOff();
    void slotPowerOffAll();
    void slotCommand(QString _kmt);
    void slotPcCommandSelect(QString _kmt);

    void slotPcCommandAll(QString _kmt);
    void slotEkranIzle();
    void slotEkranIzleDurdur();
    void slotEkranIzleAll();
    void slotEkranIzleAllDurdur();
    void slotPcEkle(QString _ip,QString _mac);
    void slotPcSil(int _index,QString _ip,QString _mac);

private:
    bool pcrightmenu;
    QMenu *pContextMenu;
    QString publickey;
    QStatusBar *statusbar;
    QWidget *mainWidget;
    QLabel *sliderValuelabel;
    QWidget *selectWidget;
    QWidget *ustMenuWidget;
    QSlider *slider;

    bool tamReset=false;
    QWidget *maclistwidget;
    //QTableWidget *tablewidget;
    QComboBox * ekranScale;
    int gercekliste;
    int pcopencount;
    QScrollArea *scrollArea;
    QString font="12";
    QTimer *newPcDetectTimer;
    int tabWidgetIndex=0;
    QLabel *hostsCountLabel;

    QTabWidget *tabwid;
    QTabWidget *tabwidprofil;
    bool streamState;
    QProcess videoProcess;

     //QTableWidget *twl;

    int en,boy;

    QGridLayout *layout;

    QPushButton *ayarKaydetButton;
    QToolButton *hostTableListButton;
    QToolButton *hostTableListNameFindButton;
    QToolButton *vncConnectButton;
    QToolButton *ftpConnectButton;
    QToolButton *hostAddressButton;
    QToolButton *macListeButton;
    QToolButton *settingButton;
    QToolButton* listePcButton;
    QToolButton* sshButton;
    QToolButton *commandExampleButton;
    QToolButton *commandExecuteButton;
    QToolButton *commandExecuteAllButton;
    QToolButton *fileSelectButton;
    QToolButton *fileCopyButton;
    QToolButton *fileCopyInstallButton;
    QToolButton *fileCopyInstallScriptButton;

    QToolButton *fileCopyAllButton;
    QToolButton *sshAramaButton;
    QToolButton *vncAramaButton;

    QToolButton *sendMessageButton;
    QToolButton *sendMessageAllButton;

    QToolButton *tcpekranImageButton;
    QToolButton *tcpekranKilitButton;
    QToolButton *tcpduyuruMesajButton;
    QToolButton *tcppcKapatButton;
    QToolButton *tcppcRebootButton;

    QToolButton *tcpcommandsendMessageButton;
    QToolButton *tcpcommandsessionButton;
    QToolButton *bilgiAlButton;


    QToolButton *fileTransferButton;

     QLabel *pcIp;
    QLabel *pcMac;
    QLabel *pcName;
    QLabel *pcIplbl;
    QLabel *pcNamelbl;
    QLabel *pcMaclbl;
    QLabel *pcUserlbl;
    QLabel *pcScreenlbl;
    QLabel *pcSystemlbl;


    QLabel *socketNumberLabel;
    QLabel *destlabel;

    /*****************************************************************/
    bool webblockstate;
    /*****************************************************************/
    QLineEdit *status;
    QWidget *hostListe;
    QPalette *palette;

    QTextEdit *te;
//    QTcpServer* m_server;
    QList<QTcpSocket*> connection_list;
    QComboBox *comboBox_receiver;
    QLineEdit *lineEdit_message;
    QPlainTextEdit *textBrowser_receivedMessages;
    QUdpSocket *udpSocketSend = nullptr;
    QTimer *timerUdpSocketSend;
    QString selectMac="";
    QList<MyPc*> onlinePcList;
     QMenu *transparanKilitMenu();
     QMenu *kilitMenu();
     QMenu *poweroffRebootMenu();

     QMenu *duyuruMesajMenu();
     QMenu *ekranImageMenu();
     QMenu *komutMenu();

     QMenu *rdpMenu();
     QMenu *commandExampleMenu();
     QMenu *sessionMenu();
     QMenu *languageMenu();
     QStringList listQmFiles(const QString &directory);
    QUdpSocket *udpSocketGet;
    QString localDir;
    QLineEdit *commandFileL;
    QRadioButton *rb1;
    QRadioButton *rb2;
    bool udpSendDataStatus=false;
    GstElement *audio_pipeline;
    GstElement *video_pipeline;
    bool firstRun=false; 
  };

#endif // MAINWINDOW_H
