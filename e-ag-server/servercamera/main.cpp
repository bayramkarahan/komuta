#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <QCameraInfo>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QProcess *ffmpeg = new QProcess(&app);
    QStringList args;
    QStringList kameras;

    for (const QCameraInfo &cameraInfo : QCameraInfo::availableCameras()) {
        kameras.append(cameraInfo.description());
        //qDebug() << "Kamera bulundu:" << cameraInfo.deviceName();
        // qDebug() << "Kamera bulundu:" << cameraInfo.description();
    }
//return 0;
#ifdef Q_OS_WIN
    QString videoDeviceName = "Integrated Camera"; // Varsayılan
    if (!kameras.isEmpty()) {
        videoDeviceName = kameras.first();
         qDebug() <<"kullanılacak kamera:"<<videoDeviceName;
    }


    args << "-f" << "dshow"
         << "-video_size" << "640x480"
         << "-framerate" << "30"
         << "-i" << "video=Integrated Camera:audio=Mikrofon (Realtek High Definition Audio)";
    /*
         << "-vcodec" << "libx264"
         << "-preset" << "ultrafast"
         << "-tune" << "zerolatency"
         << "-pix_fmt" << "yuv420p"
         << "-acodec" << "aac"
         << "-ar" << "44100"
         << "-ac" << "2"
         << "-b:a" << "128k"
         << "-f" << "mpegts"
         << "udp://239.0.0.1:1234?ttl=1&pkt_size=1316";*/

#endif

#ifdef Q_OS_LINUX
    args << "-f" << "v4l2"
         << "-framerate" << "24"
         << "-video_size" << "320x240"
         << "-i" << "/dev/video0"
         << "-f" << "alsa"
         << "-i" << "default";
#endif

    args << "-c:v" << "libx264"
         << "-preset" << "ultrafast"
         << "-tune" << "zerolatency"
         << "-pix_fmt" << "yuv420p"
         << "-c:a" << "aac"
         << "-b:a" << "128k"
         << "-ar" << "44100"
         << "-ac" << "2"
         << "-fflags" << "+genpts+nobuffer"
         << "-flags" << "low_delay"
         << "-muxdelay" << "0"
         << "-fflags" << "+nobuffer+genpts+igndts"
         << "-flags" << "low_delay"
         << "-strict" << "-2"
         << "-f" << "mpegts"
         << "udp://239.0.0.1:1234?ttl=1&pkt_size=1316";

    ffmpeg->setProgram("ffmpeg");
    ffmpeg->setArguments(args);

    QObject::connect(ffmpeg, &QProcess::readyReadStandardError, [=]() {
        qDebug() << ffmpeg->readAllStandardError();
    });

    ffmpeg->start();

    if (!ffmpeg->waitForStarted()) {
        qCritical() << "FFmpeg başlatılamadı.";
        return -1;
    }

    qDebug() << "UDP multicast yayını başladı.";
    return app.exec();
}
