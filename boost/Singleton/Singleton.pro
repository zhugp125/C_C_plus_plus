TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

OBJECTS_DIR += ./bulider/obj

INCLUDEPATH += /usr/local/include

LIBS += /usr/local/lib/libboost_thread.a

SOURCES += main.cpp

HEADERS += \
    singleton.hpp
