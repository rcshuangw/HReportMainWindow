#ifndef HREPORTMAIWIDGET_H
#define HREPORTMAIWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include "hformatdef.h"
#include "hformatset.h"
namespace Ui {
class HReportMaiWidget;
}
class HGridCtrl;
class HReportBrowserWidget;
class HReportEditorWidget;
class HReportManager;
class HReportMaiWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HReportMaiWidget(HReportManager* mgr,QWidget *parent = 0);
    ~HReportMaiWidget();

public:
    HReportBrowserWidget* reportBrowserWidget() {return m_pReportBrowserWidget;}
    HReportEditorWidget* reportEditorWidget()   {return m_pReportEditorWidget; }
public:
    void createReportBrowserWidget();
    void createReportEditorWidget();

    void newReportWidget();
    void updateReportWidget();
    void openReportWidget();
    void delReportWidget();

public:
    //操作
    void paste();
    void cut();
    void copy();

    void setCellFormat(HFormatSet* pFormatSet,uint formatType,bool bAll = false);
    void cellFormat(HFormatSet* pFormatSet);

    bool mergeCell();
    bool splitCell();
    bool insertGridRow();
    bool insertGridColumn();
    bool removeGridRow();
    bool removeGridColumn();
    void autoSizeRows();
    void autoSizeColumns();   
    void printReportWidget();
    void printPreviewReportWidget();

signals:
     void gridcellclicked();
private:
    Ui::HReportMaiWidget *ui;
    QTabWidget* m_pTabWidget;
    HReportBrowserWidget* m_pReportBrowserWidget;
    HReportEditorWidget* m_pReportEditorWidget;
    HReportManager* m_pReportManager;

};

#endif // HREPORTMAIWIDGET_H
