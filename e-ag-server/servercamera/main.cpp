#include <QCoreApplication>
#include <QProcess>
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QProcess *ffmpeg = new QProcess(&app);
    QStringList args;

#ifdef Q_OS_LINUX
    args << "-f" << "v4l2"
         << "-framerate" << "24"
         << "-video_size" << "320x240"
         << "-use_wallclock_as_timestamps" << "1"
         << "-i" << "/dev/video0"
         << "-f" << "alsa"
         << "-use_wallclock_as_timestamps" << "1"
         << "-i" << "default";
#endif

#ifdef Q_OS_WIN
    args << "-f" << "dshow"
         << "-framerate" << "25"
         << "-video_size" << "640x480"
         << "-i" << "video=YOUR_VIDEO_DEVICE_NAME"  // GÜNCELLE!
         << "-f" << "dshow"
         << "-i" << "audio=YOUR_AUDIO_DEVICE_NAME"; // GÜNCELLE!
#endif

    args << "-vcodec" << "libx264"
         << "-preset" << "ultrafast"
         << "-tune" << "zerolatency"
         << "-pix_fmt" << "yuv420p"
         << "-acodec" << "aac"
         << "-ar" << "44100"
         << "-ac" << "2"
         << "-b:a" << "128k"
         << "-fflags" << "+genpts+nobuffer"
         << "-flags" << "low_delay"
         << "-muxdelay" << "0"
         << "-muxpreload" << "0"
         << "-f" << "mpegts"
         << "udp://239.0.0.1:1234?ttl=1&pkt_size=1316";
   /*

    QStringList args;

#ifdef Q_OS_LINUX
    args << "-f" << "v4l2"
         << "-framerate" << "25"
         << "-video_size" << "640x480"
         << "-use_wallclock_as_timestamps" << "1"
         << "-thread_queue_size" << "512"
         << "-i" << "/dev/video0"
         << "-f" << "alsa"
         << "-use_wallclock_as_timestamps" << "1"
         << "-thread_queue_size" << "512"
         << "-i" << "default";
#endif

#ifdef Q_OS_WIN
    args << "-f" << "dshow"
         << "-framerate" << "25"
         << "-video_size" << "640x480"
         << "-thread_queue_size" << "512"
         << "-i" << "video=Integrated Camera"  // Video cihaz adını güncelle
         << "-f" << "dshow"
         << "-thread_queue_size" << "512"
         << "-i" << "audio=Microphone (Realtek Audio)";  // Ses cihaz adını güncelle
#endif

    args << "-copyts"
         << "-start_at_zero"
         << "-mpegts_copyts" << "1"
         << "-avoid_negative_ts" << "make_zero"
         << "-vcodec" << "libx264"
         << "-preset" << "ultrafast"
         << "-tune" << "zerolatency"
         << "-pix_fmt" << "yuv420p"
         << "-acodec" << "aac"
         << "-ar" << "44100"
         << "-ac" << "2"
         << "-b:a" << "128k"
         << "-fflags" << "+genpts+igndts+nobuffer"
         << "-flags" << "low_delay"
         << "-bufsize" << "1000k"
         << "-muxrate" << "1500000"
         << "-avoid_negative_ts" << "make_zero"
         << "-muxdelay" << "0.2"
         << "-muxpreload" << "0.2"
         << "-max_delay" << "1000000"
         << "-f" << "mpegts"
         << "-x264-params" << "repeat_headers=1"
         << "-g" << "50"
         << "udp://239.0.0.1:1234?ttl=1&pkt_size=1316";
*/
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

    qDebug() << "Çapraz platform UDP multicast yayın başladı.";
    return app.exec();
}
