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
    void createReportBrowserWidget();
    void createReportEditorWidget();
    void newReportWidget();
    void printReportWidget();

    void updateReportWidget();
private:
    Ui::HReportMaiWidget *ui;
    QTabWidget* m_pTabWidget;
    HReportBrowserWidget* m_pReportBrowserWidget;
    HReportEditorWidget* m_pReportEditorWidget;
    HReportManager* m_pReportManager;

};

#endif // HREPORTMAIWIDGET_H
