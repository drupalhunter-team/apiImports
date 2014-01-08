#-------------------------------------------------
#
# Project created by QtCreator 2013-12-27T16:26:00
#
#-------------------------------------------------

QT       += core gui script qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = apiImports
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    apiCalls.cpp \
    settings.cpp \
    jsUtils.cpp \
    JsImportInfo.cpp \
    JsImportsModel.cpp \
    Login.cpp

HEADERS  += mainwindow.h \
    apiCalls.h \
    settings.h \
    jsUtils.h \
    JsImportInfo.h \
    JsImportsModel.h \
    Login.h
