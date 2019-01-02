#include "hgridctrlwidget.h"
#include "hgridctrl.h"
#include "hgridctrlhelper.h"
#include "hformatdef.h"
#include "hformatset.h"
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
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

    m_pGridCtrl->setRowCount(m_pGridCtrlInfo->m_GridCtrlItem.nMaxRow + 1);
    m_pGridCtrl->setColumnCount(m_pGridCtrlInfo->m_GridCtrlItem.nMaxCol + 1);
    m_pGridCtrl->setFixedColumnCount(1);
    m_pGridCtrl->setFixedRowCount(1);
    int row ,col = 0;
    if(1)
    {
        //设置固定行列
        for(int i = 0; i < m_pGridCtrlInfo->m_pGridCellItemList.count();i++)
        {
            HGridCellInfo* pInfo = (HGridCellInfo*)m_pGridCtrlInfo->m_pGridCellItemList[i];
            if(pInfo) continue;
            pInfo->m_GridCellItem.mask = GVIF_TEXT|GVIF_FORMAT;
            row = pInfo->m_GridCellItem.row;
            col = pInfo->m_GridCellItem.col;
            if (row < 1)
            {
                pInfo->m_GridCellItem.nFormat = QDT_LEFT|QDT_WORDBREAK;
                pInfo->m_GridCellItem.strText = QString("%d").arg(row);
            }
            else if (col < 1)
            {
                pInfo->m_GridCellItem.nFormat = QDT_RIGHT|QDT_VCENTER|QDT_SINGLELINE|QDT_NOPREFIX;
                pInfo->m_GridCellItem.strText = QString("%d").arg(col);
            }
            else
            {
                pInfo->m_GridCellItem.nFormat = QDT_CENTER|QDT_VCENTER|QDT_SINGLELINE|QDT_NOPREFIX;
            }
            m_pGridCtrl->setItem(&pInfo->m_GridCellItem);
        }
    }
    //else if(!m_bEnableShowHorHeader && !m_bEnableShowVerHeader)
    {
        for(int i = 0; i < m_pGridCtrlInfo->m_pGridCellItemList.count();i++)
        {
            HGridCellInfo* pInfo = (HGridCellInfo*)m_pGridCtrlInfo->m_pGridCellItemList[i];
            if(pInfo) continue;
            pInfo->m_GridCellItem.mask = GVIF_TEXT|GVIF_FORMAT;
            row = pInfo->m_GridCellItem.row;
            col = pInfo->m_GridCellItem.col;
            pInfo->m_GridCellItem.nFormat = QDT_CENTER|QDT_VCENTER|QDT_SINGLELINE|QDT_NOPREFIX;
            m_pGridCtrl->setItem(&pInfo->m_GridCellItem);
        }
    }
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
    m_pGridCtrl->setVirtualMode(b);
}

//设置单项
void HGridCtrlWidget::setCellFormat(HFormatSet* pFormatSet,uint formatType,bool bAll)
{
    HCellRange range = m_pGridCtrl->selectedCellRange();
    if(!range.isValid())
        return;
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
                pCell->setBorderColor(pFormatSet->borderLineColor());
                pCell->setBorderStyle(pFormatSet->borderPenStyle());
                pCell->setDrawBorder(pFormatSet->isBorder());
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

            if((CELL_TYPE_COLOR == formatType) | bAll)
            {
                pCell->setTextClr(pFormatSet->textColor());
                pCell->setBackClr(pFormatSet->textBkColor());
            }

            if((formatType == GRID_TYPE_ROW_HEIGHT) | bAll)
            {
                m_pGridCtrl->setRowHeight(rangeRow,pFormatSet->cellRowHeight());
            }

            if((formatType == GRID_TYPE_COL_WIDTH)  | bAll)
            {
                m_pGridCtrl->setColumnWidth(rangeCol,pFormatSet->cellColumnWidth());
            }

            if(CELL_TYPE_RESET == formatType)
            {
                if(pFormatSet->isResetFormat())
                {
                    QString strText = pCell->text();
                    pCell->reset();
                    pCell->setText(strText);
                }
                else if(pFormatSet->isResetText())
                {
                    pCell->setText("");
                }
                else if(pFormatSet->isResetAllFormat())
                {
                    pCell->reset();
                }
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
    //字体 + 字体颜色
    pFormatSet->setFormatFont(pCell->font());
    pFormatSet->setTextColor(pCell->textClr().name());
    pFormatSet->setTextBkColor(pCell->backClr().name());

    //边框
    pFormatSet->setBorderPenStyle(pCell->borderStyle());
    pFormatSet->setBorderLeftPenStyle(pCell->borderLeftStyle());
    pFormatSet->setBorderRightPenStyle(pCell->borderRightStyle());
    pFormatSet->setBorderTopPenStyle(pCell->borderTopStyle());
    pFormatSet->setBorderBottomPenStyle(pCell->borderBottomStyle());

    pFormatSet->enableBorder(pCell->isDrawBorder());
    pFormatSet->enableBorderLeft(pCell->isDrawBorderLeft());
    pFormatSet->enableBorderRight(pCell->isDrawBorderRight());
    pFormatSet->enableBorderTop(pCell->isDrawBorderTop());
    pFormatSet->enableBorderBottom(pCell->isDrawBorderBottom());
    pFormatSet->setBorderLineColor(pCell->borderColor().name());
    pFormatSet->setBorderLeftLineColor(pCell->borderLeftColor().name());
    pFormatSet->setBorderRightLineColor(pCell->borderRightColor().name());
    pFormatSet->setBorderTopLineColor(pCell->borderTopColor().name());
    pFormatSet->setBorderBottomLineColor(pCell->borderBottomColor().name());

    //对齐
    pFormatSet->setFormat(pCell->format());

    //打印相关设置

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
    if(!range.isValid() || range.count() <=1 )
        return false;
    m_pGridCtrl->setSplitSelectedCells();
}

//行列插入最后位置
bool HGridCtrlWidget::insertGridRow()
{
    HCellRange range = m_pGridCtrl->selectedCellRange();
    if(!range.isValid())
        return false;
    int nStartRow = range.minRow();
    int nRowNum = range.maxRow() - range.minRow() - 1;
    if(m_pGridCtrl->rowCount() + nRowNum > ROWMAX_COUNT)
        return false;

    for(int i = 0; i < nRowNum; i++)
    {
       if((int)-1 == m_pGridCtrl->insertRow("",nStartRow))//strHeader是插入之后会自动刷新
           return false;
    }
    return true;
}


bool HGridCtrlWidget::insertGridColumn()
{
    HCellRange range = m_pGridCtrl->selectedCellRange();
    if(!range.isValid())
        return false;
    int nStartCol = range.minCol();
    int nColNum = range.maxCol() - range.minCol() - 1;
    if(m_pGridCtrl->columnCount() + nColNum > COLMAX_COUNT)
        return false;

    for(int i = 0; i < nColNum; i++)
    {
       if((int)-1 == m_pGridCtrl->insertRow("",nStartCol))//strHeader是插入之后会自动刷新
           return false;
    }
    return true;
}

//删除行列
bool HGridCtrlWidget::removeGridRow()
{
    HCellRange range = m_pGridCtrl->selectedCellRange();
    if(!range.isValid())
        return false;
    for(int row = range.minRow(); row < range.maxRow(); row++)
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
    for(int col = range.minCol(); col < range.maxCol(); col++)
    {
       if(!m_pGridCtrl->deleteColumn(col))//strHeader是插入之后会自动刷新
           return false;
    }
    return true;
}
