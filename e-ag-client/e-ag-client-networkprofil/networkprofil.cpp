#include "networkprofil.h"
#include<QDebug>
#include<QProcess>
#include <QtCore/QTimer>
#include <stdio.h>
#include <QtCore/QCoreApplication>
#include<Database.h>

NewtworkProfil::NewtworkProfil()
{
    localDir="/usr/share/e-ag/";
    localDir1="/tmp/";
    hostAddressMacButtonSlot();
    networkProfilLoad();
    QString uport=networkTcpPort;
    std::reverse(uport.begin(), uport.end());
    udpServerGet = new QUdpSocket();
    udpServerGet->bind(uport.toInt()+uport.toInt(), QUdpSocket::ShareAddress);
    QObject::connect(udpServerGet,&QUdpSocket::readyRead,[&](){udpServerGetSlot(); });
}

NewtworkProfil::~NewtworkProfil()
{
    //QString data="portStatus|mydisp|noLogin|0|0|0|0|myenv|noLogin|0|0|0|0|0|0|0|close";
    //udpServerSendSlot(data);
    udpServerGet->close();
    udpServerGet->deleteLater();
    udpServerSend->close();
    udpServerSend->deleteLater();
}
void NewtworkProfil::socketBaglama()
{
    qDebug()<<"socket bağlantıları kuruluyor...."<<networkTcpPort;
    /***********************************/

          //  QHostAddress *host  = new QHostAddress("192.168.63.254");
         //  QHostAddress *server = new QHostAddress("192.168.23.253");*/
            QString uport=networkTcpPort;
            std::reverse(uport.begin(), uport.end());

           udpServerSend = new QUdpSocket();
           udpServerGet = new QUdpSocket();

           udpServerGet->bind(uport.toInt(), QUdpSocket::ShareAddress);

           //udpSocketGet->bind(*host, uport.toInt());
            QObject::connect(udpServerGet,&QUdpSocket::readyRead,[&](){udpServerGetSlot();});
            qDebug()<<tcpPort<<uport<<"udp bağlandı";

}
void NewtworkProfil::udpServerSendSlot(QString _data)
{
    hostAddressMacButtonSlot();
    if(udpServerSend == nullptr){
        qDebug()<<"bağlı değil";
        socketBaglama();//bağlı değilse bağlan
    }

    for(int k=0;k<ipmaclist.count();k++)
    {
        if(networkBroadCastAddress!=""&&
            serverAddress.section(".",0,2)==networkBroadCastAddress.section(".",0,2)&&
            serverAddress.section(".",0,2)==ipmaclist[k].ip.section(".",0,2))
        {
            QString msg="eagclientconf|"+ipmaclist[k].ip+"|"+ipmaclist[k].mac+"|"+_data;
            QByteArray datagram = msg.toUtf8();// +QHostAddress::LocalHost;
            udpServerSend->writeDatagram(datagram,QHostAddress(serverAddress), networkTcpPort.toInt());
            ///qDebug()<<msg<<networkTcpPort;
        }
    }

}
void NewtworkProfil::udpServerGetSlot()
{
    QByteArray datagram;
    QStringList mesaj;
    while (udpServerGet->hasPendingDatagrams()) {
        datagram.resize(int(udpServerGet->pendingDatagramSize()));
        QHostAddress sender;
        quint16 senderPort;
        udpServerGet->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        QString rmesaj=datagram.constData();
        mesaj=rmesaj.split("|");
        qDebug()<<"Server Mesaj:"<<mesaj;
        if(mesaj[0]=="eagconf")
        {
            //qDebug()<<"Gelen Udp Mesajı eagconf.........:"<<mesaj;
            QString serverAddress1=mesaj[1];
            QString networkBroadCastAddress1=mesaj[2];
            QString networkTcpPort1=mesaj[3];
            QString ftpPort1=mesaj[4];
            QString rootPath1=mesaj[5];
            QString language1=mesaj[6];
            bool lockScreenState1= stringToBool(mesaj[7]);
            bool webblockState1= stringToBool(mesaj[8]);
            bool updateState=false;
            if(serverAddress!=serverAddress1) updateState=true;
            if(networkBroadCastAddress!=networkBroadCastAddress1) updateState=true;
            if(networkTcpPort!=networkTcpPort1) updateState=true;
            if(ftpPort!=ftpPort1) updateState=true;
            if(rootPath!=rootPath1) updateState=true;
            if(language!=language1) updateState=true;
            if(lockScreenState!=lockScreenState1) updateState=true;
            if(webblockState!=webblockState1) updateState=true;
            if(updateState)
            {
                qDebug()<<"eagconf bilgileri farklı güncelleniyor.";
                networkProfilSave(rmesaj);
                system("systemctl restart e-ag-client-console.service");
            }
        }
    }
}

