#include <gst/gst.h>
#include <iostream>
#include<gst/gsterror.h>
int main(int argc, char *argv[]) {
    gst_init(&argc, &argv);

    GstElement *pipeline;
    GError *error = NULL;

    // Video ve ses pipeline'ları
    std::string videoPipeline = "udpsrc port=5000 address=239.0.1.51 ! application/x-rtp, payload=96 ! rtph264depay ! avdec_h264 ! videoconvert ! autovideosink";
    std::string audioPipeline = "udpsrc port=5001 address=239.0.1.51 ! application/x-rtp, media=(string)audio, clock-rate=(int)48000, encoding-name=(string)OPUS, payload=(int)97 ! rtpopusdepay ! opusdec ! autoaudiosink";

    // Video pipeline'ı oluştur
    pipeline = gst_parse_launch(videoPipeline.c_str(), &error);
    if (error) {
        std::cerr << "Video pipeline oluşturulamadı: " << error->message << std::endl;
        g_clear_error(&error);
        return -1;
    }
    gst_element_set_state(pipeline, GST_STATE_PLAYING);


    // Ses pipeline'ı oluştur
    pipeline = gst_parse_launch(audioPipeline.c_str(), &error);
    if (error) {
        std::cerr << "Ses pipeline oluşturulamadı: " << error->message << std::endl;
        g_clear_error(&error);
        return -1;
    }
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    std::cout << "Alıcı başladı (Ctrl+C ile durdurun)..." << std::endl;

    // Alıcı devam ederken (Ctrl+C ile durdurulana kadar) bekleyin
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);

    // Pipeline'ları durdur ve temizle
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);

    return 0;
}
