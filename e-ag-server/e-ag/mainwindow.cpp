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
#include<QDebug>
#include <QProcess>
#include <QtNetwork/qnetworkinterface.h>
#include <QtNetwork/QHostAddress>
#include<QtNetwork/QTcpSocket>
#include<QDir>
#include<QString>
#include<QDataStream>
#include<menu.h>
#include <QScrollArea>
#include<QApplication>
#include<QDesktopWidget>
#include<QtWidgets>
#include<tcpudp.h>
#include<init.h>
#include<funtion.h>
#include<SettingsWidget.h>
#include<lockWidget.h>
#include<volumeWidget.h>
#include<powerrebootWidget.h>
#include<loginLogoutWidget.h>
#include<screenViewWidget.h>
#include<vncrdpWidget.h>
#include<runcommandWidget.h>
#include<filecopyWidget.h>
#include<messageWidget.h>
#include<languageWidget.h>
#include<videoWidget.h>
#include<wolWidget.h>
#include<sliderWidget.h>
#include<baseWidget.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //QTermWidget *qterm=new QTermWidget();
    //qterm->sendData();
      /*****************************************************/
    QSize screenSize = qApp->screens()[0]->size();
    boy=screenSize.height()/153.6;
    en=boy*1.1;
    int e=en;
    int b=boy;
    this->resize(boy*200,en*105);
    int x = (screenSize.width() - this->width())/2;
    int y = (screenSize.height() - this->height()) / 2;
    this->move(x, y);
   // qDebug()<<"aşama1";

    mainWidget=new QWidget();
    localDir="/usr/share/e-ag/";
    hostAddressMacButtonSlot();
    rb1=new QRadioButton();
    rb2=new QRadioButton();
    //system("systemctl restart e-ag-networkprofil.service");
    networkProfilLoad();///hesap ve ayarların yüklenmesi yapılıyor...
//setMouseTracking(true);
//installEventFilter(this);
    /************************version*******************************************/
    QStringList arguments;
    arguments << "-c" << "dpkg -s e-ag|grep -i version";
    QString resultVersion;
    QProcess process;
    process.start("/bin/bash",arguments);
    if(process.waitForFinished())
    {
        resultVersion = process.readAll();
    }
    resultVersion.chop(1);
    QString version = resultVersion.right(5);
    setWindowTitle("e-ag "+version);
    /***********************************************************************/
    auto appIcon = QIcon(":/icons/e-ag.svg");
    this->setWindowIcon(appIcon);

   /***********************************************************************/
    pcMac=new QLabel();
    pcName=new QLabel();
    pcIp=new QLabel();
    statusbar=new QStatusBar(this);
    statusbar->showMessage(tr("..."));
    statusbar->setStyleSheet("font-size:"+QString::number(font.toInt()-4)+"px;");
    //qDebug()<<"aşama0";
      /************************************************************/
    hostListe=new QWidget();
    hostListe->setFixedSize(e*178,b*56);
    hostListe->setObjectName("hostListe");

    rubberBand = new QRubberBand(QRubberBand::Rectangle, hostListe);
    //hostListe->setStyleSheet("QWidget#hostListe{border: 0.5px solid rgb(0, 0,0,255);}");
    scrollArea=new QScrollArea();
    scrollArea->setWidget(hostListe);
    scrollArea->setFixedSize(e*180,b*56);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    /// scrollArea->setStyleSheet("background-color: #ff5533");

    /// hostListe->hide();
    layout = new QGridLayout(hostListe);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setSpacing(3);
    //hostListe->setLayout(layout);

   // qDebug()<<"aşama5";
    /*********************************************************************/
    selectPc();
