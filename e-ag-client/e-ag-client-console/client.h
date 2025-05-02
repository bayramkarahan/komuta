
#ifndef CLIENT_H
#define CLIENT_H
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
class NetProfil
{
public:
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
};

class Client: public QObject
{
  Q_OBJECT
public:
    Client();
    ~Client();
    bool webblockStateRun=false;
    QList<NetProfil> NetProfilList;
signals:
  public slots:
    QString  getIpPortStatus(QString service, int number);
    void tcpMesajSendTimerSlot();
    void socketBaglama();
    void networkProfilLoad();
    bool stringToBool(const QString& str) {
        return str.toLower() == "true"; // Büyük/küçük harf duyarsız karşılaştırma
    }
private slots:
    void commandExecuteSlot(QString command);
    void udpServerGetSlot();
    bool uygulamaCalisiyorMu(const QString& uygulamaAdi);
    void udpTrayGetSlot();
    void udpGuiGetSlot();
    void udpServerSendSlot(QString _data);
    void hostAddressMacButtonSlot();
    void webBlockAktifPasif(bool _state);
    QString findX11vncPort(QString _servis);
    QString getSeatId();
    QString getSessionInfo(QString id, QString parametre);
private:
    QProcess process;
    QTimer *timer;
    QTimer *timerControl;
    QList<IpMac> interfaceList;

    QString localDir;
    QString localDir1;
    QString ip;

    QUdpSocket *udpServerSend = nullptr;
    QUdpSocket *udpServerGet = nullptr;
    QUdpSocket *udpTraySend = nullptr;
    QUdpSocket *udpTrayGet = nullptr;
    QUdpSocket *udpGuiGet = nullptr;

    QString clientTrayEnv="";
    QString clientGuiEnv="";
     QString clientConsoleEnv="";
    QString tempdata="";
    int dataSayac=0;
    QString seatId;
    QString sessionUser;
    QString sessionUserId;
    QString sessionDisplay;
    QString sessionDisplayType;
    QString sessionDesktopManager;
    int hostportCounter;
    bool udpServerGetStatus=false;


};

#endif // CLIENT_H
