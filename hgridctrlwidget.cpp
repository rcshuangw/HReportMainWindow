#include "hgridctrlwidget.h"
#include "hgridctrl.h"
#include "hgridctrlhelper.h"
#include "hformatdef.h"
#include "hformatset.h"
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenu>
#include "SARibbonMenu.h"
HGridCtrlWidget::HGridCtrlWidget(HReportManager* mgr,QWidget* parent)
 :m_pReportManager(mgr),QWidget(parent)
{
    m_bEnableShowEditBar = false;
    m_bEnableShowTab = false;
    m_bEnableVirtualMode = false;
    m_pGridCtrl = new HGridCtrl;
}

HGridCtrlWidget::~HGridCtrlWidget()
{
    if(m_pGridCtrl)
    {
        delete m_pGridCtrl;
        m_pGridCtrl = NULL;
    }
}

void HGridCtrlWidget::initReportWidget()
{
    QVBoxLayout* vBoxLayout = new QVBoxLayout(this);
    vBoxLayout->setContentsMargins(0, 0, 0, 0);
    if(m_bEnableShowEditBar)
    {
        QHBoxLayout* hBoxLayout = new QHBoxLayout();
        m_rowColLabel = new QLabel(this);
        m_rowColLabel->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(12);
        m_rowColLabel->setFont(font);
        m_rowColLabel->setFrameShape(QFrame::Box);
        m_rowColLabel->setAlignment(Qt::AlignCenter);

        hBoxLayout->addWidget(m_rowColLabel);

        m_inputLineEdit = new QLineEdit(this);
        m_inputLineEdit->setFont(font);
        m_inputLineEdit->setObjectName(QStringLiteral("lineEdit"));

        hBoxLayout->addWidget(m_inputLineEdit);

        hBoxLayout->setStretch(0, 1);
        hBoxLayout->setStretch(1, 9);
        vBoxLayout->addLayout(hBoxLayout);
        vBoxLayout->addWidget(m_pGridCtrl);
        vBoxLayout->setStretch(0,1);
        vBoxLayout->setStretch(1,9);
        int h = vBoxLayout->heightForWidth(m_inputLineEdit->height());
        connect(m_inputLineEdit,SIGNAL(textEdited(QString)),this,SLOT(lineedit_textEdited(QString)));
    }
    else
    {
        vBoxLayout->addWidget(m_pGridCtrl);
    }
    setLayout(vBoxLayout);
    connect(m_pGridCtrl,SIGNAL(clicked(HCellID)),this,SIGNAL(gridcellclicked()));

}

void HGridCtrlWidget::setGridCtrlItem(HGridCtrlInfo* pItem)
{
    if(NULL == pItem) return;
    m_pGridCtrlInfo = pItem;//是通过指针赋值还是直接赋值  --huangw

    m_pGridCtrl->setRowCount(m_pGridCtrlInfo->m_GridCtrlItem.nMaxRow);
    m_pGridCtrl->setColumnCount(m_pGridCtrlInfo->m_GridCtrlItem.nMaxCol);
    m_pGridCtrl->setFixedColumnCount(1);
    m_pGridCtrl->setFixedRowCount(1);
    int row = 0,col = 0;
    //设置固定行列
    for(int i = 0; i < m_pGridCtrlInfo->m_pGridCellItemList.count();i++)
    {
        HGridCellInfo* pInfo = (HGridCellInfo*)m_pGridCtrlInfo->m_pGridCellItemList[i];
        if(!pInfo) continue;
        pInfo->m_GridCellItem.mask = 0;
        row = pInfo->m_GridCellItem.row;
        col = pInfo->m_GridCellItem.col;
        if (row < 1)
        {
            pInfo->m_GridCellItem.mask = GVIF_TEXT|GVIF_FORMAT;
            pInfo->m_GridCellItem.nFormat = QDT_CENTER|QDT_SINGLELINE|QDT_NOPREFIX;
        }
        else if (col < 1)
        {
            pInfo->m_GridCellItem.mask = GVIF_TEXT|GVIF_FORMAT;
            pInfo->m_GridCellItem.nFormat = QDT_CENTER|QDT_SINGLELINE|QDT_NOPREFIX;
        }
        else
        {
            pInfo->m_GridCellItem.mask = GVIF_ALL;
            pInfo->m_GridCellItem.nFormat = QDT_LEFT|QDT_VCENTER|QDT_SINGLELINE|QDT_NOPREFIX;
        }
        m_pGridCtrl->setItem(&pInfo->m_GridCellItem);
    }
    rowColRefresh();
    m_pGridCtrl->autoColumnHeader();
    m_pGridCtrl->autoRowHeader();
}

