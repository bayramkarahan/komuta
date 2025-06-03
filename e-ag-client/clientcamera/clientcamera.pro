QT += widgets
CONFIG += c++11

SOURCES += main.cpp \
           vlcwidget.cpp


HEADERS += vlcwidget.h

INCLUDEPATH += /usr/include/vlc
LIBS += -lvlc
