TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/local/lib -ljson
# QMAKE_CXX += -static

QMAKE_CXXFLAGS+= -std=c++14

SOURCES += main.cpp
