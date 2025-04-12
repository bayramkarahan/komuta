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
       std::cout << "Video Konumu Yazmalısın."<< std::endl;
       return 0;
   }

   std::string yol=args[1];
   std::cout << "Video adı:"<< yol<<std::endl;
   GstElement *vpipeline,*apipeline;
   GError *error = NULL;

    // Video ve ses pipeline'ları
    /// std::string videoPipeline = "v4l2src device=/dev/video0 ! videoconvert ! x264enc tune=zerolatency ! rtph264pay config-interval=1 pt=96 ! udpsink host=192.168.1.255 port=5000";
    ///std::string audioPipeline = "autoaudiosrc ! audioconvert ! opusenc ! rtpopuspay pt=97 ! udpsink host=192.168.1.255 port=5001";
    std::string videoPipeline = "filesrc location="+yol+" ! decodebin ! videoconvert ! x264enc tune=zerolatency bitrate=1024 ! rtph264pay ! udpsink host=239.0.1.51 port=5000";
    std::string audioPipeline = "filesrc location="+yol+" ! decodebin ! audioconvert ! opusenc ! rtpopuspay ! udpsink host=239.0.1.51 port=5001";
    //std::cout << "Video pipeline:"<< videoPipeline<<std::endl;
    //std::cout << "audio pipeline:"<< audioPipeline<<std::endl;
   // Video pipeline'ı oluştur
   vpipeline = gst_parse_launch(videoPipeline.c_str(), &error);
   if (error) {
       std::cerr << "Video pipeline oluşturulamadı: " << error->message << std::endl;
       g_clear_error(&error);
       return -1;
   }
   gst_element_set_state(vpipeline, GST_STATE_PLAYING);

   // Ses pipeline'ı oluştur
   apipeline = gst_parse_launch(audioPipeline.c_str(), &error);
   if (error) {
       std::cerr << "Ses pipeline oluşturulamadı: " << error->message << std::endl;
       g_clear_error(&error);
       return -1;
   }
   gst_element_set_state(apipeline, GST_STATE_PLAYING);

   std::cout << "Yayın başladı (Ctrl+C ile durdurun)..." << std::endl;

   // Yayın devam ederken (Ctrl+C ile durdurulana kadar) bekleyin
   GMainLoop *loop = g_main_loop_new(NULL, FALSE);
   g_main_loop_run(loop);

   // Pipeline'ları durdur ve temizle
   gst_element_set_state(vpipeline, GST_STATE_NULL);
   gst_object_unref(vpipeline);
   gst_element_set_state(apipeline, GST_STATE_NULL);
   gst_object_unref(apipeline);

    return 0;
}
