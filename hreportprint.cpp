#include "hreportprint.h"
#include <QPrinter>
#include <QPainter>
#include <QPrintPreviewDialog>
#include "hgridctrl.h"
HReportPrint::HReportPrint()
{

}

void HReportPrint::onPrintBegin(QPainter *pDC, HPrintInfo *pInfo)
{
    Q_ASSERT(pDC && pInfo);
    if (!pDC || !pInfo) return;

    // Get a DC for the current window (will be a screen DC for print previewing)
    //CSize PaperPixelsPerInch(pDC->GetDeviceCaps(LOGPIXELSX), pDC->GetDeviceCaps(LOGPIXELSY));
    //CSize ScreenPixelsPerInch(pCurrentDC->GetDeviceCaps(LOGPIXELSX), pCurrentDC->GetDeviceCaps(LOGPIXELSY));

    // Create the printer font
    pDC->save();
    int nFontSize = -10;
    QString strFontName = "Arial";
    m_PrinterFont = QFont(strFontName,nFontSize);

    pDC->setFont(m_PrinterFont);

    // Get the average character width (in GridCtrl units) and hence the margins
    QFontMetrics fontMetrics(m_PrintFont);
    m_CharSize = fontMetrics.size(Qt::TextSingleLine,("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSATUVWXYZ"));
    m_CharSize.setWidth(m_CharSize.width()/52);
    int nMargins = (m_nLeftMargin+m_nRightMargin)*m_CharSize.width();

    // Get the page sizes (physical and logical)
    m_PaperSize = QSize(pDC->window().width(),pDC->window().height());

    bool m_bWysiwygPrinting = false;
    if( m_bWysiwygPrinting)
    {
        //m_LogicalPageSize.cx = ScreenPixelsPerInch.cx * m_PaperSize.cx / PaperPixelsPerInch.cx * 3 / 4;
        //m_LogicalPageSize.cy = ScreenPixelsPerInch.cy * m_PaperSize.cy / PaperPixelsPerInch.cy * 3 / 4;
    }
    else
    {
        m_PaperSize = QSize(pDC->window().width(),pDC->window().height());//CSize(pDC->GetDeviceCaps(HORZRES), pDC->GetDeviceCaps(VERTRES));

        m_LogicalPageSize.setWidth(m_pCurGridCtrl->virtualWidth()+nMargins);
        m_LogicalPageSize.setHeight(int(m_LogicalPageSize.cx*m_PaperSize.cy/m_PaperSize.cx));

    }

    m_nPageHeight = m_LogicalPageSize.height() - (m_nHeaderHeight+m_nFooterHeight + 2*m_nGap)*m_CharSize.height();

    // Get the number of pages. Assumes no row is bigger than the page size.
    int nTotalRowHeight = 0;
    m_nNumPages = 1;
    for (int row = GetFixedRowCount(); row < GetRowCount(); row++)
    {
        nTotalRowHeight += GetRowHeight(row);
        if (nTotalRowHeight > m_nPageHeight) {
            m_nNumPages++;
            nTotalRowHeight = GetRowHeight(row);
        }
    }

    // now, figure out how many additional pages must print out if rows ARE bigger
    //  than page size
    int iColumnOffset = 0;
    int i1;
    for( i1=0; i1 < GetFixedColumnCount(); i1++)
    {
        iColumnOffset += GetColumnWidth( i1);
    }
    m_nPageWidth = m_LogicalPageSize.cx - iColumnOffset - nMargins;
    m_nPageMultiplier = 1;

    if( m_bWysiwygPrinting)
    {
        int iTotalRowWidth = 0;
        for( i1 = GetFixedColumnCount(); i1 < GetColumnCount(); i1++)
        {
            iTotalRowWidth += GetColumnWidth( i1);
            if( iTotalRowWidth > m_nPageWidth)
            {
                m_nPageMultiplier++;
                iTotalRowWidth = GetColumnWidth( i1);
            }
        }
        m_nNumPages *= m_nPageMultiplier;
    }

    // Set up the print info
    pInfo->SetMaxPage(m_nNumPages);
    pInfo->m_nCurPage = 1;                        // start printing at page# 1

    ReleaseDC(pCurrentDC);
    pDC->SelectObject(pOldFont);
}

