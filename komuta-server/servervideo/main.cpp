#include <QCoreApplication>
#include <QProcess>
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QProcess *ffmpeg = new QProcess(&app);
//        "-an",                         // Ses yoksa CPU tasarrufu
//            "-stream_loop", "-1",         // Sonsuz döngü (isteğe bağlı)
    QStringList args = {
        "-re",                         // Gerçek zamanlı okuma (iyi)
        "-i", "video.mp4",
        "-c:v", "libx264",
        "-preset", "veryfast",         // 'ultrafast' daha fazla bitrate ve CPU tüketir
        "-tune", "zerolatency",
        "-bufsize", "512k",            // Küçük buffer
        "-f", "mpegts",
        "udp://239.0.0.1:1234?pkt_size=1316"
    };
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

    qDebug() << "Düşük gecikmeli multicast yayını başlatıldı.";
    return app.exec();
}
