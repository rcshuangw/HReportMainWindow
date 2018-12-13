#include "hreportprint.h"
#include <QPrinter>
#include <QPainter>
#include <QPrintPreviewDialog>
#include <QFontMetrics>
#include "hgridctrl.h"
#include "QDateTime"
#include "hgridreportwidget.h"
#include "hgridctrlwidget.h"
HPrintInfo::HPrintInfo()
{

}

HPrintInfo::~HPrintInfo()
{

}


HReportPrint::HReportPrint(HGridReportWidget* widget)
    :m_pGridReportWidget(widget)
{
    m_PrintInfo.m_pGridCtrl = NULL;
    m_PrintInfo.m_rectDraw = QRect();
    m_nLeftMargin = 1;
    m_nRightMargin = 1;
    m_nGap = 0;
    m_nHeaderHeight = 2;
}

void HReportPrint::onPrintBegin(QPainter *pDC, HPrintInfo *pInfo)
{
    //本函数只是求出页面宽度和表格宽度和页面高度
    Q_ASSERT(pDC && pInfo);
    if (!pDC || !pInfo) return;
    // Create the printer font
    pDC->save();
    int nFontSize = 10;
    QString strFontName = "Arial";
    m_PrinterFont = QFont(strFontName,nFontSize);

    pDC->setFont(m_PrinterFont);

    // Get the average character width (in GridCtrl units) and hence the margins
    QFontMetrics fontMetrics(m_PrinterFont);
    m_CharSize = fontMetrics.size(Qt::TextSingleLine,("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSATUVWXYZ"));
    m_CharSize.setWidth(m_CharSize.width()/52);
    int nMargins = (m_nLeftMargin+m_nRightMargin)*m_CharSize.width(); //边距

    // 页面大小
    m_PaperSize = QSize(pDC->window().width(),pDC->window().height());
    m_LogicalPageSize.setWidth(pInfo->m_pGridCtrl->virtualWidth()+nMargins);
    m_LogicalPageSize.setHeight(int(m_LogicalPageSize.width()*m_PaperSize.height()/m_PaperSize.height()));
    m_nPageHeight = m_LogicalPageSize.height() - (m_nHeaderHeight+m_nFooterHeight + 2*m_nGap)*m_CharSize.height();

    //获取固定列宽
    int iColumnOffset = 0;
    int i1;
    for( i1=0; i1 < pInfo->m_pGridCtrl->fixedColumnCount(); i1++)
    {
        iColumnOffset += pInfo->m_pGridCtrl->columnWidth( i1);
    }
    //页面宽度 = 逻辑页面宽度 - 固定列宽 - 边距
    m_nPageWidth = m_LogicalPageSize.width() - iColumnOffset - nMargins;
    m_nPageMultiplier = 1;
    pDC->restore();
}

