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
    void initGridReportWidget();
    void updateGridReportWidget();
    void setGridReportType(QWidget* w);
    void setEditorGridReportAttr();
    void setBrowserGridReportAttr();
    void clearGridReportWidget();
    bool loadGridCtrlFile(const char* filename);
    bool saveGridCtrlFile(const char* filename);
    QString tabName();
    void setTabName(const QString& tableName);
    //void setShowTable(bool bshow);
   // bool isShowTable();
    QString sheetName(short nSheet);
    void setSheetName(short nSheet, const QString& lpszNewValue);
    void setNumSheet(long num);
    long numSheet();
    void setSheet(long index);
    long sheet();

    //设置属性
    void enableShowEditBar(bool);
    void enableShowHorizontalHeader(bool);//显示水平表格头
    void enableShowVerticalHeader(bool); //显示垂直表格头
    void enableAutoSize(bool);
    void setFillRange(bool);
    void enableEditor(bool);//编辑（复制粘贴拷贝)操作
    void enableShowGridLines(bool);
    void enableShowTab(bool);
    void enableSelectRange(bool);
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
    bool m_bEnableShowHorHeader;
    bool m_bEnableShowVerHeader;
    bool m_bEnableAutoSize;
    bool m_bEnableEditor;
    bool m_bEnableShowGridLines;
    bool m_bEnableShowTab;
    bool m_bEnableSelectRange;
};
#endif // HGRIDREPORTWIDGET_H