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

#define GRID_ATTR_BROWSER  0x01
#define GRID_ATTR_EDITOR   0x02
//tab页的具体内容
class  HGridCtrlWidget : public QWidget
{
    Q_OBJECT
public:
    HGridCtrlWidget(HReportManager* mgr,QWidget* parent = 0);
    ~HGridCtrlWidget();
public:
    void initReportWidget();
    void setGridCtrlItem(HGridCtrlInfo* pItem);
    void getGridCtrlItem(HGridCtrlInfo* pItem);
public:
    //属性
    void setVirtualMode(bool);
    void enableShowEditBar(bool);
    void enableShowTab(bool);
    void enableHorizontalHeader(bool bEnable = true);
    void enableVerticalHeader(bool bEnable = true);
    void enablePrintColour(bool);
    void enableShowGrids(bool);
    void rowColRefresh();

    void setCellFormat(HFormatSet* pFormatSet,uint formatType,bool bAll = false);
    void cellFormat(HFormatSet* pFormatSet);
    void setPrintFormat(HFormatSet* pFormatSet);

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

public:
    HGridCtrl* gridCtrl() {return m_pGridCtrl;}

signals:
    void gridcellclicked();
public slots:
    //void gridCell_clicked(HCellID);
    void lineedit_textEdited(const QString &text);
protected:
    void contextMenuEvent(QContextMenuEvent *event);

private:
    void contextEditorMenuEvent(QContextMenuEvent* event);
    void contextBrowserMenuEvent(QContextMenuEvent* event);
private:
    bool m_bEnableShowEditBar;
    bool m_bEnableShowTab;
    bool m_bEnableVirtualMode;
    bool m_bHorizontalHeader;
    bool m_bVerticalHeader;
    bool m_bShowGrids;
    bool m_bPrintColour;
private:
    HReportManager* m_pReportManager;
    HGridCtrl* m_pGridCtrl;
    long m_nNumSheets;
    QLabel* m_rowColLabel;
    QLineEdit* m_inputLineEdit;
    HGridCtrlInfo* m_pGridCtrlInfo;
};

#endif // HREPORTWIDGET_H
