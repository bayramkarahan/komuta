#include <QCoreApplication>
#include <QDebug>
#include <QStringList>
#include<Database.h>
#include<QJsonObject>
#include<QJsonValue>

QString localDir;
bool stringToBool(const QString& str) {
    return str.toLower() == "true"; // Büyük/küçük harf duyarsız karşılaştırma
}
void networkProfilSave(QString data)
{
    qDebug()<<"Gelen Veri:"<<data;
    QStringList mesaj;
    mesaj=data.split("|");
    DatabaseHelper *db=new DatabaseHelper(localDir+"e-ag.json");
    QJsonObject veri;
    veri["networkIndex"]= mesaj[9].toInt();
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

    db->Sil("networkIndex",mesaj[9].toInt());
    db->Ekle(veri);
    exit(true);

}

int main(int argc, char *argv[])
{
    localDir="/usr/share/e-ag/";
    QCoreApplication a(argc, argv);
    QStringList arguments = a.arguments();

    //qDebug() << "Uygulama Adı:" << arguments.at(0); // İlk argüman genellikle uygulama adıdır
    if (arguments.size() > 1) {
        //qDebug() << "İlk Argüman:" << arguments.at(1);
         networkProfilSave(arguments.at(1));
    }
    // Argümanları kullanarak uygulamanızın davranışını kontrol edebilirsiniz.
    if (arguments.contains("--verbose")) {
        qDebug() << "Detaylı çıktı modu etkin.";
    }


    return a.exec();
}

