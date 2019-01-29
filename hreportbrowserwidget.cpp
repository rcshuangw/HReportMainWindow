#include "hreportbrowserwidget.h"
#include "hgridreportwidget.h"
#include "hgridreportmgr.h"
#include "hgridctrlhelper.h"
#include "SARibbonMenu.h"
#include <QHBoxLayout>
HReportBrowserWidget::HReportBrowserWidget(HReportManager* mgr,QWidget* parent)
    :m_pReportManager(mgr),QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    m_pGridReportWidget = new HGridReportWidget(this);
    m_pGridReportWidget->setBrowserGridReportAttr();
    layout->setContentsMargins(3, 3, 3, 3);
    layout->addWidget(m_pGridReportWidget);
    m_pGridReportWidget->hide();
    setLayout(layout);
    m_wReportID = (quint16)-1;
    m_wSheetNo = (quint16)-1;
}

void HReportBrowserWidget::newReportWidget(quint16 wReportID)
{
    if(!m_pReportManager || !m_pReportManager->gridCtrlFile())
        return;
    m_wReportID = wReportID;
    HGridCtrlInfo* pInfo = m_pReportManager->gridCtrlFile()->getGridCtrlInfoById(m_wReportID);
    if(!pInfo) return;
    m_pGridReportWidget->setMaxRow(pInfo->gridReportRow());
    m_pGridReportWidget->setMaxCol(pInfo->gridReportCol());
    m_pGridReportWidget->setNumSheet(1);
    m_pGridReportWidget->init();
    m_pGridReportWidget->show();
}

void HReportBrowserWidget::openReportWidget(quint16 wReportID)
{
    if(!m_pReportManager)
        return;
    m_wReportID = wReportID;
    HGridCtrlInfo* pInfo = m_pReportManager->gridCtrlFile()->getGridCtrlInfoById(m_wReportID);
    if(!pInfo) return;
    m_pGridReportWidget->setMaxRow(pInfo->gridReportRow());
    m_pGridReportWidget->setMaxCol(pInfo->gridReportCol());
    m_pReportManager->gridCtrlFile()->loadRelateVarFile(m_wReportID);

    m_pGridReportWidget->setNumSheet(1);
    char szFile[256],szPath[256];
    getDataFilePath(DFPATH_REPORT,szPath);
    sprintf(szFile,"%s%s%06d%s",szPath,"RPT",m_wReportID,".rpt");
    //存表格
    m_pGridReportWidget->setReportFile(QString(szFile));
    m_pGridReportWidget->open();//需要从文件中读取

    if((quint16)-1 == m_wSheetNo)
    {
        for(int i = 0; i < m_pReportManager->gridCtrlFile()->m_pRelateVarList.count();i++)
        {
            HRelateVar* pVar =  m_pReportManager->gridCtrlFile()->m_pRelateVarList.at(i);
            if(!pVar) continue;
            int row = pVar->row();
            int col = pVar->col();
            m_pGridReportWidget->setText(row,col,"");
            m_pGridReportWidget->enableOnlyRead(row,col,false);
        }
    }

    m_pGridReportWidget->show();
}

void HReportBrowserWidget::delReportWidget(quint16 wReportID)
{
    if(!m_pReportManager || (quint16)-1 == wReportID)
        return;
    m_pGridReportWidget->clear();
}

void HReportBrowserWidget::loadSheet()
{

}

void HReportBrowserWidget::loadPrevSheet()
{

}

void HReportBrowserWidget::loadNextSheet()
{

}

void HReportBrowserWidget::refreshReportWidget()
{
    loadSheetNo(m_wSheetNo);
}

