#include <gst/gst.h>
#include <iostream>

int main(int argc, char *argv[]) {
    gst_init(&argc, &argv);

    GstElement *pipeline;
    GError *error = NULL;

    // Video ve ses pipeline'ları
    std::string videoPipeline = "filesrc location=a.mp4 ! decodebin ! videoconvert ! x264enc tune=zerolatency bitrate=1024 ! rtph264pay ! udpsink host=239.0.0.1 port=5000 filesrc location=a.mp4 ! decodebin ! audioconvert ! opusenc ! rtpopuspay ! udpsink host=239.0.0.1 port=5001";
    // Video pipeline'ı oluştur
    pipeline = gst_parse_launch(videoPipeline.c_str(), &error);
    if (error) {
        std::cerr << "Video pipeline oluşturulamadı: " << error->message << std::endl;
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