//Qt打印的边缘由Qt本身提供接口设置
void HReportPrint::onPrint(QPainter *pDC, HPrintInfo *pInfo)
{
    if (!pDC || !pInfo)
        return;
    //打印的原点仍然在左上角
    int transPointX = 0;
    int transPointY = 0;
    pDC->translate(0,0);
    pDC->setWindow(QRect(QPoint(0,0),m_LogicalPageSize));
    pDC->setViewport(QRect(QPoint(0,0),m_PaperSize));
    transPointX = m_nLeftMargin * m_CharSize.width();
    pDC->translate(transPointX, 0);

    pDC->setFont(m_PrinterFont);
    HGridCtrl* pGridCtrl = pInfo->m_pGridCtrl;
    if(!pGridCtrl) return;

    // Header
    pInfo->m_rectDraw.setTop(0);
    pInfo->m_rectDraw.setLeft(0);
    pInfo->m_rectDraw.setRight(m_LogicalPageSize.width() - (m_nLeftMargin + m_nRightMargin) * m_CharSize.width());
    pInfo->m_rectDraw.setBottom(m_nHeaderHeight * m_CharSize.height());

    //报表头文字
    printHeader(pDC, pInfo);

    //移动原点到报表头下面

    transPointY = m_nHeaderHeight * m_CharSize.height();
    pDC->translate(transPointX, transPointY);

    //头和表格之间的空间
    transPointY += m_nGap * m_CharSize.height();
    pDC->translate(transPointX, transPointY);

    // We need to find out which row to start printing for this page.
    m_nCurrPrintRow = pGridCtrl->fixedRowCount();
    m_nPrintColumn = pGridCtrl->fixedColumnCount();
    int i1, i2;

    // now, calculate which print column to start displaying
    /*for( i1 = 0; i1 < iWideColPageOffset; i1++)
    {
        for( i2 = m_nPrintColumn; i2 < GetColumnCount(); i2++)
        {
            iTotalRowWidth += GetColumnWidth( i2);
            if( iTotalRowWidth > m_nPageWidth)
            {
                m_nPrintColumn = i2;
                iTotalRowWidth = 0;
                break;
            }
        }
    }
*/
    //如果要打印列则打印
    bool bEnableShowRow = false;
    if(bEnableShowRow && pGridCtrl->fixedRowCount() > 0)
        printRowHeadings(pDC, pInfo);   // print row buttons on each page

    int iColumnOffset = 0;

    //固定列宽
    for( i1=0; i1 < pGridCtrl->fixedColumnCount(); i1++)
    {
        iColumnOffset += pGridCtrl->columnWidth( i1);
    }

    // Print the column headings
    bool bEnableShowCol = false;
    if(bEnableShowCol && pGridCtrl->fixedColumnCount() > 0)
    {
        //如果打印列
        pInfo->m_rectDraw.setBottom(pGridCtrl->fixedRowHeight());

        //pDC->translate( 0, pGridCtrl->fixedRowHeight());
        m_nPageWidth += iColumnOffset;
        m_nPrintColumn = 0;
        PrintColumnHeadings(pDC, pInfo);
        m_nPageWidth -= iColumnOffset;
        m_nPrintColumn = pGridCtrl->fixedColumnCount();
        transPointX += iColumnOffset;
        transPointY += pGridCtrl->fixedRowHeight();
        pDC->translate( transPointX, transPointY);
    }
    else
    {
        transPointX += iColumnOffset;
        pDC->translate( transPointX,transPointY);
    }

    if (m_nCurrPrintRow >= pGridCtrl->rowCount()) return;

    bool bFirstPrintedRow = true;
    QRect rect;
    rect.setBottom(-1);

    //Used for merge cells
    //by Huang Wei
    /*int Row=m_nCurrPrintRow;
    QRect range;
    range.bottom = -1;
    while (Row < GetRowCount())
    {
        range.top = range.bottom+1;
        range.bottom = range.top + GetRowHeight(Row) - 1;

        if (range.bottom > m_nPageHeight)
        {
            range.bottom=range.top;
            break;
        }
        Row++;
    }*/

    while (m_nCurrPrintRow < pGridCtrl->rowCount())
    {
        rect.setTop(rect.bottom()+1);
        rect.setBottom(rect.top() + pGridCtrl->rowHeight(m_nCurrPrintRow) - 1);

        if (rect.bottom() > m_nPageHeight) break;            // Gone past end of page

        rect.setRight(-1);

        // modified to allow printing of wide grids on multiple pages
        for (int col = m_nPrintColumn; col < pGridCtrl->columnCount(); col++)
        {
            rect.setLeft(rect.right() + 1);
            rect.setRight(rect.left() + pGridCtrl->columnWidth(col) - 1);

            if( rect.right() > m_nPageWidth)
                break;

            HGridCellBase* pCell = pGridCtrl->getCell(m_nCurrPrintRow, col);
            /*if (pCell)
            {
                //Used for merge cells
                //by Huang Wei
                int row=m_nCurrPrintRow;
                if(!pCell->IsMerged())
                {
                    if(!pCell->IsMergeWithOthers())
                    {
                        pCell->PrintCell(pDC, row, col, rect);
                    }
                }
                else
                {
                    CRect mergerect=rect;
                    if(cellRangeRect(pCell->m_MergeRange,&mergerect))
                    {
                        //mergerect.DeflateRect(0,0,1,1);
                        mergerect.OffsetRect(rect.TopLeft()-mergerect.TopLeft());
                        pCell->PrintCell(pDC, row, col, mergerect);
                    }
                }
            }*/

            if (pCell)
                pCell->printCell(pDC, m_nCurrPrintRow, col, rect);

            //增加列和行是否允许绘制

            if (pGridCtrl->gridLines() == GVL_BOTH || pGridCtrl->gridLines() == GVL_HORZ)
            {
                int Overlap = (col == 0)? 0:1;
                pDC->drawLine(QPoint(rect.left()-Overlap, rect.bottom()),QPoint(rect.right(), rect.bottom()));
                if (m_nCurrPrintRow == 0) {
                    pDC->drawLine(QPoint(rect.left()-Overlap, rect.top()),QPoint(rect.right(), rect.top()));
                }
            }

            if (pGridCtrl->gridLines() == GVL_BOTH || pGridCtrl->gridLines() == GVL_VERT)
            {
                int Overlap = (bFirstPrintedRow)? 0:1;
                pDC->drawLine(QPoint(rect.right(), rect.top()-Overlap),QPoint(rect.right(), rect.bottom()));
                if (col == 0) {
                    pDC->drawLine(QPoint(rect.left(), rect.top()-Overlap),QPoint(rect.left(), rect.bottom()));
                }
            }
        }
        m_nCurrPrintRow++;
        bFirstPrintedRow = false;
    }

    //Used for merge cells
    //by Huang Wei
   /* CRect white_rect(CPoint(0,0),m_LogicalPageSize);
    white_rect.top=range.bottom+1;
    pDC->FillSolidRect(white_rect,RGB(255,255,255));*/

    // Footer
    pInfo->m_rectDraw.setBottom(m_nFooterHeight * m_CharSize.height());
    pDC->translate(m_nLeftMargin * m_CharSize.width(), m_LogicalPageSize.height() + m_nFooterHeight * m_CharSize.height());
    printFooter(pDC, pInfo);

    // SetWindowOrg back for next page
    pDC->translate(0,0);

    pDC->restore();
}

