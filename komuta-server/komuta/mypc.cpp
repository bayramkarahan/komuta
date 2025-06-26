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
#include "mypc.h"
#include<QRegularExpression>
#include<QTextStream>
#include<QDebug>
#include<QLabel>
#include<QToolButton>
#include<QProcess>
#include <QMouseEvent>
#include<QApplication>
#include<QModelIndex>
#include<QMenu>
#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <QVBoxLayout>
#include<QDialogButtonBox>
#include<MyCommand.h>
#include<VideoPlayer.h>

MyPc::MyPc(const QString _mac, QString _ip, QWidget *parent) : QWidget(parent)
{
    receiver=new MulticastReceiver(this);
    setObjectName("mypcobject");
    timertcpConnectControl= new QTimer(this);
    connect(timertcpConnectControl, SIGNAL(timeout()), this, SLOT(timertcpConnectControlSlot()));
    timertcpConnectControl->start(3000);

    localDir="/usr/share/komuta/";
    #if defined(Q_OS_WIN)
        localDir="c:/komuta/";
    #elif defined(Q_OS_LINUX)
        localDir="/usr/share/komuta/";
    #endif
    hostnameLabel=new QLabel(this);
    select=false;
    QPalette palet;

    palet.setColor(QPalette::Window, QColor(0,0,0,0));
    setPalette(palet);
    setAutoFillBackground(true);
    sshstateLabel=new QLabel(this);
    vncstateLabel=new QLabel(this);
    userstateLabel=new QLabel(this);
    selectLabel=new QLabel(this);
    selectLabel->setObjectName("selectLabel");
    xrdpstateLabel=new QLabel(this);
    btncommand=new QToolButton(this);
    btnayar=new QToolButton(this);
    iconstateLabel=new QLabel(this);
    //videoWidget=new VideoPlayer(this);
    iconstateLabel->setObjectName("iconLabel");
    iconstateLabel->setScaledContents(true);
    iconstateLabel->setStyleSheet("background-color:rgba(0,0,0,0)");
    btncommand->setText("C");
    sshstateLabel->setText("S");
    vncstateLabel->setText("V");
    xrdpstateLabel->setText("R");
    userstateLabel->setText("X");

    selectLabel->setStyleSheet("QLabel{border: 1px solid gray;border-radius: 5px;}");
   // btncommand->setAlignment(Qt::AlignCenter);
    sshstateLabel->setAlignment(Qt::AlignCenter);
    vncstateLabel->setAlignment(Qt::AlignCenter);
    xrdpstateLabel->setAlignment(Qt::AlignCenter);
    userstateLabel->setAlignment(Qt::AlignCenter);
    hostnameLabel->setAlignment(Qt::AlignTop|Qt::AlignCenter);
    hostnameLabel->raise();

    connect(btncommand, &QToolButton::clicked, [=]() {
        /*qDebug()<<"komut:"<<command;
        qDebug()<<"komut Sonucu:"<<commandDetail;
        qDebug()<<"komut durumu:"<<commandState;*/
        MyCommand *commanddlg= new MyCommand(tr("Komut Süreci"),command,commandDetail,commandState, "", "", "", w*50, h*30,this);
        commanddlg->exec();
        //delete commanddlg;
        commanddlg = nullptr;  // Güvenlik için
    });
    connect(btnayar, &QToolButton::clicked, [=]() {
        qDebug()<<"slotPcAyar";
        slotPcAyar();

});

    btnayar->setIcon(QIcon(":icons/settings.svg"));
    btnayar->setAutoRaise(true);
    //iconLabel->setAutoFillBackground(true);
    multiSelect=false;
    auto layout = new QGridLayout(this);
    layout->setContentsMargins(2, 2, 2,2);
    layout->setVerticalSpacing(1);
    layout->addWidget(hostnameLabel, 2, 1,1,6,Qt::AlignHCenter);
    //layout->addWidget(videoWidget, 3,1,1,5,Qt::AlignHCenter);
    layout->addWidget(iconstateLabel, 3,1,1,6,Qt::AlignHCenter);
    layout->addWidget(btncommand, 4,1,1,1,Qt::AlignHCenter);
    layout->addWidget(sshstateLabel, 4, 2,1,1,Qt::AlignHCenter);
    layout->addWidget(vncstateLabel, 4, 3,1,1,Qt::AlignHCenter);
    layout->addWidget(xrdpstateLabel, 4, 4,1,1,Qt::AlignHCenter);
    layout->addWidget(userstateLabel, 4, 5,1,1,Qt::AlignHCenter);
    layout->addWidget(btnayar, 4, 6,1,1,Qt::AlignHCenter);
    this->setLayout(layout);

    this->ip=_ip;
    this->mac=_mac;

    setCommandButonState(false);

    DatabaseHelper *db=new DatabaseHelper(localDir+"persist.json");
    QJsonArray dizi=db->Ara("mac",this->mac);
    if(dizi.count()>0)
    {
        //qDebug()<<"Kayıtlı Host.";
        QJsonObject veri=dizi.first().toObject();
        this->mac=veri.value("mac").toString();
        this->ip=veri.value("ip").toString();
        this->caption=veri.value("caption").toString();
        this->hostname=veri.value("hostname").toString();
        if(this->caption!="")
            hostnameLabel->setText(this->caption);
        else
            hostnameLabel->setText(this->hostname);
        this->visibleState=veri.value("visibleState").toBool();
    }else
    {
        ///qDebug()<<"Yeni Host Ekleniyor.";
        QJsonObject veri;
        veri["mac"] = this->mac;
        veri["ip"] = this->ip;
        veri["caption"] = "";
        veri["hostname"] = "";
        veri["visibleState"] = true;
        db->Ekle(veri);
    }
}
void MyPc::timertcpConnectControlSlot()
{
    tcpConnectCounter++;
    if(!iconControlState)
    {
        iconstateLabel->clear();
    }
     //iconstateLabel->setText(QString::number(tcpConnectCounter));
    if(tcpConnectCounter>5)
    {
        setConnectState(false);
        setSshState(false);
        setVncState(false);
        setXrdpState(false);
        setUser("noLogin");
        tcpConnectCounter=0;
        emit pcCloseSignal(ip,mac);
    }

}
void MyPc::setCommandState(QString _command,QString _commandDetail,QString _commandState)
{
    command=_command;
    commandDetail=_commandDetail;
    commandState=_commandState;
    if(commandState=="0")
    {
        btncommand->setToolTip(command);
        btncommand->setStyleSheet("border: 1px solid gray; "
                                  "border-radius: 6px;"
                                  "font-size:8px;"
                                  " text-align: center;"
                                  "background-color: #00ff00;");
    }
    else
    {
        btncommand->setStyleSheet("border: 1px solid gray; "
                                  "border-radius: 6px;"
                                  "font-size:8px;"
                                  " text-align: center;"
                                  "background-color: #ff0000;");
    }
}
void MyPc::setConnectState(bool state){
    connectState=state;
    if(state)
    {
        iconstateLabel->setStyleSheet("background-color:rgba(0,230,0,130)");
    }
    else
    {
       iconstateLabel->setStyleSheet("background-color:rgba(127,127,127,100)");
    }
}
void MyPc::setCommandButonState(bool state){
   if(state)
    {
          btncommand->setStyleSheet("border: 1px solid gray; "
                                      "border-radius: 6px;"
                                      "font-size:8px;"
                                      " text-align: center;"
                                      "background-color: #00ff00;");
    }
    else
    {
        btncommand->setStyleSheet("border: 1px solid gray; "
                                    "border-radius: 6px;"
                                    "font-size:8px;"
                                    " text-align: center;"
                                    "background-color: #aaaaaa;");
    }
}
void MyPc::setSshState(bool state){
sshState=state;
  if(state)
  {
     // sshConnectCounter=0;
      sshstateLabel->setStyleSheet("border: 1px solid gray; "
                                  "border-radius: 6px;"
                                   "font-size:8px;"
                                   " text-align: center;"
                                  "background-color: #00ff00;");

  }
  else
  {
      sshstateLabel->setStyleSheet("border: 1px solid gray; "
                                  "border-radius: 6px;"
                                   "font-size:8px;"
                                   " text-align: center;"
                                  "background-color: #ff0000;");

  }
  /*
    QStringList list=PcData::onlinePcListe;
    list=listReplace(list, "sshclose", ss, 3,mac);//sshstate
    PcData::onlinePcListe=list;
*/
}
void MyPc::setVncState(bool state){
     vncState=state;
     if(state)
    {
         //vncConnectCounter=0;
        vncstateLabel->setStyleSheet("border: 1px solid gray; "
                                    "border-radius: 6px;"
                                    "font-size:8px;"
                                    "background-color: #00ff00;");
    }
    else
    {
        vncstateLabel->setStyleSheet("border: 1px solid gray; "
                                    "border-radius: 6px;"
                                    "font-size:8px;"
                                    "background-color: #ff0000;");
    }
/*
    QStringList list=PcData::onlinePcListe;
    list=listReplace(list, "vncclose", vs, 4,mac);//vncstate
    PcData::onlinePcListe=list;
*/
}
void MyPc::setXrdpState(bool state){
      xrdpState=state;
     if(state)
    {
         //xrdpConnectCounter=0;
       xrdpstateLabel->setStyleSheet("border: 1px solid gray; "
                                    "border-radius: 6px;"
                                     "font-size:8px;"
                                     " text-align: center;"

                                    "background-color: #00ff00;");

     }
    else
    {
        xrdpstateLabel->setStyleSheet("border: 1px solid gray; "
                                    "border-radius: 6px;"
                                     "font-size:8px;"
                                     " text-align: center;"

                                    "background-color: #ff0000;");
    }

}
void MyPc::setKilitControlState(bool state){
    // qDebug()<<"kilitstate"<<cs;
    if(state==true&&transparanKilitControlState==false&&iconControlState==false)
    {
        ///qDebug()<<"kilitli";
        iconstateLabel->setPixmap(QPixmap(":icons/lock.svg"));
        kilitControlState=true;
    }
    if(state==false&&transparanKilitControlState==false&&iconControlState==false)
    {
        iconstateLabel->setPixmap(QPixmap(""));
        kilitControlState=false;
    }
}
void MyPc::setKilitTransparanControlState(bool state){
    //qDebug()<<"transparan kilitstatecontrol"<<cs<<state;
    if(state==true&&kilitControlState==false&&iconControlState==false)
    {
        qDebug()<<"transparan kilitli";
        iconstateLabel->setPixmap(QPixmap(":icons/transparanlock.svg"));
        transparanKilitControlState=true;
    }
    if(state==false&&kilitControlState==false&&iconControlState==false)
    {
        iconstateLabel->setPixmap(QPixmap(""));
        transparanKilitControlState=false;
    }
}
void MyPc::setIconControlState(bool state)
{
    //qDebug()<<"ip address: "<<this->netProfil.serverAddress;

    //return;
    if(state==true&&transparanKilitControlState==false&&kilitControlState==false)
    {

        QStringList ipparts=ip.split(".");
        QString newIp="udp://@239.0."+ipparts[2]+"."+ipparts[3]+":1234?localaddr="+this->netProfil.serverAddress;
        qDebug()<<"izleniyor..."<<newIp;
        if (receiver && receiver->isRunning())
            return;

        if (receiver) {
            receiver->stop();
            delete receiver;
            receiver = nullptr;
        }

        receiver = new MulticastReceiver(this);
        receiver->urlAddress = newIp;

        connect(receiver, &MulticastReceiver::frameReady, this, [this](const QImage &img) {
            if (prevImage != img)
                iconstateLabel->setPixmap(QPixmap::fromImage(img).scaled(iconstateLabel->size(), Qt::KeepAspectRatio));
            prevImage= img;
        });

        receiver->start();
        //iconstateLabel->show();
        iconControlState=true;
    }
    if(state==false&&transparanKilitControlState==false&&kilitControlState==false)
    {
        if (receiver) {
            receiver->streamStatus=false;
            receiver->stop();
            receiver->wait();

            disconnect(receiver, nullptr, this, nullptr);  // sinyal bağlantılarını kes
            delete receiver;
            receiver = nullptr;
            iconstateLabel->clear(); // Ekranı temizle

        }

         iconstateLabel->clear();
        iconControlState=false;

    }

}
void MyPc::setUser(QString _usr)
{
    user=_usr;
    if(_usr!="noLogin")
    {
     userstateLabel->setStyleSheet("border: 1px solid gray; "
                                    "border-radius: 6px;"
                                     "font-size:8px;"
                                     " text-align: center;"
                                    "background-color: #00ff00;");
    }else
    {
     userstateLabel->setStyleSheet("border: 1px solid gray; "
                                    "border-radius: 6px;"
                                     "font-size:8px;"
                                     " text-align: center;"
                             "background-color: #ff0000;");
    }

}
void MyPc::setHostname(QString _hostname)
{
    hostname=_hostname;
    if(this->caption!="")
        hostnameLabel->setText(this->caption);
    else
    {
        hostnameLabel->setText(this->hostname);
        this->caption=this->hostname;
    }
    if(hostname!=_hostname)
    {
        //qDebug()<<"Yeni Host Ekleniyor.";
        QJsonObject veri;
        veri["mac"] = this->mac;
        veri["ip"] = this->ip;
        veri["caption"] = this->caption;
        veri["hostname"] = this->hostname;
        veri["visibleState"] =this->visibleState;
        DatabaseHelper *db=new DatabaseHelper(localDir+"persist.json");
        db->Sil("mac",this->mac);
        db->Ekle(veri);
    }
    if(this->caption=="")
     {
        this->caption=this->hostname;
    }
}
void MyPc::setSize(int _w, int _h, QString _font)
{
    font=_font;
    int fnt=_font.toInt();
    hostnameLabel->setStyleSheet("font-size:"+QString::number(fnt-2)+"px; background-color:rgba(200,200,200,255);");
    w=_w/6;
    h=_h/6;
    setFixedSize(w*7,h*7);
    /**************************************/
    hostnameLabel->setFixedSize(w*6.8,h*1.1);

    btncommand->setFixedSize(w*1,h*1);
    sshstateLabel->setFixedSize(w*1,h*1);
    vncstateLabel->setFixedSize(w*1,h*1);
    xrdpstateLabel->setFixedSize(w*1,h*1);
    userstateLabel->setFixedSize(w*1,h*1);

    selectLabel->setFixedSize(w*7, h*7);
    //btnpc->setFixedSize(w*7, h*3);
    //videoWidget->setFixedSize(w*6.9, h*4.6);
    iconstateLabel->setFixedSize(w*6.9, w*3.4);
    //layout1->SetFixedSize->setFixedSize(w*7, h*5);

    btnayar->setFixedSize(w*1, h*1);
    btnayar->setIconSize(QSize(w*1.4,h*1.4));

}
MyPc::~MyPc()
{
// qDebug()<<"Pc nesnesi Silindi-----------: "<<ip<<mac;
    if (receiver) {
        receiver->stop();
        delete receiver;
        receiver = nullptr;
    }
}
void MyPc::slotMouseClick()
{

    if(connectState)
    {
        QPalette palet;

        //qDebug()<<"tıklllllandıı";
        select=true;
         emit pcClickSignal(mac);//nesneler arası data transferi***

        if(select){
            palet.setColor(QPalette::Window, QColor(0,200,250,150));
            setPalette(palet);
            setAutoFillBackground(true);

        }
        else{
            palet.setColor(QPalette::Window, QColor(0,0,0,0));
            setPalette(palet);
            setAutoFillBackground(true);

        }
    }

}
void MyPc::slotPcAyar()
{
   // qDebug()<<"ayar click";
    QDialog * d = new QDialog();
    d->setWindowTitle("Host Bilgileri");
    auto appIcon = QIcon(":/icons/about.svg");
    d->setWindowIcon(appIcon);

    QSize screenSize = qApp->screens()[0]->size();
   int boy=screenSize.height()/153.6;
   int en=boy*1.1;

    d->setFixedSize(en*60,boy*60);
    QLineEdit * lineEditA = new QLineEdit();
    QLabel *pcnameLabel=new QLabel();
    QLabel *pcstate=new QLabel();
    QLabel *sshstate=new QLabel();
    QLabel *vncstate=new QLabel();
    QLabel *xrdpstate=new QLabel();
    QLabel *connectstate=new QLabel();
    QLabel *displaystate=new QLabel();
    QLabel *userstate=new QLabel();
     QLabel *osstate=new QLabel();

    //QLineEdit * lineEditB = new QLineEdit();
    //QLineEdit * lineEditC = new QLineEdit();
    QCheckBox *cha=new QCheckBox("Listede Gözükmemesi için Gizle");
    //QCheckBox *chb=new QCheckBox("Girdi Değeri");
   // QCheckBox *chc=new QCheckBox("Girdi Değeri");

    QDialogButtonBox * buttonBox = new QDialogButtonBox();

    buttonBox->addButton("Kaydet", QDialogButtonBox::AcceptRole);
    buttonBox->addButton("Vazgeç", QDialogButtonBox::RejectRole);


    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    QVBoxLayout * vbox = new QVBoxLayout();
    QHBoxLayout * hbox1 = new QHBoxLayout();
    hbox1->addWidget(pcnameLabel);
    hbox1->addWidget(lineEditA);

   /* QHBoxLayout * hbox2 = new QHBoxLayout();
    hbox2->addWidget(lineEditB);
    hbox2->addWidget(chb);*/

    /*QHBoxLayout * hbox3 = new QHBoxLayout();
    hbox3->addWidget(lineEditC);
    hbox3->addWidget(chc);*/
    pcnameLabel->setText("Liste Adı:");
    //vbox->addWidget(pcnameLabel);
    vbox->addLayout(hbox1);
    vbox->addWidget(cha);
    vbox->addWidget(pcstate);
    vbox->addWidget(sshstate);
    vbox->addWidget(vncstate);
    vbox->addWidget(xrdpstate);
    vbox->addWidget(connectstate);
    vbox->addWidget(userstate);
    vbox->addWidget(displaystate);
     vbox->addWidget(osstate);
  //  vbox->addLayout(hbox2);
  //  vbox->addLayout(hbox3);
    vbox->addWidget(buttonBox);

    d->setLayout(vbox);
    lineEditA->setText(caption);

    if(connectState)connectstate->setText("Pc: Açık");else connectstate->setText("Pc: Kapalı");
    if(sshState)sshstate->setText("Ssh: Açık");else sshstate->setText("Ssh: Kapalı");
    if(vncState) vncstate->setText("Vnc: Açık ("+vncport+")");else vncstate->setText("Vnc: Kapalı ("+vncport+")");
    if(xrdpState)xrdpstate->setText("Xrdp: Açık");else xrdpstate->setText("Xrdp: Kapalı");
    if(connectstate)connectstate->setText("Tcp: Açık");else connectstate->setText("Tcp: Kapalı");
    //displaystate->setText("Ekran:"+display);
    userstate->setText("Kullanıcı:"+user);
    osstate->setText("Sunucu:"+hostname);

   // lineEditB->setText("");
   // lineEditC->setText("");

     if(visibleState)cha->setChecked(false);else cha->setChecked(true);
   // chb->setChecked(true);
   // chc->setChecked(true);


    int result = d->exec();
    if(result == QDialog::Accepted)
    {
        if(lineEditA->text()!="") caption=lineEditA->text(); else caption="";
        if(cha->checkState()==Qt::Checked)visibleState=false; else visibleState=true;

            //qDebug()<<"Yeni Host Ekleniyor.";
            QJsonObject veri;
            veri["mac"] = this->mac;
            veri["ip"] = this->ip;
            veri["caption"] = this->caption;
            veri["hostname"] = this->hostname;
            veri["visibleState"] =this->visibleState;
            if(this->caption!="?")
                hostnameLabel->setText(this->caption);
            else
                hostnameLabel->setText(this->hostname);
            DatabaseHelper *db=new DatabaseHelper(localDir+"persist.json");
            db->Sil("mac",this->mac);
            db->Ekle(veri);
            //qDebug()<<"mypc gizleniyor"<<mac<<visibleState;
            if(!visibleState) { emit pcHideSignal(this->mac);}
    }
}
void MyPc::mousePressEvent(QMouseEvent *event)
{
slotMouseClick();
    if (event->button()==Qt::RightButton)
    {
    if(!multiSelect){
        //pcselectMenu();
        //pContextSelectMenu->exec(mapToGlobal(event->pos()),nullptr);
        //qDebug()<<"burası pc içi";
        emit pcRightClickSignal();
        QWidget::mousePressEvent(event);
    }
    else
    {
        //qDebug()<<"burası pc içi";
        emit pcRightClickSignal();
        QWidget::mousePressEvent(event);
    }
    }
}
void MyPc::mouseDoubleClickEvent(QMouseEvent *event)
{
slotMouseDoubleClick();
}

