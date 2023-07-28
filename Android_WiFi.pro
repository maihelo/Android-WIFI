#-------------------------------------------------
#
# Project created by QtCreator 2021-07-20T21:15:57
#
#-------------------------------------------------

QT       += core gui network charts androidextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#QT += androidextras

TARGET = Android_WiFi
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        Widget.cpp \
        cmd_queue.cpp \
        hmi_driver.cpp \
        main.cpp \
        process_fun.cpp \
        widget2.cpp

HEADERS += \
        cmd_queue.h \
        hmi_driver.h \
        process_fun.h \
        widget.h \
        widget2.h

FORMS += \
        widget.ui \
        widget2.ui

CONFIG += mobility
MOBILITY = 

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android_sources

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Android_sources/AndroidManifest.xml