void HReportPrint::printRowHeadings(QPainter *pDC, HPrintInfo* pInfo)
{
    if(!pDC || !pInfo)
        return;
    pDC->save();
    pDC->setFont(m_PrinterFont);

    QRect rect;
    rect.setRight(-1);

    bool bFirst = true;
    for( int iCol = 0; iCol < pInfo->m_pGridCtrl->fixedColumnCount(); iCol++)
    {
        rect.setLeft(rect.right() + 1);
        rect.setRight(rect.left() + pInfo->m_pGridCtrl->columnWidth( iCol) - 1);

        rect.setBottom(-1);
        for( int iRow = m_nCurrPrintRow; iRow < pInfo->m_pGridCtrl->rowCount(); iRow++)
        {
            rect.setTop(rect.bottom() + 1);
            rect.setBottom(rect.top() + pInfo->m_pGridCtrl->rowHeight( iRow) - 1);

            if( rect.bottom() > m_nPageHeight)
                break;

            HGridCellBase* pCell = pInfo->m_pGridCtrl->getCell(iRow, iCol);
            if (pCell)
                pCell->printCell(pDC, iRow, iCol, rect);

            if (pInfo->m_pGridCtrl->gridLines() == GVL_BOTH || pInfo->m_pGridCtrl->gridLines() == GVL_HORZ)
            {
                int Overlap = (iCol == 0)? 0:1;
                pDC->drawLine(QPoint(rect.left()-Overlap, rect.bottom()),QPoint(rect.right(), rect.bottom()));
                if( bFirst) {
                    pDC->drawLine(QPoint(rect.left()-Overlap, rect.top()-1),QPoint(rect.right(), rect.top()-1));
                    bFirst = false;
                }
            }
            if (pInfo->m_pGridCtrl->gridLines() == GVL_BOTH || pInfo->m_pGridCtrl->gridLines() == GVL_VERT)
            {
                int Overlap = (iRow == 0)? 0:1;
                pDC->drawLine(QPoint(rect.right()-Overlap, rect.top()),QPoint(rect.right(), rect.bottom()));
                if (iCol == 0) {
                    pDC->drawLine(QPoint(rect.left(), rect.top()-Overlap),QPoint(rect.left(), rect.bottom()));
                }
            }

        }
    }
    pDC->restore();
}

