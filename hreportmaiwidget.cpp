#include "hreportmaiwidget.h"
#include "ui_hreportmaiwidget.h"
#include "hgridctrl.h"
#include "hgridcelldef.h"
#include "hgridreport.h"
#include <QHBoxLayout>
QString strStyleSheet = " QTabWidget::pane {border-top: 1px solid #C2C7CB;} \
                          QTabWidget::tab-bar {left: 5px; } \
        QTabBar::tab {  background-color:#D5E4F2; \
        border: 2px solid #C4C4C3; min-width: 200px;margin-left: 5px; \
        border-bottom-color: #C2C7CB; border-top-left-radius: 4px; \
        border-top-right-radius: 4px;min-width: 8ex;padding: 2px;} \
        QTabBar::tab:selected, QTabBar::tab:hover { \
        background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, \
        stop: 0 #fafafa, stop: 0.4 #f4f4f4,stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);} \
        QTabBar::tab:selected {border-color: #9B9B9B;border-bottom-color: #C2C7CB; } \
        QTabBar::tab:!selected {margin-top: 2px; }";

HReportMaiWidget::HReportMaiWidget(QWidget *parent) :
    QWidget(parent),
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
    m_pReportBrowserWidget = new HGridReportWidget(m_pTabWidget);
    m_pReportBrowserWidget->setGridReportType(GRIDREPORT_TYPE_BROWSER);
    m_pTabWidget->insertTab(0,m_pReportBrowserWidget,QStringLiteral("浏览窗"));
}

void HReportMaiWidget::createReportEditorWidget()
{
    m_pReportEditorWidget = new HGridReportWidget(m_pTabWidget);
    m_pReportEditorWidget->setGridReportType(GRIDREPORT_TYPE_EDITOR);
    m_pTabWidget->insertTab(1,m_pReportEditorWidget,QStringLiteral("编辑框"));
}
