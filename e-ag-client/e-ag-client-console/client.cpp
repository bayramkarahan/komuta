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
/************************************************/
    QTimer *tcpMesajSendTimer = new QTimer();
    QObject::connect(tcpMesajSendTimer, &QTimer::timeout, [&](){
        tcpMesajSendTimerSlot();
    });
    tcpMesajSendTimer->start(7000);
    networkProfilLoad();
    if(stringToBool(webblockState)) webBlockAktifPasif(true);
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
 //qDebug()<<"clientConsoleEnv"<<clientConsoleEnv;
 /******************************************************/
      if(clientTrayEnv=="")
        {
          clientTrayEnv="noLogin|0|0|0|0";
       }

      bool sshState;
      int vncState;
      bool ftpState;
      /*************************************/
      if (getIpPortStatus("systemctl status ssh.service|grep 'running'|wc -l",0)=="open")
          sshState=true;
      else sshState=false;

      QString vncports=findX11vncPort("netstat -tulnp");
      //qDebug()<<"vnc portları: "<<vncports;
      //findX11vncPort("lsof -i -P -n | grep x11vnc|grep IPv4");
       /*************************************/
      if (getIpPortStatus("systemctl status vsftpd.service|grep 'running'|wc -l",0)=="open")
          ftpState=true;
      else ftpState=false;
      /*************************************/
      QString data="trayenv|"+clientTrayEnv+"|"+clientConsoleEnv+"|"+QString::number(sshState)+"|"+vncports+"|"+QString::number(ftpState);
      /*if(tempdata!=data)
      {

          udpServerSendSlot(data);
          tempdata=data;
          dataSayac=1;

      }
      else dataSayac++;
      if(dataSayac>3)
      {
          udpServerSendSlot(data);
          tempdata=data;
          dataSayac=0;

      }*/
      udpServerSendSlot(data);
      tempdata=data;
      data="";
      //pgrep 15 karakterden fazla olmamalı bundan dolayı tray yerine tra bırakılmıştır
      if (!uygulamaCalisiyorMu("pgrep e-ag-client-tra")) {
          clientTrayEnv="noLogin|0|0|0|0";
      }

}

QString Client::findX11vncPort(QString kmt) {
    //qDebug()<<"x11vnc portu test ediliyor....."<<kmt;
    QString ports="";
    QProcess process;
    process.start(kmt);
    process.waitForFinished();
    QString output = process.readAllStandardOutput();
    //qDebug()<<"test sonucu:"<<output.split("\n");

    QStringList lines = output.split("\n");
    for (const QString& line : lines) {

            QStringList parts = line.split(" ");
         if (line.contains("x11vnc")) {
             if (line.contains("tcp6")) {
                // qDebug()<<"satir"<<line;
            for (const QString& part : parts) {
                if (part.contains("59")) {
                    //qDebug()<<"satir"<<part.split(":")[3];
                    //return part.split(":")[1];
                    ports=ports+part.split(":")[3]+"-";

                }
            }
             }
        }
    }
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
    QString data="portStatus|mydisp|noLogin|0|0|0|0|myenv|noLogin|0|0|0|0|0|0|0|close";
    udpServerSendSlot(data);
    udpServerSend->close();
    udpServerSend->deleteLater();
}

void Client::socketBaglama()
{
    qDebug()<<"socket bağlantıları kuruluyor...."<<networkTcpPort;
    /***********************************/

          //  QHostAddress *host  = new QHostAddress("192.168.63.254");
         //  QHostAddress *server = new QHostAddress("192.168.23.253");*/
            QString uport=networkTcpPort;
            std::reverse(uport.begin(), uport.end());

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

            qDebug()<<tcpPort<<uport<<"udp bağlandı";
            tcpMesajSendTimerSlot();


}

