TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ./TrimString

SOURCES += main.cpp \
    IniParser.cpp

HEADERS += \
    IniParser.h \
    TrimString.h
