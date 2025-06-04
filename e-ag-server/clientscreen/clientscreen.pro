QT += core gui widgets
CONFIG += c++17
TARGET = MulticastViewer
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    multicast_receiver.cpp

HEADERS += \
    mainwindow.h \
    multicast_receiver.h

FORMS +=
# Linux için FFmpeg ayarları
unix {
    LIBS += -lqtermwidget5
    INCLUDEPATH += /usr/include/qtermwidget5
    INCLUDEPATH += /usr/include
    LIBS += -lavformat -lavcodec -lavutil -lswscale
}

# Windows için FFmpeg ayarları (örnek: FFmpeg statik binary kurulu dizin)
win32 {
    INCLUDEPATH += C:/ffmpeg/include
    LIBS += -LC:/ffmpeg/lib \
            -lavformat \
            -lavcodec \
            -lavutil \
            -lswscale
}
