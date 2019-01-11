#include "hreporttreewidget.h"
#include "hgridctrlhelper.h"
#include "hgridreportmgr.h"
#include <QAction>
#include <QMenu>
#include <QHeaderView>
#include <QInputDialog>
#include <QMessageBox>
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
    //setHeaderItem(NULL);
    QTreeWidgetItem* rootItem = new QTreeWidgetItem(this,0);
    rootItem->setText(0,QStringLiteral("厂站报表一览"));
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
        newItem->setData(0,Qt::UserRole,gridCtrlInfo->m_GridCtrlItem.wReportID);
        newItem->setText(0,gridCtrlInfo->m_GridCtrlItem.strReportName);
        newItem->setIcon(0,QIcon(":/tree/icon/spreadsheets.png"));
        rootItem->addChild(newItem);
    }
    //connect(this,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),SLOT(changedReportItem(QTreeWidgetItem*,QTreeWidgetItem*)));
    connect(this,SIGNAL(itemClicked(QTreeWidgetItem*,int)),SLOT(clickReportItem(QTreeWidgetItem*,int)));
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
    newItem->setData(0,Qt::UserRole,pInfo->m_GridCtrlItem.wReportID);
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
    QPoint point = event->pos();
    QTreeWidgetItem* curItem = (QTreeWidgetItem*)itemAt(point);
    if(!curItem)
        return;
    if(1 != curItem->type())
        return;
   initReportTreeWidgetMenu(event);
}

void HReportTreeWidget::initReportTreeWidgetMenu(QContextMenuEvent* event)
{
    //右键菜单只有3个，删除，重命名，导入
    QMenu* menu = new QMenu;
    QAction *renameAct = new QAction(QStringLiteral("重命名表格文件"),this);
    renameAct->setStatusTip(QStringLiteral("重新命名表格模板文件"));
    menu->addAction(renameAct);
    connect(renameAct,SIGNAL(triggered(bool)),this,SLOT(renameReport()));

    QAction *delAct = new QAction(QStringLiteral("删除表格文件"),this);
    delAct->setIcon(QIcon(":/icon/icon/delGrid.png"));
    delAct->setStatusTip(QStringLiteral("删除一个表格模板文件"));
    menu->addAction(delAct);
    connect(delAct,SIGNAL(triggered(bool)),this,SLOT(delReport()));

    menu->addSeparator();

    QAction *importFileAct = new QAction(QStringLiteral("导入表格模板"),this);
    importFileAct->setStatusTip(QStringLiteral("导入一个表格模板文件"));
    menu->addAction(importFileAct);
    connect(importFileAct,SIGNAL(triggered(bool)),this,SLOT(importReportFile()));
    menu->popup(event->globalPos());
}

void HReportTreeWidget::renameReport()
{
    if(!m_pReportMgr || !m_pReportMgr->gridCtrlFile()) return;
    QTreeWidgetItem* curItem = (QTreeWidgetItem*)currentItem();
    if(!curItem)
        return;
    if(1 != curItem->type())
        return;
    QString strOldName = curItem->text(0);
    bool ok;
    QString text = QInputDialog::getText(this, QStringLiteral("重命名设置"),QStringLiteral("新名称:"), QLineEdit::Normal,strOldName, &ok);
    if (ok && !text.isEmpty() && strOldName != text)
    {
        if(m_pReportMgr->gridCtrlFile()->renameGridCtrlInfo(curItem->data(0,Qt::UserRole).toInt(),text))
            curItem->setText(0,text);
    }
}

void HReportTreeWidget::openReport()
{

}

void HReportTreeWidget::delReport()
{
    if(QMessageBox::No == QMessageBox::warning(this, QStringLiteral("警告"),QStringLiteral("确定要删除此表格?"),QMessageBox::Ok | QMessageBox::No))
        return;
    if(!m_pReportMgr || !m_pReportMgr->gridCtrlFile())
        return;
    QTreeWidgetItem* curItem = (QTreeWidgetItem*)currentItem();
    if(!curItem || 1 != curItem->type())
        return;
    QString strName = curItem->text(0);
    int id = curItem->data(0,Qt::UserRole).toInt();
    emit reportDel(strName,id);
    delReportTreeWidgetItem();
}

void HReportTreeWidget::importReportFile()
{

}

void HReportTreeWidget::clickReportItem(QTreeWidgetItem* curItem,int)
{
    if(!m_pReportMgr || !m_pReportMgr->gridCtrlFile())
        return;
    if(!curItem || 1 != curItem->type())
        return;
    QString strName = curItem->text(0);
    int id = curItem->data(0,Qt::UserRole).toInt();
    emit reportOpen(strName,id);
}

void HReportTreeWidget::changedReportItem(QTreeWidgetItem* curItem,QTreeWidgetItem* preItem)
{
    if(!curItem || !preItem || curItem == preItem)
        return;
    if(!m_pReportMgr || !m_pReportMgr->gridCtrlFile())
        return;
    if(1 != curItem->type())
        return;
    QString strName = curItem->text(0);
    int id = curItem->data(0,Qt::UserRole).toInt();
    emit reportOpen(strName,id);
}
