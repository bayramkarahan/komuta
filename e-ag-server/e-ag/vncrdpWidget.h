#ifndef VNCRDPWIDGET_H
#define VNCRDPWIDGET_H
#include<CustomInputDialog.h>
QWidget* MainWindow::rdpWidget()
{
    int e=en;
    int b=boy;
    int yukseklik=b*8;

    QWidget *sor=new QWidget();
    sor->setWindowTitle(tr("Ekran Yansıtma Seçenekleri"));
    sor->setStyleSheet("font-size:"+QString::number(font.toInt())+"px;");

    sor->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Tool);
    // sor->setFixedSize(e*42,b*15);

    sor->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - sor->width())/2;
    int y = (screenGeometry.height() - sor->height()) / 2;
    sor->move(x, y);
    QCheckBox *cb=new QCheckBox(sor);
    cb->setText("");
    cb->setFixedSize(e*3,yukseklik);
    cb->setText("");
    cb->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    QLabel *cbLabel=new QLabel(sor);
    cbLabel->setText(tr("Sunucuyu\nKontrol \nEdebilsin"));
    cbLabel->setFixedSize(e*20,b*5);
    cbLabel->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    cbLabel->setAlignment(Qt::AlignCenter);

    QToolButton *vncPc=new QToolButton();
    vncPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    vncPc->setIcon(QIcon(":/icons/vnc.svg"));
    vncPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    vncPc->setFixedSize(e*15,yukseklik*2);
    vncPc->setAutoRaise(true);
    vncPc->setIconSize(QSize(b*8,yukseklik));
    // vncPc->setAutoFillBackground(true);
    vncPc->setText(tr("Vnc Ekran\n Erişimi"));
    connect(vncPc, &QToolButton::clicked, [=]() {
        slotVnc(_display);
    });

    QToolButton *rdpPc=new QToolButton();
    rdpPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    rdpPc->setIcon(QIcon(":/icons/rdp.svg"));
    rdpPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    rdpPc->setFixedSize(e*15,yukseklik*2);
    rdpPc->setAutoRaise(true);
    rdpPc->setIconSize(QSize(b*8,yukseklik));
    // rdpPc->setAutoFillBackground(true);
    rdpPc->setText(tr("Rdp Ekran\n Erişimi"));
    connect(rdpPc, &QToolButton::clicked, [=]() {
        slotRdp();
    });
    QLabel *boyutLabel=new QLabel(sor);
    boyutLabel->setText(tr("Sunucu Ekran Boyutu"));
    boyutLabel->setFixedSize(e*25,b*5);
    boyutLabel->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    QComboBox *ekranScale1 = new QComboBox();
    ekranScale1->setFixedSize(e*25,yukseklik);
    // ekranScale1->move(0,40);
    // ekranScale1->setFrame(true);
    ekranScale1->setStyleSheet(" font-size:"+QString::number(font.toInt()-2)+"px;");
    ekranScale1->addItem("800x600");
    ekranScale1->addItem("1024x768");
    ekranScale1->addItem("1280x1024");
    ekranScale1->addItem("1366x768");
    ekranScale1->addItem("1920x1080");
    ekranScale1->addItem("3840x2160");

    ekranScale1->setCurrentIndex(4);


    QToolButton *serverEkranYansitSeciliPcButton= new QToolButton();
    serverEkranYansitSeciliPcButton->setFixedSize(e*18,yukseklik*2);
    //serverEkranYansitSeciliPcButton->setIconSize(QSize(150,30));
    serverEkranYansitSeciliPcButton->setText(tr("Ekranı Pc'lere\n Yansıt"));
    serverEkranYansitSeciliPcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    serverEkranYansitSeciliPcButton->setAutoRaise(true);
    serverEkranYansitSeciliPcButton->setIconSize(QSize(b*8,yukseklik));
    //  serverEkranYansitSeciliPcButton->setAutoFillBackground(true);

    serverEkranYansitSeciliPcButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    serverEkranYansitSeciliPcButton->setIcon(QIcon(":icons/networkvnc.svg"));

    connect(serverEkranYansitSeciliPcButton, &QPushButton::clicked, [=]() {
        bool cbstate=cb->checkState();
        QString viewState="";
        //qDebug()<<cbstate;
        if (!cbstate) viewState="-viewonly";
        slotVncFlip(ekranScale1->currentText(),viewState);

    });


    QToolButton* ekranYansitDurdur = new QToolButton();
    ekranYansitDurdur->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    ekranYansitDurdur->setIcon(QIcon(":/icons/networkvncstop.svg"));
    ekranYansitDurdur->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ekranYansitDurdur->setFixedSize(e*18,yukseklik*2);
    ekranYansitDurdur->setAutoRaise(true);
    ekranYansitDurdur->setIconSize(QSize(b*8,yukseklik));
    // ekranYansitDurdur->setAutoFillBackground(true);
    ekranYansitDurdur->setText(tr("Yansıtmayı \nDurdur"));
    connect(ekranYansitDurdur, &QToolButton::clicked, [=]() {
        //slotEkranIzleDurdur();
        slotVncFlipStop();
    });

    QToolButton *helpButton= new QToolButton;
    helpButton->setFixedSize(e*12,yukseklik*2);
    helpButton->setAutoRaise(true);
    // bilgiButton->setAutoFillBackground(true);
    helpButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    helpButton->setText(tr("Yardım"));
    helpButton->setIcon(QIcon(":/icons/help.svg"));
    helpButton->setIconSize(QSize(b*8,yukseklik));
    helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(helpButton, &QToolButton::clicked, [=]() {
        QTextDocument *doc=new QTextDocument();

        doc->setHtml(tr("<center><h2>Ekran Paylaşımı</h2></center>"
                     "<center><img src=\":/icons/ekranpaylasimi.png\" /></center> "
                     "<br/>1-Ekran paylaşımı vnc servisi ile çalıştırılmaktadır."
                     "<center><img src=\":/icons/istemci.png\" /></center>"
                     "<br/>2-İstemci simgelerinin altındaki V işareti vnc servisini ifade eder."
                     "<br/><br/>3-V işareti yeşilse vnc çalışıyor. Kırmızı ise vnc çalışmıyordur."
                     "<br/><br/>4-Sorunsuz ekran paylaşımı yapmak için istemcilerde vnc servisinin çalışıyor olması gerekmektedir."
                     "<br/><br/>5-Sunucu ekranı paylaşılırken, istemci ekranında hangi çözünürlükte görülmesini istiyorsak çözünürlük seçenekleri kullanılınabilir."
                     "<br/><br/>6-Sunucu ekranı paylaşılırken, istemciler ekranı kontrol edip/edemeyeceği seçilebilir."
                     "<br/><br/>7-Canlı istemci ekranına erişim \"Vnc Ekran Erişimi\" ile yapılabilir."
                     "<br/><br/>8-Canlı istemci ekranından bağımsız erişim \"Rdp Ekran Erişimi\" ile yapılabilir."
                        ));
        QPrinter pdf;
        pdf.setOutputFileName("/tmp/ekranpaylasimi.pdf");
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
        d1->setWindowTitle(tr("Ekran Paylaşımı Yardım Penceresi"));
        d1->setFixedSize(QSize(boy*215,boy*100));
        auto appIcon = QIcon(":/icons/e-ag.svg");
        d1->setWindowIcon(appIcon);

        d1->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

        d1->setLayout(vbox);
        d1->exec();
    });


    auto widget = new QWidget;
    auto layout = new QGridLayout(sor);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

    //layout->addWidget(cb, 4,0,1,2);
    layout->addWidget(vncPc, 1,0,2,1,Qt::AlignCenter);
    layout->addWidget(rdpPc, 1,1,2,1,Qt::AlignCenter);


    layout->addWidget(boyutLabel, 1,2,1,1,Qt::AlignCenter);
    layout->addWidget(ekranScale1,2,2,1,1,Qt::AlignCenter);

    layout->addWidget(cb, 1,3,1,1,Qt::AlignCenter);
    layout->addWidget(cbLabel, 2,3,1,1,Qt::AlignCenter);

    layout->addWidget(serverEkranYansitSeciliPcButton, 1,4,2,1,Qt::AlignCenter);
