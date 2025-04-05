#include <QApplication>
#include <gst/gst.h>
#include <iostream>
#include<QHostAddress>
#include<QNetworkInterface>
#include<QNetworkAddressEntry>

class IpMac
{
public:
    QString ip;
    QString mac;
    QString broadcast;

};
 QList<IpMac> ipmaclist;

void hostAddressMacButtonSlot()
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
int main(int argc, char *argv[]) {
    gst_init(&argc, &argv);
    hostAddressMacButtonSlot();
    for(int k=0;k<ipmaclist.count();k++)
    {
        qDebug()<<ipmaclist[k].ip;
        QStringList ipparts=ipmaclist[k].ip.split(".");
        QString newIp="239.0."+ipparts[2]+"."+ipparts[3];
        qDebug()<<newIp;

    GstElement *vpipeline,*apipeline;
    GError *error = NULL;

    // Video ve ses pipeline'ları
    std::string videoPipeline = "ximagesrc ! videoscale ! video/x-raw,width=800,height=600 ,framerate=15/1 ! videoconvert ! x264enc tune=zerolatency bitrate=512 ! rtph264pay ! udpsink host="+newIp.toStdString()+" port=5000";
    //  ximagesrc ! video/x-raw,framerate=30/1 ! videoconvert ! x264enc tune=zerolatency bitrate=1024 ! rtph264pay ! udpsink host="+newIp.toStdString()+" port=5000";
    //  ximagesrc ! video/x-raw,framerate=15/1 ! videoconvert ! x264enc tune=zerolatency bitrate=512 ! rtph264pay ! udpsink host=239.0.0.1 port=5000
    //  Video pipeline'ı oluştur
    vpipeline = gst_parse_launch(videoPipeline.c_str(), &error);
    if (error) {
        std::cerr << "Ekran yansıtma pipeline oluşturulamadı: " << error->message << std::endl;
        g_clear_error(&error);
        return -1;
    }
    gst_element_set_state(vpipeline, GST_STATE_PLAYING);


    std::cout << "Yayın başladı (Ctrl+C ile durdurun)..." << std::endl;

    // Yayın devam ederken (Ctrl+C ile durdurulana kadar) bekleyin
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);

    // Pipeline'ları durdur ve temizle
    gst_element_set_state(vpipeline, GST_STATE_NULL);
    gst_object_unref(vpipeline);
    gst_element_set_state(apipeline, GST_STATE_NULL);
    gst_object_unref(apipeline);
    }
    return 0;
}

