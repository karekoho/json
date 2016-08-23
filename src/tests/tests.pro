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
    json_value_test_interface.cpp \
    json_test.cpp \
    json_object_test.cpp \
    json_value_test.cpp \
    ../json/value.cpp \
    json_value_parse_mock.cpp \
    ../json/object.cpp \
    ../json/array.cpp \
    ../json/basic_json.cpp

HEADERS += \
    json_value_test_interface.h \
    json_test.h \
    unit_test.h \
    json_object_test.h \
    json_value_test.h \
    ../json/value.h \
    ../json/json.h \
    json_value_parse_mock.h \
    ../json/basic_json.h

SUBDIRS += \
    ../json/json.pro



