#-------------------------------------------------
#
# Project created by QtCreator 2017-09-21T14:04:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    hgridreport.cpp \
    hgridctrlhelper.cpp \
    hgridctrlwidget.cpp

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
    hgridreport.h \
    hgridctrlhelper.h \
    hgridctrlwidget.h

RESOURCES += \
    saribbonresouce.qrc


LIBS += -L..\..\lib -lH5RibbonBar -lgridctrl

FORMS += \
    formatsetdlg.ui \
    hborderset.ui \
    hfontset.ui \
    hreportmaiwidget.ui \
    hreportnewdlg.ui
