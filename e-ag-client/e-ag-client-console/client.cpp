#include "client.h"
#include<QDebug>
#include<QProcess>
#include <QtCore/QTimer>
#include <stdio.h>
#include <QtCore/QCoreApplication>
#include<Database.h>

Client::Client()
{

    localDir="/usr/share/e-ag/";
    localDir1="/tmp/";
    hostAddressMacButtonSlot();
/************************************************/
    QTimer *tcpMesajSendTimer = new QTimer();
    QObject::connect(tcpMesajSendTimer, &QTimer::timeout, [&](){
        tcpMesajSendTimerSlot();
    });
    tcpMesajSendTimer->start(7000);

    networkProfilLoad();

    for (const NetProfil &item : NetProfilList) {
        if (item.serverAddress=="") continue;
        if (item.selectedNetworkProfil==false) continue;
        if(item.webblockState) webBlockAktifPasif(true);
    }

}


void Client::udpServerSendSlot(QString _data)
{

    if(udpServerGetStatus) return;
    hostAddressMacButtonSlot();
    if(udpServerSend == nullptr){
        qDebug()<<"Server bağlı değil! Bağlanıyor...";
        socketBaglama();//bağlı değilse bağlan
    }

    /***********************************************************************/
    for (const NetProfil &item : NetProfilList) {
        if (item.serverAddress=="") continue;
        if (item.selectedNetworkProfil==false) continue;
        for(int k=0;k<interfaceList.count();k++)
        {
            if(item.networkBroadCastAddress==interfaceList[k].broadcast)
            {
                QString msg="eagclientconf|"+interfaceList[k].ip+"|"+interfaceList[k].mac+"|"+_data;
                QByteArray datagram = msg.toUtf8();// +QHostAddress::LocalHost;
                udpServerSend->writeDatagram(datagram,QHostAddress(item.serverAddress), item.networkTcpPort.toInt());
                qDebug()<<msg<<item.networkTcpPort;
            }
        }
    }
}

void Client::udpGuiGetSlot()
{
    QByteArray datagram;
    QStringList mesaj;

    while (udpGuiGet->hasPendingDatagrams()) {
        datagram.resize(int(udpGuiGet->pendingDatagramSize()));
        QHostAddress sender;
        quint16 senderPort;

        udpGuiGet->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString rmesaj=datagram.constData();
        qDebug()<<"udpClientGuiRead:"<<rmesaj;
        clientGuiEnv=rmesaj;
        if(rmesaj=="webblocktrue")
            webBlockAktifPasif(true);

        if(rmesaj=="webblockfalse")
            webBlockAktifPasif(false);
    }
}

