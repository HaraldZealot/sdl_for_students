TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    sdlwrapper.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    sdlwrapper.h


unix|win32: LIBS += -lSDL2
