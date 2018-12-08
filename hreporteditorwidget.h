﻿#ifndef HREPORTEDITORWIDGET_H
#define HREPORTEDITORWIDGET_H
#include <QTabWidget>
class HReportManager;
class HGridReportWidget;

class HReportEditorWidget : public QWidget
{
    Q_OBJECT
public:
    HReportEditorWidget(HReportManager* mgr,QWidget *parent = 0);
    ~HReportEditorWidget();

public:
    void newReportWidget();

public:
    HReportManager* m_pReportManager;
    HGridReportWidget* m_pGridReportWidget;
};

#endif // HREPORTEDITORWIDGET_H