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
    //设置属性
    void setVirtualMode(bool);
    void enableShowEditBar(bool);
    void enableShowTab(bool);

    void setCellFormat(uint formatType,HFormatSet* pFormatSet);
    void cellFormat(HFormatSet* pFormatSet);

    //基本
    void setHorizontalAlign(GV_ITEM* item,quint32 hAlign);
    //quint32 horizontalAlign();
    void setVerticalAlign(GV_ITEM* item,quint32 vAlign);
    //quint32 verticalAlign();
    void enableAutoWrapText(GV_ITEM* item,bool bAutoWrapText);
    //bool isAutoWrapText();
    void enableMergeCell(GV_ITEM* item,bool bMergCell);
    //bool isMergeCell();

    //字体
    void setFontFamily(GV_ITEM* item,const QString& fontFamily);
    void setFont(GV_ITEM* item,const QFont& font);
    void setFontSize(GV_ITEM* item,quint8);
    void enableFontUnderline(GV_ITEM* item,bool);
    void enableFontBold(GV_ITEM* item,bool);
    void enableFontItalic(GV_ITEM* item,bool);
    //字体颜色
    void setTextColor(GV_ITEM* item,const QString&);
    void setTextBkColor(GV_ITEM* item,const QString&);

    //设置边框
    void setCellBorderFormat(int row,int col,HFormatSet* pset);

    //设置打印边界
    void setPrintMarginInfo(HFormatSet* pSet);


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
