#include "hreportbrowserwidget.h"
#include "hgridreportwidget.h"
#include <QHBoxLayout>
HReportBrowserWidget::HReportBrowserWidget(HReportManager* mgr,QWidget* parent)
    :m_pReportManager(mgr),QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    m_pGridReportWidget = new HGridReportWidget(m_pReportManager,this);
    layout->addWidget(m_pGridReportWidget);
    m_pGridReportWidget->hide();
    setLayout(layout);
}

void HReportBrowserWidget::newReportWidget()
{
    if(!m_pReportManager)
        return;
    m_pGridReportWidget->clearGridReportWidget();
    m_pGridReportWidget->setNumSheet(1);
    m_pGridReportWidget->updateGridReportWidget();
    m_pGridReportWidget->show();
}

void HReportBrowserWidget::printReportWidget()
{
    if(!m_pReportManager)
        return;
    m_pGridReportWidget->printPreview();
}