//    layout->addWidget(serverEkranYansitButton, 1,5,2,1,Qt::AlignCenter);

    layout->addWidget(ekranYansitDurdur, 1,6,2,1,Qt::AlignCenter);
  //  layout->addWidget(ekranYansitDurdurAll, 1,7,2,1,Qt::AlignCenter);
    layout->addWidget(helpButton, 1,8,2,1,Qt::AlignCenter);

    return sor;
        // sor->show();

    //slotVncFlip(ekranScale->currentText());
}

void MainWindow::vncDisplaySlot()
{
    slotVnc(_display);
}
void MainWindow::slotVnc(QString _dsp){
    QString display=_dsp;
    QString  komut;
    for(int i=0;i<onlinePcList.count();i++)
    {
        if(onlinePcList[i]->connectState&&(onlinePcList[i]->select))
        {
            display=onlinePcList[i]->vncport.split("-")[0];
            // qDebug()<<"vnc:"<<onlinePcList[i]->vncport;
            // udpSendData("x11komut",kmt,onlinePcList[i]->ip);
        }
    }
    komut.append("nohup ssvncviewer -scale 0.9 ").append(pcIp->text()).append(":"+display+" \-passwd \/usr\/bin\/x11vncpasswd &");
    qDebug()<<"vnc:"<<komut;
    system(komut.toStdString().c_str());
    mesajSlot(tr("Seçili Hostda Vnc Başlatıldı."));

}
void MainWindow::slotVncFlip(QString scale,QString viewState){
    QString kmt10="kill $(ps -aux|grep 5901|awk '{print $2 }')";
    system(kmt10.toStdString().c_str());
    QString kmt20="";

    QString seatUser=getSessionInfo(getSeatId(),"USER=");
    QStringRef _sessionUser=seatUser.rightRef(seatUser.length()-5);
    seatUser=_sessionUser.toString();

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    QString seatDisplay = env.value("DISPLAY"); // For Unix-like systems

   /* QString seatDisplay=getSessionInfo(getSeatId(),"DISPLAY=");
    QStringRef _sessionDisplay=seatDisplay.rightRef(seatDisplay.length()-9);
    seatDisplay=_sessionDisplay.toString();*/
    if (seatDisplay=="")seatDisplay=":1";
    qDebug()<<"display: "<<seatDisplay;
    //return;

    if(scale!="")
        kmt20="nohup sudo -u "+seatUser+" /usr/bin/x11vnc -display "+seatDisplay+" -geometry "+scale+" -forever -loop -noxdamage -repeat -rfbauth /usr/bin/x11vncpasswd -rfbport 5901 -shared &";
    else
        kmt20="nohup sudo -u "+seatUser+" /usr/bin/x11vnc -display "+seatDisplay+" -forever -loop -noxdamage -repeat -rfbauth /usr/bin/x11vncpasswd -rfbport 5901 -shared &";
    //qDebug()<<"Çalışacak Komut: "<<seatUser<<seatDisplay<<kmt20;
    system(kmt20.toStdString().c_str());
    system("sleep 2");
   // QString  kmt(viewState+":5901");
    /*************************************************************************/
    /************************************************************************/
    QString uport="7879";
    for(int i=0;i<onlinePcList.count();i++)
    {

        if(onlinePcList[i]->connectState&&(onlinePcList[i]->select||onlinePcList[i]->multiSelect))
        {
            QString  komut;
            komut.append("/usr/bin/vncviewer "+viewState+" \-fullscreen ").append(onlinePcList[i]->netProfil.serverAddress).append(":5901 \-passwd \/usr\/bin\/x11vncpasswd ");
            //udpSendData("x11command","x11command",komut);
            uport=onlinePcList[i]->netProfil.networkTcpPort;
            std::reverse(uport.begin(), uport.end());

            QString msg="x11command|vncviewer|"+komut+"|"+onlinePcList[i]->netProfil.serverAddress+"|"+uport;
            QByteArray datagram = msg.toUtf8();
            udpSocketSend->writeDatagram(datagram,QHostAddress(onlinePcList[i]->ip), uport.toInt());
            qDebug()<<"Mesaj Gönderildi:"<<msg;
        }
    }
    /*************************************************************************/
    /*************************************************************************/

    //udpSendData("x11command","vncviewer",kmt);

    mesajSlot("Seçili Hostlara Ekran Yansıltıldı.");
}
void MainWindow::slotVncFlipStop(){
    QString  kmt;
    kmt.append("pkill vncviewer");

    udpSendData("x11command","x11command",kmt);
    #if defined(Q_OS_WIN)


    #elif defined(Q_OS_LINUX)
        QString kmt10="kill $(ps -aux|grep 5901|awk '{print $2 }')";
        system(kmt10.toStdString().c_str());
    #endif

    mesajSlot(tr("Seçili Hostlarda Ekran Yansıtma Durduruldu."));

}
void MainWindow::slotVncFlipAll(QString scale,QString viewState){
    QString kmt10="kill $(ps -aux|grep 5901|awk '{print $2 }')";
    system(kmt10.toStdString().c_str());

    QString kmt20="";
    if(scale!="")
        kmt20="nohup /usr/bin/x11vnc -geometry "+scale+" -forever -loop -noxdamage -repeat -rfbauth /usr/bin/x11vncpasswd -rfbport 5901 -shared &";
    else
        kmt20="nohup /usr/bin/x11vnc -forever -loop -noxdamage -repeat -rfbauth /usr/bin/x11vncpasswd -rfbport 5901 -shared &";
    system(kmt20.toStdString().c_str());
    QString kmt11="sleep 1";
    system(kmt11.toStdString().c_str());
    hostAddressMacButtonSlot();
    for(int k=0;k<interfaceList.count();k++)
    {
        QString  kmt;
        kmt.append("vncviewer "+viewState+" -fullscreen ").append(interfaceList[k].ip).append(":5901 \-passwd \/usr\/bin\/x11vncpasswd");
        udpSendData("x11command","x11command",kmt);
        system("sleep 0.1");
    }
    mesajSlot(tr("Tüm Hostlara Ekran Yansıltıldı."));

}
void MainWindow::slotVncFlipAllStop(){
    QString  kmt;
    kmt.append("pkill vncviewer");
    udpSendData("x11command","x11command",kmt);
    /*for(int i=0;i<onlinePcList.count();i++)
    {
        if(onlinePcList[i]->connectState)
        {
            udpSendData("x11komut",kmt,onlinePcList[i]->ip);
        }
    }*/
    QString kmt10="kill $(ps -aux|grep 5901|awk '{print $2 }')";
    system(kmt10.toStdString().c_str());
    mesajSlot(tr("Tüm Hostlarda Ekran Yansıtma Durduruldu."));

}
void MainWindow::slotRdp(){
    hostAddressMacButtonSlot();
    QString seatUser=getSessionInfo(getSeatId(),"USER=");
    QStringRef _sessionUser=seatUser.rightRef(seatUser.length()-5);
    seatUser=_sessionUser.toString();
    CustomInputDialog  cid(tr("XRDP Erişim Bilgileri"),tr("Client Kullanıcı Adını Girizin\n"
                            "Açık Masaüsütünü Kontrol Etmek için VNC Tercih Edin."),seatUser,300,150);
QString _remoteuser = cid.getText();
    bool ok;

CustomInputDialog  cid1(tr("İstemci Parolası"),tr(" İstemcideki Kullanıcının Parolasını Giriniz :"),"",300,100);
QString _remotepasswd=cid1.getText();

    if(_remoteuser!=""&&_remotepasswd!="")
    {
        QString  komut;
        if(pcIp->text()=="")
        {
        QMessageBox msgBox;
        msgBox.setText(tr(" Client Bilgisayar Seçiniz..."));
        msgBox.exec();
        }else
        {
        komut.append("nohup  rdesktop ").append(" -u ").append(_remoteuser).append(" -p ").append(_remotepasswd+" ").append(pcIp->text()).append(" -g 75% &");
        system(komut.toStdString().c_str());
        qDebug()<<"rdp:"<<komut;
        }

    }

      mesajSlot(tr("Seçili Hostda Rdp Başlatıldı."));

}


#endif // VNCRDPWIDGET_H
