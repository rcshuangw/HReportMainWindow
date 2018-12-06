#-------------------------------------------------
#
# Project created by QtCreator 2017-09-21T14:04:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += printsupport
TARGET = SARibbonMainWindowExample
TEMPLATE = app
DESTDIR = ..\..\bin
INCLUDEPATH += \
              ../include \
              ../SARibbonBar

SOURCES += main.cpp\
    mainwindow.cpp \ 
    hreportwindowact.cpp \
    hformatsetdlg.cpp \
    hborderset.cpp \
    hfontset.cpp \
    hreportmaiwidget.cpp \
    hreportbrowserwidget.cpp \
    hgridreportmgr.cpp \
    hreporttreewidget.cpp \
    hreportnewdlg.cpp \
    hgridctrlhelper.cpp \
    hgridctrlwidget.cpp \
    hreportprint.cpp \
    hreporteditorwidget.cpp \
    hgridreportwidget.cpp

HEADERS  += \
    mainwindow.h \ 
    hborderset.h \
    hformatsetdlg.h \
    hfontset.h \
    hreportmaiwidget.h \
    hreportbrowserwidget.h \
    hgridreportmgr.h \
    hreporttreewidget.h \
    hreportnewdlg.h \
    hgridctrlhelper.h \
    hgridctrlwidget.h \
    hreportprint.h \
    hreporteditorwidget.h \
    hgridreportwidget.h

RESOURCES += \
    saribbonresouce.qrc


LIBS += -L..\..\lib -lH5RibbonBar -lgridctrl

FORMS += \
    formatsetdlg.ui \
    hborderset.ui \
    hfontset.ui \
    hreportmaiwidget.ui \
    hreportnewdlg.ui
