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
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
 {
   localDir="/usr/share/e-ag/";
    networkProfilLoad();

    QString uport=networkTcpPort;
    std::reverse(uport.begin(), uport.end());

    udpConsoleGet=new QUdpSocket();
    udpConsoleSend = new QUdpSocket();

    udpConsoleGet->bind(51512, QUdpSocket::ShareAddress);
    QObject::connect(udpConsoleGet,&QUdpSocket::readyRead,[&](){udpConsoleGetSlot();});
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
      QString seatId=getSeatId();
        x11user=getSessionInfo(seatId,"USER=");
        QStringRef _sessionUser=x11user.rightRef(x11user.length()-5);
        x11user=_sessionUser.toString();


        x11display=getSessionInfo(seatId,"DISPLAY=:");
        QStringRef _sessionDisplay=x11display.rightRef(x11display.length()-9);
        x11display=_sessionDisplay.toString();
        /******************************************************/
        if(!x11display.contains("0", Qt::CaseInsensitive))//!=0
        {
             QString kmt20="nohup /usr/bin/x11vnc -forever -loop -noxdamage -repeat -rfbauth /usr/bin/x11vncpasswd -rfbport 5901 -shared &";
             system(kmt20.toStdString().c_str());
        }
        //sendConsoleCount=0;
        QTimer *udpSocketSendConsoleTimer = new QTimer();
        QObject::connect(udpSocketSendConsoleTimer, &QTimer::timeout, [this,udpSocketSendConsoleTimer](){
            x11mydispresult="clientTrayEnv|"+x11user+"|"+x11display;
            QByteArray datagram = x11mydispresult.toUtf8();// +QHostAddress::LocalHost;
            udpConsoleSend->writeDatagram(datagram,QHostAddress::LocalHost, 51511);
            qDebug()<<"client console  gönderildi:"<<x11mydispresult;
            //sendConsoleCount++;
            //if(sendConsoleCount>7) udpSocketSendConsoleTimer->stop();
        });
        udpSocketSendConsoleTimer->start(5000);

       }

 void MainWindow::networkProfilLoad()
 {

     DatabaseHelper *db=new DatabaseHelper(localDir+"e-ag.json");
     //QJsonArray dizi=db->Oku();
     QJsonArray dizi=db->Ara("selectedNetworkProfil",true);
     if(dizi.count()>0)
     {
         //qDebug()<<"Kayıtlı Host.";
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

     }else
     {
         qDebug()<<"Yeni Network Ekleniyor.";
         hostAddressMacButtonSlot();
         for(int i=0;i<ipmaclist.count();i++)
         {
         //qDebug()<<"broadcast address:"<<i<<ipmaclist[i].broadcast;
         QJsonObject veri;
         veri["networkIndex"] =QString::number(db->getIndex("networkIndex"));
         veri["selectedNetworkProfil"] =true;
         veri["networkName"] = "network";
         veri["networkTcpPort"] = "7879";
         veri["serverAddress"]="";
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

void MainWindow::udpConsoleGetSlot()
{
    QByteArray datagram;
    while (udpConsoleGet->hasPendingDatagrams()) {
        datagram.resize(int(udpConsoleGet->pendingDatagramSize()));
        QHostAddress sender;
        quint16 senderPort;
        udpConsoleGet->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        QString rmesaj=datagram.constData();
        tcpMessageControlSlot(rmesaj);
    }
}

void MainWindow::tcpMessageControlSlot(QString _data)
{
        qDebug()<<"Gelen Mesaj:"<<_data;
        QStringList lst=_data.split("|");
        gelenKomut->setText(lst[1]+"  "+lst[2]);

        if(lst[1]=="ekranmesaj")
        {
            qDebug()<<"ekranmesaj:"<<lst[1]<<lst[2];
            ekran->setWindowFlags(Qt::Tool);
            ekran->ekranMesaj("Yönetici Mesajı:",lst[2]);
            ekran->show();

        }
        else if(lst[1]=="vncviewer")
        {
            qDebug()<<"mesaj:"<<lst[1]<<lst[2]<<lst[3];
            system("pkill vncviewer &");
            QStringList params=lst[2].split(":");
            QString  kmt;
            kmt.append("nohup vncviewer "+params[0]+" \-fullscreen ").append(lst[3]).append(":"+params[1]+" \-passwd \/usr\/bin\/x11vncpasswd &");
            qDebug()<<"komut:"<<kmt;
            system(kmt.toStdString().c_str());
            /*ekran->setWindowFlags(Qt::Tool);
            ekran->ekranKomutMesaj("Çalışan Komut:",kmt);
            ekran->show();*/

        }
        else if(lst[1]=="kilitstatetrue")
        {
            qDebug()<<"ekrankilittrue:"<<lst[1];
            //ekran->close();
            if (!kilitstate)
            {
                kilitstate=true;
                transparankilitstate=false;
                ekranimagestate=false;
                ekran->setWindowFlags(Qt::Tool);
                ekran->ekranKilit("Yönetici Mesajı:","Ekran Kilitlendi!");
                ekran->show();
            }

        }
        else if(lst[1]=="kilitstatefalse")
        {
            qDebug()<<"ekrankilitac:"<<lst[1];
            ekran->close();
            kilitstate=false;
        }
        else if(lst[1]=="transparankilitstatetrue")
        {
            qDebug()<<"kilittransparanstatetrue";
            if (!transparankilitstate)
            {
                kilitstate=false;
                transparankilitstate=true;
                ekranimagestate=false;
                ekran->setWindowFlags(Qt::Tool);
                ekran->ekranTransparanKilit();
                ekran->show();
            }

        }
        else if(lst[1]=="transparankilitstatefalse")
        {
            qDebug()<<"ekrantransparankilitac:"<<lst[1];
            ekran->close();
            transparankilitstate=false;
        }
        else if(lst[1]=="x11command")
        {
            ekran->setWindowFlags(Qt::Tool);
            //QString komut="nohup "+lst[2]+" &";
            //system(komut.toStdString().c_str());
            QProcess process;
            QStringList arguments;
            arguments << "-c" << lst[2]+" &";
            process.start("/bin/bash",arguments);
            int exitCode ;
            QString stdOut;
            QString stdErr;

            if (process.waitForFinished()) {
                exitCode = process.exitCode();
                stdOut = process.readAllStandardOutput();
                stdErr = process.readAllStandardError();
                // Durum kontrolü
                if (process.exitStatus() == QProcess::NormalExit && exitCode == 0 && stdErr.isEmpty()) {
                    //qDebug() << "Paket başarıyla kuruldu.";
                    //qDebug() << "Çıktı:" << stdOut;
                    //QString mesaj="consolecommand|consolecommand|"+command+"|0|"+stdOut;

                    ekran->command=lst[2];
                    ekran->commandDetail=stdOut;
                    ekran->commandState="0";
                    ekran->ekranKomutMesaj();
                } else {
                    //qDebug() << "Kurulum sırasında hata oluştu.";
                    //qDebug() << "Çıkış kodu:" << exitCode;
                    // qDebug() << "Hata çıktısı:" << stdErr;
                    //QString mesaj="consolecommand|consolecommand|"+command+"|1"+stdErr;
                    //ekran->ekranKomutMesaj();

                    ekran->command=lst[2];
                    ekran->commandDetail=stdErr;
                    ekran->commandState="1";
                     ekran->ekranKomutMesaj();
                }
            } else {
                ekran->command=lst[2];
                ekran->commandDetail="Komut zamanında tamamlanamadı veya hata oluştu.";
                ekran->commandState="1";
                ekran->ekranKomutMesaj();

            }





            ekran->show();
        }
        else if(lst[1]=="consolecommand")
        {
            auto ekrn=new Ekran();
            ekrn->command=lst[2];
            ekrn->commandDetail=lst[4];
            ekrn->commandState=lst[3];
            //ekrn->setWindowFlags(Qt::Tool);
            ekrn->ekranKomutMesaj();
            ekrn->show();
        }
        else if(lst[1]=="volumeoff")
        {
             if(QFile::exists("/usr/bin/wpctl"))
            {
            QString komut="nohup wpctl set-mute @DEFAULT_AUDIO_SINK@ 1 &";
            system(komut.toStdString().c_str());
            }
            if(QFile::exists("/usr/bin/pactl"))
            {
            QString komut1="nohup pactl set-sink-mute @DEFAULT_SINK@ 1 &";
            system(komut1.toStdString().c_str());
            }
        }
        else if(lst[1]=="volumeon")
        {
             if(QFile::exists("/usr/bin/wpctl"))
            {
            QString komut="nohup wpctl set-mute @DEFAULT_AUDIO_SINK@ 0 &";
            system(komut.toStdString().c_str());
            }
            if(QFile::exists("/usr/bin/pactl"))
            {
            QString komut1="nohup pactl set-sink-mute @DEFAULT_SINK@ 0 &";
            system(komut1.toStdString().c_str());
            }
        }
        else if(lst[1]=="videoyayinbaslat")
        {
            qDebug()<<"komut:"<<lst[1]<<lst[2];

            gst_init(nullptr, nullptr);


            GError *error = NULL;

            // Video ve ses pipeline'ları
            std::string videoPipeline = "udpsrc port=5000 address=239.0.0.1 ! application/x-rtp, payload=96 ! rtph264depay ! avdec_h264 ! videoconvert ! autovideosink";
            std::string audioPipeline = "udpsrc port=5001 address=239.0.0.1 ! capsfilter caps=\"application/x-rtp, media=(string)audio, clock-rate=(int)48000, encoding-name=(string)OPUS, payload=(int)97\" ! rtpopusdepay ! opusdec ! autoaudiosink";

            // Video pipeline'ı oluştur
            pipeline = gst_parse_launch(videoPipeline.c_str(), &error);
            if (error) {
                std::cerr << "Video pipeline oluşturulamadı: " << error->message << std::endl;
                g_clear_error(&error);
                return;
            }
            gst_element_set_state(pipeline, GST_STATE_PLAYING);


            // Ses pipeline'ı oluştur
            pipeline = gst_parse_launch(audioPipeline.c_str(), &error);
            if (error) {
                std::cerr << "Ses pipeline oluşturulamadı: " << error->message << std::endl;
                g_clear_error(&error);
                return ;
            }
            gst_element_set_state(pipeline, GST_STATE_PLAYING);

            /*std::cout << "Alıcı başladı (Ctrl+C ile durdurun)..." << std::endl;

            // Alıcı devam ederken (Ctrl+C ile durdurulana kadar) bekleyin
            GMainLoop *loop = g_main_loop_new(NULL, FALSE);
            g_main_loop_run(loop);

            // Pipeline'ları durdur ve temizle
            gst_element_set_state(pipeline, GST_STATE_NULL);
            gst_object_unref(pipeline);
*/

        }
        else if(lst[1]=="videoyayindurdur")
        {
            // Pipeline'ları durdur ve temizle
            gst_element_set_state(pipeline, GST_STATE_NULL);
            gst_object_unref(pipeline);

        }
}
QString MainWindow::myMessageBox(QString baslik, QString mesaj, QString evet, QString hayir, QString tamam, QMessageBox::Icon icon)
{
    Qt::WindowFlags flags = 0;
    flags |= Qt::Dialog;
    flags |= Qt::X11BypassWindowManagerHint;

    QMessageBox messageBox(this);
    messageBox.setWindowFlags(flags);
    messageBox.setText(baslik+"\t\t\t");
    messageBox.setInformativeText(mesaj);
    QAbstractButton *evetButton;
    QAbstractButton *hayirButton;
    QAbstractButton *tamamButton;

    if(evet=="evet") evetButton =messageBox.addButton(tr("Evet"), QMessageBox::ActionRole);
    if(hayir=="hayir") hayirButton =messageBox.addButton(tr("Hayır"), QMessageBox::ActionRole);
    if(tamam=="tamam") tamamButton =messageBox.addButton(tr("Tamam"), QMessageBox::ActionRole);

    messageBox.setIcon(icon);
    messageBox.exec();
    if(messageBox.clickedButton()==evetButton) return "evet";
    if(messageBox.clickedButton()==hayirButton) return "hayır";
    if(messageBox.clickedButton()==tamamButton) return "tamam";
    return "";
}

MainWindow::~MainWindow()
{
  //  delete ui;
}
QString MainWindow::getSessionInfo(QString id, QString parametre)
{
    QString tempsessionParametre;
    QString filename="/run/systemd/sessions/"+id;

    if(QFile::exists(filename))
    {
        const int size = 256;
        FILE* fp = fopen(filename.toStdString().c_str(), "r");
        if(fp == NULL)
        {
            perror("Error opening /run/systemd/sessions/");
        }

        char line[size];
        fgets(line, size, fp);    // Skip the first line, which consists of column headers.
        while(fgets(line, size, fp))
        {
            QString satir=line;
            satir.chop(1);
            //   tempsessionlist<<satir;
            //qDebug()<<"satir: "<<satir;
            if(satir.contains(parametre)){
                tempsessionParametre=satir;
            }
        }

        fclose(fp);
    }

    return tempsessionParametre;
}
QString  MainWindow::getSeatId()
{
    QString tempseatId;
    if(QFile::exists("/run/systemd/seats/seat0"))
    {
        QStringList list;
        const int size = 256;
        //seat=fileToList("/run/systemd/seats","seat0");
        //qDebug()<<"seat:"<<seat;
        FILE* fp = fopen("/run/systemd/seats/seat0", "r");
        if(fp == NULL)
        {
            perror("Error opening /run/systemd/seats/seat0");
        }

        char line[size];
        fgets(line, size, fp);    // Skip the first line, which consists of column headers.
        while(fgets(line, size, fp))
        {
            QString satir=line;
            satir.chop(1);
            if(satir.contains("ACTIVE=")){
                QStringRef _seatid=satir.rightRef(satir.length()-7);
                tempseatId=_seatid.toString();
                //qDebug()<<seatId;
            }

        }

        fclose(fp);
    }

    return tempseatId;
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
    system("sh -c \"pkexec env DISPLAY=$DISPLAY XAUTHORITY=$XAUTHORITY e-ag-client-gui\"");
 }


QMenu* MainWindow::createMenu()
{

    auto minimizeAction = new QAction(tr("Gi&zle"), this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);
    auto restoreAction = new QAction(tr("&Ayarlar"), this);
    connect( restoreAction, SIGNAL(triggered()), this, SLOT(widgetShow()));
    auto menu = new QMenu(this);
    menu->addAction(minimizeAction);
    //menu->addAction(maximizeAction);
    menu->addAction(restoreAction);
    menu->addSeparator();

    return menu;
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason_)
{
  switch (reason_) {
  case QSystemTrayIcon::Trigger:
   // this->trayIcon->showMessage("e-ag", "İstemci Uygulaması!");
        widgetShow();
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
