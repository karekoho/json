# QMAKE_MAC_SDK = macosx10.15

QT += core
QT -= gui

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lcppunit
# LIBS += /usr/local/lib/libjson.a

QMAKE_CXXFLAGS+= -std=c++11
QMAKE_LFLAGS +=  -std=c++11

TARGET = test_debug
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ../json/json_exception.cpp \
    ../json/json_value.cpp \
    ../json/json_undefined.cpp \
    ../json/json_string.cpp \
    ../json/json_object.cpp \
    ../json/json_number.cpp \
    ../json/json_json.cpp \
    ../json/json_array.cpp \

HEADERS += \
    json_value_test_interface.h \
    json_test.h \
    unit_test.h \
    json_object_test.h \
    json_value_test.h \
    json_undefined_test.h \
    json_string_test.h \
    json_number_test.h \
    json_null_test.h \
    json_boolean_test.h \
    json_array_test.h \
    json_object_iterator_test.h \
    json_array_iterator_test.h \
    json_leaf_iterator_test.h \
    json_leaf_test.h \
    test_selector.h \
    test_selector_test.h \
    json_exception_test.h \
    json_mock_value.h \
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
    ../json/json_exception.h \

SUBDIRS += \
    ../json/json.pro

DISTFILES += \
    ../../build/tests/CMakeLists.txt