void HGridCtrlWidget::getGridCtrlItem(HGridCtrlInfo* pItem)
{
    pItem = m_pGridCtrlInfo;
    for(int i = 0; i < m_pGridCtrlInfo->m_pGridCellItemList.count();i++)
    {
        HGridCellInfo* pInfo = (HGridCellInfo*)m_pGridCtrlInfo->m_pGridCellItemList[i];
        if(pInfo) continue;
        //pInfo->m_GridCellItem.row = row;
        //pInfo->m_GridCellItem.col = col;
        m_pGridCtrl->item(&pInfo->m_GridCellItem);
    }
}

/*
void HGridCtrlWidget::gridCell_clicked(HCellID cellID)
{
    emit gridcellclicked(cellID);
}*/

void HGridCtrlWidget::enableShowEditBar(bool b)
{
    m_bEnableShowEditBar = b;
}

void HGridCtrlWidget::enableShowTab(bool b)
{
    m_bEnableShowTab = b;
}

void HGridCtrlWidget::setVirtualMode(bool b)
{
    m_bEnableVirtualMode = b;
    m_pGridCtrl->setVirtualMode(b);
}

//以下属性是打印表格所用
void HGridCtrlWidget::enableHorizontalHeader(bool bEnable)
{
    m_bHorizontalHeader = bEnable;
}

void HGridCtrlWidget::enableVerticalHeader(bool bEnable)
{

    m_bVerticalHeader = bEnable;
}

void HGridCtrlWidget::enablePrintColour(bool b)
{

}

void HGridCtrlWidget::enableShowGrids(bool b)
{

}

void HGridCtrlWidget::rowColRefresh()
{
    if(m_bHorizontalHeader)
        m_pGridCtrl->setColumnWidth(0,25);
    else
        m_pGridCtrl->setColumnWidth(0,0);

    if(!m_bVerticalHeader)
        m_pGridCtrl->setRowHeight(0,0);
    else
    {
        m_pGridCtrl->setRowHeight(0,m_pGridCtrl->defCellHeight());
    }
}

void HGridCtrlWidget::setPrintFormat(HFormatSet *pFormatSet)
{
    if(!pFormatSet)
        return;
    enableHorizontalHeader(pFormatSet->isPageShowRowHeader());
    enableVerticalHeader(pFormatSet->isPageShowColumnHeader());
    enableShowGrids(pFormatSet->isPageShowGrid());
    enablePrintColour(pFormatSet->isPagePrintColour());
    rowColRefresh();
}

//以上属性是打印表格所用

