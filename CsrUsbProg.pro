TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    usbdriver.cpp \
    usbprogrammer.cpp \
    stopwatch.cpp \
    devicemanager.cpp \
    flash.cpp

unix:!symbian: LIBS += -lusb-1.0

HEADERS += \
    usbdriver.h \
    usbprogrammer.h \
    stopwatch.h \
    devicemanager.h \
    flash.h \
    bc_def.h