void Client::networkProfilLoad()
{

    DatabaseHelper *db=new DatabaseHelper(localDir+"e-ag.json");
    //QJsonArray dizi=db->Oku();
    QJsonArray dizi=db->Ara("selectedNetworkProfil",true);
    NetProfilList.clear();
    if(dizi.count()>0)
    {
        for (const QJsonValue &item : dizi) {
            QJsonObject veri=item.toObject();
            //qDebug()<<"Yüklenen Ağ Profili:" <<veri;
            NetProfil np;
            np.networkIndex=veri["networkIndex"].toString();
            np.selectedNetworkProfil=veri["selectedNetworkProfil"].toBool();
            np.networkName=veri["networkName"].toString();
            np.networkTcpPort=veri["networkTcpPort"].toString();
            np.networkBroadCastAddress=veri["networkBroadCastAddress"].toString();
            np.serverAddress=veri["serverAddress"].toString();
            np.ftpPort=veri["ftpPort"].toString();
            np.rootPath=veri["rootPath"].toString();
            np.language=veri["language"].toString();
            np.lockScreenState=veri["lockScreenState"].toBool();
            np.webblockState=veri["webblockState"].toBool();
            NetProfilList.append(np);
        }
    }else{
        qDebug()<<"Yeni Network Ekleniyor.";
        hostAddressMacButtonSlot();
        for(int i=0;i<interfaceList.count();i++)
        {
            //qDebug()<<"broadcast address:"<<i<<ipmaclist[i].broadcast;
            QJsonObject veri;
            veri["networkIndex"] =QString::number(db->getIndex("networkIndex"));
            veri["selectedNetworkProfil"] =true;
            veri["networkName"] = "network";
            veri["networkTcpPort"] = "7879";
            veri["serverAddress"]="";
            veri["networkBroadCastAddress"]=interfaceList[i].broadcast;
            veri["ftpPort"]="12345";
            veri["rootPath"]="/tmp/";
            veri["language"]="tr_TR";
            veri["lockScreenState"]=false;
            veri["webblockState"]=false;
            db->Sil("networkBroadCastAddress",interfaceList[i].broadcast);
            db->Ekle(veri);
        }
        //internet yoksa olur
        if(interfaceList.count()==0)
        {
            //qDebug()<<"broadcast address:"<<i<<interfaceList[i].broadcast;
            QJsonObject veri;
            veri["networkIndex"] =QString::number(db->getIndex("networkIndex"));
            veri["selectedNetworkProfil"] =true;
            veri["networkName"] = "networknullip";
            veri["networkTcpPort"] = "7879";
            veri["serverAddress"]="";
            veri["networkBroadCastAddress"]="";
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

void Client::udpServerGetSlot()
{
    udpServerGetStatus=true;
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
        if(mesaj[0]=="webblockserversendfile")
        {
            qDebug()<<"*********************************************************";
            qDebug()<<"gelen dosya"<<mesaj[1];
            QString dosya=mesaj[1];
            qDebug()<<"*********************************************************";
            QString kmt1="cp /tmp/"+dosya+" /usr/share/e-ag/";
            QString kmt2="chmod 777 /usr/share/e-ag/"+dosya;
            system(kmt1.toStdString().c_str());system("sleep 0.1");
            system(kmt2.toStdString().c_str());system("sleep 0.1");
            bool webblockState=false;
            for (const NetProfil &item : NetProfilList) {
                if (item.serverAddress=="") continue;
                if (item.selectedNetworkProfil==false) continue;
                if(item.webblockState) webblockState=true;
            }
            if(webblockState)
            {
                qDebug()<<"Client webblockState Ayarları:"<<webblockState;
                webBlockAktifPasif(true);
            }
            if(!webblockState)
            {
                qDebug()<<"Client webblockState Ayarları:"<<webblockState;
                webBlockAktifPasif(false);
            }
        }
        else if(mesaj[0]=="debscriptsendfile")
        {
            qDebug()<<"*********************************************************";
            qDebug()<<"gelen dosya"<<mesaj[1];
            QString dosya=mesaj[1];
            qDebug()<<"*********************************************************";
            QString kmt2="chmod 755 /tmp/debeagscript&";
            QString kmt3="bash /tmp/debeagscript&";
            system(kmt2.toStdString().c_str());
            system("sleep 0.1");
            system(kmt3.toStdString().c_str());
        }
        else if(mesaj[0]=="scriptsendfile")
        {
            qDebug()<<"*********************************************************";
            qDebug()<<"gelen dosya"<<mesaj[1];
            QString dosya=mesaj[1];
            qDebug()<<"*********************************************************";
            QString kmt2="chmod 755 /tmp/eagscript&";
            QString kmt3="bash /tmp/eagscript&";
            system(kmt2.toStdString().c_str());
            system("sleep 0.1");
            system(kmt3.toStdString().c_str());
        }
        else if(mesaj[0]=="homesendfile")
        {
            qDebug()<<"*********************************************************";
            qDebug()<<"gelen dosya"<<mesaj[1];
            qDebug()<<"clientTrayEnv: "<<clientConsoleEnv;
            qDebug()<<"masaüstü kullanıcısı: "<<clientConsoleEnv.split("|")[1];
            QString dosya=mesaj[1];
            QString guiusername=clientConsoleEnv.split("|")[1];
            qDebug()<<"*********************************************************";
            QString kmt1="cp /tmp/"+dosya+" /home/"+guiusername+"/";
            QString kmt2="chmod 777 /home/"+guiusername+"/"+dosya;
            QString kmt3="chown "+guiusername+":"+guiusername+" /home/"+guiusername+"/"+dosya;
            system(kmt1.toStdString().c_str());system("sleep 0.1");
            system(kmt2.toStdString().c_str());system("sleep 0.1");
            system(kmt3.toStdString().c_str());
        }
        else if(mesaj[0]=="desktopsendfile")
        {
            qDebug()<<"*********************************************************";
            qDebug()<<"gelen dosya"<<mesaj[1];
            qDebug()<<"masaüstü kullanıcısı: "<<clientConsoleEnv.split("|")[1];
            QString dosya=mesaj[1];
            QString guiusername=clientConsoleEnv.split("|")[1];
            qDebug()<<"*********************************************************";
            QString kmt1="cp /tmp/"+dosya+" /home/"+guiusername+"/Masaüstü/";
            QString kmt2="chmod 777 /home/"+guiusername+"/Masaüstü/"+dosya;
            QString kmt3="chown "+guiusername+":"+guiusername+" /home/"+guiusername+"/Masaüstü/"+dosya;
            system(kmt1.toStdString().c_str());system("sleep 0.1");
            system(kmt2.toStdString().c_str());system("sleep 0.1");
            system(kmt3.toStdString().c_str());
        }
        else if(mesaj[0]=="desktopsendworkfile")
        {
            qDebug()<<"*********************************************************";
            qDebug()<<"gelen dosya"<<mesaj[1];
            qDebug()<<"masaüstü kullanıcısı: "<<clientConsoleEnv.split("|")[1];
            QString dosya=mesaj[1];
            QString guiusername=clientConsoleEnv.split("|")[1];
            qDebug()<<"*********************************************************";
            QString kmt0="mv /home/"+guiusername+"/Masaüstü/"+dosya+" /home/"+guiusername+"/Masaüstü/e-ag-server.old";
            QString kmt1="cp /tmp/"+dosya+" /home/"+guiusername+"/Masaüstü/";
            QString kmt2="chmod 777 /home/"+guiusername+"/Masaüstü/"+dosya;
            QString kmt3="chown "+guiusername+":"+guiusername+" /home/"+guiusername+"/Masaüstü/"+dosya;
            system(kmt0.toStdString().c_str());system("sleep 0.1");
            system(kmt1.toStdString().c_str());system("sleep 0.1");
            system(kmt2.toStdString().c_str());system("sleep 0.1");
            system(kmt3.toStdString().c_str());
        }
        else if(mesaj[0]=="x11command")
        {
            ///qDebug()<<"ClientTray'a gonderildi: "<<rmesaj;
            QByteArray datagram = rmesaj.toUtf8();// +QHostAddress::LocalHost;
            udpTraySend->writeDatagram(datagram,QHostAddress::LocalHost, 51512);
        }
        else if(mesaj[0]=="consolecommand")
        {
            commandExecuteSlot(mesaj[2]);
            QByteArray datagram = rmesaj.toUtf8();// +QHostAddress::LocalHost;
            udpTraySend->writeDatagram(datagram,QHostAddress::LocalHost, 51512);
        }
        else if(mesaj[0]=="dosyatopla")
        {

            QString severip=mesaj[3];
            QString guiusername=clientConsoleEnv.split("|")[1];
            hostAddressMacButtonSlot();//local ip adresi tespit ediliyor.

            QDir directory("/home/"+guiusername+"/Masaüstü");
            QStringList filelist = directory.entryList(QStringList() << "e-ag-server.*",QDir::Files);
            QString ad="";
            QString gercekad="";
            foreach(QString filename, filelist) {
                QFileInfo fi(filename);
                QString uzanti = fi.completeSuffix();
                gercekad="/home/"+guiusername+"/Masaüstü\/"+filename;
                ad="-e-ag-server."+uzanti;
            }

            for(int i=0;i<interfaceList.count();i++)
            {

                QString komut="/usr/bin/scd-client "+severip+" 12345 PUT "+gercekad+" /"+interfaceList[i].ip+ad;
                // system(komut.toStdString().c_str());
                qDebug()<<"komut: "<<komut;
                qDebug()<<"kopayalanacak dosya: "<<gercekad;
                qDebug()<<"yeni dosya adı: "<<interfaceList[i].ip+ad;
                qDebug()<<"guiusername: "<<guiusername;
                QStringList arguments;
                arguments << "-c" << komut;
                QProcess process;
                process.start("/bin/bash",arguments);
                process.waitForFinished(-1); // will wait forever until finished

               /// udpServerSendSlot("sendfileclient|"+ipmaclist[i].ip+ad);
                for (const NetProfil &item : NetProfilList) {
                    if (item.serverAddress=="") continue;
                    if (item.selectedNetworkProfil==false) continue;
                    if(item.networkBroadCastAddress!=""&&
                     item.serverAddress.section(".",0,2)==item.networkBroadCastAddress.section(".",0,2)&&
                     item.serverAddress.section(".",0,2)==interfaceList[i].ip.section(".",0,2))
                 {
                     QString msg="eagclientconf|"+interfaceList[i].ip+"|"+interfaceList[i].mac+"|"+"sendfileclient|"+interfaceList[i].ip+ad;
                     QByteArray datagram = msg.toUtf8();// +QHostAddress::LocalHost;
                     udpServerSend->writeDatagram(datagram,QHostAddress(item.serverAddress), item.networkTcpPort.toInt());
                     ///qDebug()<<msg<<networkTcpPort;
                 }
            }

            }
        }
    }
    udpServerGetStatus=false;
}

void Client::udpTrayGetSlot()
{
    QByteArray datagram;
    QStringList mesaj;
    while (udpTrayGet->hasPendingDatagrams()) {
        datagram.resize(int(udpTrayGet->pendingDatagramSize()));
        QHostAddress sender;
        quint16 senderPort;
        udpTrayGet->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        QString rmesaj=datagram.constData();
        QStringList mesaj=rmesaj.split("|");
        //qDebug()<<"udpClientTrayRead:"<<rmesaj;
        //if(mesaj[0]=="eagconf") networkProfilSave(rmesaj);
        if(mesaj[0]=="clientTrayEnv")  clientTrayEnv=rmesaj;
    }
}
void Client::tcpMesajSendTimerSlot()
{

    sessionUser=getSessionInfo(getSeatId(),"USER=");
    QStringRef _sessionUser=sessionUser.rightRef(sessionUser.length()-5);
    sessionUser=_sessionUser.toString();

    sessionUserId=getSessionInfo(getSeatId(),"UID=");
    QStringRef _sessionUserId=sessionUserId.rightRef(sessionUserId.length()-4);
    sessionUserId=_sessionUserId.toString();

    sessionDisplay=getSessionInfo(getSeatId(),"DISPLAY=:");
    QStringRef _sessionDisplay=sessionDisplay.rightRef(sessionDisplay.length()-9);
    sessionDisplay=_sessionDisplay.toString();

    sessionDesktopManager=getSessionInfo(getSeatId(),"SERVICE=");
    QStringRef _sessionDesktopManager=sessionDesktopManager.rightRef(sessionDesktopManager.length()-8);
    sessionDesktopManager=_sessionDesktopManager.toString();

    sessionDisplayType=getSessionInfo(getSeatId(),"ORIGINAL_TYPE=");
    QStringRef _sessionDisplayType=sessionDisplayType.rightRef(sessionDisplayType.length()-14);
    sessionDisplayType=_sessionDisplayType.toString();

    QSysInfo sysinfo;
    //= new QSysInfo();
    /*qDebug()<<"buildCpuArchitecture: " <<sysinfo.buildCpuArchitecture();
    qDebug()<<"currentCpuArchitecture: " <<sysinfo.currentCpuArchitecture();
    qDebug()<<"kernel type and version:" <<sysinfo.kernelType()<<sysinfo.kernelVersion().left(1);
    qDebug()<<"product name and version:  " <<sysinfo.prettyProductName();
    */
    //qDebug()<<"product name and version:  " <<sysinfo.machineHostName();

    // QString projeversion=sysinfo.prettyProductName()+sysinfo.kernelVersion().left(1);
    QString hostname=sysinfo.machineHostName();

    //qDebug()<<sessionUser<<sessionDisplay<<sessionUserId<<projeversion<<sessionDesktopManager<<sessionDisplayType;
    clientConsoleEnv="consolenv|"+sessionUser+"|"+sessionDisplay+"|"+sessionUserId+"|"+hostname+"|"+sessionDesktopManager;
    //clientConsoleEnv="consolenv||||"+hostname+"|";

    //qDebug()<<"clientConsoleEnv"<<clientConsoleEnv;
    /******************************************************/
    if(clientTrayEnv=="")
    {
        clientTrayEnv="clientTrayEnv|noLogin|0";
    }

    //pgrep 15 karakterden fazla olmamalı bundan dolayı tray yerine tra bırakılmıştır
    if (!uygulamaCalisiyorMu("pgrep e-ag-client-tra")) {
        clientTrayEnv="clientTrayEnv|noLogin|0";
    }


    bool sshState;
    bool xrdpState;
    /*************************************/
    if (getIpPortStatus("systemctl status ssh.service|grep 'running'|wc -l",0)=="open")
        sshState=true;
    else sshState=false;
    QString vncports=findX11vncPort("netstat -tulnp");
    //qDebug()<<"vnc portları: "<<vncports;
    //findX11vncPort("lsof -i -P -n | grep x11vnc|grep IPv4");
    /*************************************/
    if (getIpPortStatus("systemctl status xrdp.service|grep 'running'|wc -l",0)=="open")
        xrdpState=true;
    else xrdpState=false;
    /*************************************/
    QString data=clientTrayEnv+"|"+clientConsoleEnv+"|"+QString::number(sshState)+"|"+vncports+"|"+QString::number(xrdpState);
    udpServerSendSlot(data);
    tempdata=data;
    data="";

}


void Client::socketBaglama()
{

    QString uport="7879";
    if(NetProfilList.count()>0)
        uport=NetProfilList.first().networkTcpPort;
    std::reverse(uport.begin(), uport.end());
    qDebug()<<"SocketBaglama";
    qDebug()<<"Socket bağlantı portu: "<<uport;
    /***********************************/
qDebug()<<"debug socketBaglama2";
    //  QHostAddress *host  = new QHostAddress("192.168.63.254");
    //  QHostAddress *server = new QHostAddress("192.168.23.253");*/

    udpServerSend = new QUdpSocket();
    udpTraySend= new QUdpSocket();
    udpServerGet = new QUdpSocket();
    udpTrayGet=new QUdpSocket();
    udpGuiGet=new QUdpSocket();

    udpServerGet->bind(uport.toInt(), QUdpSocket::ShareAddress);
    udpTrayGet->bind(51511, QUdpSocket::ShareAddress);
    udpGuiGet->bind(51521, QUdpSocket::ShareAddress);

    //udpSocketGet->bind(*host, uport.toInt());
    QObject::connect(udpServerGet,&QUdpSocket::readyRead,[&](){udpServerGetSlot();});
    QObject::connect(udpTrayGet,&QUdpSocket::readyRead,[&](){udpTrayGetSlot();});
    QObject::connect(udpGuiGet,&QUdpSocket::readyRead,[&](){udpGuiGetSlot();});

    qDebug()<<uport<<"udp bağlandı";
    tcpMesajSendTimerSlot();


}

void Client::hostAddressMacButtonSlot()
{
    QHostAddress localhost = QHostAddress(QHostAddress::LocalHost);
interfaceList.clear();
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
                  interfaceList.append(im);
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
void Client::commandExecuteSlot(QString command)
{
//echo '12' |sudo -S -u root -i apt-get update'
qDebug()<<command;
QStringList arguments;
arguments << "-c" << command+" &";
process.start("/bin/bash",arguments);
process.waitForFinished(-1); // will wait forever until finished
QString stdout = process.readAllStandardOutput();
QString stderr = process.readAllStandardError();
stdout.chop(1);
stderr.chop(1);
qDebug()<<"out:"<<stdout<<stdout.count();
qDebug()<<"err:"<<stderr<<stderr.count();
 //if(stdout)
//this->ui->lineEdit_message->setText(stdout);
//on_pushButton_sendMessage_clicked();
//this->ui->lineEdit_message->setText(stderr);
//on_pushButton_sendMessage_clicked();

//mesajSlot("Komut Çalıştırıldı");
qDebug()<<"Komut Çalıştırıldı";
}

void Client::webBlockAktifPasif(bool _state)
{
    webblockStateRun=true;
    if(_state)
    {
        QString kmt28="iptables -F &";
        system(kmt28.toStdString().c_str());

        int sr=0;
        DatabaseHelper *db=new DatabaseHelper(localDir+"webblockserver.json");
        //QJsonArray dizi=db->Oku();
        QJsonArray dizi=db->Ara("selectedWord",true);
        for (const QJsonValue &item : dizi) {
            QJsonObject veri=item.toObject();
            ///qDebug()<<veri["word"].toString();
            QString kmt28="iptables -A OUTPUT -p tcp -m string --string '"+veri["word"].toString()+"' --algo kmp -j REJECT &";
            //iptables -A OUTPUT -p tcp -m string --string 'youtube' --algo kmp -j REJECT
            //qDebug()<<"iptables komutu: "<<kmt28;
            system(kmt28.toStdString().c_str());
        }
    }
    if(!_state)
    {
        QString kmt28="iptables -F";
        system(kmt28.toStdString().c_str());

    }
}

QString Client::getIpPortStatus(QString service,int number)
{
    QString result="";
    QStringList arguments;
    arguments << "-c" << QString(service);
    QProcess process;
    process.start("/bin/bash",arguments);
    if(process.waitForFinished(-1))
    {
        result = process.readAll();
        result.chop(1);
    }
    // qDebug()<<"Port sorgulama:"<<result<<service;
    if(result.toInt()>number){ return "open";}
    else {return "close";}
}
bool Client::uygulamaCalisiyorMu(const QString& uygulamaAdi) {
    QString komut=uygulamaAdi;
    QStringList arguments;
    arguments << "-c" << komut;
    QProcess process;
    process.start("/bin/bash",arguments);
    process.waitForFinished();
    //qDebug()<<"çalışan komut: "<<komut;
    if (process.exitCode() == 0) {
        // Uygulama çalışıyor
        return true;
    } else {
        // Uygulama çalışmıyor
        return false;
    }
}
QString Client::findX11vncPort(QString kmt) {
    //qDebug()<<"x11vnc portu test ediliyor....."<<kmt;
    QString ports="";
    QProcess process;
    process.start(kmt);
    process.waitForFinished();
    QString output = process.readAllStandardOutput();
    //qDebug()<<"findX11vncPort test sonucu:"<<output.split("\n");

    QStringList lines = output.split("\n");
    for (const QString& line : lines) {


        if (line.contains("x11vnc")) {
            if (line.contains("tcp6")) {
                QStringList parts = line.split(" ");
                 //qDebug()<<"satir"<<line<<parts;
                for (const QString& part : parts) {
                    if (part.contains(":59")) {
                        //qDebug()<<"satir"<<part.split(":")[3];
                        //return part.split(":")[1];
                        ports=ports+part.split(":")[3]+"-";

                    }
                }
            }
        }
    }
    //qDebug()<<"findX11vncPort test sonucu00:"<<ports;


    return ports;
}
QString  Client::getSeatId()
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
QString Client::getSessionInfo(QString id, QString parametre)
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
Client::~Client()
{
    //QString data="portStatus|mydisp|noLogin|0|0|0|0|myenv|noLogin|0|0|0|0|0|0|0|close";
    //udpServerSendSlot(data);
    udpServerSend->close();
    udpServerSend->deleteLater();
}
