#include "hreporteditorwidget.h"
#include "hgridreportwidget.h"
#include "hgridreportmgr.h"
#include "hgridctrlhelper.h"
#include "hgridctrlhelper.h"
#include "hformatdef.h"
#include "hformatset.h"
#include "SARibbonMenu.h"
#include <QHBoxLayout>
HReportEditorWidget::HReportEditorWidget(HReportManager* mgr,QWidget *parent)
   :m_pReportManager(mgr),QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    m_pGridReportWidget = new HGridReportWidget(this);
    m_pGridReportWidget->setEditorGridReportAttr();
    layout->setContentsMargins(3, 3, 3, 3);
    layout->addWidget(m_pGridReportWidget);
    m_pGridReportWidget->hide();
    setLayout(layout);
    connect(m_pGridReportWidget,SIGNAL(gridcellclicked()),this,SIGNAL(gridcellclicked()));
}

HReportEditorWidget::~HReportEditorWidget()
{

}

void HReportEditorWidget::newReportWidget(quint16 wReportID)
{
    if(!m_pReportManager || !m_pReportManager->gridCtrlFile())
        return;
    saveReportWidget();
    m_wReportID = wReportID;
    HGridCtrlInfo* pInfo = m_pReportManager->gridCtrlFile()->getGridCtrlInfoById(m_wReportID);
    if(!pInfo) return;
    m_pGridReportWidget->setMaxRow(pInfo->m_GridCtrlItem.nMaxRow);
    m_pGridReportWidget->setMaxCol(pInfo->m_GridCtrlItem.nMaxCol);
    m_pGridReportWidget->setNumSheet(1);
    m_pGridReportWidget->init();//此时无文件需用默认值初始化
    m_pGridReportWidget->show();
}

void HReportEditorWidget::openReportWidget(quint16 wReportID)
{
    if(!m_pReportManager || !m_pReportManager->gridCtrlFile())
        return;
    saveReportWidget();
    m_wReportID = wReportID;
    HGridCtrlInfo* pInfo = m_pReportManager->gridCtrlFile()->getGridCtrlInfoById(m_wReportID);
    if(!pInfo) return;
    m_pGridReportWidget->setMaxRow(pInfo->m_GridCtrlItem.nMaxRow);
    m_pGridReportWidget->setMaxCol(pInfo->m_GridCtrlItem.nMaxCol);
    m_pReportManager->gridCtrlFile()->loadRelateVarFile(m_wReportID);
    m_pGridReportWidget->setNumSheet(1);
    m_pGridReportWidget->update();//需要从文件中读取
    for(int i = 0; i < m_pReportManager->gridCtrlFile()->m_pRelateVarList.count();i++)
    {
        HRelateVar* pVar =  m_pReportManager->gridCtrlFile()->m_pRelateVarList.at(i);
        if(!pVar) continue;
        int row = pVar->row();
        int col = pVar->col();
        QString str = pVar->desc();
        m_pGridReportWidget->setText(row,col,str);
    }
    m_pGridReportWidget->show();
}

void HReportEditorWidget::saveReportWidget()
{
    if(!m_pReportManager || !m_pReportManager->gridCtrlFile())
        return;
    //先存变量
    m_pReportManager->gridCtrlFile()->saveRelateVarFile(m_wReportID);
    char szFile[256],szPath[256];
    getDataFilePath(DFPATH_REPORT,szPath);
    sprintf(szFile,"%s%s%6u%s",szPath,"RPT",m_wReportID,".rpt");
    //存表格
    m_pGridReportWidget->save(QString(szFile));
    //存表格信息
    m_pReportManager->gridCtrlFile()->saveGridCtrlInfoFile();
}

void HReportEditorWidget::delReportWidget()
{
    if(!m_pReportManager)
        return;
    m_pGridReportWidget->clear();
}

