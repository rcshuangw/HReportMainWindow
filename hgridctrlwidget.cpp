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

void HGridCtrlWidget::gridCell_clicked(HGridCell* pCell)
{
    emit gridcellclickded(pCell);
}

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

void HGridCtrlWidget::setCellFormat(uint formatType,HFormatSet* pFormatSet)
{
    HCellRange range = m_pGridCtrl->selectedCellRange();
    if(!range.isValid())
        return;
    for(int rangeRow = range.minRow(); rangeRow <= range.maxRow();rangeRow++)
    {
        for(int rangeCol = range.minCol();rangeCol <= range.maxCol();rangeCol++)
        {
            GV_ITEM pItem;
            pItem.row = rangeRow;
            pItem.col = rangeCol;
            bool bok = m_pGridCtrl->item(&pItem);
            HGridCellBase* pCell = m_pGridCtrl->getCell(rangeRow,rangeCol);
            if(bok)
            {
                if(formatType == CELL_TYPE_HORIZONTAL)
                {
                    int horizontalAlign = pFormatSet->horizontalAlign();
                    setHorizontalAlign(&pItem,horizontalAlign);
                }
                else if(formatType == CELL_TYPE_VERTICAL)
                {
                    int verticalAlign = pFormatSet->verticalAlign();
                    setVerticalAlign(&pItem,verticalAlign);
                }
                else if(formatType == CELL_TYPE_BORDER_All)
                {
                    setCellBorderFormat(rangeRow,rangeCol,pFormatSet);
                }
                else if(formatType == CELL_TYPE_ROW_HEIGHT)
                {
                    m_pGridCtrl->setRowHeight(rangeRow,pFormatSet->cellRowHeight());
                }
                else if(formatType == CELL_TYPE_COL_WIDTH)
                {
                    m_pGridCtrl->setColumnWidth(rangeCol,pFormatSet->cellColumnWidth());
                }
            }
        }
    }
}

void HGridCtrlWidget::cellFormat(HFormatSet* pFormatSet)
{

}

//基本
void HGridCtrlWidget::setHorizontalAlign(GV_ITEM* pItem,quint32 hAlign)
{
    bool bok = m_pGridCtrl->item(pItem);
    quint32 nFormat = pItem->nFormat;
    if(bok)
    {
        if(hAlign == QDT_LEFT)
        {
           nFormat = nFormat & ~QDT_RIGHT;
           nFormat = nFormat & ~QDT_HCENTER;
           nFormat = nFormat & QDT_LEFT;
        }
        else if(hAlign == QDT_RIGHT)
        {
            nFormat = nFormat & ~QDT_LEFT;
            nFormat = nFormat & ~QDT_HCENTER;
            nFormat = nFormat & QDT_RIGHT;
        }
        else
        {
            nFormat = nFormat & ~QDT_RIGHT;
            nFormat = nFormat & ~QDT_LEFT;
            nFormat = nFormat & QDT_HCENTER;
        }
    }
    m_pGridCtrl->setItem(pItem);
}

void HGridCtrlWidget::setVerticalAlign(GV_ITEM* pItem,quint32 vAlign)
{
    bool bok = m_pGridCtrl->item(pItem);
    quint32 nFormat = pItem->nFormat;
    if(bok)
    {
        if(vAlign == QDT_TOP)
        {
           nFormat = nFormat & ~QDT_BOTTOM;
           nFormat = nFormat & ~QDT_VCENTER;
           nFormat = nFormat & QDT_TOP;
        }
        else if(vAlign == QDT_BOTTOM)
        {
            nFormat = nFormat & ~QDT_TOP;
            nFormat = nFormat & ~QDT_VCENTER;
            nFormat = nFormat & QDT_BOTTOM;
        }
        else if(vAlign == QDT_VCENTER)
        {
            nFormat = nFormat & ~QDT_TOP;
            nFormat = nFormat & ~QDT_BOTTOM;
            nFormat = nFormat & QDT_VCENTER;
        }
        else
        {
            nFormat = nFormat & ~QDT_TOP;
            nFormat = nFormat & ~QDT_BOTTOM;
            nFormat = nFormat & ~QDT_VCENTER;
        }
    }
    m_pGridCtrl->setItem(pItem);
}

void HGridCtrlWidget::enableAutoWrapText(GV_ITEM* item,bool bAutoWrapText)
{
    bool bok = m_pGridCtrl->item(pItem);
    quint32 nFormat = pItem->nFormat;
    if(bok)
    {
        if(bAutoWrapText)
        {
           nFormat = nFormat & ~QDT_SINGLELINE;
           nFormat = nFormat & QDT_WORDBREAK;
        }
        else
        {
            nFormat = nFormat & ~QDT_WORDBREAK;
            nFormat = nFormat & QDT_SINGLELINE;
        }
    }
    m_pGridCtrl->setItem(pItem);
}

void HGridCtrlWidget::enableMergeCell(bool bMergCell)
{

}


//字体
void HGridCtrlWidget::setFontFamily(GV_ITEM* pItem,const QString& fontFamily)
{
    if(!pItem) return;
    pItem->mask = pItem->mask & GVIF_FONT;
    bool bok = m_pGridCtrl->item(pItem);
    QFont font = pItem->lfFont;
    if(bok)
    {
        font.setFamily(fontFamily);
    }
    m_pGridCtrl->setItem(pItem);
}

