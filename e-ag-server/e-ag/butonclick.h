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
#ifndef BUTONCLICK_H
#define BUTONCLICK_H
#include<QAbstractButton>
#include<QTableWidget>
#include<QApplication>
#include<QDesktopServices>
#include<QDateTime>
#include <gst/gst.h>
#include <iostream>
#include<Database.h>

void MainWindow::wolSlot()
{
   // qDebug()<<"ayar click";
    QDialog * d = new QDialog();
    d->setWindowTitle("Kapalı Host Listesi");
    d->setFixedSize(QSize(boy*100,boy*100));
    d->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    auto appIcon = QIcon(":/icons/e-ag.svg");
    d->setWindowIcon(appIcon);

    /***********************************************************************/
   QTableWidget *twl=new QTableWidget;

    twl->setFixedSize(QSize(boy*95,boy*75));
    twl->setColumnCount(4);
    //twl->setRowCount(0);

    twl->setHorizontalHeaderItem(0, new QTableWidgetItem("Seç"));
    twl->setHorizontalHeaderItem(1, new QTableWidgetItem("Ip"));
    twl->setHorizontalHeaderItem(2, new QTableWidgetItem("Mac"));
    twl->setHorizontalHeaderItem(3, new QTableWidgetItem("Adı"));

    twl->setSelectionBehavior(QAbstractItemView::SelectRows);
    twl->setSelectionMode(QAbstractItemView::SingleSelection);
    //connect(tw, &QTableWidget::cellClicked, this, cellClicked());
    twl->setRowCount(0);
    twl->setColumnWidth(0, boy*5);
    twl->setColumnWidth(1, boy*25);
    twl->setColumnWidth(2,boy*30);
    twl->setColumnWidth(3,boy*30);
    DatabaseHelper *db=new DatabaseHelper(localDir+"persist.json");
    QJsonArray dizi=db->Oku();
    int sr=0;

    for (const QJsonValue &item : dizi) {
        QJsonObject veri=item.toObject();
            twl->setRowCount(twl->rowCount()+1);
            QCheckBox *mCheck = new QCheckBox();
            mCheck->setChecked(false);
            twl->setCellWidget(sr,0,mCheck);
            //qDebug()<<"Kayıtlı Host.";
            twl->setItem(sr, 1, new QTableWidgetItem(veri.value("mac").toString()));//ip
            twl->setItem(sr, 2, new QTableWidgetItem(veri.value("ip").toString()));//mac
            twl->setItem(sr, 3, new QTableWidgetItem(veri.value("caption").toString()));//caption
            //twl->setItem(sr, 4, new QTableWidgetItem(veri.value("hostname").toString()));//name
            sr++;
    }

    /********************************************************************/
        QToolButton *powerOnButton= new QToolButton;
        powerOnButton->setFixedSize(QSize(boy*40,boy*10));
        powerOnButton->setIconSize(QSize(boy*40,boy*5));
        powerOnButton->setStyleSheet("Text-align:center");
        powerOnButton->setIcon(QIcon(":/icons/boot.svg"));
        powerOnButton->setAutoRaise(true);
        powerOnButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        // powerOnButton->setFont(f2);
        powerOnButton->setText("Seçili Pc'leri Aç");

        connect(powerOnButton, &QPushButton::clicked, [=]() {
            int numRows = twl->rowCount();

            for ( int i = 0 ; i < numRows ; i++)
            {

                QCheckBox* mBox = static_cast<QCheckBox*> (twl->cellWidget(i,0));
                 if (mBox->isChecked())
                {
                     QString _ip = twl->model()->data(twl->model()->index(i, 1)).toString().simplified();
                     QString _mac = twl->model()->data(twl->model()->index(i, 2)).toString().simplified();
                     QString ad = twl->model()->data(twl->model()->index(i, 3)).toString().simplified();
                   // qDebug()<<i<<mBox->isChecked()<<_ip<<_mac<<ad;

                      slotWakeOnLan(_ip,_mac);
                }
            }

        });
        /*********************************************************************/
        /********************************************************************/
      QToolButton *powerOnButtonAll= new QToolButton;
      powerOnButtonAll->setFixedSize(QSize(boy*40,boy*10));
      powerOnButtonAll->setIconSize(QSize(boy*40,boy*5));
      powerOnButtonAll->setStyleSheet("Text-align:center");
      powerOnButtonAll->setIcon(QIcon(":/icons/boot.svg"));
      powerOnButtonAll->setAutoRaise(true);
      powerOnButtonAll->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
      // powerOnButtonAll->setFont(f2);
      powerOnButtonAll->setText("Tüm Pc'leri Aç");

      connect(powerOnButtonAll, &QPushButton::clicked, [=]() {
          int numRows = twl->rowCount();
          for ( int i = 0 ; i < numRows ; i++)
          {
              QString _ip = twl->model()->data(twl->model()->index(i, 1)).toString().simplified();
              QString _mac = twl->model()->data(twl->model()->index(i, 2)).toString().simplified();
              // QString ad = twl->model()->data(twl->model()->index(i, 3)).toString().simplified();
              // qDebug()<<i<<mBox->isChecked()<<ip<<mac<<ad;
              slotWakeOnLan(_ip,_mac);
          }
      });
      /*********************************************************************/

        QVBoxLayout * vbox = new QVBoxLayout();
        vbox->addWidget(twl);
        QHBoxLayout * hbox = new QHBoxLayout();
        hbox->addWidget(powerOnButton);
        hbox->addWidget(powerOnButtonAll);
        vbox->addLayout(hbox);

        d->setLayout(vbox);
        d->exec();


}

