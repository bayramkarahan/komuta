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
#ifndef TCPUDP_H
#define TCPUDP_H
void  MainWindow::udpSendData(QString _mesajTur,QString _mesaj,QString _ip)
{
    //qDebug()<<"Mesaj Gönderilecek:"<<_mesajTur<<_mesaj<<_ip;
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
        ///qDebug()<<"Mesajın Gideceği Ağ:" <<networkBroadCastAddress;
        QString uport=networkTcpPort;
        std::reverse(uport.begin(), uport.end());
        if(networkBroadCastAddress!=""&&
            serverAddress.section(".",0,2)==networkBroadCastAddress.section(".",0,2)&&
            serverAddress.section(".",0,2)==_ip.section(".",0,2))
        {
        QString msg=_mesajTur+"|"+_mesaj+"|"+serverAddress+"|"+uport;
            ///qDebug()<<"Mesaj Gönderildi:"<<msg;
        QByteArray datagram = msg.toUtf8();
        udpSocketSend->writeDatagram(datagram,QHostAddress(_ip), uport.toInt());
        }
        ///system("sleep 0.1");
    }
}
void MainWindow::udpSocketServerRead()
{
    // qDebug()<<"Client Gelen Udp Mesaj:";
    QByteArray datagram;
    QStringList mesaj;

    while (udpSocketGet->hasPendingDatagrams()) {
        datagram.resize(int(udpSocketGet->pendingDatagramSize()));
        QHostAddress sender;
        quint16 senderPort;

        udpSocketGet->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString rmesaj=datagram.constData();
        ///qDebug()<<rmesaj;

        mesaj=rmesaj.split("|");
        // qDebug()<<"Client Gelen Udp Mesaj:"<<mesaj[0]<<mesaj[1]<<mesaj[2]<<mesaj[3];
        QStringList lst;
        QString _mac=mesaj[2];
        for(int i=0;i<onlinePcList.count();i++)
        {
            if(_mac.toUpper()==onlinePcList[i]->mac.toUpper()&&mesaj[3]=="sendfileclient"){
               qDebug()<<"Dosya Geldi: "<<mesaj[3]<<mesaj[4];
                QString dosya=mesaj[4];
               QString guiusername = qgetenv("USER");  //getenv("USERNAME"); //for windows
                QString kmt1="cp /tmp/"+dosya+" /home/"+guiusername+"/Masaüstü/";
                QString kmt2="chmod 777 /home/"+guiusername+"/Masaüstü/"+dosya;
                QString kmt3="chown "+guiusername+":"+guiusername+" /home/"+guiusername+"/Masaüstü/"+dosya;
                system(kmt1.toStdString().c_str());///system("sleep 0.1");
                system(kmt2.toStdString().c_str());///system("sleep 0.1");
                system(kmt3.toStdString().c_str());
           }

            if(_mac.toUpper()==onlinePcList[i]->mac.toUpper()&&mesaj[0]=="eagclientconf"){
                onlinePcList[i]->tcpConnectCounter=0;
                //qDebug()<<"gelen mesaj:"<<rmesaj<<mesaj.count();
                // btnlist[i]->tcpConnectCounter=0;
                onlinePcList[i]->setPcState(true);
                onlinePcList[i]->setConnectState(true);
                onlinePcList[i]->ip=mesaj[1];

                if(mesaj.count()==18)
                {
                    onlinePcList[i]->setUser(mesaj[4]);
                    ///onlinePcList[i]->setDisplay(mesaj[5]);
                    //if(onlinePcList[i]->caption==""){
                        onlinePcList[i]->setHostname(mesaj[13]);
                   // }
                    //onlinePcList[i]->setCaption(mesaj[13]);
/*
                    if(mesaj[6]=="1")
                        onlinePcList[i]->setKilitControlState(true);
                    else
                        onlinePcList[i]->setKilitControlState(false);


                    if(mesaj[7]=="1")
                        onlinePcList[i]->setKilitTransparanControlState(true);
                    else
                        onlinePcList[i]->setKilitTransparanControlState(false);

                    if(mesaj[8]=="1")
                        onlinePcList[i]->setIconControlState(true);
                    else
                        onlinePcList[i]->setIconControlState(false);
                    */
                    if(mesaj[15]=="1")
                        onlinePcList[i]->setSshState(true);
                    else
                        onlinePcList[i]->setSshState(false);

                    if(mesaj[16]!="0"){
                        onlinePcList[i]->setVncState(true);
                        onlinePcList[i]->vncport=mesaj[16];
                    }
                    else {
                        onlinePcList[i]->setVncState(false);
                        onlinePcList[i]->vncport=mesaj[16];
                    }

                    if(mesaj[17]=="1")onlinePcList[i]->setFtpState(true);
                    else onlinePcList[i]->setFtpState(false);

                }
            }

        }

    }


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
        ///qDebug()<<datagram;
        for(int i=1;i<255;i++)
        {
            QString broadadres;
            broadadres=networkBroadCastAddress.section(".",0,2)+"."+QString::number(i);
            //qDebug()<<broadadres;
            //udpSocketSend->writeDatagram(datagram,QHostAddress("255.255.255.255"), uport.toInt());
            udpSocketSend->writeDatagram(datagram,QHostAddress(broadadres), uport.toInt());
        }
        pcDetect();
    }
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
                  ipmaclist.append(im);

                 // qDebug()<<"mac:"<<networkInterface.hardwareAddress();
                  //qDebug()<<"ip  address:"<<entry.ip().toString();
                 // qDebug()<<"broadcast  address:"<<entry.broadcast().toString();
              }
           }
       }
