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

#include "mainwindow.h"
#include<QTabWidget>
#include<QLabel>
#include<QGridLayout>
#include<QPushButton>
#include<QFile>
#include<QFileDialog>
#include<QRegularExpression>
#include<QTimeEdit>
#include<QDate>
#include<QTimer>
#include<QTime>
#include<QMessageBox>
#include<QApplication>
#include<QDesktopWidget>
#include<QMenu>
#include<QCloseEvent>
#include<QProcess>
#include<QAuthenticator>
#include<QApplication>
#include <stdio.h>
#include <QtCore/QCoreApplication>
#include <gst/gst.h>
#include <iostream>
#include<gst/gsterror.h>
#include<Database.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
 {
    localDir="/usr/share/e-ag/";
    networkProfilLoad();
     udpBroadCastSend = new QUdpSocket();
    /*******************************************************************/
    webblockcb= new QCheckBox("Her Açılışta Web Sitelerini Engelle.");

    ekran=new Ekran();
    gelenKomut=new QLabel("-------------------");

    trayIcon=new QSystemTrayIcon(this);
    this->resize(340,300);
    setFixedWidth(400);
    setFixedHeight(400);
    setWindowTitle("e-ag-client-tray");
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()/2 - this->width()/2);
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
    this->setStyleSheet("background-color: #dfdfdf;");


      //*******************tray***********************************/
      // Tray icon menu
      auto menu = this->createMenu();
      this->trayIcon->setContextMenu(menu);

      // App icon
      auto appIcon = QIcon(":/icons/e-ag-client.svg");
      this->trayIcon->setIcon(appIcon);
      this->setWindowIcon(appIcon);

      // Displaying the tray icon
      this->trayIcon->show();     // Note: without explicitly calling show(), QSystemTrayIcon::activated signal will never be emitted!

      // Interaction
      connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::iconActivated);


      timergizle = new QTimer(this);
      connect(timergizle, SIGNAL(timeout()), this, SLOT(gizle()));
      timergizle->start(1);

/**************************************************************************/
        QTimer *udpSocketSendConsoleTimer = new QTimer();
        QObject::connect(udpSocketSendConsoleTimer, &QTimer::timeout, [&](){
            sendBroadcastDatagram();
           });
        udpSocketSendConsoleTimer->start(5000);

       }
 void MainWindow::sendBroadcastDatagram()
 {
     DatabaseHelper *db=new DatabaseHelper(localDir+"e-ag.json");
     QJsonArray dizi=db->Ara("selectedNetworkProfil",true);
     for (const QJsonValue &item : dizi) {
         QJsonObject veri=item.toObject();
         this->networkIndex=veri["networkIndex"].toString();
         this->selectedNetworkProfil=veri["selectedNetworkProfil"].toBool();
         this->networkName=veri["networkName"].toString();
         this->networkTcpPort=veri["networkTcpPort"].toString();
         this->networkBroadCastAddress=veri["networkBroadCastAddress"].toString();
         this->serverAddress=veri["serverAddress"].toString();
         this->ftpPort=veri["ftpPort"].toString();
         this->rootPath=veri["rootPath"].toString();
         this->language=veri["language"].toString();
         this->lockScreenState=veri["lockScreenState"].toBool();
         this->webblockState=veri["webblockState"].toBool();
         QString lockScreenStatestr= "false";
         QString webblockStatestr="false";
         if(this->lockScreenState)lockScreenStatestr="true";
         if(this->webblockState)webblockStatestr="true";

         ///qDebug()<<"Broadcast Yapılan Ağ:" <<networkBroadCastAddress<<networkTcpPort;
         QString uport=networkTcpPort;
         std::reverse(uport.begin(), uport.end());
         QString msg;
         msg="eagconf|"+serverAddress+"|"+
               networkBroadCastAddress+"|"+
               networkTcpPort+"|"+
               ftpPort+"|"+
               rootPath+"|"+
               language+"|"+
               lockScreenStatestr+"|"+
               webblockStatestr;
         QByteArray datagram = msg.toUtf8();// +QHostAddress::LocalHost;
         QString broadadres;
         ///qDebug()<<datagram;
         for(int i=1;i<255;i++)
         {
             broadadres=networkBroadCastAddress.section(".",0,2)+"."+QString::number(i);
             //udpSocketSend->writeDatagram(datagram,QHostAddress("255.255.255.255"), uport.toInt());
             udpBroadCastSend->writeDatagram(datagram,QHostAddress(broadadres), uport.toInt()+uport.toInt());
         }
         qDebug()<<"broadCast"<<broadadres<<networkBroadCastAddress<<msg<<uport;
     }
 }


MainWindow::~MainWindow()
{
  //  delete ui;
}

