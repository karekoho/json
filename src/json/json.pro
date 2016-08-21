CONFIG += staticlib
CONFIG -= qt

QMAKE_CXXFLAGS+= -std=c++11
QMAKE_LFLAGS +=  -std=c++11

#TARGET = json
#CONFIG += console
#CONFIG -= app_bundle

TEMPLATE = lib

SOURCES += \
    value.cpp \
    basic_json.cpp

HEADERS += \
    value.h \
    json.h \
    basic_json.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/local/lib
    }
    INSTALLS += target
}

DESTDIR = ../../build/debug


