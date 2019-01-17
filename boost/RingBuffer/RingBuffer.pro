TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

OBJECTS_DIR += ./bulider/obj

SOURCES += main.cpp

HEADERS += \
    ringbuffer.hpp
