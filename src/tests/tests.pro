QT += core
QT -= gui

LIBS += -lcppunit
# LIBS += -lutil -L/usr/local/lib

#QMAKE_CXXFLAGS+= -std=c++11
#QMAKE_LFLAGS +=  -std=c++11

QMAKE_CXXFLAGS+= -std=c++14
QMAKE_LFLAGS +=  -std=c++14

TARGET = tests
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ../json/json_value.cpp \
    ../json/json_undefined.cpp \
    ../json/json_string.cpp \
    ../json/json_object.cpp \
    ../json/json_number.cpp \
    ../json/json_null.cpp \
    ../json/json_json.cpp \
    ../json/json_boolean.cpp \
    ../json/json_array.cpp

HEADERS += \
    json_value_test_interface.h \
    json_test.h \
    unit_test.h \
    json_object_test.h \
    json_value_test.h \
    json_value_parse_mock.h \
    json_undefined_test.h \
    json_string_test.h \
    json_number_test.h \
    json_null_test.h \
    json_boolean_test.h \
    json_array_test.h \
    ../json/json.h \
    ../json/json_value.h \
    ../json/json_undefined.h \
    ../json/json_string.h \
    ../json/json_object.h \
    ../json/json_number.h \
    ../json/json_null.h \
    ../json/json_json.h \
    ../json/json_boolean.h \
    ../json/json_array.h

SUBDIRS += \
    ../json/json.pro



