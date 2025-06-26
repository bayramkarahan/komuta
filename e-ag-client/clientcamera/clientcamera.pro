QT += widgets
CONFIG += c++11
TARGET=clientcamera
SOURCES += main.cpp \
           vlcwidget.cpp


HEADERS += vlcwidget.h

INCLUDEPATH += /usr/include/vlc
LIBS += -lvlc
