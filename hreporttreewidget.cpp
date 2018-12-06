#include "hreporttreewidget.h"
#include "hgridctrlhelper.h"
#include "hgridreportmgr.h"
#include <QAction>
#include <QMenu>
#include <QHeaderView>
HReportTreeWidget::HReportTreeWidget(HReportManager* mgr,QWidget *parent)
    :m_pReportMgr(mgr),QTreeWidget(parent)
{
    initReportTreeWidget();
}

void HReportTreeWidget::initReportTreeWidget()
{
    if(!m_pReportMgr)
        return;
    headerItem()->setText(0,QStringLiteral("报表模板"));
    QTreeWidgetItem* rootItem = new QTreeWidgetItem(this,0);
    rootItem->setText(0,QStringLiteral("厂站报表模板总览"));
    rootItem->setIcon(0,QIcon(":/images/Folder.png"));
    //rootItem->setGraphTreeID(9999);
    addTopLevelItem(rootItem);
    //expandItem(rootItem);

    HGridCtrlFile* doc = m_pReportMgr->gridCtrlFile();
    if(!doc) return;
    //QList<HGraph*> graphList = doc->getGraphList();
    for(int i = 0; i < doc->m_pGridCtrlInfoList.count();i++)
    {
        HGridCtrlInfo* gridCtrlInfo = (HGridCtrlInfo*)doc->m_pGridCtrlInfoList[i];
        if(!gridCtrlInfo)
            continue;
        QTreeWidgetItem* newItem = new QTreeWidgetItem(rootItem,1);
        //newItem->setGraphTreeID(gridCtrlInfo->m_GridCtrlItem.wReportID);
        newItem->setText(0,gridCtrlInfo->m_GridCtrlItem.strReportName);
        newItem->setIcon(0,QIcon(":/tree/icon/spreadsheets.png"));
        rootItem->addChild(newItem);
    }
    //connect(this,SIGNAL(itemClicked(QTreeWidgetItem*,int)),SLOT(clickReportItem(QTreeWidgetItem*,int)));
}

void HReportTreeWidget::addReportTreeWidgetItem()
{
    if(!m_pReportMgr || !m_pReportMgr->gridCtrlFile())
        return;
    QTreeWidgetItem *parentItem = (QTreeWidgetItem*)topLevelItem(0);
    //int type = parentItem->type();
    if(!parentItem )
        return;

    HGridCtrlInfo* pInfo = m_pReportMgr->gridCtrlFile()->getCurGridCtrlInfo();

    QTreeWidgetItem* newItem = new QTreeWidgetItem(parentItem,1);
    //newItem->setGraphTreeID(pInfo->m_GridCtrlItem.wReportID);
    newItem->setText(0,pInfo->m_GridCtrlItem.strReportName);
    newItem->setIcon(0,QIcon(":/tree/icon/spreadsheets.png"));
    parentItem->addChild(newItem);
    expandItem(newItem);
    setCurrentItem(newItem);
    //emit itemClicked(newItem,0);
}

void HReportTreeWidget::delReportTreeWidgetItem()
{
    if(!m_pReportMgr)
        return;
    QTreeWidgetItem *curItem = (QTreeWidgetItem*)currentItem();
    if(!curItem || curItem->type() != 1) return;
    QTreeWidgetItem *parentItem = (QTreeWidgetItem*)curItem->parent();
    QTreeWidgetItem* childItem = dynamic_cast<QTreeWidgetItem*>(curItem->child(0));
    if(!childItem)
        return;
    parentItem->removeChild(curItem);
    delete curItem;
    curItem = NULL;
    setCurrentItem(parentItem);
}

void HReportTreeWidget::importReportTreeWigetItem()
{

}

void HReportTreeWidget::contextMenuEvent(QContextMenuEvent *event)
{

}

void HReportTreeWidget::initReportMenu(QContextMenuEvent* event)
{
    QMenu* menu = new QMenu;
    QAction *newAct = new QAction(QStringLiteral("新建表格文件"),this);
    newAct->setStatusTip(QStringLiteral("新建一个表格模板文件"));
    menu->addAction(newAct);
    connect(newAct,SIGNAL(triggered(bool)),SLOT(newReport()));

    QAction *importFileAct = new QAction(QStringLiteral("导入表格模板"),this);
    importFileAct->setStatusTip(QStringLiteral("导入一个表格模板文件"));
    menu->addAction(importFileAct);
    connect(importFileAct,SIGNAL(triggered(bool)),this,SLOT(importReportFile()));
    menu->popup(event->globalPos());
}

void HReportTreeWidget::intReportFileMenu(QContextMenuEvent* event)
{
    QMenu* menu = new QMenu;
    QAction *delAct = new QAction(QStringLiteral("删除表格模板"),this);
    delAct->setStatusTip(QStringLiteral("删除一个表格模板文件"));
    menu->addAction(delAct);
    connect(delAct,SIGNAL(triggered(bool)),SLOT(delGraph()));
    menu->addSeparator();
    QAction *saveAsAct = new QAction(QStringLiteral("另存表格模板为"),this);
    saveAsAct->setStatusTip(QStringLiteral("另存一个表格模板文件"));
    menu->addAction(saveAsAct);

    menu->popup(event->globalPos());
}

void HReportTreeWidget::newReport()
{

}

void HReportTreeWidget::openReport()
{

}

void HReportTreeWidget::delReport()
{

}


void HReportTreeWidget::saveAsReport()
{

}

void HReportTreeWidget::importReportFile()
{

}

void HReportTreeWidget::clickReportItem(QTreeWidgetItem*,int)
{

}

void HReportTreeWidget::changedReportItem(QTreeWidgetItem*,QTreeWidgetItem*)
{

}