//设置编辑框单项
void HGridCtrlWidget::setCellFormat(HFormatSet* pFormatSet,uint formatType,bool bAll)
{
    if(!pFormatSet)
        return;
    HCellRange range = m_pGridCtrl->selectedCellRange();
    if(!range.isValid())
        return;

    //以下部分必须是单独设置
    if(CELL_TYPE_RESET == formatType)
    {
        if(pFormatSet->isResetFormat())
        {
            m_pGridCtrl->clearFormats(range);
        }
        else if(pFormatSet->isResetText())
        {
            m_pGridCtrl->clearFormatting(range);
        }
        else if(pFormatSet->isResetAllFormat())
        {
            m_pGridCtrl->clearCells(range);
        }
        return;
    }
    else if((formatType == GRID_TYPE_ROW_HEIGHT))
    {
        for(int rangeRow = range.minRow(); rangeRow <= range.maxRow();rangeRow++)
            m_pGridCtrl->setRowHeight(rangeRow,pFormatSet->cellRowHeight());
        return;
    }

    else if(formatType == GRID_TYPE_COL_WIDTH)
    {
        for(int rangeCol = range.minCol();rangeCol <= range.maxCol();rangeCol++)
            m_pGridCtrl->setColumnWidth(rangeCol,pFormatSet->cellColumnWidth());

        return;
    }

    //以下部分可以单独设置也可以通过单元格属性框确认后设置
    for(int rangeRow = range.minRow(); rangeRow <= range.maxRow();rangeRow++)
    {
        for(int rangeCol = range.minCol();rangeCol <= range.maxCol();rangeCol++)
        {
            HGridCellBase* pCell = m_pGridCtrl->getCell(rangeRow,rangeCol);
            if(NULL == pCell) return;
            if((CELL_TYPE_ALIGNMENT == formatType) |(CELL_TYPE_AUTOWRAPTEXT == formatType)| bAll)
            {
                pCell->setFormat(pFormatSet->format());
            }

            if((CELL_TYPE_FONT == formatType) | bAll)
            {
                pCell->setFont(pFormatSet->formatFont());
            }

            if((CELL_TYPE_BORDER == formatType) | bAll)
            {
                //外边框
                if(pFormatSet->isBorderOutSide())
                {
                    if(rangeRow == range.minRow())
                    {
                        pCell->setBorderTopColor(pFormatSet->borderTopLineColor());
                        pCell->setBorderTopStyle(pFormatSet->borderTopPenStyle());
                        pCell->setDrawBorderTop(pFormatSet->isBorderOutSide());
                    }

                    if(rangeRow == range.maxRow())//最大行的下一个单元格
                    {
                        pCell->setBorderBottomColor(pFormatSet->borderBottomLineColor());
                        pCell->setBorderBottomStyle(pFormatSet->borderBottomPenStyle());
                        pCell->setDrawBorderBottom(pFormatSet->isBorderOutSide());
                    }

                    if(rangeCol == range.minCol())
                    {
                        pCell->setBorderLeftColor(pFormatSet->borderLeftLineColor());
                        pCell->setBorderLeftStyle(pFormatSet->borderLeftPenStyle());
                        pCell->setDrawBorderLeft(pFormatSet->isBorderOutSide());
                    }

                    if(rangeCol == range.maxCol())
                    {
                        pCell->setBorderRightColor(pFormatSet->borderRightLineColor());
                        pCell->setBorderRightStyle(pFormatSet->borderRightPenStyle());
                        pCell->setDrawBorderRight(pFormatSet->isBorderOutSide());
                    }
                }
                else
                {
                    //pCell->setBorderColor(pFormatSet->borderLineColor());
                    //pCell->setBorderStyle(pFormatSet->borderPenStyle());
                    //pCell->setDrawBorder(pFormatSet->isBorder());
                    pCell->setBorderLeftColor(pFormatSet->borderLeftLineColor());
                    pCell->setBorderLeftStyle(pFormatSet->borderLeftPenStyle());
                    pCell->setDrawBorderLeft(pFormatSet->isBorderLeft());
                    pCell->setBorderRightColor(pFormatSet->borderRightLineColor());
                    pCell->setBorderRightStyle(pFormatSet->borderRightPenStyle());
                    pCell->setDrawBorderRight(pFormatSet->isBorderRight());
                    pCell->setBorderTopColor(pFormatSet->borderTopLineColor());
                    pCell->setBorderTopStyle(pFormatSet->borderTopPenStyle());
                    pCell->setDrawBorderTop(pFormatSet->isBorderTop());
                    pCell->setBorderBottomColor(pFormatSet->borderBottomLineColor());
                    pCell->setBorderBottomStyle(pFormatSet->borderBottomPenStyle());
                    pCell->setDrawBorderBottom(pFormatSet->isBorderBottom());
                }

                //最小行的上一个单元格
                if(rangeRow == range.minRow())
                {
                    HGridCellBase* pRowOutCell = m_pGridCtrl->getCell(rangeRow-1,rangeCol);
                    if(pRowOutCell)
                    {
                        pRowOutCell->setDrawBorderBottom(pCell->isDrawBorderTop());
                        pRowOutCell->setBorderBottomColor(pCell->borderTopColor());
                        pRowOutCell->setBorderBottomStyle(pCell->borderTopStyle());
                    }
                }

                if(rangeRow == range.maxRow())//最大行的下一个单元格
                {
                    HGridCellBase* pRowOutCell = m_pGridCtrl->getCell(rangeRow+1,rangeCol);
                    if(pRowOutCell)
                    {
                        pRowOutCell->setDrawBorderTop(pCell->isDrawBorderBottom());
                        pRowOutCell->setBorderTopColor(pCell->borderBottomColor());
                        pRowOutCell->setBorderTopStyle(pCell->borderBottomStyle());
                    }
                }

                if(rangeCol == range.minCol())
                {
                    HGridCellBase* pRowOutCell = m_pGridCtrl->getCell(rangeRow,rangeCol-1);
                    if(pRowOutCell)
                    {
                        pRowOutCell->setDrawBorderRight(pCell->isDrawBorderLeft());
                        pRowOutCell->setBorderRightColor(pCell->borderLeftColor());
                        pRowOutCell->setBorderRightStyle(pCell->borderLeftStyle());
                    }
                }

                if(rangeCol == range.maxCol())
                {
                    HGridCellBase* pRowOutCell = m_pGridCtrl->getCell(rangeRow,rangeCol+1);
                    if(pRowOutCell)
                    {
                        pRowOutCell->setDrawBorderLeft(pCell->isDrawBorderRight());
                        pRowOutCell->setBorderLeftColor(pCell->borderRightColor());
                        pRowOutCell->setBorderLeftStyle(pCell->borderRightStyle());
                    }
                }
            }

            if((CELL_TYPE_COLOR == formatType) | bAll)
            {
                pCell->setTextClr(pFormatSet->textColor());
                pCell->setBackClr(pFormatSet->textBkColor());
            }
        }
    }
    //如果类型时GRID_TYPE_ALL 则打印相关的设置都要增加
}

