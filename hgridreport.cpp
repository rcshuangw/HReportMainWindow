#include "hgridreport.h"
#include <QTabBar>
#include <QVBoxLayout>
#include "hgridctrlwidget.h"
#include "hgridctrlhelper.h"
#include "hgridreportmgr.h"
HGridReportWidget::HGridReportWidget(HReportManager* mgr,QWidget *parent)
   :m_pReportManager(mgr),QWidget(parent)
{
    setNumSheet(0);
    initGridReportWidget();
    //m_rowColLabel = new Q
}

HGridReportWidget::~HGridReportWidget()
{

}

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
}

void HGridReportWidget::setEditGridReportAttr()
{
    enableShowEditBar(true);
    enableShowTab(false);
    enableEditor(true);
}

void HGridReportWidget::setBrowserGridReportAttr()
{
    enableShowEditBar(false);
    enableShowTab(true);
    enableEditor(false);
}

bool HGridReportWidget::loadGridCtrlFile(const char* filename)
{
    return true;
}

bool HGridReportWidget::saveGridCtrlFile(const char* filename)
{
    return false;
}

QString HGridReportWidget::tabName()
{
    return "";
}

void HGridReportWidget::setTabName(const QString& tableName)
{

}

QString HGridReportWidget::sheetName(short nSheet)
{
    if(nSheet > numSheet())
        return "";
    return m_tabWidget->tabBar()->tabText(nSheet);
}

void HGridReportWidget::setSheetName(short nSheet, const QString& strNewName)
{
    if(nSheet > numSheet())
        return;
    m_tabWidget->tabBar()->setTabText(nSheet,strNewName);

}

void HGridReportWidget::setNumSheet(long num)
{
    m_nNumSheets = num;
}

long HGridReportWidget::numSheet()
{
    return m_nNumSheets;
}

void HGridReportWidget::setSheet(long index)
{
    if(index > numSheet())
        return;
    if(m_tabWidget->tabBar()->currentIndex() != index)
    {
        m_tabWidget->tabBar()->setCurrentIndex(index);
    }
}

long HGridReportWidget::sheet()
{
    return 1;
}

void HGridReportWidget::enableShowEditBar(bool)
{

}

void HGridReportWidget::enableShowHorizontalHeader(bool)//显示水平表格头
{

}

void HGridReportWidget::enableShowVerticalHeader(bool) //显示垂直表格头
{

}

void HGridReportWidget::enableAutoSize(bool)
{

}

void HGridReportWidget::setFillRange(bool)
{

}

void HGridReportWidget::enableEditor(bool)//编辑（复制粘贴拷贝)操作
{

}

void HGridReportWidget::enableShowGridLines(bool)
{

}

void HGridReportWidget::enableShowTab(bool bShow)
{
    if(bShow)
         m_tabWidget->tabBar()->show();
    else
         m_tabWidget->tabBar()->hide();
}

void HGridReportWidget::enableSelectRange(bool)
{

}


void HGridReportWidget::gridCell_clicked(HGridCell* pCell)
{
    emit gridcellclickded(pCell);
}

