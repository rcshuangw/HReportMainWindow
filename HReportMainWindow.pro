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
              ../SARibbonBar \
              D:\qt-workspace\include

SOURCES += main.cpp\
    mainwindow.cpp \ 
    hreportwindowact.cpp \
    hformatsetdlg.cpp \
    hborderset.cpp \
    hfontset.cpp \
    hreportbrowserwidget.cpp \
    hgridreportmgr.cpp \
    hreporttreewidget.cpp \
    hreportnewdlg.cpp \
    hgridctrlhelper.cpp \
    #hgridctrlwidget.cpp \
    #hreportprint.cpp \
    hreporteditorwidget.cpp \
    #hgridreportwidget.cpp \
    hformatset.cpp \
    hopsheetvardlg.cpp \
    hreportmainwidget.cpp

HEADERS  += \
    mainwindow.h \ 
    hborderset.h \
    hformatsetdlg.h \
    hfontset.h \
    hreportbrowserwidget.h \
    hgridreportmgr.h \
    hreporttreewidget.h \
    hreportnewdlg.h \
    hgridctrlhelper.h \
    #hgridctrlwidget.h \
    #hreportprint.h \
    hreporteditorwidget.h \
    #hgridreportwidget.h \
    hformatset.h \
    hformatdef.h \
    hopsheetvardlg.h \
    hreportmainwidget.h

RESOURCES += \
    saribbonresouce.qrc


LIBS += -L..\..\lib -lH5RibbonBar -lgridctrl -ldatafile

FORMS += \
    formatsetdlg.ui \
    hborderset.ui \
    hfontset.ui \
    hreportnewdlg.ui \
    hopsheetvardlg.ui \
    hreportmainwidget.ui