void NewtworkProfil::networkProfilSave(QString data)
{
   // qDebug()<<"Gelen Tray eagconf Veri:"<<data;
    QStringList mesaj;
    mesaj=data.split("|");
    DatabaseHelper *db=new DatabaseHelper(localDir+"e-ag.json");
    QJsonObject veri;
    veri["networkIndex"]= QString::number(db->getIndex("networkIndex"));
    veri["selectedNetworkProfil"] =true;
    veri["networkName"] = "network";
    veri["networkTcpPort"] = mesaj[3];
    veri["serverAddress"]=mesaj[1];
    veri["networkBroadCastAddress"]=mesaj[2];
    veri["ftpPort"]=mesaj[4];
    veri["rootPath"]=mesaj[5];
    veri["language"]=mesaj[6];
    veri["lockScreenState"]=stringToBool(mesaj[7]);
    veri["webblockState"]=stringToBool(mesaj[8]);
    db->Sil("networkBroadCastAddress",mesaj[2]);
    db->Ekle(veri);
    networkProfilLoad();
}
void NewtworkProfil::networkProfilLoad()
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
    }else{
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
void NewtworkProfil::hostAddressMacButtonSlot()
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
                  // qDebug()<<"broadcast  address:"<<entry.broadcast().toString();
               ///  qDebug()<<"type:"<<networkInterface.name()<<networkInterface.type();
                QString program="ethtool -s "+networkInterface.name()+" wol g &";
                system(program.toStdString().c_str());
                  /*
                 if(networkInterface.type()==QNetworkInterface::Ethernet)
                 {

                     //QString program = "notepad.exe"; // Çalıştırılacak uygulamanın yolu (Windows için)
                     QStringList arguments;
                     arguments << "&"; // Uygulamaya geçirilecek argümanlar (isteğe bağlı)

                     QProcess *process = new QProcess();

                     // Uygulamanın başlamasıyla ilgili bir sinyali bağlayabiliriz (isteğe bağlı)
                     QObject::connect(process, &QProcess::started, [=](){
                         qDebug() << "Uygulama başlatıldı:" << program;
                     });

                     // Uygulamanın bitmesiyle ilgili bir sinyali bağlayabiliriz (isteğe bağlı)
                     QObject::connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                                      [=](int exitCode, QProcess::ExitStatus exitStatus){
                                          qDebug() << "Uygulama bitti. Çıkış kodu:" << exitCode
                                                   << ", Durum:" << (exitStatus == QProcess::NormalExit ? "Normal" : "Çökme");
                                          process->deleteLater(); // İşlem nesnesini sil
                                      });

                     // Uygulamayı asenkron olarak başlat
                     process->start(program, arguments);

                     if (!process->waitForStarted(1000)) { // Uygulamanın başlayıp başlamadığını kısa bir süre kontrol et (isteğe bağlı)
                         qDebug() << "Uygulama başlatılamadı:" << process->errorString();
                         process->deleteLater();
                     } else {
                         qDebug() << "Uygulama başlatılıyor ve ana akış devam ediyor...";
                         // Burada ana uygulamanızın diğer işlemleri devam edebilir.
                     }

                  //system(kmt27.toStdString().c_str());

                 }*/
               }
           }
       }


}