void HGridCtrlWidget::setFont(GV_ITEM* pItem,const QFont& font)
{
    if(!pItem) return;
    pItem->mask = pItem->mask & GVIF_FONT;
    bool bok = m_pGridCtrl->item(pItem);
    if(bok)
    {
        pItem->lfFont = font;
    }
    m_pGridCtrl->setItem(pItem);
}

void HGridCtrlWidget::setFontSize(GV_ITEM* pItem,quint8 size)
{
    if(!pItem) return;
    pItem->mask = pItem->mask & GVIF_FONT;
    bool bok = m_pGridCtrl->item(pItem);
    QFont font = pItem->lfFont;
    if(bok)
    {
        font.setPointSize(size);
    }
    m_pGridCtrl->setItem(pItem);
}

void HGridCtrlWidget::enableFontUnderline(GV_ITEM* pItem,bool b)
{
    if(!pItem) return;
    pItem->mask = pItem->mask & GVIF_FONT;
    bool bok = m_pGridCtrl->item(pItem);
    QFont font = pItem->lfFont;
    if(bok)
    {
        font.setUnderline(b);
    }
    m_pGridCtrl->setItem(pItem);
}

void HGridCtrlWidget::enableFontBold(GV_ITEM* pItem,bool b)
{
    if(!pItem) return;
    pItem->mask = pItem->mask & GVIF_FONT;
    bool bok = m_pGridCtrl->item(pItem);
    QFont font = pItem->lfFont;
    if(bok)
    {
        font.setBold(b);
    }
    m_pGridCtrl->setItem(pItem);
}

void HGridCtrlWidget::enableFontItalic(GV_ITEM* pItem,bool b)
{
    if(!pItem) return;
    pItem->mask = pItem->mask & GVIF_FONT;
    bool bok = m_pGridCtrl->item(pItem);
    QFont font = pItem->lfFont;
    if(bok)
    {
        font.setItalic(b);
    }
    m_pGridCtrl->setItem(pItem);
}

void HGridCtrlWidget::setTextColor(GV_ITEM* pItem,const QString& strTextClr)
{
    if(!pItem) return;
    pItem->mask = pItem->mask & GVIF_FGCLR;
    bool bok = m_pGridCtrl->item(pItem);
    if(bok)
    {
        QColor textClr = QColor(strTextClr);
        if(textClr.isValid())
            pItem->crFgClr = textClr;
    }
    m_pGridCtrl->setItem(pItem);
}

void HGridCtrlWidget::setTextBkColor(GV_ITEM* pItem,const QString& strTextBkClr)
{
    if(!pItem) return;
    pItem->mask = pItem->mask & GVIF_BKCLR;
    bool bok = m_pGridCtrl->item(pItem);
    if(bok)
    {
        QColor textBkClr = QColor(strTextBkClr);
        if(textBkClr.isValid())
            pItem->crBkClr = textBkClr;
    }
    m_pGridCtrl->setItem(pItem);
}

void HGridCtrlWidget::setCellBorderFormat(int row,int col,HFormatSet* pFormatSet)
{
    if(row < 0 || col < 0) return;
    if(!pFormatSet) return;
    HGridCell *pCell = m_pGridCtrl->getCell(row,col);
    if(NULL == pCell) return;
    if(!pFormatSet->isBorder())//无边框
    {
        pCell->setDrawBorder(false);
    }
    else
    {
        pCell->setDrawBorder(true);
        //左
        if(pFormatSet->isBorderLeft())
        {
            pCell->setDrawBorderLeft(true);
            pCell->setBorderLeftStyle(pFormatSet->borderLeftPenStyle());
            pCell->setBorderLeftColor(pFormatSet->borderLeftLineColor());
        }
        else
            pCell->setDrawBorderLeft(false);

        //右
        if(pFormatSet->isBorderRight())
        {
            pCell->setDrawBorderRight(true);
            pCell->setBorderRightStyle(pFormatSet->borderRightPenStyle());
            pCell->setBorderRightColor(pFormatSet->borderRightLineColor());
        }
        else
            pCell->setDrawBorderRight(false);

        //上
        if(pFormatSet->isBorderTop())
        {
            pCell->setDrawBorderTop(true);
            pCell->setBorderTopStyle(pFormatSet->borderTopPenStyle());
            pCell->setBorderTopColor(pFormatSet->borderTopLineColor());
        }
        else
            pCell->setDrawBorderRight(false);

        if(pFormatSet->isBorderBottom())
        {
            pCell->setDrawBorderBottom(true);
            pCell->setBorderBottomStyle(pFormatSet->borderBottomPenStyle());
            pCell->setBorderBottomColor(pFormatSet->borderBottomLineColor());
        }
        else
            pCell->setDrawBorderBottom(false);
    }
}

void HGridCtrlWidget::setPrintMarginInfo(HFormatSet *pSet)
{
    if(NULL == pSet)
        return;
    m_pGridCtrl->setPrintMarginInfo(pSet->pageHeaderHeight(),pSet->pageFooterHeight(),pSet->pageLeftMargin(),pSet->pageRightMargin(),
                                    pSet->pageTopMargin(),pSet->pageBottomMargin(),1);
    //设置头文字，设置尾部文字
    //设置打印其他相关信息
    //m_pGridCtrl->setH
}

