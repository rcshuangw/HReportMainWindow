#ifndef HREPORTMAIWIDGET_H
#define HREPORTMAIWIDGET_H

#include <QWidget>
#include <QTabWidget>
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

public:
    //操作
    void paste();
    void cut();
    void copy();
    void newReportWidget();
    void printReportWidget();
    void printPreviewReportWidget();

    void updateReportWidget();
private:
    Ui::HReportMaiWidget *ui;
    QTabWidget* m_pTabWidget;
    HReportBrowserWidget* m_pReportBrowserWidget;
    HReportEditorWidget* m_pReportEditorWidget;
    HReportManager* m_pReportManager;

};

#endif // HREPORTMAIWIDGET_H
