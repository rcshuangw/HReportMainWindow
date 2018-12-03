#include "mainwindow.h"
#include "hformatsetdlg.h"
#include "hreportnewdlg.h"
#include "hgridreportmgr.h"
#include "hgridctrlhelper.h"
#include "hreporttreewidget.h"
#include "hreportmaiwidget.h"
#include "hgridcelldef.h"
void HReportMainWindow::New(const QString& str)
{
    if(!m_pGridReportMgr || m_pGridReportMgr->gridCtrlFile())
        return;
    HReportNewDlg reportNewdlg;
    if(QDialog::Accepted == reportNewdlg.exec())//如果找到名称
    {
        GC_ITEM item;
        item.strReportName = reportNewdlg.strReportName;
        item.nMaxCol = reportNewdlg.nMaxCol;
        item.nMaxRow = reportNewdlg.nMaxRow;
        item.btType = 0;
        item.wReportID = 0;
        m_pGridReportMgr->gridCtrlFile()->addGridCtrlInfo(&item);
    }
    else
        return;
    m_pReportTreeWidget->addReportTreeWidgetItem();
    //m_pReportMainWidget->up
}

void HReportMainWindow::Open(const QString&,const int graphID)
{

}

void HReportMainWindow::Del(const QString&,const int graphID)
{

}

void HReportMainWindow::ImportFile(const QString&)
{

}


void HReportMainWindow::paste_click()
{

}

void HReportMainWindow::cut_click()
{

}

void HReportMainWindow::copy_click()
{

}

void HReportMainWindow::formatPainter_click()
{

}

void HReportMainWindow::bold_click()
{

}

void HReportMainWindow::italic_click()
{

}

void HReportMainWindow::underline_click()
{

}

void HReportMainWindow::fontColor_click()
{

}

void HReportMainWindow::fontbkColor_click()
{

}

void HReportMainWindow::borderBottom_click()
{

}

void HReportMainWindow::borderTop_click()
{

}

void HReportMainWindow::borderLeft_click()
{

}

void HReportMainWindow::borderRight_click()
{

}

void HReportMainWindow::borderNone_click()
{

}

void HReportMainWindow::borderAll_click()
{

}

void HReportMainWindow::borderOutSide_click()
{

}

void HReportMainWindow::borderInside_click()
{

}

void HReportMainWindow::borderInsideHor_click()
{

}

void HReportMainWindow::borderInsideVer_click()
{

}

void HReportMainWindow::fontSizeIncrease_click()
{

}

void HReportMainWindow::fontSizeDecrease_click()
{

}

void HReportMainWindow::clearAllFormat_click()
{

}

void HReportMainWindow::clearFormats_click()
{

}

void HReportMainWindow::clearFommating_click()
{

}

void HReportMainWindow::alignTop_click()
{

}

void HReportMainWindow::alignMiddle_click()
{

}

void HReportMainWindow::alignBottom_click()
{

}

void HReportMainWindow::alignLeft_click()
{

}

void HReportMainWindow::alignCenter_click()
{

}

void HReportMainWindow::alignRight_click()
{

}

void HReportMainWindow::autoWrapText_click()
{

}

void HReportMainWindow::mergeCenter_click()
{

}

void HReportMainWindow::mergeCells_click()
{

}

void HReportMainWindow::mergeSplit_click()
{

}

void HReportMainWindow::cellInsert_click()
{

}

void HReportMainWindow::cellInsertRow_click()
{

}

void HReportMainWindow::cellInsertCol_click()
{

}

void HReportMainWindow::cellDelete_click()
{

}

void HReportMainWindow::cellRemoveRow_click()
{

}

void HReportMainWindow::cellRemoveCol_click()
{

}

void HReportMainWindow::cellRowHeight_click()
{

}

void HReportMainWindow::cellAutoRowHeight_click()
{

}

void HReportMainWindow::cellColWidth_click()
{

}

void HReportMainWindow::cellAutoColWidth_click()
{

}

void HReportMainWindow::cellDefaultColWidth_click()
{

}

void HReportMainWindow::cellSetFormat_click()
{

}

void HReportMainWindow::option_click()
{
    HFormatSetDlg dlg;
    dlg.exec();
}

void HReportMainWindow::printDialog_click()
{

}

void HReportMainWindow::printOption_click()
{

}

void HReportMainWindow::printPreview_click()
{

}

void HReportMainWindow::opSheet_click()
{

}

void HReportMainWindow::hideRibbon_click()
{

}

void HReportMainWindow::information_click()
{

}
