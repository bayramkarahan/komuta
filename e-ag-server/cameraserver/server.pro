QT       += core gui
QT += network

SOURCES += yayinci.cpp

LIBS += -lgstreamer-1.0 -lgstapp-1.0 -lgstvideo-1.0 -lgstaudio-1.0
INCLUDEPATH += /usr/include/gstreamer-1.0
PKGCONFIG += gstreamer-1.0 gstreamer-base-1.0 gstreamer-video-1.0 gstreamer-rtp-1.0
LIBS += -lgstreamer-1.0 -lgstapp-1.0 -lgstvideo-1.0 -lgobject-2.0 -lglib-2.0 -lgstaudio-1.0

INCLUDEPATH += /usr/include/gstreamer-1.0 \
               /usr/include/glib-2.0 \
               /usr/lib/glib-2.0/include \
               /usr/include/gstreamer-1.0/gst/video

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=

HEADERS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