//qDebug()<<"ip  address:"<<ipmaclist.count();


}
QStringList MainWindow::readArp()
{
    QStringList list;
    const int size = 256;

        char ip_address[size];
        int hw_type;
        int flags;
        char mac_address[size];
        char mask[size];
        char device[size];

        FILE* fp = fopen("/proc/net/arp", "r");
        if(fp == NULL)
        {
            perror("Error opening /proc/net/arp");
        }

        char line[size];
        fgets(line, size, fp);    // Skip the first line, which consists of column headers.
        while(fgets(line, size, fp))
        {
            sscanf(line, "%s 0x%x 0x%x %s %s %s\n",
                   ip_address,
                   &hw_type,
                   &flags,
                   mac_address,
                   mask,
                   device);
            if(flags==2)
            {
                ///qDebug()<< ip_address<< mac_address<<hw_type<<flags;
                list<<QString(ip_address)+"|"+ QString(mac_address);


            }
        }

        fclose(fp);
   return list;
}
QString MainWindow::getMacForIP(QString ipAddress)
{
    // qDebug()<<"mac adresleri:";
    QString mac="";
    const int size = 256;

        char ip_address[size];
        int hw_type;
        int flags;
        char mac_address[size];
        char mask[size];
        char device[size];

        FILE* fp = fopen("/proc/net/arp", "r");
        if(fp == NULL)
        {
            perror("Error opening /proc/net/arp");
        }

        char line[size];
        fgets(line, size, fp);    // Skip the first line, which consists of column headers.
        while(fgets(line, size, fp))
        {
            sscanf(line, "%s 0x%x 0x%x %s %s %s\n",
                   ip_address,
                   &hw_type,
                   &flags,
                   mac_address,
                   mask,
                   device);
            if(ipAddress==QString(ip_address))
                mac=QString(mac_address);

        }

        fclose(fp);

     return mac;
}

QString MainWindow::getIpPortStatus(QString service)
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
    qDebug()<<"Port sorgulama:"<<result<<service;
    if(result.toInt()>0){ return "open";}
    else {return "close";}
}

