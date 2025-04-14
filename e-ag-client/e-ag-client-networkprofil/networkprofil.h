
#ifndef NETWORKPROFIL_H
#define NETWORKPROFIL_H
#include <QTcpSocket>
#include <QDataStream>
#include<QTimer>
#include<QUdpSocket>
#include<QNetworkInterface>
#include<QProcess>
#include<QObject>
#include<QSysInfo>
#include<QDir>
class IpMac
{
public:
    QString ip;
    QString mac;
    QString broadcast;
    QString subnet;

};

class NewtworkProfil: public QObject
{
  Q_OBJECT
public:
    NewtworkProfil();
    ~NewtworkProfil();
    QString networkIndex;
    bool selectedNetworkProfil;
    QString networkName;
    QString serverAddress;
    QString networkBroadCastAddress;
    QString networkTcpPort;
    QString ftpPort;
    QString rootPath;
    QString language;
    bool lockScreenState;
    bool webblockState;
    bool webblockStateRun=false;
signals:
  public slots:
    void socketBaglama();
    void networkProfilLoad();
    bool stringToBool(const QString& str) {
        return str.toLower() == "true"; // Büyük/küçük harf duyarsız karşılaştırma
    }
private slots:
    void udpServerGetSlot();
    void networkProfilSave(QString data);
    void udpServerSendSlot(QString _data);
    void hostAddressMacButtonSlot();
 private:
    QProcess process;
    QList<IpMac> ipmaclist;
    QString localDir;
    QString localDir1;
    QString ip;
    QString tcpPort;
    QUdpSocket *udpServerSend = nullptr;
    QUdpSocket *udpServerGet = nullptr;

};

#endif // NETWORKPROFIL_H
