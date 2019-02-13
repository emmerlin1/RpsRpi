QT += core
QT -= gui
QT += sql

CONFIG += c++11

TARGET = rotational_speed
CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += /mnt/raspberry-rootfs/usr/include
LIBS += -L/mnt/raspberry-rootfs/usr/lib -lwiringPi

TEMPLATE = app

SOURCES += main.cpp \
    lightsenseprod.cpp \
    lightsensecons.cpp \
    lightsenseconstants.cpp \
    sqlcons.cpp

DISTFILES +=

target.path = /home/pi/rotational_speed
INSTALLS += target

HEADERS += \
    lightsenseprod.h \
    lightsensecons.h \
    lightsenseconstants.h \
    sqlcons.h


