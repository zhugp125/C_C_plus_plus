TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/include

SOURCES += main.cpp \
    FileClient.cpp

HEADERS += \
    FileClient.h