void HReportEditorWidget::contextMenuEvent(QContextMenuEvent* event)
{
    QPoint pt = event->pos();
    pt.setY(pt.y() - 30);//27是QLabel和QLineEdit的高度，直接取控件高度好像不准
    QRect cellRect;
    m_pGridReportWidget->selectedRect(cellRect);
    if(!cellRect.contains(pt))
        return;

    SARibbonMenu *subMenu = new SARibbonMenu(this);
    QAction* setVarAct = new QAction(QIcon(":/icon/icon/insertVar.png"),QStringLiteral("设置变量"),this);
    QAction* delVarAct = new QAction(QIcon(":/icon/icon/removeVar.png"),QStringLiteral("删除变量"),this);
    subMenu->addAction(setVarAct);
    subMenu->addAction(delVarAct);
    subMenu->addSeparator();

    QAction* pasteAct = new QAction(this);
    pasteAct->setIcon(QIcon(":/icon/icon/Paste.png"));
    pasteAct->setText(QStringLiteral("粘贴"));
    QAction* cutAct = new QAction(this);
    cutAct->setIcon(QIcon(":/icon/icon/Cut.png"));
    cutAct->setText(QStringLiteral("剪切"));
    QAction* copyAct = new QAction(this);
    copyAct->setIcon(QIcon(":/icon/icon/Copy.png"));
    copyAct->setText(QStringLiteral("拷贝"));
    subMenu->addAction(cutAct);
    subMenu->addAction(copyAct);
    subMenu->addAction(pasteAct);
    subMenu->addSeparator();

    SARibbonMenu* insertMenu = subMenu->addRibbonMenu(QIcon(":/icon/icon/sCellsInsertDialog.png"),QStringLiteral("插入"));
    QAction* insertRowAct = new QAction(QIcon(":/icon/icon/InsertRow.png"),QStringLiteral("插入行"),this);
    QAction* insertColAct = new QAction(QIcon(":/icon/icon/InsertColumn.png"),QStringLiteral("插入列"),this);
    insertMenu->addAction(insertRowAct);
    insertMenu->addAction(insertColAct);
    SARibbonMenu* removeMenu = subMenu->addRibbonMenu(QIcon(":/icon/icon/sCellsDelete.png"),QStringLiteral("删除"));
    QAction* removeRowAct = new QAction(QIcon(":/icon/icon/RemoveRow.png"),QStringLiteral("删除行"),this);
    QAction* removeColAct = new QAction(QIcon(":/icon/icon/RemoveColumn.png"),QStringLiteral("删除列"),this);
    removeMenu->addAction(removeRowAct);
    removeMenu->addAction(removeColAct);
    QAction *clearFormatingAct = new QAction(QIcon(":/icon/icon/ClearFormatting.png"),QStringLiteral("清除内容"),this);
    subMenu->addRibbonMenu(insertMenu);
    subMenu->addRibbonMenu(removeMenu);
    subMenu->addAction(clearFormatingAct);
    subMenu->addSeparator();

    subMenu->popup(event->globalPos());
}

void HReportEditorWidget::paste()
{
    m_pGridReportWidget->paste();
}

void HReportEditorWidget::cut()
{

}

void HReportEditorWidget::copy()
{

}

//设置编辑框单项
void HReportEditorWidget::setCellFormat(HFormatSet* pFormatSet,uint formatType,bool bAll)
{
    if(!pFormatSet)
        return;

    //以下部分必须是单独设置
    if(CELL_TYPE_RESET == formatType)
    {
        if(pFormatSet->isResetFormat())
        {
            m_pGridReportWidget->enableResetFormat(true);
        }
        else if(pFormatSet->isResetText())
        {
            m_pGridReportWidget->enableResetText(true);
        }
        else if(pFormatSet->isResetAllFormat())
        {
            m_pGridReportWidget->enableResetAllFormat(true);
        }
        return;
    }
    else if((formatType == GRID_TYPE_ROW_HEIGHT))
    {
        m_pGridReportWidget->setRowHeight(pFormatSet->cellRowHeight());
        return;
    }

    else if(formatType == GRID_TYPE_COL_WIDTH)
    {
        m_pGridReportWidget->setColumnWidth(pFormatSet->cellColumnWidth());
        return;
    }

    //带all的
    if((CELL_TYPE_ALIGNMENT == formatType) |(CELL_TYPE_AUTOWRAPTEXT == formatType)| bAll)
    {
        m_pGridReportWidget->setFormat(pFormatSet->format());
    }

    if((CELL_TYPE_FONT == formatType) | bAll)
    {
        m_pGridReportWidget->setFont(pFormatSet->formatFont());
    }

    if((CELL_TYPE_BORDER == formatType) | bAll)
    {
        GV_BORDER_ITEM borderItem;
        borderItem.bBorderOutSide = pFormatSet->isBorderOutSide();
        borderItem.bBorderLeft = pFormatSet->isBorderLeft();
        borderItem.bBorderTop = pFormatSet->isBorderTop();
        borderItem.bBorderRight = pFormatSet->isBorderRight();
        borderItem.bBorderBottom = pFormatSet->isBorderBottom();
        borderItem.nLeftBorderStyle = pFormatSet->borderLeftPenStyle();
        borderItem.strLeftBoderClr = pFormatSet->borderLeftLineColor();
        borderItem.nRightBorderStyle = pFormatSet->borderRightPenStyle();
        borderItem.strRightBoderClr = pFormatSet->borderRightLineColor();
        borderItem.nTopBorderStyle = pFormatSet->borderTopPenStyle();
        borderItem.strTopBoderClr = pFormatSet->borderTopLineColor();
        borderItem.nBottomBorderStyle = pFormatSet->borderBottomPenStyle();
        borderItem.strBottomBoderClr = pFormatSet->borderBottomLineColor();
        m_pGridReportWidget->setBorder(&borderItem);
    }

    if((CELL_TYPE_COLOR == formatType) | bAll)
    {
        m_pGridReportWidget->setTextColor(pFormatSet->textColor());
        m_pGridReportWidget->setTextBkColor(pFormatSet->textBkColor());
    }
}

