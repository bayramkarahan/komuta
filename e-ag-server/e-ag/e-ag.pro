#-------------------------------------------------
#
# Project created by QtCreator 2019-05-03T10:22:08
#
#-------------------------------------------------

QT       += core gui network printsupport multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = e-ag
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
    baseWidget.h \
    filecopyWidget.h \
    languageWidget.h \
    lockWidget.h \
    loginLogoutWidget.h \
        mainwindow.h \
    menu.h \
    messageWidget.h \
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
LIBS += -lqtermwidget5
INCLUDEPATH += /usr/include/qtermwidget5
#LIBS += -lgstreamer-1.0 -lgstapp-1.0 -lgstvideo-1.0 -lgstaudio-1.0
#INCLUDEPATH += /usr/include/gstreamer-1.0
PKGCONFIG += gstreamer-1.0 gstreamer-base-1.0 gstreamer-video-1.0 gstreamer-rtp-1.0
LIBS += -lgstreamer-1.0 -lgstapp-1.0 -lgstvideo-1.0 -lgobject-2.0 -lglib-2.0 -lgstaudio-1.0

INCLUDEPATH += /usr/include/gstreamer-1.0 \
               /usr/include/glib-2.0 \
               /usr/lib/glib-2.0/include \
               /usr/include/gstreamer-1.0/gst/video

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

target.path = /usr/bin

desktop_file.files = e-ag.desktop
desktop_file.path = /usr/share/applications/

icon.files = icons/e-ag.svg
icon.path = /usr/share/icons/

#x11service.files = x11vnc-e-ag.service
#x11service.path = /lib/systemd/system/

#x11servicesh.files = x11vnc-e-ag.sh
#x11servicesh.path = /usr/bin/

x11passwd.files = x11vncpasswd
x11passwd.path = /usr/bin/

x11servicedesktop.files = e-ag-x11vncdesktop.service
x11servicedesktop.path = /lib/systemd/system/

x11servicelogin.files = e-ag-x11vnclogin.service
x11servicelogin.path = /lib/systemd/system/

ngx.files = nginx.conf
ngx.path = /etc/nginx/

#webdisable.files = webdisable.sh
#webdisable.path = /usr/share/e-ag/

#filezilla.files = filezilla.xml
#filezilla.path = /usr/share/e-ag/

polkit_policy.files = e-ag.policy
polkit_policy.path = /usr/share/polkit-1/actions/
polkit_rules.files = e-ag.rules
polkit_rules.path = /usr/share/polkit-1/rules.d/

lang.files = translations/*.qm
lang.path = /usr/share/e-ag/translations/

INSTALLS += target desktop_file icon x11passwd\
x11servicedesktop x11servicelogin lang polkit_rules polkit_policy

DISTFILES +=e-ag.svg\
    e-ag.desktop\
    x11vncpasswd\
    e-ag-x11vncdesktop.service\
    e-ag-x11vnclogin.service\




