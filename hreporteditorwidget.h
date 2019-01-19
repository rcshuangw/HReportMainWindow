﻿#ifndef HREPORTEDITORWIDGET_H
#define HREPORTEDITORWIDGET_H
#include <QTabWidget>
class HReportManager;
class HGridReportWidget;
class HFormatSet;
class HReportEditorWidget : public QWidget
{
    Q_OBJECT
public:
    HReportEditorWidget(HReportManager* mgr,QWidget *parent = 0);
    ~HReportEditorWidget();

public:
    void newReportWidget(quint16 wReportID);
    void openReportWidget(quint16 wReportID);
    void saveReportWidget();
    void delReportWidget();

public:
    void paste();
    void cut();
    void copy();

    void setCellFormat(HFormatSet* pFormatSet,uint formatType,bool bAll = false);
    void cellFormat(HFormatSet* pFormatSet);

    //操作
    bool mergeCell();
    bool splitCell();
    bool insertGridRow();
    bool insertGridColumn();
    bool removeGridRow();
    bool removeGridColumn();
    void autoSizeRows();
    void autoSizeColumns();
public:
    void setGridCtrlAttr(uint nAttrType,HFormatSet* pFormatSet);

protected:
    void contextMenuEvent(QContextMenuEvent *event);
signals:
    void gridcellclicked();

private:
    quint16 m_wReportID;
private:
    HReportManager* m_pReportManager;
    HGridReportWidget* m_pGridReportWidget;
};

#endif // HREPORTEDITORWIDGET_H
