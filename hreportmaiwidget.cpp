#include "hreportmaiwidget.h"
#include "ui_hreportmaiwidget.h"
#include "hgridctrl.h"
#include "hgridcelldef.h"
#include "hgridctrlhelper.h"
#include "hreporteditorwidget.h"
#include "hreportbrowserwidget.h"
#include "hgridreportwidget.h"
#include "hgridreportmgr.h"
#include <QHBoxLayout>
//"#3892ED"border-color: #9B9B9B;border-bottom-color: #C2C7CB;
QString strStyleSheet = " QTabWidget::pane {border-top: 1px solid #C9D9ED;} \
                          QTabWidget::tab-bar {left: 2px; } \
        QTabBar::tab {  background-color:#D5E4F2; \
        border: 1px solid #C9D9ED; min-width: 200px;margin-left: 2px; border-top-left-radius: 4px; \
        border-top-right-radius: 4px;padding: 2px;} \
        QTabBar::tab:selected, QTabBar::tab:hover { \
        background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, \
        stop: 0 #fafafa, stop: 0.4 #f4f4f4,stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);} \
        QTabBar::tab:selected {background-color:#BFDBFF; color: #3892ED } \
        QTabBar::tab:!selected {margin-top: 2px; background-color:#D5E4F2;}";

HReportMaiWidget::HReportMaiWidget(HReportManager* mgr,QWidget *parent) :
    m_pReportManager(mgr),QWidget(parent),
    ui(new Ui::HReportMaiWidget)
{
    ui->setupUi(this);
    m_pTabWidget = new QTabWidget(this);
    m_pTabWidget->setTabPosition(QTabWidget::North);
    m_pTabWidget->setStyleSheet(strStyleSheet);
    ui->verticalLayout->addWidget(m_pTabWidget);
    createReportBrowserWidget();
    createReportEditorWidget();
    //setLayout(layout);
}

HReportMaiWidget::~HReportMaiWidget()
{
    delete ui;
}

void HReportMaiWidget::createReportBrowserWidget()
{
    //QHBoxLayout *layout = new QHBoxLayout(m_pTabWidget);
    m_pReportBrowserWidget = new HReportBrowserWidget(m_pReportManager,m_pTabWidget);
    //layout->addWidget(m_pReportBrowserWidget);

    m_pTabWidget->insertTab(0,m_pReportBrowserWidget,QStringLiteral("浏览窗"));
}

void HReportMaiWidget::createReportEditorWidget()
{
    //QHBoxLayout *layout = new QHBoxLayout(m_pTabWidget);
    m_pReportEditorWidget = new HReportEditorWidget(m_pReportManager,m_pTabWidget);
    connect(m_pReportEditorWidget,SIGNAL(gridcellclicked()),this,SIGNAL(gridcellclicked()));
    //layout->addWidget(m_pReportEditorWidget);
    m_pTabWidget->insertTab(1,m_pReportEditorWidget,QStringLiteral("编辑框"));
}

void HReportMaiWidget::newReportWidget(int nReportID)
{
    if(!m_pReportManager)
        return;
    //m_pReportBrowserWidget->newReportWidget();
    m_pReportEditorWidget->newReportWidget(nReportID);
}

void HReportMaiWidget::openReportWidget()
{
    if(!m_pReportManager)
        return;
    m_pReportBrowserWidget->openReportWidget();
    //m_pReportEditorWidget->openReportWidget();
}

void HReportMaiWidget::delReportWidget()
{
    if(!m_pReportManager)
        return;
    m_pReportBrowserWidget->delReportWidget();
    m_pReportEditorWidget->delReportWidget();
}

void HReportMaiWidget::printReportWidget()
{
    if(!m_pReportManager)
        return;
    m_pReportBrowserWidget->printReportWidget();
}

void HReportMaiWidget::printPreviewReportWidget()
{
    if(!m_pReportManager)
        return;
    m_pReportBrowserWidget->printPreviewReportWidget();
}

void HReportMaiWidget::updateReportWidget()
{
    if(!m_pReportManager || !m_pReportManager->gridCtrlFile())
        return;
    HGridCtrlInfo* pInfo = m_pReportManager->gridCtrlFile()->getCurGridCtrlInfo();
    if(!pInfo) return;
}

void HReportMaiWidget::paste()
{
    if(!m_pReportManager)
        return;
    //如果浏览框也支持粘贴，则此处要判断当前窗口是否为浏览窗口
    int index = m_pTabWidget->currentIndex();
    if(0 == index) //浏览框
        m_pReportBrowserWidget->paste();
    else if(1 == index) //编辑框
        m_pReportEditorWidget->paste();
}

void HReportMaiWidget::cut()
{

}

void HReportMaiWidget::copy()
{

}

void HReportMaiWidget::setCellFormat(HFormatSet* pFormatSet,uint formatType,bool bAll)
{
    m_pReportEditorWidget->setCellFormat(pFormatSet,formatType,bAll);
    m_pReportBrowserWidget->setCellFormat(pFormatSet,formatType,bAll);
}

void HReportMaiWidget::cellFormat(HFormatSet* pFormatSet)
{
    m_pReportEditorWidget->cellFormat(pFormatSet);
}

//操作
bool HReportMaiWidget::mergeCell()
{
    return m_pReportEditorWidget->mergeCell();
}

bool HReportMaiWidget::splitCell()
{
    return m_pReportEditorWidget->splitCell();
}

bool HReportMaiWidget::insertGridRow()
{
    return m_pReportEditorWidget->insertGridRow();
}

bool HReportMaiWidget::insertGridColumn()
{
    return m_pReportEditorWidget->insertGridColumn();
}

bool HReportMaiWidget::removeGridRow()
{
    return m_pReportEditorWidget->removeGridRow();
}

bool HReportMaiWidget::removeGridColumn()
{
    return m_pReportEditorWidget->removeGridColumn();
}

void HReportMaiWidget::autoSizeRows()
{
    m_pReportEditorWidget->autoSizeRows();
}

void HReportMaiWidget::autoSizeColumns()
{
    m_pReportEditorWidget->autoSizeColumns();
}
