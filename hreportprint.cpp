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


HReportPrint::HReportPrint()
{
    m_PrintInfo.m_pGridCtrl = NULL;
    m_PrintInfo.m_rectDraw = QRect();
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
    m_LogicalPageSize.setWidth(m_pCurGridCtrl->virtualWidth()+nMargins);
    m_LogicalPageSize.setHeight(int(m_LogicalPageSize.width()*m_PaperSize.height()/m_PaperSize.height()));
    m_nPageHeight = m_LogicalPageSize.height() - (m_nHeaderHeight+m_nFooterHeight + 2*m_nGap)*m_CharSize.height();

    //获取固定列宽
    int iColumnOffset = 0;
    int i1;
    for( i1=0; i1 < m_pCurGridCtrl->fixedColumnCount(); i1++)
    {
        iColumnOffset += m_pCurGridCtrl->columnWidth( i1);
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
    pDC->translate(0, m_nHeaderHeight * m_CharSize.height());

    //头和表格之间的空间
    pDC->translate(0, m_nGap * m_CharSize.height());

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


    PrintRowButtons( pDC, pInfo);   // print row buttons on each page
    */
    int iColumnOffset = 0;

    //固定列宽
    for( i1=0; i1 < pGridCtrl->fixedColumnCount(); i1++)
    {
        iColumnOffset += pGridCtrl->columnWidth( i1);
    }

    // Print the column headings
    bool bEnableShowCol = false;
    if(bEnableShowCol)
    {
        pInfo->m_rectDraw.setBottom(pGridCtrl->fixedRowHeight());

        pDC->translate( 0, pGridCtrl->fixedRowHeight());
        m_nPageWidth += iColumnOffset;
        m_nPrintColumn = 0;
        PrintColumnHeadings(pDC, pInfo);
        m_nPageWidth -= iColumnOffset;
        m_nPrintColumn = pGridCtrl->fixedColumnCount();
        pDC->translate( -iColumnOffset, -pGridCtrl->fixedRowHeight());

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
                    pDC->drawLine(QPoint(rect.left(), rect.top()-Overlap),QPoint(rect.right(), rect.bottom()));
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

void HReportPrint::PrintColumnHeadings(QPainter *pDC, HPrintInfo* /*pInfo*/)
{
   /* CFont *pOldFont = pDC->SelectObject(&m_PrinterFont);

    CRect rect;
    rect.bottom = -1;

    BOOL bFirst = TRUE;
    BOOL bOriginal;


    // modified to allow column hdr printing of multi-page wide grids
    for (int row = 0; row < GetFixedRowCount(); row++)
    {
        rect.top = rect.bottom+1;
        rect.bottom = rect.top + GetRowHeight(row) - 1;

        rect.right = -1;

        // if printColumn > fixedcolumncount we are on page 2 or more
        // lets printout those fixed cell headings again the 1 or more that would be missed
        // added by M.Fletcher 12/17/00
        if(m_nPrintColumn>= GetFixedColumnCount())
        {
           bOriginal=bFirst;
           // lets print the missing fixed cells on left first out to last fixed column
           PrintFixedRowCells(0,GetFixedColumnCount(), row, rect, pDC, bFirst);
           bFirst=bOriginal;
        }

        // now back to normal business print cells in heading after all fixed columns
        PrintFixedRowCells(m_nPrintColumn, GetColumnCount(), row, rect, pDC, bFirst);

    } // end of Row Loop

    pDC->SelectObject(pOldFont);
    */
} // end of CGridCtrl::PrintColumnHeadings


void HReportPrint::onPrintEnd(QPainter *p, HPrintInfo *pInfo)
{

}

void HReportPrint::printHeader(QPainter *pDC, HPrintInfo *pInfo)
{
    QString strRight;
    //strRight.LoadString(AFX_IDS_APP_TITLE);

    // print parent window title in the centre (Gert Rijs)
    QString strCenter;


    QRect   rc(pInfo->m_rectDraw);
    if( !strCenter.isEmpty() )
        pDC->drawText( rc, QDT_CENTER | QDT_SINGLELINE | QDT_NOPREFIX | QDT_VCENTER, strCenter);
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
    //strLeft = QString(("Page %1 of %2").arg(pInfo->m_nCurPage).arg(pInfo->GetMaxPage()));

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

void HReportPrint::printPriview()
{
    QPrinter printer;
    QPrintPreviewDialog dlg(&printer,NULL);
    connect(&dlg, SIGNAL(paintRequested(QPrinter*)),this,SLOT(printPreview(QPrinter*)));
    dlg.exec();
}

void HReportPrint::printPriview(QPrinter* p)
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
        for(int j= 0;j < numPages ;j++) //页数
        {
          if(i != 0 || j != 0)
              p->newPage();

          int index = firstPage + j;
          HGridCtrl* pGridCtrl = ((HGridCtrlWidget*)m_pGridReportWidget->m_tabWidget->widget(index))->gridCtrl();
          if(!pGridCtrl) continue;
          m_PrintInfo.m_pGridCtrl = pGridCtrl;
          m_PrintInfo.m_nCurPage = j;
          printPages(p);
        }
    }
}

void HReportPrint::printPages(QPrinter* p)
{
    QPainter painter(p);
    for(int i = 0;i < p->numCopies();i++)
    {
        for(int j= 0;j < m_pGridReportWidget->numSheet();j++) //页数
        {
          if(i != 0 || j != 0)
              p->newPage();
          HGridCtrl* pGridCtrl = ((HGridCtrlWidget*)m_pGridReportWidget->m_tabWidget->widget(j))->gridCtrl();
          if(!pGridCtrl) continue;
          m_PrintInfo.m_pGridCtrl = pGridCtrl;
          m_PrintInfo.m_nCurPage = j;
          printPages(p);
        }
    }
}

/*
 * // EFW - Various changes in the next few functions to support the
// new print margins and a few other adjustments.
void HGridCtrl::OnBeginPrinting(CDC *pDC, CPrintInfo *pInfo)
{
    // OnBeginPrinting() is called after the user has committed to
    // printing by OK'ing the Print dialog, and after the framework
    // has created a CDC object for the printer or the preview view.

    // This is the right opportunity to set up the page range.
    // Given the CDC object, we can determine how many rows will
    // fit on a page, so we can in turn determine how many printed
    // pages represent the entire document.


}

void HGridCtrl::OnPrint(CDC *pDC, CPrintInfo *pInfo)
{

}


// added by M.Fletcher 12/17/00
void HGridCtrl::PrintFixedRowCells(int nStartColumn, int nStopColumn, int& row, CRect& rect,
                                   CDC *pDC, bool& bFirst)
{
   // print all cells from nStartColumn to nStopColumn on row
   for (int col =nStartColumn; col < nStopColumn; col++)
   {
      rect.left = rect.right+1;
      rect.right =    rect.left + GetColumnWidth( col) - 1;

      if( rect.right > m_nPageWidth)
         break;

      CGridCellBase* pCell = GetCell(row, col);
      if (pCell)
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
      }

      //if (m_nGridLines == GVL_BOTH || m_nGridLines == GVL_HORZ)
      //{
      //   int Overlap = (col == 0)? 0:1;
      //
      //   pDC->MoveTo(rect.left-Overlap, rect.bottom);
      //   pDC->LineTo(rect.right, rect.bottom);
      //
      //   if (row == 0)
      //   {
      //      pDC->MoveTo(rect.left-Overlap, rect.top);
      //      pDC->LineTo(rect.right, rect.top);
      //    }
      //}

      //if (m_nGridLines == GVL_BOTH || m_nGridLines == GVL_VERT)
      //{
      //   int Overlap = (row == 0)? 0:1;

      //   pDC->MoveTo(rect.right, rect.top-Overlap);
      //   pDC->LineTo(rect.right, rect.bottom);
      //
      //   if( bFirst)
      //   {
      //      pDC->MoveTo(rect.left-1, rect.top-Overlap);
      //      pDC->LineTo(rect.left-1, rect.bottom);
      //      bFirst = false;
      //    }

      // }

   } // end of column cells loop


} // end of HGridCtrl::PrintFixedRowCells

void HGridCtrl::PrintColumnHeadings(CDC *pDC, CPrintInfo* pInfo)
{
    CFont *pOldFont = pDC->SelectObject(&m_PrinterFont);

    CRect rect;
    rect.bottom = -1;

    bool bFirst = true;
    bool bOriginal;


    // modified to allow column hdr printing of multi-page wide grids
    for (int row = 0; row < GetFixedRowCount(); row++)
    {
        rect.top = rect.bottom+1;
        rect.bottom = rect.top + GetRowHeight(row) - 1;

        rect.right = -1;

        // if printColumn > fixedcolumncount we are on page 2 or more
        // lets printout those fixed cell headings again the 1 or more that would be missed
        // added by M.Fletcher 12/17/00
        if(m_nPrintColumn>= GetFixedColumnCount())
        {
           bOriginal=bFirst;
           // lets print the missing fixed cells on left first out to last fixed column
           PrintFixedRowCells(0,GetFixedColumnCount(), row, rect, pDC, bFirst);
           bFirst=bOriginal;
        }

        // now back to normal business print cells in heading after all fixed columns
        PrintFixedRowCells(m_nPrintColumn, GetColumnCount(), row, rect, pDC, bFirst);

    } // end of Row Loop

    pDC->SelectObject(pOldFont);
} // end of HGridCtrl::PrintColumnHeadings
*/