// qDebug()<<"aşama51";
    /********************************************************************/
    textBrowser_receivedMessages=new QPlainTextEdit();
    textBrowser_receivedMessages->hide();
    textBrowser_receivedMessages->resize(this->width(),b*24-2);
    textBrowser_receivedMessages->setStyleSheet("background-color: #a3a3a3");
   /***********************************************************************/
    tabwid=new QTabWidget();
    tabwid->setFixedSize(this->width(),boy*24);
    tabwid->addTab(baseWidget(),QIcon(":/icons/toolbox.svg"),tr("Temel İşlemler"));
    tabwid->addTab(rdpWidget(),QIcon(":/icons/vnc.svg"),tr("Ekran Paylaşımı"));
    tabwid->addTab(commandWidget(),QIcon(":/icons/bash.svg"),tr("Komut Çalıştır"));
    tabwid->addTab(messageWidget(),QIcon(":/icons/message.svg"),tr("Mesaj Yaz"));
    tabwid->addTab(fileWidget(),QIcon(":/icons/filecopy.svg"),tr("Dosya Kopyala"));
    tabwid->addTab(videoWidget(),QIcon(":/icons/camera.svg"),tr("Video/Kamera"));
    tabwid->addTab(settingsWidget(),QIcon(":/icons/settings.svg"),tr("Ayarlar"));
    tabwid->addTab(textBrowser_receivedMessages,QIcon(":/icons/log.svg"),tr("İşlem Raporu"));
    tabwid->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    tabwid->setTabPosition(QTabWidget::North);
    /***********************************************************************/
    ekranScale = new QComboBox();
    ekranScale->setFixedSize(en*2,boy);
    ekranScale->setFrame(true);
    ekranScale->setStyleSheet("background-color: #dcdcdc; font-size:"+QString::number(font.toInt()-4)+"px;");
    ekranScale->addItem("800x600");
    ekranScale->addItem("1024x768");
    ekranScale->addItem("1280x1024");
    ekranScale->addItem("1366x768");
    ekranScale->setCurrentIndex(3);
    /*********************************************************************/

    newPcDetectTimer= new QTimer(this);
    connect(newPcDetectTimer, SIGNAL(timeout()), this, SLOT(pcDetect()));
    //newPcDetectTimer->start(5000);
    /********************* Broadcast Message yollanıyor *****************************************/
    QString uport="7879";
    if(NetProfilList.count()>0)
        uport=NetProfilList.first().networkTcpPort;

    udpSocketSend = new QUdpSocket(this);
    udpSocketGet = new QUdpSocket();
    udpSocketGet->bind(uport.toInt(), QUdpSocket::ShareAddress);
    QObject::connect(udpSocketGet,&QUdpSocket::readyRead,[&](){udpSocketServerRead();});
    //qDebug()<<"Port.:"<<uport;
    /*********************************************************/

 QGridLayout* layoutMain = new QGridLayout(mainWidget);
 layoutMain->setContentsMargins(0, 0, 0,0);
 layoutMain->setVerticalSpacing(0);
 layoutMain->setHorizontalSpacing(0);
 layoutMain->addWidget(tabwid, 0,0,1,1);
 //layoutMain->addWidget(toolBar, 3,0,1,1);

 layoutMain->addWidget(selectWidget, 4,0,1,1);
 layoutMain->addWidget(scrollArea, 6,0,1,1);
 layoutMain->addWidget(statusbar,7,0,1,1);

setMinimumSize(width(),height());
mainWidget->setLayout(layoutMain);
this->setCentralWidget(mainWidget);


statusbar->addPermanentWidget(sliderWidget(),0);

/*************************************************************************/
 hostListe->show();