//获取cell表格的属性
void HReportEditorWidget::cellFormat(HFormatSet* pFormatSet)
{
    if(!pFormatSet)
        return;

    //pFormatSet->setText(pCell->text());
    //字体 + 字体颜色
    pFormatSet->setFormatFont(m_pGridReportWidget->font());
    pFormatSet->setTextColor(m_pGridReportWidget->textColor());
    pFormatSet->setTextBkColor(m_pGridReportWidget->textBkColor());

    //边框
    GV_BORDER_ITEM item;
    m_pGridReportWidget->getBorder(&item);
    pFormatSet->setBorderLeftPenStyle(item.nLeftBorderStyle);
    pFormatSet->setBorderRightPenStyle(item.nRightBorderStyle);
    pFormatSet->setBorderTopPenStyle(item.nTopBorderStyle);
    pFormatSet->setBorderBottomPenStyle(item.nBottomBorderStyle);

    pFormatSet->enableBorderLeft(item.bBorderLeft);
    pFormatSet->enableBorderRight(item.bBorderRight);
    pFormatSet->enableBorderTop(item.bBorderTop);
    pFormatSet->enableBorderBottom(item.bBorderBottom);

    pFormatSet->setBorderLeftLineColor(item.strLeftBoderClr);
    pFormatSet->setBorderRightLineColor(item.strRightBoderClr);
    pFormatSet->setBorderTopLineColor(item.strTopBoderClr);
    pFormatSet->setBorderBottomLineColor(item.strBottomBoderClr);

    //对齐
    pFormatSet->setFormat(m_pGridReportWidget->format());

    //行高列宽
    pFormatSet->setCellRowHeight(m_pGridReportWidget->rowHeight());
    pFormatSet->setCellColumnWidth(m_pGridReportWidget->columnWidth());

    //合并单元格
    pFormatSet->enableMergeCell(m_pGridReportWidget->isMerged());
    //打印相关设置
}

//操作
bool HReportEditorWidget::mergeCell()
{
    return m_pGridReportWidget->mergeCell();
}

bool HReportEditorWidget::splitCell()
{
    return m_pGridReportWidget->splitCell();
}

bool HReportEditorWidget::insertGridRow()
{
    return m_pGridReportWidget->insertGridRow();
}

bool HReportEditorWidget::insertGridColumn()
{
    return m_pGridReportWidget->insertGridColumn();
}

bool HReportEditorWidget::removeGridRow()
{
    return m_pGridReportWidget->removeGridRow();
}

bool HReportEditorWidget::removeGridColumn()
{
    return m_pGridReportWidget->removeGridColumn();
}

void HReportEditorWidget::autoSizeRows()
{
    m_pGridReportWidget->autoSizeRows();
}

void HReportEditorWidget::autoSizeColumns()
{
    m_pGridReportWidget->autoSizeColumns();
}
