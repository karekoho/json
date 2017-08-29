CONFIG += staticlib
CONFIG -= qt

QMAKE_CXXFLAGS+= -std=c++11
QMAKE_LFLAGS +=  -std=c++11

TEMPLATE = lib

SOURCES += \
    json_value.cpp \
    json_undefined.cpp \
    json_string.cpp \
    json_object.cpp \
    json_number.cpp \
    json_json.cpp \    
    json_array.cpp \    

HEADERS += \
    json_value.h \
    json_undefined.h \
    json_string.h \
    json_object.h \
    json_number.h \
    json_null.h \
    json_json.h \
    json_boolean.h \
    json_array.h \
    json_leaf.h \    
    json_exception.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/local/lib
    }
    INSTALLS += target
}

DESTDIR = ../../build/debug

DISTFILES += \
    ../../README.md \
    ../../CMakeLists.txt


