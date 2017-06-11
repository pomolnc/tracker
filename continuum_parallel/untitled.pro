TEMPLATE = app

QT += core gui widgets

CONFIG += console c++11
CONFIG -= app_bundle
#CONFIG -= qt

DEFINES-= UNICODE

INCLUDEPATH += ./Dist64

LIBS +=     -ladvapi32   \
            $$PWD\Dist64\MTC.lib

SOURCES += main.cpp \
    Cameras.cpp \
    Collection.cpp \
    Facet.cpp \
    main.cpp \
    Marker.cpp \
    Markers.cpp \
    MCamera.cpp \
    MTXPoint.cpp \
    Persistence.cpp \
    Vector.cpp \
    Xform3D.cpp \
    XPoints.cpp \
    processing.cpp \
    UtilityFunctions.cpp

SUBDIRS += \
    untitled.pro

DISTFILES +=

HEADERS += \
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
    resource.h \
    Vector.h \
    Xform3D.h \
    XPoints.h \
    processing.h \
    UtilityFunctions.h
