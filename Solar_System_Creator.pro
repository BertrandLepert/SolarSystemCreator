#-------------------------------------------------
#
# Project created by QtCreator 2016-04-25T17:07:18
#
#-------------------------------------------------

QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Solar_System_Creator
TEMPLATE = app


SOURCES += main.cpp\
    calculsAlignement.cpp \
    mainwindow.cpp \
    display_opengl.cpp \
    gl_widget.cpp \
    salorselectionglwidget.cpp \
    planetselection.cpp

HEADERS  += \
    calculsAlignement.h \
    mainwindow.h \
    display_opengl.h \
    gl_widget.h \
    salorselectionglwidget.h \
    planetselection.h

FORMS    += mainwindow.ui

LIBS += -lSDLmain -lSDL -lGLU -lSDL_image -ljpeg -lSOIL -lglut -lSDL_ttf
