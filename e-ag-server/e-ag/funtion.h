#ifndef FUNTION_H
#define FUNTION_H
#include <stdio.h>
#include <stdlib.h>
void MainWindow::updateSlider(int val)
{
     sliderValuelabel->setText(QString::number(val));
    //double nwidth=en*13*val/100;
    double nwidth=en*20*val/100;
    double nheight=en*20*val/100;
    int columnSayisi=hostListe->width()/(nwidth+en*4);
     //pcListeGuncelleSlot(columnSayisi,nwidth,nheight);
    pcListeGuncelleSlotnew("updateSlider");
    mesajSlot("Host Boyutları Değiştirildi.");
}
void MainWindow::selectSlot()
{
    for(int i=0;i<onlinePcList.count();i++)
    {
        // onlinePcList[i]->select=!(onlinePcList[i]->select);
        /// onlinePcList[i]->slotMouseClick();
        onlinePcList[i]->slotMouseDoubleClick();
    }
    mesajSlot("Host Seçimi Yapıldı.");
}
void MainWindow::terminalSlot()
{
    QString kmt10="x-terminal-emulator -x -e \"ssh "+remoteUserName+"@"+pcIp->text()+"\"";
    system(kmt10.toStdString().c_str());
    mesajSlot("Seçili Hostda Terminal Başlatıldı.");
}
void MainWindow::slotWakeOnLan(QString _ip,QString _mac)
{

   _mac=_mac.toUpper();
    QHostAddress FakeAddress;
    QUdpSocket udpSocket1;
//qDebug()<<"mac adresi:"<<_mac;
    hostAddressMacButtonSlot();
   for(int k=0;k<ipmaclist.count();k++)
    {
             if(ipmaclist[k].ip.section(".",0,2)==_ip.section(".",0,2))
            {
                char MACAddr [6];
                char MagicPacket [102]; // Magic package for remote boot

                int j = sscanf (_mac.toLatin1().data(), "%2x-%2x-%2x-%2x-%2x-%2x",
                                & MACAddr [0], & MACAddr [1], & MACAddr [2], & MACAddr [3], & MACAddr [4], & MACAddr [5]);

                // Set to hexadecimal before the magicpacket array 6 characters ff
                memset (MagicPacket, 0xff, 6);

                int packetsize = 6; // the beginning of the initial value is 6, do not wrong. I is because the effect of the initial value of the written as 0, it is too effortless.
                // Build MagicPacket.
                for (int z = 0; z <16; z++)
                {
                    memcpy (MagicPacket + packetsize, MACAddr, 6);
                    packetsize += 6;
                }

                FakeAddress.setAddress (ipmaclist[k].broadcast);
               // qDebug()<<"broad cast adress:"<<ipmaclist[k].broadcast;
              // udpSocket1.writeDatagram(MagicPacket, 102, QHostAddress(ipmaclist[k].broadcast), 9);
               //system("sleep 0.5");

               QString kmt29="wakeonlan "+_mac;
                system(kmt29.toStdString().c_str());


            }


    }
   mesajSlot("Seçili Hostlar Uzaktan  Başlatıl.");

}

void MainWindow::slotFtp(){
///ftpConnectButtonSlot();
mesajSlot("Seçili Hostda Ftp Başlatıldı.");

}
void MainWindow::slotSelectPcMesaj(QString _msg){
    for(int i=0;i<onlinePcList.count();i++)
    {
        if(onlinePcList[i]->connectState&&(onlinePcList[i]->select||onlinePcList[i]->multiSelect))
        {
            udpSendData("ekranmesaj",_msg,onlinePcList[i]->ip);
        }
    }
    mesajSlot("Seçili Hostlara Mesaj Gönderildi.");

}


QString MainWindow::getIpPortStatus(QString ip_,QString port)
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

#endif // FUNTION_H