void MainWindow::hostAddressMacButtonSlot()
{
    QHostAddress localhost = QHostAddress(QHostAddress::LocalHost);
ipmaclist.clear();
    foreach (const QNetworkInterface& networkInterface, QNetworkInterface::allInterfaces()) {
           foreach (const QNetworkAddressEntry& entry, networkInterface.addressEntries()) {
               QHostAddress *hostadres=new QHostAddress(entry.ip().toString());
               if(hostadres->protocol() == QAbstractSocket::IPv4Protocol &&
                       !hostadres->isLoopback() )
               {
                  IpMac im;
                  im.ip=entry.ip().toString();
                  im.mac=networkInterface.hardwareAddress();
                  im.broadcast=entry.broadcast().toString();
                  im.subnet=entry.netmask().toString();
                  ipmaclist.append(im);
                 // qDebug()<<"mac:"<<networkInterface.hardwareAddress();
                  //qDebug()<<"ip  address:"<<entry.ip().toString();
                 // qDebug()<<"broadcast  address:"<<entry.broadcast().toString();
              }
           }
       }



}

void  MainWindow::gizle()
{
       QWidget::hide();
    timergizle->stop();

  }
void  MainWindow::widgetShow()
{

    qDebug()<<"ekranı göster";
    system("sh -c \"pkexec env DISPLAY=$DISPLAY XAUTHORITY=$XAUTHORITY e-ag-gui\"");
 }

QMenu* MainWindow::createMenu()
{

    auto minimizeAction = new QAction(tr("Gi&zle"), this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);
    auto restoreAction = new QAction(tr("&Ayarlar"), this);
    ///connect( restoreAction, SIGNAL(triggered()), this, SLOT(widgetShow()));
    auto menu = new QMenu(this);
    ///menu->addAction(minimizeAction);
    //menu->addAction(maximizeAction);
    ///menu->addAction(restoreAction);
    ///menu->addSeparator();

    return menu;
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason_)
{
  switch (reason_) {
  case QSystemTrayIcon::Trigger:
    this->trayIcon->showMessage("e-ag", "İstemci Uygulaması!");
        ///widgetShow();
    break;
  default:
    ;
  }
}

void MainWindow::WidgetClosed()
{

    QWidget::hide();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
     emit WidgetClosed();
     //QWidget::hide();
     event->ignore();

}
void MainWindow::networkProfilLoad()
{

    DatabaseHelper *db=new DatabaseHelper(localDir+"e-ag.json");
    //QJsonArray dizi=db->Oku();
    QJsonArray dizi=db->Ara("selectedNetworkProfil",true);
    if(dizi.count()>0)
    {
        qDebug()<<"Kayıtlı Host."<<localDir;
        QJsonObject veri=dizi.first().toObject();
        //qDebug()<<"Yüklenen Ağ Profili:" <<veri;
        this->networkIndex=veri["networkIndex"].toString();
        this->selectedNetworkProfil=veri["selectedNetworkProfil"].toBool();
        this->networkName=veri["networkName"].toString();
        this->networkTcpPort=veri["networkTcpPort"].toString();
        this->networkBroadCastAddress=veri["networkBroadCastAddress"].toString();
        this->serverAddress=veri["serverAddress"].toString();
        this->ftpPort=veri["ftpPort"].toString();
        this->rootPath=veri["rootPath"].toString();
        this->language=veri["language"].toString();
        this->lockScreenState=veri["lockScreenState"].toBool();
        this->webblockState=veri["webblockState"].toBool();

        hostAddressMacButtonSlot();
        for(int i=0;i<ipmaclist.count();i++)
        {
            if(ipmaclist[i].broadcast==networkBroadCastAddress)
            {
                if(ipmaclist[i].ip!=serverAddress)
                {
                    qDebug()<<"Server Ip Numarası Güncelleniyor..";
                    QJsonObject veri;
                    veri["networkIndex"] =this->networkIndex;
                    veri["selectedNetworkProfil"] =this->selectedNetworkProfil;
                    veri["networkName"] = this->networkName;
                    veri["networkTcpPort"] = this->networkTcpPort;
                    veri["serverAddress"]=ipmaclist[i].ip;
                    veri["networkBroadCastAddress"]=this->networkBroadCastAddress;
                    veri["ftpPort"]=this->ftpPort;
                    veri["rootPath"]=this->rootPath;
                    veri["language"]=this->language;
                    veri["lockScreenState"]=this->lockScreenState;
                    veri["webblockState"]=this->webblockState;
                    db->Sil("networkIndex",this->networkIndex);
                    db->Ekle(veri);
                }

            }
        }
    }else{
        qDebug()<<"Yeni Network Ekleniyor."<<localDir;

        hostAddressMacButtonSlot();
        for(int i=0;i<ipmaclist.count();i++)
        {
            //qDebug()<<"broadcast address:"<<i<<ipmaclist[i].broadcast;
            QJsonObject veri;
            veri["networkIndex"] =QString::number(db->getIndex("networkIndex"));
            veri["selectedNetworkProfil"] =true;
            veri["networkName"] = "network";
            veri["networkTcpPort"] = "7879";
            veri["serverAddress"]=ipmaclist[i].ip;
            veri["networkBroadCastAddress"]=ipmaclist[i].broadcast;
            veri["ftpPort"]="12345";
            veri["rootPath"]="/tmp/";
            veri["language"]="tr_TR";
            veri["lockScreenState"]=false;
            veri["webblockState"]=false;
            db->Ekle(veri);
        }
        networkProfilLoad();
    }
}
