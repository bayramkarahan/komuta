#ifndef FUNTION_H
#define FUNTION_H
#include <stdio.h>
#include <stdlib.h>
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

void MainWindow::slotTerminal()
{
    bool ok;
    QString _remoteuser = QInputDialog::getText(0, "İstemci Parolası",
                                                " İstemcideki Kullanıcının Adını Giriniz :", QLineEdit::Normal,
                                                "", &ok);
    QString _remotepasswd = QInputDialog::getText(0, "İstemci Parolası",
                                                  remoteUserName+"İstemcideki Kullanıcının Parolasını Giriniz :", QLineEdit::Normal,
                                                  "", &ok);
    //QString komut="sshlogin "+remoteUserName+" "+remotePassword;
    if(_remoteuser!=""&&_remotepasswd!="")
    {
        QString kmt10="xterm -fa \"Monospace\" -fs 14 -e \"ssh etapadmin@"+pcIp->text()+"\" &";
        system(kmt10.toStdString().c_str());
    }
// QString kmt10="x-terminal-emulator -e \"ssh "+remoteUserName+"@"+pcIp->text()+"\"";
    //QString kmt9="ssh etapadmin@"+pcIp->text()+"\" &";
// SSH bağlantısını başlat
    //QTermWidget *terminal=new QTermWidget();
    //qterm->show();
    //qterm->sendText(kmt10);
    //qterm->sendData(kmt9.c_str());
   // return;
   /* QStringList komut;
    komut << "grep" << "-i" << "aranacak_kelime" << "dosya_adi.txt";
    terminal->startShellProgram(komut);*/

    mesajSlot("Seçili Hostda Terminal Başlatıldı.");
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
