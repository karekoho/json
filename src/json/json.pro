CONFIG -= qt

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

#QMAKE_CXXFLAGS+= -std=c++11
#QMAKE_LFLAGS +=  -std=c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    json_exception.cpp \
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

# Default rules for deployment.
unix {
    #target.path = $$[QT_INSTALL_PLUGINS]/generic
    target.path = /usr/local/lib
}
!isEmpty(target.path): INSTALLS += target

DESTDIR = ../../build/debug

DISTFILES += \
    ../../README.md \
    ../../CMakeLists.txt
