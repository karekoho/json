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
    ../json/json_array.cpp \
    ../json/json_leaf.cpp \
    ../json/json_object_iterator.cpp \
    ../json/json_leaf_iterator.cpp \
    ../json/json_array_iterator.cpp \
    ../json/json_shared_undefined.cpp

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
    ../json/json_array.h \
    ../json/json_leaf.h \
    json_object_iterator_test.h \
    json_array_iterator_test.h \
    json_leaf_iterator_test.h \
    ../json/json_object_iterator.h \
    ../json/json_iterator.h \
    ../json/json_leaf_iterator.h \
    ../json/json_array_iterator.h \
    json_leaf_test.h \
    ../json/json_shared_undefined.h \
    test_selector.h \
    test_selector_test.h \
    ../json/json_exception.h \
    json_exception_test.h

SUBDIRS += \
    ../json/json.pro



