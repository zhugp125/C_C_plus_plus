TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/include

LIBS += /usr/local/lib/libboost_system.a
LIBS += /usr/local/lib/libboost_serialization.a
LIBS += /usr/local/lib/libboost_filesystem.a
LIBS += /usr/local/lib/libmd5.a
LIBS += /usr/local/lib/libjsoncpp.a

OBJECTS_DIR += ./bulider/obj

DESTDIR += ./bin

SOURCES += main.cpp \
    TcpConnection.cpp \
    TcpServer.cpp \
    TcpSession.cpp \
    FileData.cpp \
    TcpCommon.cpp

HEADERS += \
    TcpConnection.h \
    TcpServer.h \
    TcpSession.h \
    FileData.h \
    TcpCommon.h

DISTFILES += \
    bin/config.ini
