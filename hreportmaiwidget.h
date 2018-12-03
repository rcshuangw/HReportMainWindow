#ifndef HREPORTMAIWIDGET_H
#define HREPORTMAIWIDGET_H

#include <QWidget>
#include <QTabWidget>
namespace Ui {
class HReportMaiWidget;
}
class HGridCtrl;
class HGridReportWidget;
class HReportMaiWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HReportMaiWidget(QWidget *parent = 0);
    ~HReportMaiWidget();

public:
    void createReportBrowserWidget();
    void createReportEditorWidget();
private:
    Ui::HReportMaiWidget *ui;
    QTabWidget* m_pTabWidget;
    HGridReportWidget* m_pReportBrowserWidget;
    HGridReportWidget* m_pReportEditorWidget;

};

#endif // HREPORTMAIWIDGET_H
