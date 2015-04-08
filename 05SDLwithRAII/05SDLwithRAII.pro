TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    sdlwrapper.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    sdlwrapper.h