QWidget*  MainWindow::sliderWidget()
{
    QWidget *sWidget=new QWidget();

    slider = new QSlider(sWidget);

    slider->setMinimum(100);
    slider->setMaximum(300);
    slider->setValue(100);
    slider->setSingleStep(50);
    //slider->setSingleStep(10);
    slider->setFixedSize(100,25);

     slider->setOrientation(Qt::Horizontal);
     slider->setStyleSheet("QSlider::groove:horizontal { "
                               "border: 0px solid #990000; "
                               "height: 5px; "
                               "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4); "
                               "margin: 5px 0px; "
                               "} "
                               "QSlider::handle:horizontal { "
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #b4b4b4); "
                               "border: 0px solid #00005c; "
                               "width: 15px; "
                               "height: 8px; "
                               "margin: -8px 0px; "
                               "} ");

         QLabel *label1 = new QLabel("100",sWidget);
         QLabel *label2 = new QLabel("200",sWidget);
         QLabel *label3 = new QLabel("300",sWidget);
         sliderValuelabel = new QLabel("100",sWidget);
         int fnt=font.toInt();
         label1->setStyleSheet("font-size:"+QString::number(fnt-5)+"px; background-color:rgba(0,255,0,0);");
         label2->setStyleSheet("font-size:"+QString::number(fnt-5)+"px; background-color:rgba(0,255,0,0);");
         label3->setStyleSheet("font-size:"+QString::number(fnt-5)+"px; background-color:rgba(0,255,0,0);");
         sliderValuelabel->setStyleSheet("font-size:"+QString::number(fnt-5)+"px; background-color:rgba(0,255,0,0);");
         sliderValuelabel->setFixedSize(en*3,boy*4);
         QGridLayout *layouts = new QGridLayout(sWidget);
         layouts->setContentsMargins(0, 0, 0,0);
         layouts->setVerticalSpacing(0);
         layouts->setHorizontalSpacing(0);

         layouts->addWidget(slider, 0, 0, 1, 3,Qt::AlignCenter);
         layouts->addWidget(sliderValuelabel, 0, 3, 2, 1,Qt::AlignCenter);
         layouts->addWidget(label1, 1, 0, 1, 1,Qt::AlignLeft);
         layouts->addWidget(label2, 1, 1, 1, 1,Qt::AlignCenter);
         layouts->addWidget(label3, 1, 2, 1, 1,Qt::AlignRight);
         connect(slider, SIGNAL(valueChanged(int)), SLOT(updateSlider(int)),Qt::QueuedConnection);
         sWidget->setFixedSize(en*23,boy*5);
         sWidget->setLayout(layouts);
         return sWidget;
}
QWidget* MainWindow::videoWidget()
{
    int e=en;
    int b=boy;
   // qDebug()<<"ayar click";
    QFont ff( "Arial", 15, 0);
    int yukseklik=b*7.5;

    QWidget * d = new QWidget();
    d->setWindowTitle("video Yayın Penceresi");
    QToolButton *videoStopButton=new QToolButton();
    QToolButton *liveStreamStopButton=new QToolButton();

    QLineEdit *commandFileLE = new QLineEdit();
    commandFileLE->setFixedSize(e*50,yukseklik);
    //commandFileLE->setFont(ff);
    commandFileLE->setStyleSheet("font-size:"+QString::number(font.toInt()+2)+"px;");

    QLabel *commandFileLabel=new QLabel("Video Dosyası:");
     commandFileLabel->setFixedSize(e*15,yukseklik);
     commandFileLabel->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

     QComboBox * kamera = new QComboBox();
     kamera->setFixedSize(e*25,yukseklik);
    // kamera->setFont(ff);
     kamera->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
     /**********************************video giriş listesi alma işlemi******************************************************/

     QStringList kameralst;
     if(QFile::exists("/dev/video0"))kameralst<<"/dev/video0";
     if(QFile::exists("/dev/video1"))kameralst<<"/dev/video1";
     if(QFile::exists("/dev/video2"))kameralst<<"/dev/video2";
     if(QFile::exists("/dev/video3"))kameralst<<"/dev/video3";
     if(QFile::exists("/dev/video4"))kameralst<<"/dev/video4";
     kamera->addItems(kameralst);
     /****************************************************************************************/

      QComboBox * ses = new QComboBox();
      ses->setFixedSize(e*24.5,yukseklik);
     // ses->setFont(ff);
      ses->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
      /**********************************ses giriş listesi alma işlemi******************************************************/
      QString result="";
      QStringList arguments;
      arguments << "-c" << QString("pactl list short sources|grep 'input'|awk '{print $1,\"|\",$2}'");
      QProcess process;
      process.start("/bin/bash",arguments);
      if(process.waitForFinished(-1))
      {
         result = process.readAll();
         result.chop(1);
      }
      if(result!="")
      {
          QStringList seslst;
          seslst=result.split("\n");
          ses->addItems(seslst);
      }
      /****************************************************************************************/
    QLabel *pathLabel=new QLabel("Kamera ve Ses:");
    pathLabel->setFixedSize(e*15,yukseklik);
    pathLabel->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    // messageBox.setIcon(QMessageBox::Question);



    QToolButton *videoYayinButton=new QToolButton();
    videoYayinButton->setFixedSize(e*16,yukseklik*2);
    videoYayinButton->setAutoRaise(true);
   // videoYayinButton->setAutoFillBackground(true);
    videoYayinButton->setIcon(QIcon(":/icons/selectpcvideo.svg"));
    videoYayinButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    videoYayinButton->setIconSize(QSize(b*8,yukseklik*0.9));
    videoYayinButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    videoYayinButton->setText("Seçili \nPc'lerde\n Video Yayınla");
      connect(videoYayinButton, &QToolButton::clicked, [=]() {
       // if(pcMac->text()==""){mesajSlot("Pc Seçiniz");return;}
          QString name = QUrl::fromLocalFile(commandFileLE->text()).path(QUrl::FullyEncoded);
         name.replace("%20","%5C%20");
          QUrl pth;

        if(commandFileLE->text()!="")
        {
            QString result="";
            QStringList arguments;
            QString kmt="ffmpeg -re -i "+pth.fromPercentEncoding(name.toUtf8())+" -vcodec libx264 -g 20 -s 400x300 -acodec aac -strict -2 -f flv rtmp://127.0.0.1/live/stream";
            qDebug()<<"komut:"<<kmt;
            arguments << "-c" << kmt;

            videoProcess.start("/bin/bash",arguments);
            streamState=true;

            videoStopButton->setStyleSheet("background-color: #ff0000");
             mesajSlot("Komut Çalıştırıldı");

             hostAddressMacButtonSlot();

             for(int k=0;k<ipmaclist.count();k++)
             {

                 QString  kmt;
                 kmt.append("vlc rtmp://"+ipmaclist[k].ip+"/live/stream");

                 for(int i=0;i<onlinePcList.count();i++)
                 {
                     if(onlinePcList[i]->connectState&&
                     (onlinePcList[i]->select||onlinePcList[i]->multiSelect)&&
                      ipmaclist[k].ip.section(".",0,2)==onlinePcList[i]->ip.section(".",0,2))
                     {
                         udpSendData("x11komut",kmt,onlinePcList[i]->ip);

                     }
                 }
                 system("sleep 0.1");
             }



            mesajSlot("Seçili Pc'lere Komut Gönderildi.");



        }
    });



     QToolButton *videoYayinAllButton=new QToolButton();
     videoYayinAllButton->setFixedSize(e*16,yukseklik*2);
     videoYayinAllButton->setAutoRaise(true);
    // videoYayinAllButton->setAutoFillBackground(true);
     videoYayinAllButton->setIcon(QIcon(":/icons/allpcvideo.svg"));
     videoYayinAllButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

     videoYayinAllButton->setIconSize(QSize(b*8,yukseklik*0.9));
     videoYayinAllButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
     videoYayinAllButton->setText("Tüm \nPc'lerde\nVideo Yayınla");
     connect(videoYayinAllButton, &QToolButton::clicked, [=]() {
         QString name = QUrl::fromLocalFile(commandFileLE->text()).path(QUrl::FullyEncoded);
        name.replace("%20","%5C%20");
         QUrl pth;
        //String::toStdString()
        //pth.fromPercentEncoding(name.toUtf8()).
         /*if(commandFileLE->text()!="")
         {
             QString result="";
             QStringList arguments;
             QString kmt="ffmpeg -re -i "+pth.fromPercentEncoding(name.toUtf8())+" -vcodec libx264 -g 20 -s 400x300 -acodec aac -strict -2 -f flv rtmp://127.0.0.1/live/stream";
             qDebug()<<kmt;

             arguments << "-c" << kmt;
             videoProcess.start("/bin/bash",arguments);
             streamState=true;
             videoStopButton->setStyleSheet("background-color: #ff0000");
             mesajSlot("Komut Ağda Çalıştırıldı");
             /***********************************************/
             /*hostAddressMacButtonSlot();
             for(int k=0;k<ipmaclist.count();k++)
             {
                 QString  kmt;
                 kmt.append("vlc rtmp://"+ipmaclist[k].ip+"/live/stream");
                 for(int i=0;i<btnlist.count();i++)
                 {
                     if(btnlist[i]->connectState&&
                     ipmaclist[k].ip.section(".",0,2)==btnlist[i]->ip.section(".",0,2))
                     {
                         udpSendData("x11komut",kmt,btnlist[i]->ip);
                     }
                 }
                 system("sleep 0.1");
             }
            mesajSlot("Ağ'a Komut Gönderildi.");
         }*/
        if(commandFileLE->text()!="")
         {
         gst_init(nullptr, nullptr);

         GError *error = NULL;

         std::string videoPipeline = "filesrc location="+pth.fromPercentEncoding(name.toUtf8()).toStdString()+" ! decodebin ! videoconvert ! x264enc tune=zerolatency bitrate=1024 ! rtph264pay ! udpsink host=239.0.0.1 port=5000 filesrc location="+pth.fromPercentEncoding(name.toUtf8()).toStdString()+" ! decodebin ! audioconvert ! opusenc ! rtpopuspay ! udpsink host=239.0.0.1 port=5001";
         // Video pipeline'ı oluştur
         video_pipeline = gst_parse_launch(videoPipeline.c_str(), &error);
         if (error) {
             std::cerr << "Video pipeline oluşturulamadı: " << error->message << std::endl;
             g_clear_error(&error);
             return;
         }
         gst_element_set_state(video_pipeline, GST_STATE_PLAYING);
         slotSelectCommand("videoyayinbaslat","");
        }
     });

     fileSelectButton=new QToolButton();
     fileSelectButton->setFixedSize(e*8,yukseklik*2);
     fileSelectButton->setAutoRaise(true);
     fileSelectButton->setIcon(QIcon(":/icons/openfile.svg"));
     fileSelectButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

     fileSelectButton->setIconSize(QSize(b*6,yukseklik*0.9));
     fileSelectButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
      fileSelectButton->setText("...");
      connect(fileSelectButton, &QToolButton::clicked, [=]() {

          pcClickSlot(pcMac->text());
          QString fileName = QFileDialog::getOpenFileName(this,tr("Dosya Seç"),QDir::homePath(), tr("Files (*.*)"));
      //qDebug()<<fileName;
          commandFileLE->setText(fileName);

       mesajSlot("Dosya Seçildi.");
});


     QToolButton *liveStreamButton=new QToolButton();
     liveStreamButton->setFixedSize(e*16,yukseklik*2);
     liveStreamButton->setAutoRaise(true);
     liveStreamButton->setIcon(QIcon(":/icons/selectpccamera.svg"));
     liveStreamButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

     liveStreamButton->setIconSize(QSize(b*8,yukseklik*0.9));
     liveStreamButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
      liveStreamButton->setText("Seçili\n Pc'lere\n Kam. Yayınla");
         connect(liveStreamButton, &QToolButton::clicked, [=]() {
             QString sslst;
             sslst=ses->currentText();
            // if(pcMac->text()==""){mesajSlot("Pc Seçiniz");return;}
              QString result="";
              QStringList arguments;
              QString kmt="ffmpeg -re -i "+kamera->currentText()+" -f pulse -i "+sslst.split("|")[1]+" -ac "+sslst.split("|")[0]+" -vcodec libx264 -g 20 -s 400x300 -acodec aac -strict -2 -f flv rtmp://127.0.0.1/live/stream";
              qDebug()<<kmt;

                      arguments << "-c" << kmt;
               videoProcess.start("/bin/bash",arguments);
               streamState=true;
               liveStreamStopButton->setStyleSheet("background-color: #ff0000");
                mesajSlot("Dosya Seçili Pc'ye Kopyalandı.");
               /****************************************************/
            //  if(pcMac->text()==""){mesajSlot("Pc Seçiniz");return;}
               ///  slotCommand("vlc rtmp://"+myIpAddress+"/live/stream");
                hostAddressMacButtonSlot();
           for(int k=0;k<ipmaclist.count();k++)
                {
                    QString  kmt;
                    kmt.append("vlc rtmp://"+ipmaclist[k].ip+"/live/stream");
                    for(int i=0;i<onlinePcList.count();i++)
                    {
                        if(onlinePcList[i]->connectState&&
                        (onlinePcList[i]->select||onlinePcList[i]->multiSelect)&&
                        ipmaclist[k].ip.section(".",0,2)==onlinePcList[i]->ip.section(".",0,2))
                        {
                            udpSendData("x11komut",kmt,onlinePcList[i]->ip);
                        }
                    }
                    system("sleep 0.1");
                }
              mesajSlot("Seçili Pc'ye Komut Gönderildi.");



   });
    QToolButton *liveStreamAllButton=new QToolButton();
     liveStreamAllButton->setFixedSize(e*16,yukseklik*2);
     liveStreamAllButton->setAutoRaise(true);
     liveStreamAllButton->setIcon(QIcon(":/icons/allpccamera.svg"));
     liveStreamAllButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

     liveStreamAllButton->setIconSize(QSize(b*8,yukseklik*0.9));
     liveStreamAllButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
      liveStreamAllButton->setText("Tüm \nPc'lere \nKam. Yayınla");
         connect(liveStreamAllButton, &QToolButton::clicked, [=]() {
          /* if(ses->currentText()!=""&&kamera->currentText()!="")
           {
             QString sslst=ses->currentText();

             QString result="";
             QStringList arguments;
             QString kmt="ffmpeg -re -i "+kamera->currentText()+" -f pulse -i "+sslst.split("|")[1]+" -ac "+sslst.split("|")[0]+" -vcodec libx264 -g 20 -s 400x300 -acodec aac -strict -2 -f flv rtmp://127.0.0.1/live/stream";

             qDebug()<<kmt;

                     arguments << "-c" << kmt;
              videoProcess.start("/bin/bash",arguments);
              streamState=true;
              liveStreamStopButton->setStyleSheet("background-color: #ff0000");
           mesajSlot("video Ağ'a Yayınlandı.");
           /***********************************************/
           /*hostAddressMacButtonSlot();
      for(int k=0;k<ipmaclist.count();k++)
           {
               QString  kmt;
               kmt.append("vlc rtmp://"+ipmaclist[k].ip+"/live/stream");
               for(int i=0;i<btnlist.count();i++)
               {
                   if(btnlist[i]->connectState&&
                   ipmaclist[k].ip.section(".",0,2)==btnlist[i]->ip.section(".",0,2))
                   {
                       udpSendData("x11komut",kmt,btnlist[i]->ip);
                   }
               }
               system("sleep 0.1");
           }


          mesajSlot("Ağ'a Komut Gönderildi.");
           }*/
          gst_init(nullptr, nullptr);

          GError *error = NULL;

          // Video ve ses pipeline'ları
          //std::string videoPipeline = "v4l2src device=/dev/video0 ! videoconvert ! x264enc tune=zerolatency ! rtph264pay config-interval=1 pt=96 ! udpsink host=192.168.1.255 port=5000";
          //std::string audioPipeline = "autoaudiosrc ! audioconvert ! opusenc ! rtpopuspay pt=97 ! udpsink host=192.168.1.255 port=5001";
          //alsasrc device=hw:1,0
          video_pipeline = gst_pipeline_new ("vmypipeline");
          audio_pipeline = gst_pipeline_new ("amypipeline");
          GstElement *video_source = gst_element_factory_make ("v4l2src", "source"); // Kamera kaynağı
          GstElement *video_convert = gst_element_factory_make ("videoconvert", "convert");
          GstElement *video_encode = gst_element_factory_make ("x264enc", "encode"); // Video kodlayıcı
          GstElement *video_pay = gst_element_factory_make ("rtph264pay", "pay"); // RTP paketleyici
          GstElement *video_sink = gst_element_factory_make ("udpsink", "sink"); // UDP yayını
          g_object_set (G_OBJECT (video_sink), "host", "239.0.0.1", "port", 5000, NULL); // Hedef IP ve port
          g_object_set(video_encode, "tune", 4, NULL); // veya "stillimage", "fastdecode" vb.



          GstElement *audio_source = gst_element_factory_make("autoaudiosrc", "audio-source");
          GstElement *audio_encode = gst_element_factory_make("opusenc", "opus-encoder");
          GstElement *audio_convert = gst_element_factory_make("audioconvert", "audio_convert");
          GstElement *audio_pay = gst_element_factory_make("rtpopuspay", "rtp-payloader");
          GstElement *audio_sink = gst_element_factory_make("udpsink", "udp-sink");
          g_object_set (G_OBJECT (audio_sink), "host", "239.0.0.1", "port", 5001, NULL); // Hedef IP ve port
          g_object_set(audio_pay, "pt", 97, NULL);


          gst_bin_add_many (GST_BIN (audio_pipeline), audio_source, audio_convert,audio_encode, audio_pay, audio_sink, NULL);
          gst_element_link_many (audio_source,audio_convert, audio_encode, audio_pay,audio_sink, nullptr);

          gst_bin_add_many (GST_BIN (video_pipeline), video_source, video_convert, video_encode, video_pay, video_sink, NULL);
          gst_element_link_many (video_source, video_convert, video_encode, video_pay, video_sink, nullptr);

          GstStateChangeReturn video_ret = gst_element_set_state(video_pipeline, GST_STATE_PLAYING);
          GstStateChangeReturn audio_ret  = gst_element_set_state(audio_pipeline, GST_STATE_PLAYING);

          if (video_ret == GST_STATE_CHANGE_FAILURE) {
              std::cout << "video  başlatılamadı." << std::endl;
          }
          if (audio_ret == GST_STATE_CHANGE_FAILURE) {
              std::cout << "ses  başlatılamadı." << std::endl;
          }
        slotSelectCommand("videoyayinbaslat","");
           ///std::cout << "Yayın başladı (Ctrl+C ile durdurun)..." << std::endl;

          // Yayın devam ederken (Ctrl+C ile durdurulana kadar) bekleyin
          ///GMainLoop *loop = g_main_loop_new(NULL, FALSE);
          ///g_main_loop_run(loop);

          // Pipeline'ları durdur ve temizle
        /*  gst_element_set_state(video_pipeline, GST_STATE_NULL);
          gst_object_unref(video_pipeline);
          gst_element_set_state(audio_pipeline, GST_STATE_NULL);
          gst_object_unref(audio_pipeline);*/

   });
            videoStopButton->setFixedSize(e*12,yukseklik*2);
          videoStopButton->setAutoRaise(true);
          videoStopButton->setIcon(QIcon(":/icons/videostop.svg"));
          videoStopButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

          videoStopButton->setIconSize(QSize(b*8,yukseklik*0.9));
          videoStopButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            videoStopButton->setText("Video\nYayınını\nDurdur");
            connect(videoStopButton, &QToolButton::clicked, [=]() {
                if(streamState)
                {
                    /*videoProcess.terminate();
                    streamState=false;
                    videoStopButton->setStyleSheet("background-color: #dcdcdc");
                    slotPcCommandSelect("pkill vlc");*/
                    gst_element_set_state(video_pipeline, GST_STATE_NULL);
                    gst_object_unref(video_pipeline);
                    //gst_element_set_state(audio_pipeline, GST_STATE_NULL);
                    //gst_object_unref(audio_pipeline);
                    slotSelectCommand("videoyayindurdur","");
                    mesajSlot("Video durduruldu.");
                }

            });


          liveStreamStopButton->setFixedSize(e*12,yukseklik*2);
          liveStreamStopButton->setAutoRaise(true);
          liveStreamStopButton->setIcon(QIcon(":/icons/camerastop.svg"));
          liveStreamStopButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

          liveStreamStopButton->setIconSize(QSize(b*8,yukseklik*0.9));
          liveStreamStopButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
          liveStreamStopButton->setText("Kamera\nYayınını\nDurdur");
          connect(liveStreamStopButton, &QToolButton::clicked, [=]() {
              if(streamState)
              {
                  /*videoProcess.terminate();
                  streamState=false;
                  liveStreamStopButton->setStyleSheet("background-color: #dcdcdc");
                  slotPcCommandSelect("pkill vlc");
                  mesajSlot("Video durduruldu.");

*/
                  // Pipeline'ları durdur ve temizle
                  gst_element_set_state(video_pipeline, GST_STATE_NULL);
                  gst_object_unref(video_pipeline);
                  gst_element_set_state(audio_pipeline, GST_STATE_NULL);
                  gst_object_unref(audio_pipeline);
                slotSelectCommand("videoyayindurdur","");
              }

          });

          QToolButton *helpButton= new QToolButton;
          helpButton->setFixedSize(e*8,yukseklik*2);
          helpButton->setAutoRaise(true);
         // bilgiButton->setAutoFillBackground(true);
          helpButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
          helpButton->setText("Yardım");
          helpButton->setIcon(QIcon(":/icons/help.svg"));
          helpButton->setIconSize(QSize(b*8,yukseklik*0.9));
          helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

          connect(helpButton, &QToolButton::clicked, [=]() {
              QTextDocument *doc=new QTextDocument();

                   doc->setHtml("<center><h2>Video/Kamera Yayını</h2></center>"
                                "<center><img src=\":/icons/video.png\" /></center> "
                           "<br/>1-Sunucudaki bir Video Dosyası/Kamera login olmuş kullanıcılarda paylaşılabillir."
                           "<center><img src=\":/icons/istemci.png\" /></center>"
                           "<br/><br/>2-Video Dosyası/Kamera sadece X işareti yeşil olan istemcilere paylaşılabilir."
                           "<br/><br/>3-İstemci simgelerinin altındaki X işareti login olmuş kullanıcıyı ifade eder."
                           "<br/><br/>4-X işareti yeşilse kullanıcı login olduğunu ifade eder. Kırmızı ise login olmadığını ifade eder."
                           "<br/><br/>5-Birden fazla istemciye Video Dosyası/Kamera paylaşmak için istemci simgelerine çift tıklayıp seçilerek paylaşılabilir."
                                         );
                   QPrinter pdf;
                   pdf.setOutputFileName("/tmp/video.pdf");
                   pdf.setOutputFormat(QPrinter::PdfFormat);
                   doc->print(&pdf);

                   QTextEdit *document = new QTextEdit();
                   document->setReadOnly(true);
                   //  document->show();
                   document->setDocument(doc);
                   QVBoxLayout * vbox = new QVBoxLayout();
                   QHBoxLayout * hbox1= new QHBoxLayout();

                   // hbox1->addWidget(commandFileLabel);
                   hbox1->addWidget(document);

                   vbox->addLayout(hbox1);
                   QDialog * d1 = new QDialog();
                   d1->setWindowTitle("Video/Kamera Yayın Yardım Penceresi");
                   d1->setFixedSize(QSize(boy*150,boy*120));
                   auto appIcon = QIcon(":/icons/e-ag.svg");
                   d1->setWindowIcon(appIcon);

                   d1->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

                   d1->setLayout(vbox);
                   d1->exec();

       });
          QGridLayout * vbox = new QGridLayout();
        //  vbox->setSpacing(0);
          vbox->setContentsMargins(0, 0,0,0);
          vbox->setVerticalSpacing(0);

          vbox->addWidget(commandFileLabel,1,1,1,1,Qt::AlignLeft);
          vbox->addWidget(commandFileLE,1,2,1,2,Qt::AlignLeft);
          vbox->addWidget(pathLabel,2,1,1,1,Qt::AlignLeft);
          vbox->addWidget(kamera,2,2,1,1,Qt::AlignLeft);
          vbox->addWidget(ses,2,3,1,1,Qt::AlignLeft);

          vbox->addWidget(fileSelectButton,1,5,2,1,Qt::AlignLeft);
          vbox->addWidget(videoYayinButton,1,6,2,1,Qt::AlignLeft);
          vbox->addWidget(videoYayinAllButton,1,7,2,1,Qt::AlignLeft);
          vbox->addWidget(videoStopButton,1,8,2,1,Qt::AlignLeft);


          vbox->addWidget(liveStreamButton,1,9,2,1,Qt::AlignLeft);
          vbox->addWidget(liveStreamAllButton,1,10,2,1,Qt::AlignLeft);
          vbox->addWidget(liveStreamStopButton,1,11,2,1,Qt::AlignLeft);

          vbox->addWidget(helpButton,1,12,2,1,Qt::AlignLeft);

          d->setLayout(vbox);
return d;
}
QWidget* MainWindow::duyuruWidget()
{
    int e=en;
    int b=boy;
   // qDebug()<<"ayar click";
    QFont ff( "Arial", 20, 0);
    int yukseklik=b*7;
    QWidget * d = new QWidget();
     d->setFixedSize(this->width(),boy*16);
    d->setWindowTitle("Duyuru Mesaj Penceresi");
    QLineEdit *commandFileLE = new QLineEdit();
    commandFileLE->setFixedSize(e*80,boy*15);
   // commandFileLE->setFont(ff);
    commandFileLE->setStyleSheet("font-size:"+QString::number(font.toInt()+2)+"px;");

    QLabel *commandFileLabel=new QLabel("Mesaj / Duyuru");
    commandFileLabel->setFixedSize(e*15,yukseklik);
    commandFileLabel->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");



   QToolButton *duyuruButton=new QToolButton();
    duyuruButton->setFixedSize(e*24,yukseklik*2);
    duyuruButton->setAutoRaise(true);
   // duyuruButton->setAutoFillBackground(true);
    duyuruButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    duyuruButton->setText("Seçili Pc'lere Gönder");
    duyuruButton->setIcon(QIcon(":/icons/selectpcmessage.svg"));
    duyuruButton->setIconSize(QSize(b*8,yukseklik));
    duyuruButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

     connect(duyuruButton, &QToolButton::clicked, [=]() {
         if(pcMac->text()==""){mesajSlot("Pc Seçiniz");return;}
         slotSelectPcMesaj(commandFileLE->text());

         mesajSlot("Seçili Pc'ye Mesaj Gönderildi.");
 });



    QToolButton *duyuruAllButton=new QToolButton();
     duyuruAllButton->setFixedSize(e*24,yukseklik*2);
     duyuruAllButton->setAutoRaise(true);
    // duyuruAllButton->setAutoFillBackground(true);
     duyuruAllButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
     duyuruAllButton->setText("Tüm Pc'lere Gönder");
     duyuruAllButton->setIcon(QIcon(":/icons/allpcmessage.svg"));
     duyuruAllButton->setIconSize(QSize(b*8,yukseklik));
     duyuruAllButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

      connect(duyuruAllButton, &QToolButton::clicked, [=]() {
            for(int i=0;i<onlinePcList.count();i++)
          {
              if(onlinePcList[i]->pcState)
              {
                udpSendData("ekranmesaj",commandFileLE->text(),onlinePcList[i]->ip);

              }
          }
         mesajSlot("Ağ'a Mesaj Gönderildi.");
 });

      QToolButton *helpButton= new QToolButton;
      helpButton->setFixedSize(e*12,yukseklik*2);
      helpButton->setAutoRaise(true);
     // bilgiButton->setAutoFillBackground(true);
      helpButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
      helpButton->setText("Yardım");
      helpButton->setIcon(QIcon(":/icons/help.svg"));
      helpButton->setIconSize(QSize(b*8,yukseklik));
      helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

      connect(helpButton, &QToolButton::clicked, [=]() {
                   QTextDocument *doc=new QTextDocument();

           doc->setHtml("<center><h2>Mesaj Gönderme</h2></center>"
                        "<center><img src=\":/icons/mesaj.png\" /></center> "
                        "<br/>1-Mesaj sadece X işareti yeşil olan istemcilere gönderilebilir."
                        "<center><img src=\":/icons/istemci.png\" /></center>"
                        "<br/><br/>2-İstemci simgelerinin altındaki X işareti login olmuş kullanıcıyı ifade eder."
                        "<br/><br/>3-X işareti yeşilse kullanıcı login olduğunu ifade eder. Kırmızı ise login olmadığını ifade eder."
                        "<br/><br/>4-Birden fazla istemciye mesaj göndermek için istemci simgelerine çift tıklayıp seçilerek gönderilebilir."
                                        );
           QPrinter pdf;
               pdf.setOutputFileName("/tmp/mesaj.pdf");
               pdf.setOutputFormat(QPrinter::PdfFormat);
               doc->print(&pdf);

           QTextEdit *document = new QTextEdit();
           document->setReadOnly(true);
           //  document->show();
            document->setDocument(doc);
           QVBoxLayout * vbox = new QVBoxLayout();
            QHBoxLayout * hbox1= new QHBoxLayout();

           // hbox1->addWidget(commandFileLabel);
            hbox1->addWidget(document);

            vbox->addLayout(hbox1);
            QDialog * d1 = new QDialog();
            d1->setWindowTitle("Mesaj Gönderme Penceresi");
            d1->setFixedSize(QSize(boy*150,boy*120));
            auto appIcon = QIcon(":/icons/e-ag.svg");
            d1->setWindowIcon(appIcon);

            d1->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

            d1->setLayout(vbox);
             d1->exec();
   });



     auto layout = new QGridLayout(d);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

    layout->addWidget(commandFileLabel, 0,0,1,1,Qt::AlignCenter);
    layout->addWidget(commandFileLE, 0,1,1,1,Qt::AlignCenter);
    layout->addWidget(duyuruButton, 0,2,1,1,Qt::AlignCenter);
    layout->addWidget(duyuruAllButton, 0,3,1,1,Qt::AlignCenter);
    layout->addWidget(helpButton, 0,4,1,1,Qt::AlignCenter);


    d->setLayout(layout);

    return d;

}