//获取cell表格的属性
void HGridCtrlWidget::cellFormat(HFormatSet* pFormatSet)
{
    if(!pFormatSet)
        return;
    HCellID cellID = m_pGridCtrl->focusCell();
    if(!cellID.isValid()) return;
    HGridCellBase* pCell = m_pGridCtrl->getCell(cellID);
    if(!pCell) return;

    pFormatSet->setText(pCell->text());
    //字体 + 字体颜色
    pFormatSet->setFormatFont(pCell->font());
    pFormatSet->setTextColor(pCell->textClr().name());
    pFormatSet->setTextBkColor(pCell->backClr().name());

    //边框
    //pFormatSet->setBorderPenStyle(pCell->borderStyle());
    pFormatSet->setBorderLeftPenStyle(pCell->borderLeftStyle());
    pFormatSet->setBorderRightPenStyle(pCell->borderRightStyle());
    pFormatSet->setBorderTopPenStyle(pCell->borderTopStyle());
    pFormatSet->setBorderBottomPenStyle(pCell->borderBottomStyle());

    //pFormatSet->enableBorderOutSide(pCell->isDrawBorderOutSide());
    pFormatSet->enableBorderLeft(pCell->isDrawBorderLeft());
    pFormatSet->enableBorderRight(pCell->isDrawBorderRight());
    pFormatSet->enableBorderTop(pCell->isDrawBorderTop());
    pFormatSet->enableBorderBottom(pCell->isDrawBorderBottom());
    //pFormatSet->setBorderLineColor(pCell->borderColor().name());
    pFormatSet->setBorderLeftLineColor(pCell->borderLeftColor().name());
    pFormatSet->setBorderRightLineColor(pCell->borderRightColor().name());
    pFormatSet->setBorderTopLineColor(pCell->borderTopColor().name());
    pFormatSet->setBorderBottomLineColor(pCell->borderBottomColor().name());

    //对齐
    pFormatSet->setFormat(pCell->format());

    //行高列宽
    pFormatSet->setCellRowHeight(m_pGridCtrl->rowHeight(cellID.row));
    pFormatSet->setCellColumnWidth(m_pGridCtrl->columnWidth(cellID.col));

    //合并单元格
    pFormatSet->enableMergeCell(pCell->isMerged());
    //打印相关设置



    //lineedit和行列标签的变化
    if(m_bEnableShowEditBar)
    {
        m_inputLineEdit->setText(pFormatSet->text());
        pCell = m_pGridCtrl->getCell(0,cellID.col);
        if(!pCell) return;
        QString strRow = pCell->text();
        pCell = m_pGridCtrl->getCell(cellID.row,0);
        if(!pCell) return;
        QString strCol = pCell->text();
        m_rowColLabel->setText(strRow+strCol);
    }
}

bool HGridCtrlWidget::mergeCell()
{
    HCellRange range = m_pGridCtrl->selectedCellRange();
    if(!range.isValid() || range.count() <=1)
        return false;
    m_pGridCtrl->setMergeSelectedCells();
    return true;
}

bool HGridCtrlWidget::splitCell()
{
    HCellRange range = m_pGridCtrl->selectedCellRange();
    if(!range.isValid())
        return false;
    m_pGridCtrl->setSplitSelectedCells();
    return true;
}

//行列插入最后位置
bool HGridCtrlWidget::insertGridRow()
{
    HCellRange range = m_pGridCtrl->selectedCellRange();
    if(!range.isValid())
        return false;
    int nStartRow = range.minRow();
    int nRowNum = range.maxRow() - range.minRow() + 1;
    if(m_pGridCtrl->rowCount() + nRowNum > ROWMAX_COUNT)
        return false;

    for(int i = 0; i < nRowNum; i++)
    {
       if((int)-1 == m_pGridCtrl->insertRow("",nStartRow))//strHeader是插入之后会自动刷新
           return false;
    }
    m_pGridCtrl->setSelectedRange(range);
    return true;
}


