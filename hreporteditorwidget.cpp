#include "hreporteditorwidget.h"
#include "hgridreportwidget.h"
#include "hgridreportmgr.h"
#include <QHBoxLayout>
HReportEditorWidget::HReportEditorWidget(HReportManager* mgr,QWidget *parent)
   :m_pReportManager(mgr),QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    m_pGridReportWidget = new HGridReportWidget(m_pReportManager,this);
    m_pGridReportWidget->setEditorGridReportAttr();
    layout->addWidget(m_pGridReportWidget);
    m_pGridReportWidget->hide();
    setLayout(layout);
    connect(m_pGridReportWidget,SIGNAL(gridcellclicked()),this,SIGNAL(gridcellclicked()));
}

HReportEditorWidget::~HReportEditorWidget()
{

}

void HReportEditorWidget::newReportWidget()
{
    if(!m_pReportManager)
        return;
    m_pGridReportWidget->clearGridReportWidget();
    m_pGridReportWidget->setNumSheet(1);
    m_pGridReportWidget->updateGridReportWidget();
    m_pGridReportWidget->show();
}

/*
void HGridReportWidget::initGridReportWidget()
{
    m_tabWidget = new QTabWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(6, 6, 6, 6);
    mainLayout->addWidget(m_tabWidget);
    m_tabWidget->setTabPosition(QTabWidget::South);

    //update
    //first loop delete tabs
    updateGridReportWidget();

}

void HGridReportWidget::updateGridReportWidget()
{
    if(!m_pReportManager || !m_pReportManager->gridCtrlFile())
        return;
    int nAddCount = m_nNumSheets - m_tabWidget->count();
    if(nAddCount < 0)
    {
        while (m_tabWidget->count() > m_nNumSheets) {
            int index = m_tabWidget->count()-1;
            HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(index);
            if(w)
            {
                delete w;
                w = NULL;
            }
            m_tabWidget->removeTab(index);
        }
    }
    else
    {
        int num = m_tabWidget->count();
        for(int i = 0; i < nAddCount; i++)
        {
            HGridCtrlWidget* w = new HGridCtrlWidget(m_pReportManager,m_tabWidget);
            //要把表格模板拷贝到每个页面
            w->initReportWidget(m_uGridReportType);
            HGridCtrlInfo* pInfo = m_pReportManager->gridCtrlFile()->getCurGridCtrlInfo();
            w->setGridCtrlItem(pInfo);
            QString str = QString(QStringLiteral("第%1页")).arg(num+1);
            m_tabWidget->insertTab(i,w,str);
        }
    }
}

void HGridReportWidget::clearGridReportWidget()
{
    while (m_tabWidget->count()) {
        int index = m_tabWidget->count() - 1;
        HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(index);
        if(w)
        {
            delete w;
            w = NULL;
        }
        m_tabWidget->removeTab(index);
    }
}

void HGridReportWidget::setGridReportType(quint8 uGridReportType)
{
    m_uGridReportType = uGridReportType;
    if(m_uGridReportType == GRIDREPORT_TYPE_EDITOR)
        setEditGridReportAttr();
    else if(m_uGridReportType == GRIDREPORT_TYPE_BROWSER)
        setBrowserGridReportAttr();
}*/

void HReportEditorWidget::paste()
{
    m_pGridReportWidget->paste();
}

void HReportEditorWidget::cut()
{

}

void HReportEditorWidget::copy()
{

}