QWidget* MainWindow::languageWidget()
{
    int e=en;
    int b=boy;
    int yukseklik=e*12;

    QWidget *sor=new QWidget();
    sor->setWindowTitle("Çoklu Dil");
    sor->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    sor->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Tool);
    sor->setFixedSize(e*8,b*16);

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - sor->width())/2;
    int y = (screenGeometry.height() - sor->height()) / 2;
    sor->move(x, y);
    /******************************************************/
    QString appPath ="/usr/share/e-ag";// a.applicationDirPath();
    QSettings cfg(appPath + "/config.cfg",QSettings::IniFormat);
    QString language = cfg.value("language").toString();
    /******************************************************/
    QToolButton *languageLabelButton= new QToolButton();
    languageLabelButton->setIcon(QIcon(":/icons/language.svg"));
    languageLabelButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    languageLabelButton->setFixedSize(e*8,b*5);
    languageLabelButton->setAutoRaise(true);
    //languageLabelButton->setAutoFillBackground(true);
    languageLabelButton->setText(language.split("_")[0]);
    languageLabelButton->setStyleSheet("font-size:"+QString::number(font.toInt())+"px;");

    QToolButton *languageMenuButton= new QToolButton();
        // sessionMenuButton->setIcon(QIcon(":/icons/transparanlock.svg"));
    languageMenuButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    languageMenuButton->setFixedSize(e*8,b*7);
    languageMenuButton->setAutoRaise(true);
    //languageMenuButton->setAutoFillBackground(true);
    languageMenuButton->setText(tr("Dil Seç"));
    languageMenuButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    QMenu *menuu=languageMenu();
    languageMenuButton->setMenu(menuu);
    languageMenuButton->setPopupMode(QToolButton::InstantPopup);

    connect(languageMenuButton, &QPushButton::clicked, [=]() {
        // slotKilitAcAll();
    });

    auto widget = new QWidget;
    auto layout = new QGridLayout(sor);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

    //layout->addWidget(cb, 4,0,1,2);

    layout->addWidget(languageLabelButton, 5,0,1,1,Qt::AlignRight);
    layout->addWidget(languageMenuButton, 7,0,1,1,Qt::AlignRight);

    return sor;
        // sor->show();

    //slotVncFlip(ekranScale->currentText());
}


