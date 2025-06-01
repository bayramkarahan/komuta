#ifndef FUNTION_H
#define FUNTION_H
#include <stdio.h>
#include <stdlib.h>
#include <QProcessEnvironment>
#include <QString>
#include <iostream>

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

QString MainWindow::getActiveUserName() {
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    QString username = env.value("USER"); // For Unix-like systems
    if (username.isEmpty()) {
        username = env.value("USERNAME"); // For Windows
    }
    return username;
}
void MainWindow::slotTerminal()
{
    QString seatUser=getSessionInfo(getSeatId(),"USER=");
    QStringRef _sessionUser=seatUser.rightRef(seatUser.length()-5);
    seatUser=_sessionUser.toString();
    bool ok;
    CustomInputDialog  cid(tr("İstemci Kullanıcısı"),tr(" İstemcideki Kullanıcının Adını Giriniz :"),seatUser,300,100);
    seatUser = cid.getText();
    CustomInputDialog  cid1(tr("İstemci Parolası"),tr(" İstemcideki Kullanıcının Parolasını Giriniz :"),"",300,100);
    QString _remotepasswd=cid1.getText();
    if(seatUser!=""&&_remotepasswd!="")
    {
        QString kmt10="xterm -fa \"Monospace\" -fs 14 -e \"ssh "+seatUser+"@"+pcIp->text()+"\" &";
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


QString  MainWindow::getSeatId()
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
QString MainWindow::getSessionInfo(QString id, QString parametre)
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


#endif // FUNTION_H