void MyPc::slotMouseDoubleClick(){
    if(connectState)
    {
        //qDebug()<<"--------"<<multiSelect;
        if(multiSelect)
            slotUnselectPc();
        else
            slotSelectPc();
    }
}
void MyPc::slotSelectPc(){
    if(connectState)
    {
        multiSelect=true;
        selectLabel->setStyleSheet("QLabel{border: 2px solid blue;border-radius: 5px;}");
    }
}
void MyPc::slotUnselectPc(){
    if(connectState)
    {
        multiSelect=false;
        selectLabel->setStyleSheet("QLabel{border: 1px solid gray;border-radius: 5px;}");
    }
}
QString MyPc::getIpPortStatus(QString ip_,QString port)
{
    QString result="";
    QStringList arguments;
    arguments << "-c" << QString("nc -zv -w1 %1 %2 2>&1|grep 'open'|wc -l").arg(ip_,port);
    QProcess process;
    process.start("/bin/bash",arguments);
    if(process.waitForFinished(-1))
    {
        result = process.readAll();
        result.chop(1);
    }
    qDebug()<<"Port sorgulama:"<<ip_<<result<<port;
    if(result.toInt()>0){ return "open";}
    else {return "close";}
}

void MyPc::slothidePc()
{
    qDebug()<<"slothidePc: Host Gizlenecek...";
    QJsonObject veri;
    veri["mac"] = this->mac;
    veri["ip"] = this->ip;
    veri["caption"] = this->caption;
    veri["hostname"] = this->hostname;
    veri["visibleState"] =false;
    visibleState=false;
    if(this->caption!="?")
        hostnameLabel->setText(this->caption);
    else
        hostnameLabel->setText(this->hostname);
    DatabaseHelper *db=new DatabaseHelper(localDir+"persist.json");
    db->Sil("mac",this->mac);
    db->Ekle(veri);
    //qDebug()<<"mypc gizleniyor"<<mac<<visibleState;
    //if(!visibleState) { emit pcHideSignal(this->mac);}

}
