#include "mainwindow.h"
#include "hformatsetdlg.h"
#include "hreportnewdlg.h"
#include "hgridreportmgr.h"
#include "hgridctrlhelper.h"
#include "hreporttreewidget.h"
#include "hreportmaiwidget.h"
#include "hgridcelldef.h"
void HReportMainWindow::new_clicked()
{
    if(!m_pReportManager || !m_pReportManager->gridCtrlFile())
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
        m_pReportManager->gridCtrlFile()->addGridCtrlInfo(&item);
    }
    else
        return;
    m_pReportTreeWidget->addReportTreeWidgetItem();
    m_pReportMainWidget->newReportWidget();
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


void HReportMainWindow::paste_clicked()
{

}

void HReportMainWindow::cut_clicked()
{

}

void HReportMainWindow::copy_clicked()
{

}

void HReportMainWindow::formatPainter_clicked()
{

}

void HReportMainWindow::bold_clicked()
{

}

void HReportMainWindow::italic_clicked()
{

}

void HReportMainWindow::underline_clicked()
{

}

void HReportMainWindow::fontColor_clicked()
{

}

void HReportMainWindow::fontbkColor_clicked()
{

}

void HReportMainWindow::borderBottom_clicked()
{

}

void HReportMainWindow::borderTop_clicked()
{

}

void HReportMainWindow::borderLeft_clicked()
{

}

void HReportMainWindow::borderRight_clicked()
{

}

void HReportMainWindow::borderNone_clicked()
{

}

void HReportMainWindow::borderAll_clicked()
{

}

void HReportMainWindow::borderOutSide_clicked()
{

}

void HReportMainWindow::borderInside_clicked()
{

}

void HReportMainWindow::borderInsideHor_clicked()
{

}

void HReportMainWindow::borderInsideVer_clicked()
{

}

void HReportMainWindow::fontSizeIncrease_clicked()
{

}

void HReportMainWindow::fontSizeDecrease_clicked()
{

}

void HReportMainWindow::clearAllFormat_clicked()
{

}

void HReportMainWindow::clearFormats_clicked()
{

}

void HReportMainWindow::clearFommating_clicked()
{

}

void HReportMainWindow::alignTop_clicked()
{

}

void HReportMainWindow::alignMiddle_clicked()
{

}

void HReportMainWindow::alignBottom_clicked()
{

}

void HReportMainWindow::alignLeft_clicked()
{

}

void HReportMainWindow::alignCenter_clicked()
{

}

void HReportMainWindow::alignRight_clicked()
{

}

void HReportMainWindow::autoWrapText_clicked()
{

}

void HReportMainWindow::mergeCenter_clicked()
{

}

void HReportMainWindow::mergeCells_clicked()
{

}

void HReportMainWindow::mergeSplit_clicked()
{

}

void HReportMainWindow::cellInsert_clicked()
{

}

void HReportMainWindow::cellInsertRow_clicked()
{

}

void HReportMainWindow::cellInsertCol_clicked()
{

}

void HReportMainWindow::cellDelete_clicked()
{

}

void HReportMainWindow::cellRemoveRow_clicked()
{

}

void HReportMainWindow::cellRemoveCol_clicked()
{

}

void HReportMainWindow::cellRowHeight_clicked()
{

}

void HReportMainWindow::cellAutoRowHeight_clicked()
{

}

void HReportMainWindow::cellColWidth_clicked()
{

}

void HReportMainWindow::cellAutoColWidth_clicked()
{

}

void HReportMainWindow::cellDefaultColWidth_clicked()
{

}

void HReportMainWindow::cellSetFormat_clicked()
{

}

void HReportMainWindow::option_clicked()
{
    HFormatSetDlg dlg;
    dlg.exec();
}

void HReportMainWindow::printDialog_clicked()
{

}

void HReportMainWindow::printOption_clicked()
{

}

void HReportMainWindow::printPreview_clicked()
{
    if(!m_pReportMainWidget || !m_pReportManager)
        return;
    m_pReportMainWidget->printReportWidget();
}

void HReportMainWindow::opSheet_clicked()
{

}

void HReportMainWindow::hideRibbon_clicked()
{

}

void HReportMainWindow::information_clicked()
{

}
