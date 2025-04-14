#include <QCoreApplication>
#include<client.h>
#include <QString>
#include <QDir>
#include<QDebug>
#include<singleinstance.h>
#include <stdio.h>
#include <stdlib.h>
#include <QtCore/QCoreApplication>
#include <QtDBus/QtDBus>
#include "scdimgserver.h"
#include <QSettings>
#define  echo QTextStream(stderr) <<

#define SINGLE_INSTANCE ".Client"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

     QString name = SINGLE_INSTANCE;

    SingleInstance cInstance;
    if(cInstance.hasPrevious(name, QCoreApplication::arguments()))
    {
        qDebug() << "Client Zaten Açık...";
        return 0;
    }
    if (cInstance.listen(name)) {
        qDebug() << "Client Çalışıyor..";
    } else {
        qDebug() << "Client Çalışması İptal Edildi...";
        return 0;
    }


        Client *cl=new Client();
        cl->networkProfilLoad();

    SCDImgServer srv(0,cl->ftpPort.toInt(),cl->rootPath);

    if (srv.start())
    {
        return a.exec();
    }

    return 0;
}
