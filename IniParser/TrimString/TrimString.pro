TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/include

LIBS += /usr/local/lib/libgtest_main.a

SOURCES += \
    test/test.cpp \

HEADERS += \
    TrimString.h \