QWidget* MainWindow::temelIslemler()
{
    int e=en;
    int b=boy;
    int yukseklik=e*10;
     QWidget * d = new QWidget();
   // d->setFixedSize(e*180,b*23);
   // d->setStyleSheet("background-color: #ffdced;font-size:"+QString::number(font.toInt()-2)+"px;");



    QToolButton *vncConnectPcButton = new QToolButton();
    vncConnectPcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    vncConnectPcButton->setIcon(QIcon(":icons/vnc.svg"));
    vncConnectPcButton->setIconSize(QSize(yukseklik,boy*8));
    vncConnectPcButton->setAutoRaise(true);
   // vncConnectPcButton->setAutoFillBackground(true);
    vncConnectPcButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    vncConnectPcButton->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    vncConnectPcButton->setText("VNC");
    connect(vncConnectPcButton, &QToolButton::clicked, [=]() {
        slotVnc(_display);
    });

    QToolButton *novncConnectPcButton = new QToolButton();
    novncConnectPcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    novncConnectPcButton->setIcon(QIcon(":icons/novnc.svg"));
    novncConnectPcButton->setIconSize(QSize(yukseklik,boy*8));
    novncConnectPcButton->setAutoRaise(true);
   // vncConnectPcButton->setAutoFillBackground(true);
    novncConnectPcButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    novncConnectPcButton->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    novncConnectPcButton->setText("noVNC");
    connect(novncConnectPcButton, &QToolButton::clicked, [=]() {
        QString kmt26="env MOZ_USE_XINPUT2=1 /usr/lib/firefox/firefox "+pcIp->text()+":6085/vnc.html";
        system(kmt26.toStdString().c_str());

       // QDesktopServices::openUrl(QUrl("192.168.1.101:6085"));
    });
   /* QToolButton *xrdpConnectPcButton = new QToolButton();
    xrdpConnectPcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    xrdpConnectPcButton->setIcon(QIcon(":icons/rdp.svg"));
    xrdpConnectPcButton->setIconSize(QSize(yukseklik,boy*8));
    xrdpConnectPcButton->setAutoRaise(true);
   // xrdpConnectPcButton->setAutoFillBackground(true);
    xrdpConnectPcButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    xrdpConnectPcButton->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    xrdpConnectPcButton->setText("RDP");
    connect(xrdpConnectPcButton, &QToolButton::clicked, [=]() {
        slotRdp();
    });
*/
    QToolButton *terminalPcButton = new QToolButton();
    terminalPcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    terminalPcButton->setIcon(QIcon(":icons/ssh.svg"));
    terminalPcButton->setIconSize(QSize(yukseklik,boy*8));
    terminalPcButton->setAutoRaise(true);
  //  terminalPcButton->setAutoFillBackground(true);
    terminalPcButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    terminalPcButton->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    terminalPcButton->setText(tr("Terminal"));
    connect(terminalPcButton, &QToolButton::clicked, [=]() {
        terminalSlot();
    });

    QToolButton *selectPcButton = new QToolButton();
     selectPcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
     selectPcButton->setIconSize(QSize(yukseklik,boy*8));
     selectPcButton->setIcon(QIcon(":icons/select.svg"));
     selectPcButton->setFixedSize(yukseklik*0.95,yukseklik*1.5);
     selectPcButton->setAutoRaise(true);
    // selectPcButton->setAutoFillBackground(true);
     selectPcButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

      selectPcButton->setText(tr("Pc Seç"));
     connect(selectPcButton, &QToolButton::clicked, [=]() {
          selectSlot();

     });


    /*QToolButton *ftpPc=new QToolButton();
    ftpPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    ftpPc->setIcon(QIcon(":/icons/ftp.svg"));
    ftpPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ftpPc->setIconSize(QSize(yukseklik,boy*8));

    ftpPc->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    ftpPc->setAutoRaise(true);
   // ftpPc->setAutoFillBackground(true);
    ftpPc->setText("FTP");
    connect(ftpPc, &QToolButton::clicked, [=]() {
        ftpConnectButtonSlot();
    });
*/
    QToolButton *wolButton=new QToolButton();
    wolButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    wolButton->setIcon(QIcon(":/icons/wol.svg"));
    wolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    wolButton->setIconSize(QSize(yukseklik,boy*8));

    wolButton->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    wolButton->setAutoRaise(true);
   // ftpPc->setAutoFillBackground(true);
    wolButton->setText("Pc Aç");
    connect(wolButton, &QToolButton::clicked, [=]() {
        wolSlot();
    });


    QToolButton *helpButton= new QToolButton;
    helpButton->setFixedSize(yukseklik*0.9, yukseklik*1.5);
    helpButton->setIconSize(QSize(yukseklik,boy*8));
    helpButton->setIcon(QIcon(":/icons/help.svg"));
    helpButton->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");
    helpButton->setText(tr("Yardım"));
    helpButton->setAutoRaise(true);

     helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(helpButton, &QToolButton::clicked, [=]() {

        QTextDocument *doc=new QTextDocument();

        doc->setHtml("<center><h2>Temel İşlemler</h2></center>"
                     "<center><img src=\":/icons/temelislem.png\" /></center> "
                     "1-Ağ üzerinde açık istemcileri listelemek için Yenile seçeneği kullanılmalıdır."
                      "<br/><br/>2-Birden fazla istemciyi seçmek için çift tıklama/sol tuşa basarak alan seçimi yapılabilir."
                      "Seçili olmayan istemcileri seçmek için Pc Seç seçeneği kullanılır."
                      "<br/><br/>3-İstemcinin canlı ekranı Vnc seçeneği ile erişilebilir."
                      "<br/><br/>4-İstemcinin kullanıcıdan bağımsız ekranına Rdp seçeneği ile erişilebilir."
                      "<br/><br/>5-İstemcinin ssh üzerinden konsoluna bağlanmak için Terminal seçeneği kullanılabilir."
                      "<br/><br/>6-İstemcinin dosyalarına dosya yöneticisi ile erişmek için Ftp seçeneği kullanılabilir."
                      "<br/><br/>7-İstemcinin uzaktan başlatmak için Pc Aç seçeneği kullanılabilir."
                      "Pc Aç seçeneği için; İstemcinin BIOS seçeneklerinden Wake On Lan seçeneği aktif edilmeli. "
                      "<br/><br/>8-İstemci simgelerinin altındaki P V S F X işaretleri servisleri ifade eder."
                     "<center><img src=\":/icons/istemci.png\" /></center>"
                     "Simgeler yeşilse servis çalışıyor. Kırmızı ise servis çalışmıyordur."
                      "<br/>P=İstemci, yeşil=istemci açık/kırmızı=istemci kapalı"
                      "<br/>V=Vnc servisi, yeşil=açık/kırmızı=kapalı"
                      "<br/>S=Ssh servisi, yeşil=açık/kırmızı=kapalı"
                      "<br/>F=Ftp servisi, yeşil=açık/kırmızı=kapalı"
                      "<br/>X=x11 ekranı, yeşil=kullanıcı login olmuş/kırmızı=kullanıcı login olmamış"
                 );
        QPrinter pdf;
            pdf.setOutputFileName("/tmp/temelislem.pdf");
            pdf.setOutputFormat(QPrinter::PdfFormat);
            doc->print(&pdf);

        QTextEdit *document = new QTextEdit();
        document->setReadOnly(true);
        //  document->show();
         document->setDocument(doc);
        QVBoxLayout * vbox = new QVBoxLayout();
         QHBoxLayout * hbox1= new QHBoxLayout();

        // hbox1->addWidget(commandFileLabel);
         hbox1->addWidget(document);

         vbox->addLayout(hbox1);
         QDialog * d1 = new QDialog();
         d1->setWindowTitle("Temel İşlemler Yardım Penceresi");
         d1->setFixedSize(QSize(boy*150,boy*120));
         auto appIcon = QIcon(":/icons/e-ag.svg");
         d1->setWindowIcon(appIcon);

         d1->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

         d1->setLayout(vbox);
          d1->exec();

 });
  /******************************************************/
    auto layout = new QGridLayout(d);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
  //  layout->setHorizontalSpacing(0);
   // layout->addWidget(hostListePcButton, 0,0,3,1);
    //layout->addWidget(selectPcButton, 0,1,3,1);

    layout->addWidget(vncConnectPcButton, 0,2,3,1);
    layout->addWidget(novncConnectPcButton, 0,5,3,1);

  //  layout->addWidget(xrdpConnectPcButton, 0,6,3,1);

    layout->addWidget(terminalPcButton, 0,7,3,1);
    //layout->addWidget(ftpPc, 0,8,3,1);
    layout->addWidget(wolButton, 0,9,3,1);

    layout->addWidget(kilitWidget(), 0,10,3,1);
    layout->addWidget(kilittransparanWidget(), 0,12,3,1);
    layout->addWidget(ekranWidget(), 0,13,3,1);
    layout->addWidget(poweroffrebootWidget(), 0,20,3,1);
    layout->addWidget(volumeWidget(), 0,23,3,1);

    layout->addWidget(logoutWidget(), 0,25,3,1);
  //  layout->addWidget(languageWidget(), 0,28,3,1);

    layout->addWidget(helpButton, 0,30,3,1);
    d->setLayout(layout);
    return d;
}

#endif // BUTONCLICK_H
