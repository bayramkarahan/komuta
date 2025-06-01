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
void  MainWindow::udpSendData(QString _mesajTur,QString _gorev,QString _ekmesaj)
{
    QString uport="7879";
    udpSendDataStatus=true;
    //qDebug()<<"Mesaj Gönderilecek:"<<_mesajTur<<_mesaj<<_ip;
   /* for (const NetProfil &item : NetProfilList) {
        if (item.serverAddress=="") continue;
        if (item.selectedNetworkProfil==false) continue;
        uport=item.networkTcpPort;
        std::reverse(uport.begin(), uport.end());
    }*/
        //for(int k=0;k<interfaceList.count();k++)
        //{
            //if(item.networkBroadCastAddress==interfaceList[k].broadcast)
            //{
                /***********************************************************************/
                /***********************************************************************/
                for(int i=0;i<onlinePcList.count();i++)
                {

                    if(onlinePcList[i]->connectState&&(onlinePcList[i]->select||onlinePcList[i]->multiSelect))
                    {
                        uport=onlinePcList[i]->netProfil.networkTcpPort;
                        std::reverse(uport.begin(), uport.end());

                        QString msg=_mesajTur+"|"+_gorev+"|"+_ekmesaj+"|"+onlinePcList[i]->netProfil.serverAddress+"|"+uport;
                        QByteArray datagram = msg.toUtf8();
                        udpSocketSend->writeDatagram(datagram,QHostAddress(onlinePcList[i]->ip), uport.toInt());
                        qDebug()<<"Mesaj Gönderildi:"<<msg;
                    }
                }
                /***********************************************************************/
                /***********************************************************************/
           // }
        //}

    udpSendDataStatus=false;
}
void MainWindow::udpSocketServerRead()
{
    // sendBroadcastStatus=false;
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
        qDebug()<<"Client Mesaj:"<<rmesaj;

        QString _mac=mesaj[2];
        /********************************************/
        bool findedStatus=false;
        for(int i=0;i<onlinePcList.count();i++)
        {
            if(_mac.toUpper()==onlinePcList[i]->mac.toUpper())
            {
                findedStatus=true;
            }
        }
        if(!findedStatus){
            slotPcEkle(_mac.toUpper(),mesaj[1]);
            pcListeGuncelleSlotnew("openpcDetect");
        }

        /*********************************************/
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
                break;
           }

            if(_mac.toUpper()==onlinePcList[i]->mac.toUpper()&&mesaj[0]=="eagclientconf"){
                ///qDebug()<<"Client Mesaj:"<<rmesaj;
                onlinePcList[i]->tcpConnectCounter=0;
                //onlinePcList[i]->setPcState(true);
                onlinePcList[i]->setConnectState(true);
                onlinePcList[i]->ip=mesaj[1];
                if(mesaj.count()==15)
                {
                    onlinePcList[i]->setUser(mesaj[4]);
                    onlinePcList[i]->setHostname(mesaj[10]);

                    if(mesaj[12]=="1")
                        onlinePcList[i]->setSshState(true);
                    else
                        onlinePcList[i]->setSshState(false);

                    if(mesaj[13]!="0"){
                        onlinePcList[i]->setVncState(true);
                        onlinePcList[i]->vncport=mesaj[13];
                    }
                    else {
                        onlinePcList[i]->setVncState(false);
                        onlinePcList[i]->vncport=mesaj[13];
                    }
                    if(mesaj[14]=="1")onlinePcList[i]->setXrdpState(true);
                    else onlinePcList[i]->setXrdpState(false);
                }
                if(mesaj.count()>15)
                {
                onlinePcList[i]->setCommandState(mesaj[15],mesaj[16],mesaj[17]);
                qDebug()<<"komut:"<<mesaj[15];
                qDebug()<<"komut Sonucu:"<<mesaj[16];
                qDebug()<<"komut durumu:"<<mesaj[17];
                }
            }
        }

    }


}
void MainWindow::hostAddressMacButtonSlot()
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
                  interfaceList.append(im);

                 // qDebug()<<"mac:"<<networkInterface.hardwareAddress();
                  //qDebug()<<"ip  address:"<<entry.ip().toString();
                 // qDebug()<<"broadcast  address:"<<entry.broadcast().toString();
              }
           }
       }
//qDebug()<<"ip  address:"<<ipmaclist.count();


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
void MainWindow::pcCloseSignalSlot(QString ip,QString mac)
{
    qDebug()<<"pcCloseSignalSlot: "<<ip<<mac;
    for(int i=0;i<onlinePcList.count();i++)
    {
        if(onlinePcList[i]->mac==mac){
            slotPcSil(i,onlinePcList[i]->ip,onlinePcList[i]->mac);
        }
    }
    pcListeGuncelleSlotnew("closepcDetect");
}
void MainWindow::slotPcEkle(QString _mac,QString _ip)
{
    //qDebug() << "Pc Ekle Başla: "<<_ip;
    qDebug() << "Açılan Pc: "<<_ip;

    MyPc *mypc=new MyPc(_mac,_ip);

    qDebug() << "diğer işlemler yapılacak";

    connect(mypc, SIGNAL(pcClickSignal(QString)),this, SLOT(pcClickSlot(QString)));

    connect(mypc, SIGNAL(pcHideSignal(QString)),this,
    SLOT(pcHideSignalSlot(QString)));

    connect(mypc, SIGNAL(pcCloseSignal(QString,QString)),
            this, SLOT(pcCloseSignalSlot(QString,QString)));

    connect(mypc, SIGNAL(pcRightClickSignal()),
            this, SLOT(pcRightClickSignalSlot()));

    for (const NetProfil &item : NetProfilList) {
        qDebug()<<item.networkBroadCastAddress;
        if(_ip.section(".",0,2)==item.networkBroadCastAddress.section(".",0,2))
        {
            mypc->netProfil=item;
        }
    }


    onlinePcList.append(mypc);
    pcopencount++;
    //pcListeGuncelleSlotnew();
    //qDebug() << "Pc Ekle Son: "<<_ip;
}
void MainWindow::slotPcSil(int _index,QString _mac,QString _ip)
{
    qDebug() << "Kapatılan Pc: "<<onlinePcList[_index]->ip;
    pcopencount--;
    layout->removeWidget(onlinePcList[_index]);
    onlinePcList[_index]->deleteLater();
    onlinePcList.removeAt(_index);
    //pcListeGuncelleSlotnew();
}


#endif // TCPUDP_H
