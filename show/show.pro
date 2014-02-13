#-------------------------------------------------
#
# Project created by QtCreator 2014-02-08T03:20:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = show
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    mythread.cpp \
    ffmtool.cpp \
    pre_main.cpp \
    sock.cpp

HEADERS  += widget.h \
    bo.h \
    mythread.h \
    ffmtool.h \
    pre_main.h \
    sock.h

LIBS += -L/usr/local/lib -lavdevice -lavfilter -lpostproc -lswresample -lavformat -lavcodec -lva -lXfixes -lXext -lX11 -lasound -lSDL -lx264 -lvpx -lvorbisenc -lvorbis -ltheoraenc -ltheoradec -logg -lopus -lmp3lame -lfdk-aac -lass -lz -lrt -ldl -lswscale -lavutil -lm

