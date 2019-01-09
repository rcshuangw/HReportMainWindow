#ifndef HREPORTBROWSERWIDGET_H
#define HREPORTBROWSERWIDGET_H
#include <QWidget>
class HReportManager;
class HGridReportWidget;
//表格预览窗口
class HReportBrowserWidget : public QWidget
{
public:
    HReportBrowserWidget(HReportManager* mgr,QWidget* parent = 0);

public:

    void newReportWidget();
    void openReportWidget();
    void delReportWidget();

    //操作
    void paste();
    void cut();
    void copy();

    void printReportWidget();
    void printPreviewReportWidget();

    void setCellFormat(HFormatSet* pFormatSet,uint formatType,bool bAll = false);
    /*void initGridReportWidget();
    void updateGridReportWidget();
    void setGridReportType(quint8 uGridReportType);
    void setEditGridReportAttr();
    void setBrowserGridReportAttr();
    void clearGridReportWidget();
    bool loadGridCtrlFile(const char* filename);
    bool saveGridCtrlFile(const char* filename);

    //void setShowTable(bool bshow);
   // bool isShowTable();



signals:
    void gridcellclicked(HGridCell*);
public slots:
    void gridCell_clicked(HGridCell*);*/

public:
    HGridReportWidget* m_pGridReportWidget;
    HReportManager* m_pReportManager;
};

#endif // HREPORTBROWSERWIDGET_H
