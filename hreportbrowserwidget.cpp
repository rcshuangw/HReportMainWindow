#include "hreportbrowserwidget.h"
#include "hgridreportwidget.h"
#include "hformatset.h"
#include <QHBoxLayout>
HReportBrowserWidget::HReportBrowserWidget(HReportManager* mgr,QWidget* parent)
    :m_pReportManager(mgr),QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    m_pGridReportWidget = new HGridReportWidget(this);
    m_pGridReportWidget->setBrowserGridReportAttr();
    layout->addWidget(m_pGridReportWidget);
    m_pGridReportWidget->hide();
    setLayout(layout);
}

void HReportBrowserWidget::newReportWidget()
{
    if(!m_pReportManager )
        return;
    /*m_pGridReportWidget->clearGridReportWidget();
    m_pGridReportWidget->setNumSheet(1);
    m_pGridReportWidget->updateGridReportWidget();
    m_pGridReportWidget->show();*/
}

void HReportBrowserWidget::openReportWidget()
{
    if(!m_pReportManager)
        return;
    /*m_pGridReportWidget->clearGridReportWidget();
    m_pGridReportWidget->setNumSheet(1);
    m_pGridReportWidget->updateGridReportWidget();
    m_pGridReportWidget->show();*/
}

void HReportBrowserWidget::delReportWidget()
{
    if(!m_pReportManager)
        return;
   // m_pGridReportWidget->clearGridReportWidget();
}

void HReportBrowserWidget::printReportWidget()
{
    if(!m_pReportManager)
        return;
   // m_pGridReportWidget->print();
}

void HReportBrowserWidget::printPreviewReportWidget()
{
    if(!m_pReportManager)
        return;
   // m_pGridReportWidget->printPreview();
}

void HReportBrowserWidget::paste()
{

}

void HReportBrowserWidget::cut()
{

}

void HReportBrowserWidget::copy()
{

}

void HReportBrowserWidget::setCellFormat(HFormatSet* pFormatSet,uint formatType,bool bAll)
{
   // m_pGridReportWidget->setPrintFormat(pFormatSet);
}