/*************************************************************************/
 }

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug()<<"main move";
    int hostListePos=tabwid->height()+selectWidget->height();
    /* if (Pc *w =(Pc*) qApp->widgetAt(QCursor::pos())) {
         if(w->objectName()=="hostListe")
         {
       */      //qDebug()<<"main move22";
    rubberBand->setGeometry(QRect(QPoint(origin.x(),origin.y()-hostListePos),QPoint(event->pos().x(),event->pos().y()-hostListePos)).normalized());
    // }
    //}
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    // qDebug()<<"main release"<<mouseClickState;
    if(mouseClickState)
    {
        rubberBand->hide();
        QRect selectionRect = rubberBand->geometry();
        for (MyPc *mypc : findChildren<MyPc *>()) {
            if (selectionRect.intersects(mypc->geometry())) {
                mypc->slotSelectPc();
            } else {
                mypc->slotUnselectPc();
            }
        }
    }
    mouseClickState=false;

}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // qDebug()<<"main press";
    origin =( event->pos());
    int hostListePos=tabwid->height()+selectWidget->height();
    rubberBand->setGeometry(QRect(QPoint(origin.x(),origin.y()-hostListePos),QSize(0,0)));
    rubberBand->show();
    mouseClickState=true;
    if (event->button()==Qt::RightButton)
    {
        //qDebug()<<"burası main sağtuş";
        int  pcmultiselect=0;
        //if(pcrightmenu) pcmultiselect++;
        for(int i=0;i<onlinePcList.length();i++)
        {
            //if(btnlist[i]->mac==selectMac)
            //  {
            if(onlinePcList[i]->multiSelect||onlinePcList[i]->select){
                // if (QWidget *w =(QWidget*) qApp->widgetAt(QCursor::pos())) {
                // if(w->objectName()=="hostListe")
                //  {
                pcmultiselect++;
                //}
                //}
            }
            // }
        }
        ///

        if(pcmultiselect>0)
        {
            bool singleSelectPcStatus=false;
            bool multiSelectPcStatus=false;
            bool hostListeRightClick=false;
            bool hostListeRightClickStatus=false;
            if (QWidget *w =(QWidget*) qApp->widgetAt(QCursor::pos())) {
                if(w->objectName()=="hostListe")
                {
                    hostListeRightClick=true;
                }
            }

            if(pcmultiselect==1&&pcrightmenu) singleSelectPcStatus=true;
            if(pcmultiselect>1&&pcrightmenu) multiSelectPcStatus=true;
            if(pcmultiselect>1&&hostListeRightClick) hostListeRightClickStatus=true;

             qDebug()<<"seçilen pc sayısı: "<<pcmultiselect<<pcrightmenu<<singleSelectPcStatus<<multiSelectPcStatus<<hostListeRightClickStatus;
            if(singleSelectPcStatus||multiSelectPcStatus||hostListeRightClickStatus)
            {
                if(singleSelectPcStatus)
                    pcMenu(true); //single select pc
                else
                    pcMenu(false); //multi select pc

                pContextMenu->exec(mapToGlobal(event->pos()),nullptr);
                // qDebug()<<"burası main sağ menu"<<mouseClickState;
                mouseClickState=false;
                pcrightmenu=false;
                pcmultiselect=0;
            }
        }
    }

}

void MainWindow::resizeEvent(QResizeEvent *event)
 {
 //qDebug()<<"main boyut değişti";
 selectWidget->setFixedSize(this->width(),selectWidget->height());
 //ustMenuWidget->setFixedSize(this->width(),ustMenuWidget->height());
 textBrowser_receivedMessages->setFixedSize(this->width(),boy*19-2);
 tabwid->setFixedSize(this->width(),boy*22);
 hostListe->setFixedSize(this->width()-en*3.5,this->height()-tabwid->height()-selectWidget->height()-boy*7);
 scrollArea->setFixedSize(this->width(),this->height()-tabwid->height()-selectWidget->height()-boy*6);
if(firstRun){
     pcListeGuncelleSlotnew("mainresize");
}
else{firstRun=true;}
///QWidget::resizeEvent(event);
}
bool MainWindow::karsilastirMyPc(const MyPc *mypc1, const MyPc *mypc2) {
     return mypc1->caption < mypc2->caption; // caption göre sırala
 }
void MainWindow::pcListeGuncelleSlotnew(QString mission)
{
    //onlinePcList.clear();
    //qDeleteAll(hostListe->findChildren<MyPc *>());
    //QList<MyPc*> altNesneler = hostListe->findChildren<MyPc*>();
    //qDebug()<<altNesneler.size();
    //qDeleteAll(altNesneler);
    //Sıralama yapıldı caption göre
    std::sort(onlinePcList.begin(), onlinePcList.end(),karsilastirMyPc);
    //sadece gizli olmayanlar filtreleniyor
    std::vector<MyPc*> onlinePcList1;
    std::copy_if(onlinePcList.begin(), onlinePcList.end(), std::back_inserter(onlinePcList1), [](const MyPc *mypc) {
        return mypc->visibleState==true; // visibleState==true filtreleniyor
    });
    hostsCountLabel->setText(tr("Açık Hosts : ")+QString::number(onlinePcList1.size()));

    /*******************************************************************/

     double nwidth=en*20*slider->value()/100;
     double nheight=en*15*slider->value()/100;
     int columnSayisi=hostListe->width()/(nwidth*1.2);
     int listeSayisi=onlinePcList1.size();
     int satir=listeSayisi/columnSayisi;
     int mod=listeSayisi%columnSayisi;
     if (mod!=0) satir++;
     int sutun=columnSayisi;
     if(listeSayisi<columnSayisi)sutun=listeSayisi;
     /************************************************************/
     double nlstheight=satir*(nheight*1.2);
     //double nlstheight=(en*(gercekliste/columnSayisi+1)*13.8)*slider->value()/100;
     double tempnlstheight=(this->height()-tabwid->height()-selectWidget->height()-7*boy);
    //qDebug()<<"satir"<<satir<<"sutun"<<sutun<<"liste sayısı"<<listeSayisi<<tempnlstheight<<nlstheight;
     if(nlstheight>tempnlstheight)
        hostListe->setFixedSize(hostListe->width(),nlstheight);
     else
        hostListe->setFixedSize(hostListe->width(),tempnlstheight);


     /************************************************************/
     //qDebug()<<"Hosts Listesi Güncellendi..new";//<<columnSayisi<<nwidth<<nheight;
    qDebug()<<"Hosts Listesi Güncellendi..new"<<mission;
     int sn=0;
 //return;
     for(int i=0;i<satir;i++)
     {
         for(int k=0;k<sutun;k++)
         {
             if((sn+1)>listeSayisi) continue;
             if(onlinePcList1[sn]->visibleState)
             {
                 //qDebug()<<onlinePcList1[sn]->ip;
                 layout->addWidget(onlinePcList1[sn], i,k,1,1);
                 onlinePcList1[sn]->setSize(nwidth,nheight,font);
             }
             sn++;
        }
     }

/***************pc seçimi yapılıyor önemli***********************/
     if(onlinePcList1.size()>0)
     {
         onlinePcList1[onlinePcList1.size()-1]->slotMouseClick();

         pcClickSlot(onlinePcList1[onlinePcList1.size()-1]->mac);
     }
 }
