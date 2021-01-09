QMAKE_MAC_SDK = macosx10.15
QMAKE_CXXFLAGS+= -std=c++11
QMAKE_LFLAGS +=  -std=c++11

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    ../json/json_json.h \
    create_modify.h \
    parse.h \
    revive.h

# macx: LIBS += -L/usr/local/lib/ -ljson
LIBS += /usr/local/lib/libjson.a

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include
