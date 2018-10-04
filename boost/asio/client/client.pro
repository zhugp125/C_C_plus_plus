TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/include

LIBS += /usr/local/lib/libboost_filesystem.a
LIBS += /usr/local/lib/libboost_system.a
LIBS += /usr/local/lib/libboost_thread.a
LIBS += /usr/local/lib/libboost_date_time.a

SOURCES += \
    main.cpp
