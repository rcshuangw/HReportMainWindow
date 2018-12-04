#include "hreportmaiwidget.h"
#include "ui_hreportmaiwidget.h"
#include "hgridctrl.h"
#include "hgridcelldef.h"
#include "hgridctrlhelper.h"
#include "hgridreport.h"
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
    //m_pTabWidget->setContentsMargins(0, 0, 0, 0);
    //QHBoxLayout* layout = new QHBoxLayout(this);
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
    m_pReportBrowserWidget = new HGridReportWidget(m_pReportManager,m_pTabWidget);
    m_pReportBrowserWidget->setGridReportType(GRIDREPORT_TYPE_BROWSER);
    m_pTabWidget->insertTab(0,m_pReportBrowserWidget,QStringLiteral("浏览窗"));
}

void HReportMaiWidget::createReportEditorWidget()
{
    m_pReportEditorWidget = new HGridReportWidget(m_pReportManager,m_pTabWidget);
    m_pReportEditorWidget->setGridReportType(GRIDREPORT_TYPE_EDITOR);
    m_pReportEditorWidget->setNumSheet(1);
    m_pReportEditorWidget->updateGridReportWidget();
    m_pTabWidget->insertTab(1,m_pReportEditorWidget,QStringLiteral("编辑框"));
}

void HReportMaiWidget::newReportWidget()
{
    if(!m_pReportManager)
        return;
    m_pReportBrowserWidget->clearGridReportWidget();
    m_pReportEditorWidget->clearGridReportWidget();
    m_pReportBrowserWidget->setNumSheet(1);
    m_pReportEditorWidget->setNumSheet(1);
    m_pReportBrowserWidget->updateGridReportWidget();
    m_pReportEditorWidget->updateGridReportWidget();
}

void HReportMaiWidget::updateReportWidget()
{
    if(!m_pReportManager || !m_pReportManager->gridCtrlFile())
        return;
    HGridCtrlInfo* pInfo = m_pReportManager->gridCtrlFile()->getCurGridCtrlInfo();
    if(!pInfo) return;
    //m_pReportEditorWidget->setG
}
