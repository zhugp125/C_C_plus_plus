TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
#CONFIG -= qt

INCLUDEPATH += /usr/local/include

LIBS += /usr/local/lib/libtinyxml.a
LIBS += /usr/local/lib/libtinyxml2.a

SOURCES += main.cpp
