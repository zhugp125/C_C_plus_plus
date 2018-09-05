TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/include

LIBS += /usr/local/lib/libboost_filesystem.a
LIBS += /usr/local/lib/libboost_system.a

SOURCES += main.cpp \
    FileClient.cpp \
    ../common/md5/md5.cpp \
    ../common/jsoncpp/jsoncpp.cpp \
    ../common/common.cpp

HEADERS += \
    FileClient.h \
    ../common/md5/md5.h \
    ../common/jsoncpp/json/json.h \
    ../common/jsoncpp/json/json-forwards.h \
    ../common/common.h
