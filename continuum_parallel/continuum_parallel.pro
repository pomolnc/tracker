#-------------------------------------------------
#
# Project created by QtCreator 2017-06-11T13:16:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = continuum_parallel
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES -= UNICODE
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += ./Dist64

LIBS +=     -ladvapi32   \
            $$PWD\Dist64\MTC.lib


SOURCES += \
        main.cpp \
        widget.cpp \
    Cameras.cpp \
    Collection.cpp \
    Facet.cpp \
    Marker.cpp \
    Markers.cpp \
    MCamera.cpp \
    MTXPoint.cpp \
    Persistence.cpp \
    processing.cpp \
    UtilityFunctions.cpp \
    Vector.cpp \
    Xform3D.cpp \
    XPoints.cpp

HEADERS += \
        widget.h \
    Cameras.h \
    Collection.h \
    debug.h \
    Facet.h \
    Marker.h \
    Markers.h \
    MCamera.h \
    MTC.h \
    MTVideo.h \
    MTXPoint.h \
    Persistence.h \
    processing.h \
    resource.h \
    UtilityFunctions.h \
    Vector.h \
    Xform3D.h \
    XPoints.h

FORMS += \
        widget.ui
