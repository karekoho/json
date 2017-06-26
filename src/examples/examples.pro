TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib -ljson
#LIBS += /usr/local/lib/libjson.a

QMAKE_CXXFLAGS+= -std=c++11

SOURCES += \
    main.cpp

HEADERS += \
    parse.h \
    create_modify.h \
    revive.h
