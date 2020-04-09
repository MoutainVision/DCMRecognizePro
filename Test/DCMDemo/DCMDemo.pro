#-------------------------------------------------
#
# Project created by QtCreator 2020-03-08T14:50:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DCMDemo
TEMPLATE = app

DEFINES -= UNICODE

CONFIG(release, debug | release){
    DESTDIR = $$PWD/../../Bins/Release
}else {
    DESTDIR = $$PWD/../../Bins/Debug
}

#DEFINES                += UNICODE _UNICODE WIN32

CONFIG += c++17


INCLUDEPATH += ..\..\Dependencies\dcmtk-3.6.5\dcmdata\include

INCLUDEPATH += ..\..\Dlls\LibCore


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG(release, debug|release) {
    LIBS += -L"..\..\Dependencies\dcmtk-3.6.5\lib\Release" -ldcmtk
    LIBS += -L"..\..\Bins\Release" -lLibCore
}
else {
LIBS += -L"..\..\Dependencies\dcmtk-3.6.5\lib\Debug" -ldcmtk
LIBS += -L"..\..\Bins\Debug" -lLibCore -lLibDistortionCorrection -lLibTinyXML
}



