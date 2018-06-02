#-------------------------------------------------
#
# Project created by QtCreator 2017-11-25T21:44:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Electronic_Circuit_Simulation
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

INCLUDEPATH += /Users/HuangJuiTe/Desktop/ECE/sophomore_first_emester/AOOP/1/eigen
SOURCES += \
        main.cpp \
        ecssystem.cpp \
    electronic_component.cpp \
    linear_component.cpp \
    resistor.cpp \
    capacitor.cpp \
    inductor.cpp \
    node.cpp \
    workspace.cpp \
    resistordialog.cpp \
    capacitordialog.cpp \
    inductordialog.cpp \
    customscene.cpp \
    customline.cpp \
    scope.cpp \
    vsource.cpp \
    vsourcedialog.cpp \
    mna.cpp \
    scopegraphicsview.cpp

HEADERS += \
        ecssystem.h \
    scope.h \
    electronic_component.h \
    linear_component.h \
    resistor.h \
    capacitor.h \
    inductor.h \
    node.h \
    workspace.h \
    resistordialog.h \
    capacitordialog.h \
    inductordialog.h \
    customscene.h \
    customline.h \
    vsource.h \
    vsourcedialog.h \
    mna.h \
    scopegraphicsview.h

FORMS += \
        ecssystem.ui \
    scope.ui \
    resistordialog.ui \
    capacitordialog.ui \
    inductordialog.ui \
    vsourcedialog.ui

RESOURCES += \
    images.qrc
