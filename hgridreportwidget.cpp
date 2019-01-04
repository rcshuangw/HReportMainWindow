#include "hgridreportwidget.h"
#include <QTabBar>
#include <QVBoxLayout>
#include "hgridctrlwidget.h"
#include "hgridctrlhelper.h"
#include "hgridreportmgr.h"
#include "hreportprint.h"
HGridReportWidget::HGridReportWidget(HReportManager* mgr,QWidget *parent)
   :m_pReportManager(mgr),QWidget(parent)
{
    m_bEnableShowEditBar = false;
    m_bEnableShowTab = false;
    m_bEnableVirtual = false;
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
            connect(w,SIGNAL(gridcellclicked()),this,SLOT(gridCell_clicked()));
            HGridCtrlInfo* pInfo = m_pReportManager->gridCtrlFile()->getCurGridCtrlInfo();
            w->setGridCtrlItem(pInfo);
            setGridCtrlAttr(w);
            w->initReportWidget();
            QString str = QString(QStringLiteral("第%1页")).arg(num+1);
            m_tabWidget->insertTab(i,w,str);
        }
    }
    if(!m_bEnableShowTab)
        m_tabWidget->tabBar()->hide();
    else
        m_tabWidget->tabBar()->show();
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

void HGridReportWidget::setGridCtrlAttr(QWidget *w)
{
    if(!w) return;
    HGridCtrlWidget* pGridCtrlWidget = (HGridCtrlWidget*)w;
    pGridCtrlWidget->enableShowEditBar(m_bEnableShowEditBar);
    pGridCtrlWidget->enableShowTab(m_bEnableShowTab);
    pGridCtrlWidget->setVirtualMode(m_bEnableVirtual);
}

void HGridReportWidget::setEditorGridReportAttr()
{
    enableShowEditBar(true);
    enableShowTab(false);
    enableVritual(false);
}

void HGridReportWidget::setBrowserGridReportAttr()
{
    enableShowEditBar(false);
    enableShowTab(true);
    enableVritual(true);
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

void HGridReportWidget::enableVritual(bool b)
{
    m_bEnableVirtual = b;
    int nTabNum = m_tabWidget->count();
    for(int i = 0; i < nTabNum; i++)
    {
        HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(i);
        if(w)
        {
            w->setVirtualMode(b);
        }
    }
}

void HGridReportWidget::paste()
{
    int index = m_tabWidget->currentIndex();
    HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(index);
    if(w)
    {
        HGridCtrl* pGridCtrl = w->gridCtrl();
        if(pGridCtrl)
            pGridCtrl->onEditPaste();
    }
}

void HGridReportWidget::cut()
{
    int index = m_tabWidget->currentIndex();
    HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(index);
    if(w)
    {
        HGridCtrl* pGridCtrl = w->gridCtrl();
        if(pGridCtrl)
            pGridCtrl->onEditCut();
    }
}

void HGridReportWidget::copy()
{
    int index = m_tabWidget->currentIndex();
    HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(index);
    if(w)
    {
        HGridCtrl* pGridCtrl = w->gridCtrl();
        if(pGridCtrl)
            pGridCtrl->onEditCopy();
    }
}

void HGridReportWidget::setCellFormat(HFormatSet* pFormatSet,uint formatType,bool bAll)
{
    int index = m_tabWidget->currentIndex();
    HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(index);
    if(w)
    {
        w->setCellFormat(pFormatSet,formatType,bAll);
    }
}

void HGridReportWidget::cellFormat(HFormatSet* pFormatSet)
{
    int index = m_tabWidget->currentIndex();
    HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(index);
    if(w)
    {
        w->cellFormat(pFormatSet);
    }
}

//操作
bool HGridReportWidget::mergeCell()
{
    int index = m_tabWidget->currentIndex();
    HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(index);
    if(w)
    {
        return w->mergeCell();
    }
    return false;
}

bool HGridReportWidget::splitCell()
{
    int index = m_tabWidget->currentIndex();
    HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(index);
    if(w)
    {
        return w->splitCell();
    }
    return false;
}

//操作:插入删除行列部分
bool HGridReportWidget::insertGridRow()
{
    int index = m_tabWidget->currentIndex();
    HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(index);
    if(w)
    {
        return w->insertGridRow();
    }
    return false;
}

bool HGridReportWidget::insertGridColumn()
{
    int index = m_tabWidget->currentIndex();
    HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(index);
    if(w)
    {
        return w->insertGridColumn();
    }
    return false;
}

bool HGridReportWidget::removeGridRow()
{
    int index = m_tabWidget->currentIndex();
    HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(index);
    if(w)
    {
        return w->removeGridRow();
    }
    return false;
}

bool HGridReportWidget::removeGridColumn()
{
    int index = m_tabWidget->currentIndex();
    HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(index);
    if(w)
    {
        return w->removeGridColumn();
    }
    return false;
}

void HGridReportWidget::autoSizeRows()
{
    int index = m_tabWidget->currentIndex();
    HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(index);
    if(w)
    {
        w->autoSizeRows();
    }
}

void HGridReportWidget::autoSizeColumns()
{
    int index = m_tabWidget->currentIndex();
    HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(index);
    if(w)
    {
        w->autoSizeColumns();
    }
}

//打印部分
void HGridReportWidget::printPreview()
{
    HReportPrint print(this);
    print.printPreview();
}

void HGridReportWidget::print()
{
    HReportPrint print(this);
    print.print();
}

void HGridReportWidget::gridCell_clicked()
{
    //获取格式信息
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    int index = m_tabWidget->currentIndex();
    HGridCtrlWidget* w = (HGridCtrlWidget*)m_tabWidget->widget(index);
    if(w)
    {
        w->cellFormat(m_pReportManager->formatSet());
    }
    emit gridcellclicked();
}
