TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/include/python2.7

LIBS += /usr/lib/libpython2.7.dylib

SOURCES += main.cpp