void Client::udpServerSendSlot(QString _data)
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
        //qDebug()<<"**********************************************************";
        //qDebug()<<"udpClientTrayRead:"<<rmesaj;
        //qDebug()<<"**********************************************************";
        clientTrayEnv=rmesaj;

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
        /*
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
        }*/
    }else
    {
        qDebug()<<"Yeni Network Ekleniyor.";

        hostAddressMacButtonSlot();

            //qDebug()<<"broadcast address:"<<i<<ipmaclist[i].broadcast;
            QJsonObject veri;
            veri["networkIndex"] =QString::number(db->getIndex("networkIndex"));
            veri["selectedNetworkProfil"] =true;
            veri["networkName"] = "network";
            veri["networkTcpPort"] = "7879";
            veri["serverAddress"]="";
            veri["networkBroadCastAddress"]="";
            veri["ftpPort"]="12345";
            veri["rootPath"]="/tmp/";
            veri["language"]="tr_TR";
            veri["lockScreenState"]=false;
            veri["webblockState"]=false;
            db->Ekle(veri);

        networkProfilLoad();
    }
}

void Client::udpServerGetSlot()
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
        qDebug()<<"Gelen Udp Mesaj:"<<mesaj;
        QString x11mesaj="";
        bool sendStatus=false;
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
                DatabaseHelper *db=new DatabaseHelper(localDir+"e-ag.json");
                QJsonObject veri;
                veri["networkIndex"]= this->networkIndex;
                veri["selectedNetworkProfil"] =true;
                veri["networkName"] = "network";
                veri["networkTcpPort"] = networkTcpPort1;
                veri["serverAddress"]=serverAddress1;
                veri["networkBroadCastAddress"]=networkBroadCastAddress1;
                veri["ftpPort"]=ftpPort1;
                veri["rootPath"]=rootPath1;
                veri["language"]=language1;
                veri["lockScreenState"]=lockScreenState1;
                veri["webblockState"]=webblockState1;
                db->Sil("networkIndex",this->networkIndex);
                db->Ekle(veri);
                networkProfilLoad();
            }
            /*else
            {
                qDebug()<<"eagconf bilgileri aynı.";
                if(stringToBool(webblockState)) webBlockAktifPasif(true);
            }*/

        }
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
            if(stringToBool(webblockState)) webBlockAktifPasif(true);
        }

        if(mesaj[0]=="debeagscript")
        {
            qDebug()<<"*********************************************************";
            qDebug()<<"gelen dosya"<<mesaj[1];
            QString dosya=mesaj[1];
            qDebug()<<"*********************************************************";
            QString kmt2="chmod 755 /tmp/debeagscript";
            QString kmt3="bash /tmp/debeagscript";
            system(kmt2.toStdString().c_str());
            system("sleep 0.1");
            system(kmt3.toStdString().c_str());
        }

        if(mesaj[0]=="scriptsendfile")
        {
            qDebug()<<"*********************************************************";
            qDebug()<<"gelen dosya"<<mesaj[1];
            QString dosya=mesaj[1];
            qDebug()<<"*********************************************************";
            QString kmt2="chmod 755 /tmp/eagscript";
            QString kmt3="bash /tmp/eagscript";
            system(kmt2.toStdString().c_str());
            system("sleep 0.1");
            system(kmt3.toStdString().c_str());
        }

        if(mesaj[0]=="homesendfile")
        {
            qDebug()<<"*********************************************************";
            qDebug()<<"gelen dosya"<<mesaj[1];
            qDebug()<<"clientTrayEnv: "<<clientTrayEnv;
            qDebug()<<"masaüstü kullanıcısı: "<<clientTrayEnv.split("|")[0];
            QString dosya=mesaj[1];
            QString guiusername=clientTrayEnv.split("|")[0];
            qDebug()<<"*********************************************************";
            QString kmt1="cp /tmp/"+dosya+" /home/"+guiusername+"/";
            QString kmt2="chmod 777 /home/"+guiusername+"/"+dosya;
            QString kmt3="chown "+guiusername+":"+guiusername+" /home/"+guiusername+"/"+dosya;
            system(kmt1.toStdString().c_str());system("sleep 0.1");
            system(kmt2.toStdString().c_str());system("sleep 0.1");
            system(kmt3.toStdString().c_str());
        }
        if(mesaj[0]=="desktopsendfile")
        {
            qDebug()<<"*********************************************************";
            qDebug()<<"gelen dosya"<<mesaj[1];
            qDebug()<<"masaüstü kullanıcısı: "<<clientTrayEnv.split("|")[0];
            QString dosya=mesaj[1];
            QString guiusername=clientTrayEnv.split("|")[0];
            qDebug()<<"*********************************************************";
            QString kmt1="cp /tmp/"+dosya+" /home/"+guiusername+"/Masaüstü/";
            QString kmt2="chmod 777 /home/"+guiusername+"/Masaüstü/"+dosya;
            QString kmt3="chown "+guiusername+":"+guiusername+" /home/"+guiusername+"/Masaüstü/"+dosya;
            system(kmt1.toStdString().c_str());system("sleep 0.1");
            system(kmt2.toStdString().c_str());system("sleep 0.1");
            system(kmt3.toStdString().c_str());
        }

        if(mesaj[0]=="desktopsendworkfile")
        {
            qDebug()<<"*********************************************************";
            qDebug()<<"gelen dosya"<<mesaj[1];
            qDebug()<<"masaüstü kullanıcısı: "<<clientTrayEnv.split("|")[0];
            QString dosya=mesaj[1];
            QString guiusername=clientTrayEnv.split("|")[0];
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

        if(mesaj[0]=="sshporttest")
        {
            /*************************************/
            if (getIpPortStatus("systemctl status ssh.service|grep 'running'|wc -l",0)=="open")
                udpServerSendSlot("sshporttestopen");
            else udpServerSendSlot("sshporttestclose");
        }
        if(mesaj[0]=="vncporttest")
        {
            /*************************************/
            if (getIpPortStatus("systemctl status e-ag-x11vncdesktop.service|grep '5900'|wc -l",1)=="open"||
                    getIpPortStatus("systemctl status e-ag-x11vnclogin.service|grep '5902'|wc -l",1)=="open")
                udpServerSendSlot("vncporttestopen");
            else udpServerSendSlot("vncporttestclose");
        }
        if(mesaj[0]=="ftpporttest")
        {
            /*************************************/
            if (getIpPortStatus("systemctl status vsftpd.service|grep 'running'|wc -l",0)=="open")
                udpServerSendSlot("ftpporttestopen");
            else udpServerSendSlot("ftpporttestclose");
        }
        if(mesaj[0]=="kilitstatetrue")
        {
            //  udpSocketSendTServer("kilitstatetestopen");
            x11mesaj=rmesaj; sendStatus=true;
        }
        if(mesaj[0]=="kilitstatefalse")
        {
            //udpServerSendSlot("kilitstatetestclose");
            x11mesaj=rmesaj;sendStatus=true;
        }
        if(mesaj[0]=="transparankilitstatetrue")
        {
            x11mesaj=rmesaj; sendStatus=true;
            //  udpSocketSendTServer("kilittransparanstatetestopen");
        }
        if(mesaj[0]=="transparankilitstatefalse")
        {
            x11mesaj=rmesaj; sendStatus=true;

            // udpSocketSendTServer("kilittransparanstatetestopen");
        }
        if(mesaj[0]=="dosyatopla")
        {
            x11mesaj=rmesaj; sendStatus=false;
            QString severip=mesaj[2];
            QString guiusername=clientTrayEnv.split("|")[0];
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

            for(int i=0;i<ipmaclist.count();i++)
            {
                // QString komut="sshpass -p "+password+" scp -o StrictHostKeyChecking=no "+gercekad+" "+
                //        username+"@"+severip+":\/home\/"+username+"\/Masaüstü\/"+ipmaclist[i].ip+ad;


                QString komut="/usr/bin/scd-client "+severip+" 12345 PUT "+gercekad+" /"+ipmaclist[i].ip+ad;
                // system(komut.toStdString().c_str());
                qDebug()<<"komut: "<<komut;
                qDebug()<<"kopayalanacak dosya: "<<gercekad;
                qDebug()<<"yeni dosya adı: "<<ipmaclist[i].ip+ad;
                qDebug()<<"guiusername: "<<guiusername;
                QStringList arguments;
                arguments << "-c" << komut;
                QProcess process;
                process.start("/bin/bash",arguments);
                process.waitForFinished(-1); // will wait forever until finished
                udpServerSendSlot("sendfileclient|"+ipmaclist[i].ip+ad);
        }
        }
        if(mesaj[0]=="ekranimagestatetrue")
        {
            x11mesaj=rmesaj; sendStatus=true;
            //udpSocketSendTServer("ekranimagestatetestopen");
        }
        if(mesaj[0]=="ekranimagestatefalse")
        {
            x11mesaj=rmesaj; sendStatus=true;
            //udpSocketSendTServer("ekranimagestatetestopen");
        }
        if(mesaj[0]=="webblocktrue")
        {
            if(stringToBool(webblockState)) webBlockAktifPasif(true);
            x11mesaj=rmesaj; sendStatus=false;
        }
        if(mesaj[0]=="webblockfalse")
        {
           if(stringToBool(webblockState)) webBlockAktifPasif(false);
            x11mesaj=rmesaj; sendStatus=false;
        }

        if(mesaj[0]=="kilitstate")
        {
            qDebug()<<"Client-Gelen Mesaj:"<<rmesaj;
            /***********************************************/
            x11mesaj=rmesaj; sendStatus=true;
        }
        if(mesaj[0]=="ekranmesaj")
        {
            qDebug()<<"ClientTray'a gonderildi: "<<rmesaj;
            x11mesaj=rmesaj; sendStatus=true;
        }
        if(mesaj[0]=="consolecommand")
        {
            commandExecuteSlot(mesaj[1]);
            x11mesaj=rmesaj; sendStatus=false;
        }
        if(mesaj[0]=="x11komut")
        {
            qDebug()<<"ClientTray'a gonderildi: "<<rmesaj;
            x11mesaj=rmesaj; sendStatus=true;
        }
        if(mesaj[0]=="volumeoff")
        {
            qDebug()<<"ClientTray'a gonderildi: "<<rmesaj;
            x11mesaj=rmesaj; sendStatus=true;
        }
        if(mesaj[0]=="volumeon")
        {
            qDebug()<<"ClientTray'a gonderildi: "<<rmesaj;
            x11mesaj=rmesaj; sendStatus=true;
        }
        if(mesaj[0]=="videoyayinbaslat")
        {
            qDebug()<<"ClientTray'a gonderildi: "<<rmesaj;
            x11mesaj=rmesaj; sendStatus=true;
        }
        if(mesaj[0]=="videoyayindurdur")
        {
            qDebug()<<"ClientTray'a gonderildi: "<<rmesaj;
            x11mesaj=rmesaj; sendStatus=true;
        }
        if(mesaj[0]=="pckapat")
        {
            qDebug()<<"Client-Gelen Mesaj:"<<rmesaj;
            commandExecuteSlot(mesaj[1]);
        }
        if(mesaj[0]=="pcbaslat")
        {
            qDebug()<<"Client-Gelen Mesaj:"<<rmesaj;
            commandExecuteSlot(mesaj[1]);
        }
        if(sendStatus)
        {
            QByteArray datagram = x11mesaj.toUtf8();// +QHostAddress::LocalHost;
            udpTraySend->writeDatagram(datagram,QHostAddress::LocalHost, 51512);
            sendStatus=false;
            x11mesaj="";
        }

    }


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

/*QString Client::getIpPortStatus(QString ip_,QString port)
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
   // qDebug()<<"Port sorgulama:"<<ip_<<result<<port;
    if(result.toInt()>0){ return "open";}
    else {return "close";}
}*/

void Client::hostAddressMacButtonSlot()
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
                 if(networkInterface.type()==QNetworkInterface::Ethernet)
                 {
                   QString kmt27="ethtool -s "+networkInterface.name()+" wol g";
                  system(kmt27.toStdString().c_str());
                 }
               }
           }
       }


}
void Client::commandExecuteSlot(QString command)
{
//echo '12' |sudo -S -u root -i apt-get update'
QString komut=command;
//mesajSlot(komut);
qDebug()<<komut;

QStringList arguments;
arguments << "-c" << komut;
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
