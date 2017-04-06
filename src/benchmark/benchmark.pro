TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/local/lib -ljson
#QMAKE_CXX += -static

SOURCES += main.cpp

