#include "hgridreportwidget.h"
#include <QTabBar>
#include <QVBoxLayout>
#include "hgridctrlwidget.h"
#include "hgridctrlhelper.h"
#include "hgridreportmgr.h"
HGridReportWidget::HGridReportWidget(HReportManager* mgr,QWidget *parent)
   :m_pReportManager(mgr),QWidget(parent)
{
    m_bEnableShowEditBar = false;
    m_bEnableShowHorHeader = false;
    m_bEnableShowVerHeader = false;
    m_bEnableAutoSize = false;
    m_bEnableEditor = false;
    m_bEnableShowGridLines = false;
    m_bEnableShowTab = false;
    m_bEnableSelectRange = false;
    initGridReportWidget();
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
    m_nNumSheets = 0;

    //first loop delete tabs
    //updateGridReportWidget();
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
            setGridReportType(w);
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

void HGridReportWidget::setGridReportType(QWidget *w)
{
    if(!w) return;
    HGridCtrlWidget* pGridCtrlWidget = (HGridCtrlWidget*)w;
    pGridCtrlWidget->enableShowEditBar(m_bEnableShowEditBar);
    pGridCtrlWidget->enableShowHorizontalHeader(m_bEnableShowHorHeader);
    pGridCtrlWidget->enableShowVerticalHeader(m_bEnableShowVerHeader);
    pGridCtrlWidget->enableAutoSize(m_bEnableAutoSize);
    //pGridCtrlWidget->setFillRange(bool);
    pGridCtrlWidget->enableEditor(m_bEnableEditor);
    pGridCtrlWidget->enableShowGridLines(m_bEnableShowGridLines);
    pGridCtrlWidget->enableShowTab(m_bEnableShowTab);
    pGridCtrlWidget->enableSelectRange(m_bEnableSelectRange);
}

void HGridReportWidget::setEditorGridReportAttr()
{
    enableShowEditBar(true);
    enableShowTab(false);
    enableEditor(true);
    //统一设置属性
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

void HGridReportWidget::enableShowEditBar(bool b)
{
    m_bEnableShowEditBar = b;
    int nTabNum = m_tabWidget->count();
    for(int i = 0; i < nTabNum; i++)
    {
        HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(i);
        if(w)
        {
            w->enableShowEditBar(b);
        }
    }
}

void HGridReportWidget::enableShowHorizontalHeader(bool b)//显示水平表格头
{
    m_bEnableShowHorHeader = b;
    int nTabNum = m_tabWidget->count();
    for(int i = 0; i < nTabNum; i++)
    {
        HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(i);
        if(w)
        {
            w->enableShowHorizontalHeader(b);
        }
    }
}

void HGridReportWidget::enableShowVerticalHeader(bool b) //显示垂直表格头
{
    m_bEnableShowVerHeader = b;
    int nTabNum = m_tabWidget->count();
    for(int i = 0; i < nTabNum; i++)
    {
        HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(i);
        if(w)
        {
            w->enableShowVerticalHeader(b);
        }
    }
}

void HGridReportWidget::enableAutoSize(bool b)
{
    m_bEnableAutoSize = b;
    int nTabNum = m_tabWidget->count();
    for(int i = 0; i < nTabNum; i++)
    {
        HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(i);
        if(w)
        {
            w->enableAutoSize(b);
        }
    }
}

void HGridReportWidget::setFillRange(bool b)
{

}

void HGridReportWidget::enableEditor(bool b)//编辑（复制粘贴拷贝)操作
{
    m_bEnableEditor = b;
    int nTabNum = m_tabWidget->count();
    for(int i = 0; i < nTabNum; i++)
    {
        HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(i);
        if(w)
        {
            w->enableEditor(b);
        }
    }
}

void HGridReportWidget::enableShowGridLines(bool b)
{
    m_bEnableShowGridLines = b;
    int nTabNum = m_tabWidget->count();
    for(int i = 0; i < nTabNum; i++)
    {
        HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(i);
        if(w)
        {
            w->enableShowGridLines(b);
        }
    }
}

void HGridReportWidget::enableShowTab(bool b)
{
    m_bEnableShowTab = b;
    int nTabNum = m_tabWidget->count();
    for(int i = 0; i < nTabNum; i++)
    {
        HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(i);
        if(w)
        {
            w->enableShowTab(b);
        }
    }
}

void HGridReportWidget::enableSelectRange(bool b)
{
    m_bEnableSelectRange = b;
    int nTabNum = m_tabWidget->count();
    for(int i = 0; i < nTabNum; i++)
    {
        HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(i);
        if(w)
        {
            w->enableSelectRange(b);
        }
    }
}

void HGridReportWidget::gridCell_clicked(HGridCell* pCell)
{
    emit gridcellclickded(pCell);
}
