﻿#ifndef HGRIDREPORTWIDGET_H
#define HGRIDREPORTWIDGET_H

#include <QWidget>
//管理多个HGridCtrlWidget具体tab页面的
#include <QTabWidget>
#include <hgridctrl.h>
class HReportManager;
class HGridReportWidget : public QWidget
{
    Q_OBJECT
public:
    HGridReportWidget(HReportManager* mgr,QWidget *parent = 0);
    ~HGridReportWidget();
public:
    void setEditorGridReportAttr();
    void setBrowserGridReportAttr();
    bool loadGridCtrlFile(const char* filename);
    bool saveGridCtrlFile(const char* filename);

public:
    void initGridReportWidget();
    void updateGridReportWidget();
    void clearGridReportWidget();

public:
///////////////////////////////////////////////////////////////////////////////
///////Tab属性
/// //////////////////////////////////////////////////////////////////////////
    QString tabName();
    void setTabName(const QString& tableName);
    QString sheetName(short nSheet);
    void setSheetName(short nSheet, const QString& lpszNewValue);
    void setNumSheet(long num);
    long numSheet();
    void setSheet(long index);
    long sheet();

///////////////////////////////////////////////////////////////////////////////
///////设置属性
/// //////////////////////////////////////////////////////////////////////////
    void setGridCtrlAttr(QWidget* w);
    void enableShowEditBar(bool);
    void enableShowTab(bool);
    void enableVritual(bool);

///////////////////////////////////////////////////////////////////////////////
///////操作
/// //////////////////////////////////////////////////////////////////////////
    void paste();
    void cut();
    void copy();
    void bold(bool);
    void italic();
    void underline();


    //打印
    void printPreview();
    void print();

public:

signals:
    void gridcellclickded(HGridCell*);

public slots:
    void gridCell_clicked(HGridCell*);

public:
    HReportManager* m_pReportManager;
    QTabWidget* m_tabWidget;
private:
    long m_nNumSheets;
    bool m_bEnableShowEditBar;
    bool m_bEnableShowTab;
    bool m_bEnableVirtual;
};
#endif // HGRIDREPORTWIDGET_H
