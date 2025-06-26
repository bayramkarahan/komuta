#-------------------------------------------------
#
# Project created by QtCreator 2019-05-03T10:22:08
#
#-------------------------------------------------

QT       += core gui network printsupport multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = komuta
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    multicast_receiver.cpp \
    mypc.cpp \
    pcdata.cpp \
    rubberband.cpp \
    scdimgclient.cpp \
    scdimgserver.cpp \
    scdimgserverthread.cpp

HEADERS += \
    CustomInputDialog.h \
    Database.h \
    MyCommand.h \
    MyDialog.h \
    SettingsWidget.h \
    VideoDecodeThread.h \
    VideoPlayer.h \
    baseWidget.h \
    filecopyWidget.h \
    languageWidget.h \
    lockWidget.h \
    loginLogoutWidget.h \
        mainwindow.h \
    menu.h \
    messageWidget.h \
    multicast_receiver.h \
    mypc.h \
    pcdata.h \
    powerrebootWidget.h \
    rubberband.h \
    runcommandWidget.h \
    scdimgclient.h \
    scdimgserver.h \
    scdimgserverthread.h \
    screenViewWidget.h \
    sliderWidget.h \
    tcpudp.h \
    selectpc.h \
    funtion.h \
    videoWidget.h \
    vncrdpWidget.h \
    volumeWidget.h \
    wolWidget.h

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

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

target.path = /usr/bin

desktop_file.files = komuta.desktop
desktop_file.path = /usr/share/applications/

icon.files = icons/komuta.svg
icon.path = /usr/share/icons/

x11passwd.files = x11vncpasswd
x11passwd.path = /usr/bin/

x11servicedesktop.files = komuta-x11vncdesktop.service
x11servicedesktop.path = /lib/systemd/system/

x11servicelogin.files = komuta-x11vnclogin.service
x11servicelogin.path = /lib/systemd/system/

#webdisable.files = webdisable.sh
#webdisable.path = /usr/share/komuta/

polkit_policy.files = komuta.policy
polkit_policy.path = /usr/share/polkit-1/actions/
polkit_rules.files = komuta.rules
polkit_rules.path = /usr/share/polkit-1/rules.d/

lang.files = translations/*
lang.path = /usr/share/komuta/translations/


INSTALLS += target desktop_file icon x11passwd\
x11servicedesktop x11servicelogin langen lang polkit_rules polkit_policy

DISTFILES +=komuta.svg\
    komuta.desktop\
    x11vncpasswd\
    komuta-x11vncdesktop.service\
    komuta-x11vnclogin.service\




