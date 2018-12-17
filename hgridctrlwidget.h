#ifndef HREPORTWIDGET_H
#define HREPORTWIDGET_H

#include <QWidget>
#include "hgridglobal.h"
class HGridCtrl;
class QLabel;
class QLineEdit;
class HGridCtrlInfo;
class HGridCell;
class HReportManager;
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
    //设置属性
    void setGridCtrlWidgetAttr();
    void enableShowEditBar(bool);
    void enableShowHorizontalHeader(bool);//显示水平表格头
    void enableShowVerticalHeader(bool); //显示垂直表格头
    void enableAutoSize(bool);
    void setFillRange(bool);
    void enableEditor(bool);//编辑（复制粘贴拷贝)操作
    void enableShowGridLines(bool);
    void enableShowTab(bool);
    void enableSelectRange(bool);

public:

public:
    HGridCtrl* gridCtrl() {return m_pGridCtrl;}

signals:
    void gridcellclickded(HGridCell*);
public slots:
    void gridCell_clicked(HGridCell*);

private:
    bool m_bEnableShowEditBar;
    bool m_bEnableShowHorHeader;
    bool m_bEnableShowVerHeader;
    bool m_bShowAutoSize;
    bool m_bEnableEditor;
    bool m_bEnableShowGridLines;
    bool m_bEnableShowTab;
    bool m_bEnableSelectRange;
private:
   HReportManager* m_pReportManager;
   HGridCtrl* m_pGridCtrl;
   long m_nNumSheets;
   QLabel* m_rowColLabel;
   QLineEdit* m_inputLineEdit;
   HGridCtrlInfo* m_pGridCtrlInfo;
};

#endif // HREPORTWIDGET_H