void HReportPrint::printFixedRowCells(int nStartColumn, int nStopColumn, int& row, QRect& rect,QPainter *pDC, bool& bFirst,HPrintInfo* pInfo)
{
    if(!pDC) return;
   // print all cells from nStartColumn to nStopColumn on row
   for (int col =nStartColumn; col < nStopColumn; col++)
   {
      rect.setLeft(rect.right() + 1);
      rect.setRight(rect.left() + pInfo->m_pGridCtrl->columnWidth( col) - 1);

      if( rect.right() > m_nPageWidth)
         break;

      HGridCellBase* pCell = pInfo->m_pGridCtrl->getCell(row, col);
      if(pCell)
          pCell->printCell(pDC, row, col, rect);
      /*if (pCell)
      {
            //Used for merge cells
            //by Huang Wei
            int row=m_nCurrPrintRow;
            if(!pCell->IsMerged())
            {
                if(!pCell->IsMergeWithOthers())
                {
                    pCell->PrintCell(pDC, row, col, rect);
                }
            }
            else
            {
                CRect mergerect=rect;
                if(GetCellRangeRect(pCell->m_MergeRange,&mergerect))
                {
                    //mergerect.DeflateRect(0,0,1,1);
                    mergerect.OffsetRect(rect.TopLeft()-mergerect.TopLeft());
                    pCell->PrintCell(pDC, row, col, mergerect);
                }
            }
      }*/

      if (pInfo->m_pGridCtrl->gridLines() == GVL_BOTH || pInfo->m_pGridCtrl->gridLines() == GVL_HORZ)
      {
         int Overlap = (col == 0)? 0:1;
         pDC->drawLine(QPoint(rect.left()-Overlap, rect.bottom()),QPoint(rect.right(), rect.bottom()));
         if (row == 0)
         {
            pDC->drawLine(QPoint(rect.left()-Overlap, rect.top()),QPoint(rect.right(), rect.top()));
          }
      }

      if (pInfo->m_pGridCtrl->gridLines() == GVL_BOTH || pInfo->m_pGridCtrl->gridLines() == GVL_VERT)
      {
         int Overlap = (row == 0)? 0:1;
         pDC->drawLine(QPoint(rect.right(), rect.top() - Overlap),QPoint(rect.right(), rect.bottom()));
         if( bFirst)
         {
            pDC->drawLine(QPoint(rect.left()-1, rect.top() - Overlap),QPoint(rect.left()-1, rect.bottom()));
            bFirst = false;
          }
       }
   }
}

void HReportPrint::PrintColumnHeadings(QPainter *pDC, HPrintInfo* pInfo)
{
    if(!pDC || !pInfo)
        return;
    pDC->save();
    pDC->setFont(m_PrinterFont);

    QRect rect;
    rect.setBottom(-1);

    bool bFirst = true;
    bool bOriginal;

    // modified to allow column hdr printing of multi-page wide grids
    for (int row = 0; row < pInfo->m_pGridCtrl->fixedRowCount(); row++)
    {
        rect.setTop(rect.bottom() + 1);
        rect.setBottom(rect.top() + pInfo->m_pGridCtrl->rowHeight(row) - 1);

        rect.setRight(-1);
        // if printColumn > fixedcolumncount we are on page 2 or more
        // lets printout those fixed cell headings again the 1 or more that would be missed
        // added by M.Fletcher 12/17/00
        if(m_nPrintColumn>= pInfo->m_pGridCtrl->fixedColumnCount())
        {
           bOriginal=false;
           // lets print the missing fixed cells on left first out to last fixed column
           printFixedRowCells(0,pInfo->m_pGridCtrl->fixedColumnCount(), row, rect, pDC, bFirst,pInfo);
           bFirst=bOriginal;
        }
        // now back to normal business print cells in heading after all fixed columns
        printFixedRowCells(m_nPrintColumn, pInfo->m_pGridCtrl->columnCount(), row, rect, pDC, bFirst,pInfo);
    }
    pDC->restore();
}


void HReportPrint::onPrintEnd(QPainter *p, HPrintInfo *pInfo)
{

}

