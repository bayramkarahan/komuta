#include <gst/gst.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
int main(int argc, char *argv[]) {
    gst_init(&argc, &argv);
    std::vector<std::string> args;
    std::transform(argv, argv + argc, std::back_inserter(args), [](const char* arg) {
        return std::string(arg);
    });

    if(args.size()<2)
    {
        std::cout << "Camera Konumu Yazmalısın."<< std::endl;
        return 0;
    }
    std::string device="/dev/video0";
    device=args[1];
    std::cout << "Kamera Yol:"<< device<<std::endl;

    //GstElement *vpipeline,*apipeline;
    GError *error = NULL;

    // Video ve ses pipeline'ları

    std::string videoPipeline = "v4l2src device="+device+" ! videoconvert ! x264enc tune=zerolatency ! rtph264pay config-interval=1 pt=96 ! udpsink host=239.0.1.51 port=5000";
    std::string audioPipeline = "autoaudiosrc ! audioconvert ! opusenc ! rtpopuspay pt=97 ! udpsink host=239.0.1.51 port=5001";
    //alsasrc device=hw:1,0

    GstElement *video_pipeline = gst_pipeline_new ("vmypipeline");
    GstElement *audio_pipeline = gst_pipeline_new ("amypipeline");
  /*GstElement *video_source = gst_element_factory_make ("v4l2src", "source"); // Kamera kaynağı
    GstElement *video_convert = gst_element_factory_make ("videoconvert", "convert");
    GstElement *video_encode = gst_element_factory_make ("x264enc", "encode"); // Video kodlayıcı
    GstElement *video_pay = gst_element_factory_make ("rtph264pay", "pay"); // RTP paketleyici
    GstElement *video_sink = gst_element_factory_make ("udpsink", "sink"); // UDP yayını
    g_object_set (G_OBJECT (video_sink), "host", "239.0.1.51", "port", 5000, NULL); // Hedef IP ve port
    g_object_set(video_encode, "tune", 4, NULL); // veya "stillimage", "fastdecode" vb.
    //g_object_set (G_OBJECT (video_source), "device",device, NULL);

    GstElement *audio_source = gst_element_factory_make("autoaudiosrc", "audio-source");
    GstElement *audio_encode = gst_element_factory_make("opusenc", "opus-encoder");
    GstElement *audio_convert = gst_element_factory_make("audioconvert", "audio_convert");
    GstElement *audio_pay = gst_element_factory_make("rtpopuspay", "rtp-payloader");
    GstElement *audio_sink = gst_element_factory_make("udpsink", "udp-sink");
    g_object_set (G_OBJECT (audio_sink), "host", "239.0.1.51", "port", 5001, NULL); // Hedef IP ve port
    g_object_set(audio_pay, "pt", 97, NULL);


    gst_bin_add_many (GST_BIN (audio_pipeline), audio_source, audio_convert,audio_encode, audio_pay, audio_sink, NULL);
    gst_element_link_many (audio_source,audio_convert, audio_encode, audio_pay,audio_sink, nullptr);

    gst_bin_add_many (GST_BIN (video_pipeline), video_source, video_convert, video_encode, video_pay, video_sink, NULL);
    gst_element_link_many (video_source, video_convert, video_encode, video_pay, video_sink, nullptr);
*/
    video_pipeline = gst_parse_launch(videoPipeline.c_str(), &error);
    audio_pipeline=gst_parse_launch(audioPipeline.c_str(), &error);
    GstStateChangeReturn video_ret = gst_element_set_state(video_pipeline, GST_STATE_PLAYING);
    GstStateChangeReturn audio_ret  = gst_element_set_state(audio_pipeline, GST_STATE_PLAYING);



    if (video_ret == GST_STATE_CHANGE_FAILURE) {
        std::cout << "video  başlatılamadı." << std::endl;
    }
    if (audio_ret == GST_STATE_CHANGE_FAILURE) {
        std::cout << "ses  başlatılamadı." << std::endl;
    }

    std::cout << "Yayın başladı (Ctrl+C ile durdurun)..." << std::endl;

    // Yayın devam ederken (Ctrl+C ile durdurulana kadar) bekleyin
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);

    // Pipeline'ları durdur ve temizle
    gst_element_set_state(video_pipeline, GST_STATE_NULL);
    gst_object_unref(video_pipeline);
    gst_element_set_state(audio_pipeline, GST_STATE_NULL);
    gst_object_unref(audio_pipeline);

    return 0;
}