//Qt打印的边缘由Qt本身提供接口设置
void HReportPrint::onPrint(QPainter *pDC, HPrintInfo *pInfo)
{
    if (!pDC || !pInfo)
        return;

    //CRect rcPage(pInfo->m_rectDraw);
    CFont *pOldFont = pDC->SelectObject(&m_PrinterFont);

    // Set the page map mode to use GridCtrl units, and setup margin
    pDC->SetMapMode(MM_ANISOTROPIC);
    pDC->SetWindowExt(m_LogicalPageSize);
    pDC->SetViewportExt(m_PaperSize);
    pDC->SetWindowOrg(-m_nLeftMargin * m_CharSize.cx, 0);

    // Header
    pInfo->m_rectDraw.top    = 0;
    pInfo->m_rectDraw.left   = 0;
    pInfo->m_rectDraw.right  = m_LogicalPageSize.cx - (m_nLeftMargin + m_nRightMargin) * m_CharSize.cx;
    pInfo->m_rectDraw.bottom = m_nHeaderHeight * m_CharSize.cy;
    PrintHeader(pDC, pInfo);
    pDC->OffsetWindowOrg(0, -m_nHeaderHeight * m_CharSize.cy);

    // Gap between header and column headings
    pDC->OffsetWindowOrg(0, -m_nGap * m_CharSize.cy);

    pDC->OffsetWindowOrg(0, -GetFixedRowHeight());

    // We need to find out which row to start printing for this page.
    int nTotalRowHeight = 0;
    UINT nNumPages = 1;
    m_nCurrPrintRow = GetFixedRowCount();


    // Not only the row, but we need to figure out column, too

    // Can print 4 pages, where page 1 and 2 represent the same rows but
    // with different WIDE columns.
    //
    // .......
    // .1 .2 .  If representing page 3  -->    iPageIfIgnoredWideCols = 2
    // .......                                 iWideColPageOffset = 0
    // .3 .4 .  If representing page 2  -->    iPageIfIgnoredWideCols = 1
    // .......                                 iWideColPageOffset = 1

    int iPageIfIgnoredWideCols = pInfo->m_nCurPage / m_nPageMultiplier;
    int iWideColPageOffset = pInfo->m_nCurPage - ( iPageIfIgnoredWideCols * m_nPageMultiplier);
    if( iWideColPageOffset > 0)
        iPageIfIgnoredWideCols++;

    if( iWideColPageOffset == 0)
        iWideColPageOffset = m_nPageMultiplier;
    iWideColPageOffset--;

    // calculate current print row based on iPageIfIgnoredWideCols
    while(  m_nCurrPrintRow < GetRowCount()
            && (int)nNumPages < iPageIfIgnoredWideCols)
    {
        nTotalRowHeight += GetRowHeight(m_nCurrPrintRow);
        if (nTotalRowHeight > m_nPageHeight) {
            nNumPages++;
            if ((int)nNumPages == iPageIfIgnoredWideCols) break;
            nTotalRowHeight = GetRowHeight(m_nCurrPrintRow);
        }
        m_nCurrPrintRow++;
    }

    m_nPrintColumn = GetFixedColumnCount();
    int iTotalRowWidth = 0;
    int i1, i2;

    // now, calculate which print column to start displaying
    for( i1 = 0; i1 < iWideColPageOffset; i1++)
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
    int iColumnOffset = 0;
    for( i1=0; i1 < GetFixedColumnCount(); i1++)
    {
        iColumnOffset += GetColumnWidth( i1);
    }

    // Print the column headings
    pInfo->m_rectDraw.bottom = GetFixedRowHeight();

    if( m_nPrintColumn == GetFixedColumnCount())
    {
        // have the column headings fcn draw the upper left fixed cells
        //  for the very first columns, only
        pDC->OffsetWindowOrg( 0, +GetFixedRowHeight());

        m_nPageWidth += iColumnOffset;
        m_nPrintColumn = 0;
        PrintColumnHeadings(pDC, pInfo);
        m_nPageWidth -= iColumnOffset;
        m_nPrintColumn = GetFixedColumnCount();

        pDC->OffsetWindowOrg( -iColumnOffset, -GetFixedRowHeight());
    }
    else
    {
        // changed all of this here to match above almost exactly same
        pDC->OffsetWindowOrg( 0, +GetFixedRowHeight());

        m_nPageWidth += iColumnOffset;

        // print from column 0 ... last column that fits on the current page
        PrintColumnHeadings(pDC, pInfo);

        m_nPageWidth -= iColumnOffset;

        pDC->OffsetWindowOrg( -iColumnOffset, -GetFixedRowHeight());
    }


    if (m_nCurrPrintRow >= GetRowCount()) return;

    // Draw as many rows as will fit on the printed page.
    // Clip the printed page so that there is no partially shown
    // row at the bottom of the page (the same row which will be fully
    // shown at the top of the next page).

    bool bFirstPrintedRow = true;
    CRect rect;
    rect.bottom = -1;

    //Used for merge cells
    //by Huang Wei
    int Row=m_nCurrPrintRow;
    CRect range;
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
    }

    while (m_nCurrPrintRow < GetRowCount())
    {
        rect.top = rect.bottom+1;
        rect.bottom = rect.top + GetRowHeight(m_nCurrPrintRow) - 1;

        if (rect.bottom > m_nPageHeight) break;            // Gone past end of page

        rect.right = -1;

        // modified to allow printing of wide grids on multiple pages
        for (int col = m_nPrintColumn; col < GetColumnCount(); col++)
        {
            rect.left = rect.right+1;
            rect.right =    rect.left
                            + GetColumnWidth( col)
                            - 1;

            if( rect.right > m_nPageWidth)
                break;

            CGridCellBase* pCell = GetCell(m_nCurrPrintRow, col);
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
            //    int Overlap = (col == 0)? 0:1;
            //    pDC->MoveTo(rect.left-Overlap, rect.bottom);
            //    pDC->LineTo(rect.right, rect.bottom);
            //    if (m_nCurrPrintRow == 0) {
            //        pDC->MoveTo(rect.left-Overlap, rect.top);
            //        pDC->LineTo(rect.right, rect.top);
            //    }
            //}
            //if (m_nGridLines == GVL_BOTH || m_nGridLines == GVL_VERT)
            //{
            //    int Overlap = (bFirstPrintedRow)? 0:1;
            //    pDC->MoveTo(rect.right, rect.top-Overlap);
            //    pDC->LineTo(rect.right, rect.bottom);
            //    if (col == 0) {
            //        pDC->MoveTo(rect.left, rect.top-Overlap);
            //        pDC->LineTo(rect.left, rect.bottom);
            //    }
            //}

        }
        m_nCurrPrintRow++;
        bFirstPrintedRow = false;
    }

    //Used for merge cells
    //by Huang Wei
    CRect white_rect(CPoint(0,0),m_LogicalPageSize);
    white_rect.top=range.bottom+1;
    pDC->FillSolidRect(white_rect,RGB(255,255,255));

    // Footer
    pInfo->m_rectDraw.bottom = m_nFooterHeight * m_CharSize.cy;
    pDC->SetWindowOrg( -m_nLeftMargin * m_CharSize.cx,
        -m_LogicalPageSize.cy + m_nFooterHeight * m_CharSize.cy);
    PrintFooter(pDC, pInfo);

    // SetWindowOrg back for next page
    pDC->SetWindowOrg(0,0);

    pDC->SelectObject(pOldFont);
}

void HReportPrint::onPrintEnd(QPainter *p, CPrintInfo *pInfo)
{

}

void HReportPrint::printHeader(QPainter *p, CPrintInfo *pInfo)
{

}

void HReportPrint::printFooter(QPainter *p, CPrintInfo *pInfo)
{

}

void HReportPrint::printPage(QPainter* p,HGridCtrl* pGridCtrl,int pageNumber)
{

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
    for(int i = 0;i < p->numCopies();i++)
    {
        for(int j= 0;j < 2;j++) //页数
        {
          if(i != 0 || j != 0)
              p->newPage();
          //painter.drawText(painter.window(),Qt::AlignHCenter,"test");
            printPage();
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
