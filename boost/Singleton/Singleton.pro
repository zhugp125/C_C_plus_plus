TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

OBJECTS_DIR += ./bulider/obj

INCLUDEPATH += /usr/local/include

SOURCES += main.cpp

HEADERS += \
    singleton.hpp