void MainWindow::pcHideSignalSlot(QString _mac)
 {
    for(int i=0;i<onlinePcList.count();i++)
         {
         if(onlinePcList[i]->mac==_mac)
         {
            //qDeleteAll(hostListe->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
            layout->removeWidget(onlinePcList[i]);
            //hostListe->removeWidget(onlinePcList[i]);
            delete onlinePcList[i];
            onlinePcList.removeAt(i);
            pcDetect();
            break;
         }
        }

 }

void MainWindow::mesajSlot(QString msg)
{

    textBrowser_receivedMessages->moveCursor (QTextCursor::End);
    textBrowser_receivedMessages->insertPlainText (msg+"\n");
    statusbar->showMessage(msg);
}
void MainWindow::pcClickSlot(QString _mac)
{
/*
if(remoteUserName==""||remotePassword==""||
        localUserName==""||localPassword=="")
{
    ///localNetwork!=""||tcpPort!="")
    QMessageBox msgBox;
     msgBox.setText("Uygulamanın Sorunsuz Çalışması İçin Eksik Bilgileri Doldurunuz!");
     msgBox.exec();
   acountButtonSlot();
}
*/

    QPalette palet;
    for(int i=0;i<onlinePcList.length();i++)
     {
        if(onlinePcList[i]->mac!=_mac)
        {
         onlinePcList[i]->select=false;
        /// btnlist[i]->slotUnselectPc();
         palet.setColor(QPalette::Window, QColor(0,0,0,0));
         onlinePcList[i]->setPalette(palet);
         onlinePcList[i]->setAutoFillBackground(true);
        }
        else
        {
            system("nohup rm -rf ~/.ssh &");

           pcIp->setText(onlinePcList[i]->ip);
           pcMac->setText(onlinePcList[i]->mac);
           pcName->setText(onlinePcList[i]->caption);
          /// btnlist[i]->slotUnselectPc();
            pcNamelbl->setText(tr("Pc Adı: ")+pcName->text());
            pcIplbl->setText(tr("Ip: ")+pcIp->text());
            pcMaclbl->setText(tr("Mac: ")+pcMac->text());

            pcUserlbl->setText(tr("Kullanıcı: ")+onlinePcList[i]->user);
           /// pcScreenlbl->setText("Ekran: "+onlinePcList[i]->display);
            pcSystemlbl->setText(tr("Sistem: ")+onlinePcList[i]->hostname.trimmed());
           /* if(btnlist[i]->display=="")  _display="0";
            else
                _display=onlinePcList[i]->display.right(1);
*/

        }
      }
    selectMac=pcMac->text();

}
void MainWindow::pcRightClickSignalSlot()
{
    pcrightmenu=true;
}

MainWindow::~MainWindow()
{
    qDebug()<<"e-ag Kapatıldı.";
    system("sleep 1");
    slotVncFlipStop();
    system("sleep 1");
    if(streamState)
    {
        system("pkill servervideo");
        system("pkill clientvideo");
        system("pkill servercamera");
        system("pkill clientcamera");
    }

}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);
}