void HReportPrint::printHeader(QPainter *pDC, HPrintInfo *pInfo)
{
    QString strRight;
    strRight = "my test";

    // print parent window title in the centre (Gert Rijs)
    QString strCenter = "hello,world";


    QRect   rc(pInfo->m_rectDraw);
    //QRect rc(0,0,100,100);
    if( !strCenter.isEmpty() )
        pDC->drawText( rc, QDT_LEFT | QDT_SINGLELINE | QDT_NOPREFIX | QDT_VCENTER, strCenter);
    if( !strRight.isEmpty() )
        pDC->drawText( rc, QDT_RIGHT | QDT_SINGLELINE | QDT_NOPREFIX | QDT_VCENTER, strRight);

    // draw ruled-line across top
    pDC->setPen(Qt::black);
    pDC->drawLine(QPoint(rc.left(), rc.bottom()),QPoint(rc.right(), rc.bottom()));

    pDC->restore();
}

void HReportPrint::printFooter(QPainter *pDC, HPrintInfo *pInfo)
{
    if(!pDC || !pInfo)
        return;
    //获取页尾文字
    QString strLeft;
    strLeft = QString(("Page %1 ")).arg(pInfo->m_nCurPage);

    // date and time on the right
    QString strRight;
    QDateTime dt = QDateTime::currentDateTime();
    strRight = dt.toString("yyyy-MM-dd hh:mm:ss");

    QRect rc(pInfo->m_rectDraw);

    // draw ruled line on bottom
    //先画条线 如果不需要可以删除
    pDC->setPen(Qt::black);
    pDC->drawLine(QPoint(rc.left(), rc.top()),QPoint(rc.right(), rc.top()));

    if( !strLeft.isEmpty() )
       pDC->drawText(rc,QDT_LEFT | QDT_SINGLELINE | QDT_NOPREFIX | QDT_VCENTER,strLeft);
    if( !strRight.isEmpty() )
       pDC->drawText( rc, QDT_RIGHT | QDT_SINGLELINE | QDT_NOPREFIX | QDT_VCENTER,strRight);

    pDC->restore();
}

void HReportPrint::printPage(QPainter* p)
{
    onPrintBegin(p,&m_PrintInfo);
    onPrint(p,&m_PrintInfo);
    onPrintEnd(p,&m_PrintInfo);
}

void HReportPrint::printPreview()
{
    QPrinter printer;
    QPrintPreviewDialog dlg(&printer,NULL);
    connect(&dlg, SIGNAL(paintRequested(QPrinter*)),this,SLOT(printPreview(QPrinter*)));
    dlg.exec();
}

void HReportPrint::printPreview(QPrinter* p)
{
    QPainter painter(p);
    for(int j= 0;j < m_pGridReportWidget->numSheet() ;j++) //页数
    {
      if(j != 0)
          p->newPage();

      HGridCtrl* pGridCtrl = ((HGridCtrlWidget*)m_pGridReportWidget->m_tabWidget->widget(j))->gridCtrl();
      if(!pGridCtrl) continue;
      m_PrintInfo.m_pGridCtrl = pGridCtrl;
      m_PrintInfo.m_nCurPage = j;
      printPage(&painter);
    }

}

void HReportPrint::printPages(QPrinter* p)
{
    QPainter painter(p);
    //预览打印是支持分页打印的
    int firstPage = p->fromPage() - 1;
    if(firstPage >= m_pGridReportWidget->numSheet())
        return;
    if(firstPage == (int)-1)
        firstPage = 0;
    int lastPage = p->toPage() - 1;
    if(lastPage == -1 || lastPage >= m_pGridReportWidget->numSheet())
        lastPage = m_pGridReportWidget->numSheet();
    int numPages = lastPage - firstPage - 1;

    for(int i = 0;i < p->numCopies();i++)
    {
        for(int j= 0;j < numPages;j++) //页数
        {
          if(i != 0 || j != 0)
              p->newPage();
          HGridCtrl* pGridCtrl = ((HGridCtrlWidget*)m_pGridReportWidget->m_tabWidget->widget(j))->gridCtrl();
          if(!pGridCtrl) continue;
          m_PrintInfo.m_pGridCtrl = pGridCtrl;
          m_PrintInfo.m_nCurPage = j;
          printPage(&painter);
        }
    }
}

