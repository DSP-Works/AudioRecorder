QT       += core gui widgets multimedia

TARGET = AudioRecorder
TEMPLATE = app

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        audioinput.cpp \
        audiorecorder.cpp

HEADERS += \
        mainwindow.h \
        audioinput.h \
        audiorecorder.h
