#ifndef HREPORTWIDGET_H
#define HREPORTWIDGET_H

#include <QWidget>
#include "hgridglobal.h"
#include "hgridcelldef.h"
class HGridCtrl;
class QLabel;
class QLineEdit;
class HGridCtrlInfo;
class HCellID;
class HReportManager;
class HFormatSet;
//tab页的具体内容
class  HGridCtrlWidget : public QWidget
{
    Q_OBJECT
public:
    HGridCtrlWidget(HReportManager* mgr,QWidget* parent = 0);
    ~HGridCtrlWidget();

    void initReportWidget();
    void setGridCtrlItem(HGridCtrlInfo* pItem);
    void getGridCtrlItem(HGridCtrlInfo* pItem);

public:
    //属性
    void setVirtualMode(bool);
    void enableShowEditBar(bool);
    void enableShowTab(bool);

    void setCellFormat(HFormatSet* pFormatSet,uint formatType,bool bAll = false);
    void cellFormat(HFormatSet* pFormatSet);

    //操作
    bool mergeCell();
    bool splitCell();
    bool insertGridRow();
    bool insertGridColumn();
    bool removeGridRow();
    bool removeGridColumn();
public:

public:
    HGridCtrl* gridCtrl() {return m_pGridCtrl;}

signals:
    void gridcellclicked();
public slots:
    //void gridCell_clicked(HCellID);

private:
    bool m_bEnableShowEditBar;
    bool m_bEnableShowTab;
    bool m_bEnableVirtualMode;
private:
   HReportManager* m_pReportManager;
   HGridCtrl* m_pGridCtrl;
   long m_nNumSheets;
   QLabel* m_rowColLabel;
   QLineEdit* m_inputLineEdit;
   HGridCtrlInfo* m_pGridCtrlInfo;
};

#endif // HREPORTWIDGET_H
