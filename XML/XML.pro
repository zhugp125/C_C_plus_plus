TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
#CONFIG -= qt

INCLUDEPATH += /usr/local/include

SOURCES += main.cpp \
    tinyxml2/tinyxml2.cpp \
    tinyxml/tinystr.cpp \
    tinyxml/tinyxml.cpp \
    tinyxml/tinyxmlerror.cpp \
    tinyxml/tinyxmlparser.cpp

HEADERS += \
    tinyxml2/tinyxml2.h \
    tinyxml/tinystr.h \
    tinyxml/tinyxml.h
