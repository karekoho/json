QT += core
QT -= gui

LIBS += -lcppunit
# LIBS += -lutil -L/usr/local/lib

QMAKE_CXXFLAGS+= -std=c++11
QMAKE_LFLAGS +=  -std=c++11

TARGET = tests
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    json_test.cpp \
    json_value_test.cpp

HEADERS += \
    json_test.h \
    unit_test.h \
    json_value_test.h