bool HGridCtrlWidget::insertGridColumn()
{
    HCellRange range = m_pGridCtrl->selectedCellRange();
    if(!range.isValid())
        return false;
    int nStartCol = range.minCol();
    int nColNum = range.maxCol() - range.minCol() + 1;
    if(m_pGridCtrl->columnCount() + nColNum > COLMAX_COUNT)
        return false;

    quint32 nFormat = m_pGridCtrl->defaultCell(false,false)->format();
    for(int i = 0; i < nColNum; i++)
    {
       if((int)-1 == m_pGridCtrl->insertColumn("",nFormat,nStartCol))//strHeader是插入之后会自动刷新
           return false;
    }
    m_pGridCtrl->setSelectedRange(range);
    return true;
}

//删除行列
bool HGridCtrlWidget::removeGridRow()
{
    HCellRange range = m_pGridCtrl->selectedCellRange();
    if(!range.isValid())
        return false;
    for(int row = range.minRow(); row <= range.maxRow(); row++)
    {
       if(!m_pGridCtrl->deleteRow(row))//strHeader是插入之后会自动刷新
           return false;
    }
    return true;
}

bool HGridCtrlWidget::removeGridColumn()
{
    HCellRange range = m_pGridCtrl->selectedCellRange();
    if(!range.isValid())
        return false;
    for(int col = range.minCol(); col <= range.maxCol(); col++)
    {
       if(!m_pGridCtrl->deleteColumn(col))//strHeader是插入之后会自动刷新
           return false;
    }
    return true;
}

void HGridCtrlWidget::autoSizeRows()
{
    if(!m_pGridCtrl)
        return;
    m_pGridCtrl->autoSizeRows();
}

void HGridCtrlWidget::autoSizeColumns()
{
    if(!m_pGridCtrl)
        return;
    m_pGridCtrl->autoSizeColumns();
}

void HGridCtrlWidget::lineedit_textEdited(const QString &text)
{
    HCellID cellID = m_pGridCtrl->focusCell();
    if(!cellID.isValid()) return;
    HGridCellBase* pCell = m_pGridCtrl->getCell(cellID);
    if(!pCell) return;
    pCell->setText(text);
}


void HGridCtrlWidget::contextMenuEvent(QContextMenuEvent *event)
{
    if(m_bEnableShowEditBar)
        contextEditorMenuEvent(event);
    else
        contextBrowserMenuEvent(event);
}

void HGridCtrlWidget::contextEditorMenuEvent(QContextMenuEvent* event)
{
    QPoint pt = event->pos();
    pt.setY(pt.y() - 27);//27是QLabel和QLineEdit的高度，直接取控件高度好像不准
    HCellRange cellRange = m_pGridCtrl->selectedCellRange();
    if(!cellRange.isValid()) return;
    QRect cellRect;
    m_pGridCtrl->cellRangeRect(cellRange,cellRect);


    if(!cellRect.contains(pt))
        return;
    //

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

void HGridCtrlWidget::contextBrowserMenuEvent(QContextMenuEvent* event)
{
    QPoint pt = event->pos();
    HCellRange cellRange = m_pGridCtrl->selectedCellRange();
    if(!cellRange.isValid()) return;
    QRect cellRect;
    m_pGridCtrl->cellRangeRect(cellRange,cellRect);


    if(!cellRect.contains(pt))
        return;
    //

    SARibbonMenu *subMenu = new SARibbonMenu(this);

    QAction* loadAct = new QAction(QIcon(":/icon/icon/selectSheet.png"),QStringLiteral("选择操作票"),this);
    QAction* preSheetAct = new QAction(QIcon(":/icon/icon/previousSheet.png"),QStringLiteral("前一张操作票"),this);
    QAction* nextSheetAct = new QAction(QIcon(":/icon/icon/nextSheet.png"),QStringLiteral("后一张操作票"),this);
    subMenu->addAction(loadAct);
    subMenu->addAction(preSheetAct);
    subMenu->addAction(nextSheetAct);
    subMenu->addSeparator();

    QAction* refreshAct = new QAction(QIcon(":/icon/icon/Refresh.png"),QStringLiteral("刷新"),this);
    QAction* printAct = new QAction(QIcon(":/icon/icon/OpSheet.png"),QStringLiteral("显示设置"),this);
    QAction* copyAct = new QAction(QIcon(":/icon/icon/Copy.png"),QStringLiteral("清除内容"),this);
    subMenu->addAction(refreshAct);
    subMenu->addAction(printAct);
    subMenu->addAction(copyAct);
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