void MainWindow::pcDetect()
{
    QStringList arpList=readArp();
    /*arpList.append("192.168.1.211|11:1d:65:ea:11:22");
    arpList.append("192.168.1.212|12:1d:65:ea:11:22");
    arpList.append("192.168.1.213|13:1d:65:ea:11:22");
    arpList.append("192.168.1.214|14:1d:65:ea:11:22");
    arpList.append("192.168.1.215|15:1d:65:ea:11:22");
    arpList.append("192.168.1.216|16:1d:65:ea:11:22");
    arpList.append("192.168.1.217|17:1d:65:ea:11:22");
    arpList.append("192.168.1.218|18:1d:65:ea:11:22");
    arpList.append("192.168.1.219|19:1d:65:ea:11:22");
    arpList.append("192.168.1.221|21:1d:65:ea:11:22");
    arpList.append("192.168.1.222|22:1d:65:ea:11:22");
    arpList.append("192.168.1.223|23:1d:65:ea:11:22");
    arpList.append("192.168.1.224|24:1d:65:ea:11:22");
    arpList.append("192.168.1.225|25:1d:65:ea:11:22");
    arpList.append("192.168.1.226|26:1d:65:ea:11:22");
    arpList.append("192.168.1.227|27:1d:65:ea:11:22");
    arpList.append("192.168.1.228|28:1d:65:ea:11:22");
    arpList.append("192.168.1.229|29:1d:65:ea:11:22");*/

    /*************************************************************/
    bool openrefreshState=false;
    bool closerefreshState=false;
    for(int i=0;i<arpList.count();i++)
    {
        QString fmac = arpList[i].split("|")[1];
        bool bul=false;
        for (int i=0;i<onlinePcList.count();i++) {
            if (onlinePcList[i]->mac == fmac)
                bul=true;
        }
        if (!bul) {
            //Yeni pc varsa ekleme yapılır
            slotPcEkle(arpList[i].split("|")[0],arpList[i].split("|")[1]);
            openrefreshState=true;
        }
    }

    /******************************************************/
    for(int i=0;i<onlinePcList.count();i++)
    {
        QString fmac = onlinePcList[i]->mac;
        bool bul=false;
        for (int i=0;i<arpList.count();i++) {
            if (arpList[i].split("|")[1] == fmac)
                bul=true;
        }
        if (!bul) {
            // Kapatılan pc varsa kaldırılır
           slotPcSil(i,onlinePcList[i]->ip,onlinePcList[i]->mac);
            closerefreshState=true;
        }
    }
    if(openrefreshState)
    {
        //qDebug() << "Liste Güncellemesi yapılıyor.....: ";
        pcListeGuncelleSlotnew("openpcDetect");
    }
    if(closerefreshState)
    {
        //qDebug() << "Liste Güncellemesi yapılıyor.....: ";
        pcListeGuncelleSlotnew("closepcDetect");
    }

}

void MainWindow::slotPcEkle(QString _ip,QString _mac)
{
    //qDebug() << "Pc Ekle Başla: "<<_ip;
    qDebug() << "Açılan Pc: "<<_ip;
    MyPc *mypc=new MyPc(_mac,_ip);
    connect(mypc, SIGNAL(pcClickSignal(QString)),this, SLOT(pcClickSlot(QString)));

    connect(mypc, SIGNAL(pcHideSignal(QString)),this,
    SLOT(pcHideSignalSlot(QString)));
    /*
    connect(cpc, SIGNAL(pcTcpPortControlSignal(QString,QString)),
            this, SLOT(pcTcpPortControlSignalSlot(QString,QString)));

    connect(cpc, SIGNAL(pcSshPortControlSignal(QString,QString)),
            this, SLOT(pcSshPortControlSignalSlot(QString,QString)));

    connect(cpc, SIGNAL(pcVncPortControlSignal(QString,QString)),
            this, SLOT(pcVncPortControlSignalSlot(QString,QString)));

    connect(cpc, SIGNAL(pcFtpPortControlSignal(QString,QString)),
            this, SLOT(pcFtpPortControlSignalSlot(QString,QString)));

    connect(cpc, SIGNAL(pcKilitStateControlSignal(QString,QString,bool)),
            this, SLOT(pcKilitStateControlSignalSlot(QString,QString,bool)));

    connect(cpc, SIGNAL(pcKilitTransparanStateControlSignal(QString,QString,bool)),
            this, SLOT(pcKilitTransparanStateControlSignalSlot(QString,QString,bool)));

    connect(cpc, SIGNAL(pcIconStateControlSignal(QString,QString,bool)),
            this, SLOT(pcIconStateControlSignalSlot(QString,QString,bool)));

    connect(cpc, SIGNAL(pcMenuSignal(QString,QString,QString)),
            this, SLOT(pcMenuSignalSlot(QString,QString,QString)));

    connect(cpc, SIGNAL(pcListeStateSignal()),
            this, SLOT(pcListeStateSlot()));
*/
    connect(mypc, SIGNAL(pcRightClickSignal()),
            this, SLOT(pcRightClickSignalSlot()));

    onlinePcList.append(mypc);
    pcopencount++;
    //pcListeGuncelleSlotnew();
    //qDebug() << "Pc Ekle Son: "<<_ip;
}
void MainWindow::slotPcSil(int _index,QString _ip,QString _mac)
{
    qDebug() << "Kapatılan Pc: "<<onlinePcList[_index]->ip;
    pcopencount--;
    layout->removeWidget(onlinePcList[_index]);
    onlinePcList[_index]->deleteLater();
    onlinePcList.removeAt(_index);
    //pcListeGuncelleSlotnew();
}


#endif // TCPUDP_H
