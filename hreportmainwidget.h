#ifndef HREPORTMAINWIDGET_H
#define HREPORTMAINWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include "hformatdef.h"
#include "hformatset.h"
namespace Ui {
class HReportMainWidget;
}
class HGridCtrl;
class HReportBrowserWidget;
class HReportEditorWidget;
class HReportManager;
class HReportMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HReportMainWidget(HReportManager* mgr,QWidget *parent = 0);
    ~HReportMainWidget();

public:
    HReportBrowserWidget* reportBrowserWidget() {return m_pReportBrowserWidget;}
    HReportEditorWidget* reportEditorWidget()   {return m_pReportEditorWidget; }
public:
    void createReportBrowserWidget();
    void createReportEditorWidget();

    void newReportWidget(quint16 nReportID);
    void updateReportWidget();
    void openReportWidget(quint16 nReportID);
    void saveReportWidget();
    void delReportWidget(quint16 nReportID);

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
    Ui::HReportMainWidget *ui;
    QTabWidget* m_pTabWidget;
    HReportBrowserWidget* m_pReportBrowserWidget;
    HReportEditorWidget* m_pReportEditorWidget;
    HReportManager* m_pReportManager;

};

#endif // HREPORTMAIWIDGET_H