void HReportBrowserWidget::loadSheetNo(quint16 sheetNo)
{
    if(!m_pReportManager)
        return;
    if((quint16)-1 != sheetNo)
        m_wSheetNo = sheetNo;
    HGridCtrlInfo* pInfo = m_pReportManager->gridCtrlFile()->getGridCtrlInfoById(m_wReportID);
    if(!pInfo) return;
    m_pGridReportWidget->setMaxRow(pInfo->gridReportRow());
    m_pGridReportWidget->setMaxCol(pInfo->gridReportCol());
    m_pReportManager->gridCtrlFile()->loadRelateVarFile(m_wReportID);

    m_pGridReportWidget->setNumSheet(1);
    char szFile[256],szPath[256];
    getDataFilePath(DFPATH_REPORT,szPath);
    sprintf(szFile,"%s%s%06d%s",szPath,"RPT",m_wReportID,".rpt");
    //存表格
    m_pGridReportWidget->setReportFile(QString(szFile));
    m_pGridReportWidget->open();//需要从文件中读取
    if((quint16)-1 == m_wSheetNo)
    {
        for(int i = 0; i < m_pReportManager->gridCtrlFile()->m_pRelateVarList.count();i++)
        {
            HRelateVar* pVar =  m_pReportManager->gridCtrlFile()->m_pRelateVarList.at(i);
            if(!pVar) continue;
            int row = pVar->row();
            int col = pVar->col();
            m_pGridReportWidget->setText(row,col,"");
            m_pGridReportWidget->enableOnlyRead(row,col,false);
        }
        m_pGridReportWidget->show();
        return;
    }

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
    m_pGridReportWidget->printPreview();
}


void HReportBrowserWidget::setCellFormat(HFormatSet* pFormatSet,uint formatType,bool bAll)
{
   // m_pGridReportWidget->setPrintFormat(pFormatSet);
}

void HReportBrowserWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QPoint pt = event->pos();
    QRect cellRect;
    m_pGridReportWidget->selectedRect(cellRect);

    if(!cellRect.contains(pt))
        return;
    SARibbonMenu *subMenu = new SARibbonMenu(this);

    QAction* loadAct = new QAction(QIcon(":/icon/icon/selectSheet.png"),QStringLiteral("选择操作票"),this);
    QAction* preSheetAct = new QAction(QIcon(":/icon/icon/previousSheet.png"),QStringLiteral("前一张操作票"),this);
    QAction* nextSheetAct = new QAction(QIcon(":/icon/icon/nextSheet.png"),QStringLiteral("后一张操作票"),this);
    subMenu->addAction(loadAct);
    subMenu->addAction(preSheetAct);
    subMenu->addAction(nextSheetAct);
    connect(loadAct,SIGNAL(triggered(bool)),this,SLOT(loadSheet()));
    connect(preSheetAct,SIGNAL(triggered(bool)),this,SLOT(loadPrevSheet()));
    connect(nextSheetAct,SIGNAL(triggered(bool)),this,SLOT(loadNextSheet()));
    subMenu->addSeparator();

    QAction* refreshAct = new QAction(QIcon(":/icon/icon/Refresh.png"),QStringLiteral("刷新"),this);
    QAction* printAct = new QAction(QIcon(":/icon/icon/OpSheet.png"),QStringLiteral("显示设置"),this);
    QAction* clearFormattingAct = new QAction(QIcon(":/icon/icon/Copy.png"),QStringLiteral("清除内容"),this);
    subMenu->addAction(refreshAct);
    subMenu->addAction(printAct);
    subMenu->addAction(clearFormattingAct);
    connect(refreshAct,SIGNAL(triggered(bool)),this,SLOT(refreshReportWidget()));
    //connect(printAct,SIGNAL(triggered(bool)),this,SLOT(refreshReportWidget()));
    //connect(printAct,SIGNAL(triggered(bool)),this,SLOT(refreshReportWidget()));
    subMenu->addSeparator();


    QAction* printDialogAct = new QAction(this);
    printDialogAct->setIcon(QIcon(":/icon/icon/PrintDialogAccess.png"));
    printDialogAct->setText(QStringLiteral("快速打印"));
    subMenu->addAction(printDialogAct);

    QAction* printOptionAct = new QAction(this);
    printOptionAct->setIcon(QIcon(":/icon/icon/PrintOptionsMenuWord.png"));
    printOptionAct->setText(QStringLiteral("打印选项"));
    subMenu->addAction(printOptionAct);

    QAction* printPreviewAct = new QAction(this);
    printPreviewAct->setIcon(QIcon(":/icon/icon/PrintPreviewZoomMenu.png"));
    printPreviewAct->setText(QStringLiteral("打印预览"));
    subMenu->addAction(printPreviewAct);


    subMenu->popup(event->globalPos());
}
