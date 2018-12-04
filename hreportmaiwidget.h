#ifndef HREPORTMAIWIDGET_H
#define HREPORTMAIWIDGET_H

#include <QWidget>
#include <QTabWidget>
namespace Ui {
class HReportMaiWidget;
}
class HGridCtrl;
class HGridReportWidget;
class HReportManager;
class HReportMaiWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HReportMaiWidget(HReportManager* mgr,QWidget *parent = 0);
    ~HReportMaiWidget();

public:
    void createReportBrowserWidget();
    void createReportEditorWidget();
    void newReportWidget();
    void updateReportWidget();
private:
    Ui::HReportMaiWidget *ui;
    QTabWidget* m_pTabWidget;
    HGridReportWidget* m_pReportBrowserWidget;
    HGridReportWidget* m_pReportEditorWidget;
    HReportManager* m_pReportManager;

};

#endif // HREPORTMAIWIDGET_H
