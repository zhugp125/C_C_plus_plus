TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/include

LIBS += /usr/local/lib/libboost_filesystem.a
LIBS += /usr/local/lib/libboost_system.a

SOURCES += main.cpp \
    common.cpp \
    ./md5/md5.cpp \
    ./jsoncpp/jsoncpp.cpp

HEADERS += \
    common.h \
    ./md5/md5.h \
    ./jsoncpp/json/json.h \
    ./jsoncpp/json/json-forwards.h
