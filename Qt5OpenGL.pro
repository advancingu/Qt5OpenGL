#-------------------------------------------------
#
# Project created by QtCreator 2012-12-26T06:24:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt5OpenGL
TEMPLATE = app


SOURCES += main.cpp \
    window.cpp \
    basicusagescene.cpp

HEADERS += \
    window.h \
    abstractscene.h \
    basicusagescene.h \
    glassert.h

OTHER_FILES += \
    Shaders/phong.vert \
    Shaders/phong.frag \
    shaders/phong.vert \
    shaders/phong.frag

RESOURCES += \
    resources.qrc

unix:LIBS += -lGLU
win32:LIBS += -lglu32
