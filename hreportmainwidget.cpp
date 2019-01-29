#include "hreportmainwidget.h"
#include "ui_hreportmainwidget.h"
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

HReportMainWidget::HReportMainWidget(HReportManager* mgr,QWidget *parent) :
    m_pReportManager(mgr),QWidget(parent),
    ui(new Ui::HReportMainWidget)
{
    ui->setupUi(this);
    m_pTabWidget = new QTabWidget(this);
    m_pTabWidget->setTabPosition(QTabWidget::North);
    m_pTabWidget->setStyleSheet(strStyleSheet);
    ui->verticalLayout->addWidget(m_pTabWidget);
    m_pReportManager->setReportMainWidget(this);
    createReportBrowserWidget();
    createReportEditorWidget();
    //setLayout(layout);
}

HReportMainWidget::~HReportMainWidget()
{
    delete ui;
}

void HReportMainWidget::createReportBrowserWidget()
{
    //QHBoxLayout *layout = new QHBoxLayout(m_pTabWidget);
    m_pReportBrowserWidget = new HReportBrowserWidget(m_pReportManager,m_pTabWidget);
    //layout->addWidget(m_pReportBrowserWidget);

    m_pTabWidget->insertTab(0,m_pReportBrowserWidget,QStringLiteral("浏览窗"));
}

void HReportMainWidget::createReportEditorWidget()
{
    //QHBoxLayout *layout = new QHBoxLayout(m_pTabWidget);
    m_pReportEditorWidget = new HReportEditorWidget(m_pReportManager,m_pTabWidget);
    connect(m_pReportEditorWidget,SIGNAL(gridcellclicked()),this,SIGNAL(gridcellclicked()));
    //layout->addWidget(m_pReportEditorWidget);
    m_pTabWidget->insertTab(1,m_pReportEditorWidget,QStringLiteral("编辑框"));
}

void HReportMainWidget::newReportWidget(quint16 nReportID)
{
    if(!m_pReportManager)
        return;
    m_pReportBrowserWidget->newReportWidget(nReportID);
    m_pReportEditorWidget->newReportWidget(nReportID);
}

void HReportMainWidget::openReportWidget(quint16 nReportID)
{
    if(!m_pReportManager)
        return;
    m_pReportBrowserWidget->openReportWidget(nReportID);
    m_pReportEditorWidget->openReportWidget(nReportID);
}

void HReportMainWidget::saveReportWidget()
{
    if(!m_pReportManager)
        return;
    m_pReportEditorWidget->saveReportWidget();
}

void HReportMainWidget::delReportWidget(quint16 nReportID)
{
    if(!m_pReportManager)
        return;
    m_pReportBrowserWidget->delReportWidget(nReportID);
    m_pReportEditorWidget->delReportWidget(nReportID);
}

void HReportMainWidget::printReportWidget()
{
    if(!m_pReportManager)
        return;
    m_pReportBrowserWidget->printReportWidget();
}

void HReportMainWidget::printPreviewReportWidget()
{
    if(!m_pReportManager)
        return;
    m_pReportBrowserWidget->printPreviewReportWidget();
}

void HReportMainWidget::updateReportWidget()
{
    if(!m_pReportManager || !m_pReportManager->gridCtrlFile())
        return;
    HGridCtrlInfo* pInfo = m_pReportManager->gridCtrlFile()->getCurGridCtrlInfo();
    if(!pInfo) return;
}

void HReportMainWidget::paste()
{
    if(!m_pReportManager)
        return;
    //如果浏览框也支持粘贴，则此处要判断当前窗口是否为浏览窗口
    m_pReportEditorWidget->paste();
}

void HReportMainWidget::cut()
{

}

void HReportMainWidget::copy()
{

}

void HReportMainWidget::setCellFormat(HFormatSet* pFormatSet,uint formatType,bool bAll)
{
    m_pReportEditorWidget->setCellFormat(pFormatSet,formatType,bAll);
    m_pReportBrowserWidget->setCellFormat(pFormatSet,formatType,bAll);
}

void HReportMainWidget::cellFormat(HFormatSet* pFormatSet)
{
    m_pReportEditorWidget->cellFormat(pFormatSet);
}

//操作
bool HReportMainWidget::mergeCell()
{
    return m_pReportEditorWidget->mergeCell();
}

bool HReportMainWidget::splitCell()
{
    return m_pReportEditorWidget->splitCell();
}

bool HReportMainWidget::insertGridRow()
{
    return m_pReportEditorWidget->insertGridRow();
}

bool HReportMainWidget::insertGridColumn()
{
    return m_pReportEditorWidget->insertGridColumn();
}

bool HReportMainWidget::removeGridRow()
{
    return m_pReportEditorWidget->removeGridRow();
}

bool HReportMainWidget::removeGridColumn()
{
    return m_pReportEditorWidget->removeGridColumn();
}

void HReportMainWidget::autoSizeRows()
{
    m_pReportEditorWidget->autoSizeRows();
}

void HReportMainWidget::autoSizeColumns()
{
    m_pReportEditorWidget->autoSizeColumns();
}
