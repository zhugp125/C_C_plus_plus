TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Account.cpp \
        LoggerImp.cpp \
        StandardOutputLogger.cpp \
        main.cpp

HEADERS += \
    Account.h \
    LoggerImp.h \
    StandardOutputLogger.h \
    client.hpp \
    logger.hpp
