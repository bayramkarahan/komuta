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
#include<filecrud.h>
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
#include<ekranresmi.h>
#include <stdio.h>
#include <QtCore/QCoreApplication>
#include <gst/gst.h>
#include <iostream>
#include<gst/gsterror.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
 {
    //udpSocketSendMyDisp = new QUdpSocket();
    udpConsoleGet=new QUdpSocket();
    udpConsoleSend = new QUdpSocket();

    udpConsoleGet->bind(51512, QUdpSocket::ShareAddress);
    QObject::connect(udpConsoleGet,&QUdpSocket::readyRead,[&](){udpConsoleGetSlot();});

    /*******************************************************************/
    webblockcb= new QCheckBox("Her Açılışta Web Sitelerini Engelle.");

    ekran=new Ekran();
    gelenKomut=new QLabel("-------------------");
    localDir="/tmp/";
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

/***************************************************************/
        //webBlockAktifPasif();
/***************************************************************/
    QStringList arguments;
        arguments << "-c" << QString("printenv USER");
        QProcess process;
        process.start("/bin/bash",arguments);
        if(process.waitForFinished())
        {
            x11user = process.readAll();
           /// qDebug()<<"mydisp user bilgi:"<<user;
               x11user.chop(1);
        }
        QStringList argumentss;
        argumentss << "-c" << QString("printenv DISPLAY");


        process.start("/bin/bash",argumentss);
        if(process.waitForFinished())
        {
            x11display = process.readAll();
            ///qDebug()<<"mydisp display bilgi:"<<display;
               x11display.chop(1);
        }


        if(!x11display.contains("0", Qt::CaseInsensitive))//!=0
        {
             QString kmt20="nohup /usr/bin/x11vnc -forever -loop -noxdamage -repeat -rfbauth /usr/bin/x11vncpasswd -rfbport 5901 -shared &";
             system(kmt20.toStdString().c_str());
        }

 /**************************************************************************/
      /*  QTimer *mydispTimer = new QTimer();
        QObject::connect(mydispTimer, &QTimer::timeout, [&](){

            x11mydispresult=x11user+"|"+
                    x11display+"|"+
                    QString::number(kilitstate)+"|"+
                    QString::number(transparankilitstate)+"|"+
                    QString::number(ekranimagestate);
               QByteArray datagram = x11mydispresult.toUtf8();// +QHostAddress::LocalHost;
            udpSocketSendMyDisp->writeDatagram(datagram,QHostAddress::LocalHost, 5555);
            ////qDebug()<<"server'a mesaj gönderildi:"<< serverlist[0]<<_data;
        });
        mydispTimer->start(2000);

        /**************************************************************************/
        QTimer *udpSocketSendConsoleTimer = new QTimer();
        QObject::connect(udpSocketSendConsoleTimer, &QTimer::timeout, [&](){
            if(ekranimagestate)  kaydetTimerSlot(serverIp);
            x11mydispresult=x11user+"|"+
                              x11display+"|"+
                              QString::number(kilitstate)+"|"+
                              QString::number(transparankilitstate)+"|"+
                              QString::number(ekranimagestate);
            QByteArray datagram = x11mydispresult.toUtf8();// +QHostAddress::LocalHost;
            udpConsoleSend->writeDatagram(datagram,QHostAddress::LocalHost, 51511);
            qDebug()<<"client console  gönderildi:"<<x11mydispresult;
        });
        udpSocketSendConsoleTimer->start(2000);


        /***************************************************************************/


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
     ///   qDebug()<<"x11'den Gelen Udp Mesaj:"<<rmesaj;
   tcpMessageControlSlot(rmesaj);

    }
}
void MainWindow::webBlockAktifPasif()
{
    QStringList ayarlst=fileToList("/usr/share/e-ag/","e-ag-x11client.conf");


    /**********************************************************/
        if(listGetLine(ayarlst,"rootusername")!="")
        {
            QString strrootusername=listGetLine(ayarlst,"rootusername").split("|")[1];
            //qDebug()<<strwebblockstate;
            rootusername=strrootusername;
        }
        /**********************************************************/
            if(listGetLine(ayarlst,"rootpassword")!="")
            {
                QString strrootpassword=listGetLine(ayarlst,"rootpassword").split("|")[1];
                //qDebug()<<strwebblockstate;
                rootpassword=strrootpassword;
            }

/**********************************************************/
    if(listGetLine(ayarlst,"webblockstate")!="")
    {
        QString strwebblockstate=listGetLine(ayarlst,"webblockstate").split("|")[1];
        //qDebug()<<strwebblockstate;
        webblockstate=strwebblockstate.toInt();
        webblockcb->setChecked(webblockstate);
    }
    /******************************************************************/
    if(webblockstate==true)
    {
     komutSudoExpect("/usr/share/e-ag/webdisable.sh",rootusername,rootpassword);
    }
    if(webblockstate==false)
    {
    komutSudoExpect("iptables -F",rootusername,rootpassword);
    }
       /*********************************************************/

}
void MainWindow::tcpMessageControlSlot(QString _data)
{

    QDesktopWidget widget;
    QRect desktopScreenSize = widget.availableGeometry(widget.primaryScreen());
    FileCrud *fcc=new FileCrud();
    fcc->dosya=localDir+"tcpMessage";
    ///qDebug()<<"dosya bilgi:"<<fcc->dosya;
    /**************************************************************************/
    if (ekranimagestate)
    {
       kaydetTimerSlot(serverIp);
    }
  

  //  if(fcc->fileExists()&&fileToList(localDir,"tcpMessage").count()!=0)
   // {
   //     QStringList str=fileToList(localDir,"tcpMessage");
    QStringList str;
    str.append(_data);
        if(str[0].count()==0){
          ////  qDebug()<<"gelen bilgi YOK!!";
            return;}
        qDebug()<<"gelen bilgi:"<<str;
        QStringList lst=str[0].split("|");
        gelenKomut->setText(lst[1]+"  "+lst[2]);

        if(lst[0]=="dosyatopla")
        {

            //lst[2]
            QString severip=lst[2];
            //lst[4]
            QString username=lst[4];
            //lst[5]
            QString password=lst[5] ;
            QString localusername=lst[5] ;
            hostAddressMacButtonSlot();//local ip adresi tespit ediliyor.

            QDir directory(QDir::homePath()+"\/Masaüstü");
             QStringList filelist = directory.entryList(QStringList() << "e-ag-server.*",QDir::Files);
             QString ad="";
             QString gercekad="";
             foreach(QString filename, filelist) {
                 QFileInfo fi(filename);
                 QString uzanti = fi.completeSuffix();
                 gercekad=QDir::homePath()+"\/Masaüstü\/"+filename;
                 ad="-e-ag-server."+uzanti;
             }

             for(int i=0;i<ipmaclist.count();i++)
             {
                // QString komut="sshpass -p "+password+" scp -o StrictHostKeyChecking=no "+gercekad+" "+
                 //        username+"@"+severip+":\/home\/"+username+"\/Masaüstü\/"+ipmaclist[i].ip+ad;

                 //qDebug()<<komut;
                QString komut="/usr/bin/scd-client "+severip+" 12345 PUT "+gercekad+" /"+ipmaclist[i].ip+ad;
                // system(komut.toStdString().c_str());
                QStringList arguments;
                arguments << "-c" << komut;
                QProcess process;
                process.start("/bin/bash",arguments);
                process.waitForFinished(-1); // will wait forever until finished
                //udpSendData(_mesajtype,_targetPath,_ip);

              /*   QStringList arguments;
                 arguments << "-c" << komut;
                 QProcess process;
                 process.start("/bin/bash",arguments);
                 process.waitForFinished(-1); // will wait forever until finished*/
             }

        }
        if(lst[0]=="webblock")
        {
           

            webblockstate=lst[1].toInt();
            webblockcb->setChecked(webblockstate);

            //twl->setRowCount(0);
            QStringList list=fileToList("/usr/share/e-ag/","webblocklist");
            for(int i=0;i<list.count();i++)
            {
                QString line=list[i];
                QStringList lst=line.split("|");
               // twl->setRowCount(twl->rowCount()+1);
               // twl->setItem(i, 0, new QTableWidgetItem(lst[0]));//ip

            }

            /*************************************************/
            webBlockAktifPasif();
            /**************************************************/

        }
        if(lst[0]=="ekranmesaj")
        {
            qDebug()<<"ekranmesaj:"<<lst[0]<<lst[1];
            ekran->setWindowFlags(Qt::Tool);
            ekran->ekranMesaj("Yönetici Mesajı:",lst[1]);
            ekran->show();

        }
        if(lst[0]=="kilitstatetrue")
        {
            qDebug()<<"ekrankilittrue:"<<lst[0];
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
        if(lst[0]=="kilitstatefalse")
        {
            qDebug()<<"ekrankilitac:"<<lst[0];
            ekran->close();
            kilitstate=false;
        }
        if(lst[0]=="transparankilitstatetrue")
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
        if(lst[0]=="transparankilitstatefalse")
        {
            qDebug()<<"ekrantransparankilitac:"<<lst[0];
            ekran->close();
            transparankilitstate=false;
        }
        if(lst[0]=="ekranimagestatetrue")
        {
            qDebug()<<"GClient:"<<lst[0];
            qDebug()<<"Gelen Mesaj....:"<<lst;
            serverIp=lst[2];
            if (!ekranimagestate)
            {
                kilitstate=false;
                transparankilitstate=false;
                ekranimagestate=true;

                kaydetTimerSlot(serverIp);
                //rootusername=lst[4];
                //rootpassword=lst[5];

            }
        }
        if(lst[0]=="ekranimagestatefalse")
        {
            qDebug()<<"GClient:"<<lst[0];
           ekranimagestate=false;
            kaydetTimerSlot(serverIp);

        }
        if(lst[0]=="x11komut")
        {
           // qDebug()<<"komut:"<<lst[1]<<lst[2]<<lst[3]<<lst[4]<<lst[5]<<lst[6]<<lst[7];
           QString komut="nohup "+lst[1]+" &";
            system(komut.toStdString().c_str());
          //  komutSudoExpect(lst[1],lst[6],lst[7]);
            //qDebug()<<"ekranmesaj:"<<lst[0]<<lst[1];
            ekran->setWindowFlags(Qt::Tool);
            ekran->ekranKomutMesaj("Çalışan Komut:",lst[1]);
            ekran->show();
        }

        if(lst[0]=="consolecommand")
        {
            //qDebug()<<"console komutu geldi....";
            // qDebug()<<"komut:"<<lst[1]<<lst[2]<<lst[3]<<lst[4]<<lst[5]<<lst[6]<<lst[7];
            //QString komut="nohup "+lst[1]+" &";
            //system(komut.toStdString().c_str());
            //  komutSudoExpect(lst[1],lst[6],lst[7]);
            //qDebug()<<"ekranmesaj:"<<lst[0]<<lst[1];
            ekran->setWindowFlags(Qt::Tool);
            ekran->ekranKomutMesaj("Çalışan Komut:",lst[1]);
            ekran->show();
        }

        if(lst[0]=="volumeoff")
        {
            // qDebug()<<"komut:"<<lst[1]<<lst[2]<<lst[3]<<lst[4]<<lst[5]<<lst[6]<<lst[7];
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

        if(lst[0]=="volumeon")
        {
            // qDebug()<<"komut:"<<lst[1]<<lst[2]<<lst[3]<<lst[4]<<lst[5]<<lst[6]<<lst[7];
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

            //  komutSudoExpect(lst[1],lst[6],lst[7]);
        }
        if(lst[0]=="videoyayinbaslat")
        {
            qDebug()<<"komut:"<<lst[0]<<lst[1];

            gst_init(nullptr, nullptr);


            GError *error = NULL;

            // Video ve ses pipeline'ları
            std::string videoPipeline = "udpsrc port=5000 ! application/x-rtp, payload=96 ! rtph264depay ! avdec_h264 ! videoconvert ! autovideosink";
            std::string audioPipeline = "udpsrc port=5001 ! capsfilter caps=\"application/x-rtp, media=(string)audio, clock-rate=(int)48000, encoding-name=(string)OPUS, payload=(int)97\" ! rtpopusdepay ! opusdec ! autoaudiosink";

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
        if(lst[0]=="videoyayindurdur")
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

QStringList MainWindow::listRemove(QStringList list,QString data)
 {
       QRegularExpression re(data);
     for(int i=0;i<list.count();i++)if(list[i].contains(re)) list.removeAt(i);
    // qDebug()<<list;
     return list;
 }
QString MainWindow::listGetLine(QStringList list,QString data)
{
    QRegularExpression re(data);
   for(int i=0;i<list.count();i++) if(list[i].contains(re)) return list[i];
   //qDebug()<<list;
   return "";
}
QStringList MainWindow::fileToList(QString path, QString filename)
{
  FileCrud *fcc=new FileCrud();
  fcc->dosya=path+filename;
 // qDebug()<<fcc->dosya;
  QStringList list;
  for(int i=1;i<=fcc->fileCount();i++)
  {
       QString line=fcc->fileGetLine(i);
      // qDebug()<<line;
       if(line!="")
       {
           line.chop(1);
           QStringList lst=line.split("|");
           QString ln="";
           if(lst.count()>0)ln.append(lst[0]);
           if(lst.count()>1)ln.append("|").append(lst[1]);
           if(lst.count()>2)ln.append("|").append(lst[2]);
           if(lst.count()>3)ln.append("|").append(lst[3]);
           if(lst.count()>4)ln.append("|").append(lst[4]);
           if(lst.count()>5)ln.append("|").append(lst[5]);
           if(lst.count()>6)ln.append("|").append(lst[6]);
           if(lst.count()>7)ln.append("|").append(lst[7]);
           if(lst.count()>8)ln.append("|").append(lst[8]);
           if(lst.count()>9)ln.append("|").append(lst[9]);
           if(lst.count()>10)ln.append("|").append(lst[10]);
           if(lst.count()>11)ln.append("|").append(lst[11]);
           if(lst.count()>12)ln.append("|").append(lst[12]);
           if(lst.count()>13)ln.append("|").append(lst[13]);

             list <<ln;
           //qDebug()<<ln;
           // list <<lst[0]+"|"+lst[1]+"|"+lst[2]+"|"+lst[3]+"|"+lst[4]+"|"+lst[5];

       }
  }
     return list;
}
void MainWindow::listToFile(QString path,QStringList list, QString filename)
{
  FileCrud *fcc=new FileCrud();
  fcc->dosya=path+filename;
  fcc->fileRemove();
  for(int i=0;i<list.count();i++)
  {
       QString line=list[i];
       if(line!="")
       {
           //line.chop(1);
           QStringList lst=line.split("|");
           //qDebug()<<line;
           QString ln="";
           if(lst.count()>0)ln.append(lst[0]);
           if(lst.count()>1)ln.append("|").append(lst[1]);
           if(lst.count()>2)ln.append("|").append(lst[2]);
           if(lst.count()>3)ln.append("|").append(lst[3]);
           if(lst.count()>4)ln.append("|").append(lst[4]);
           if(lst.count()>5)ln.append("|").append(lst[5]);
           if(lst.count()>6)ln.append("|").append(lst[6]);
           if(lst.count()>7)ln.append("|").append(lst[7]);
           if(lst.count()>8)ln.append("|").append(lst[8]);
           if(lst.count()>9)ln.append("|").append(lst[9]);
           if(lst.count()>10)ln.append("|").append(lst[10]);
           if(lst.count()>11)ln.append("|").append(lst[11]);
           if(lst.count()>12)ln.append("|").append(lst[12]);
           if(lst.count()>13)ln.append("|").append(lst[13]);

           //qDebug()<<ln;
           fcc->fileWrite(ln);

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

void MainWindow::komutSudoExpect(QString komut,QString username,QString password)
{
     QStringList liste;
     liste<<"#!/usr/bin/expect";
     liste<<"spawn su - "+username;
     liste<<"expect \"Parola:\"";
     liste<<"send \""+password+"\\n\"";
     liste<<"send \""+password+"\\n\"";
     liste<<"send \"echo "+password+"|sudo -S "+komut+"\\n\"";
     liste<<"send \"exit\\n\"";
     liste<<"interact";
     listToFile("/home/"+QDir::homePath().split("/")[2]+"/",liste,"run.sh");


     QString kmt22="chmod 777 /home/"+QDir::homePath().split("/")[2]+"/run.sh";
     system(kmt22.toStdString().c_str());


     QString result="";
     QStringList arguments;
     arguments << "-c" << QString("/home/"+QDir::homePath().split("/")[2]+"/run.sh");
     QProcess process;
     process.start("/bin/bash",arguments);
     if(process.waitForFinished())
     {
         // version = process.readAll();
         //   result.chop(3);
     }

     QString kmt24="rm -rf /home/"+QDir::homePath().split("/")[2]+"/run.sh";
     system(kmt24.toStdString().c_str());

}
