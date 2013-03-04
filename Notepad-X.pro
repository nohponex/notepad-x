#-------------------------------------------------
#
# Project created by QtCreator 2012-09-14T21:35:56
#
#-------------------------------------------------

QT       += core
QT       += gui

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Notepad-X
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Components/tabbarx.cpp \
    Components/tabwidgetx.cpp \
    Classes/iconpack.cpp \
    Documents/defaultdocument.cpp \
    Dialogs/aboutdialog.cpp \
    Components/externalwindow.cpp \
    Classes/syntaxhighlighter.cpp \
    Classes/linenumberarea.cpp \
    Components/plaintexteditx.cpp \
    Classes/templatedocument.cpp \
    Classes/json.cpp \
    Classes/toolbar.cpp \
    Components/console.cpp \
    Components/findreplace.cpp \
    Dialogs/settingsdialog.cpp

HEADERS  += mainwindow.h \
    Components/tabbarx.h \
    Components/tabwidgetx.h \
    Classes/iconpack.h \
    Documents/IDocument.h \
    Documents/defaultdocument.h \
    Dialogs/aboutdialog.h \
    Components/externalwindow.h \
    Classes/syntaxhighlighter.h \
    Classes/linenumberarea.h \
    Components/plaintexteditx.h \
    Classes/templatedocument.h \
    Classes/json.h \
    Classes/toolbar.h \
    Components/console.h \
    Components/findreplace.h \
    Dialogs/settingsdialog.h



RESOURCES += \
    Icons.qrc

FORMS += \
    dialog.ui \
    mainwindow.ui \
    settings.ui

OTHER_FILES += \
    Todo.txt \
    LICENSE.txt \
    README.txt \

win32 {
    RC_FILE = notepad-x.rc
}
win32:debug {
    CONFIG  += console
}
#CONFIG += release
#CONFIG += static
