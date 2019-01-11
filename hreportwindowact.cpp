#include "mainwindow.h"
#include "hformatsetdlg.h"
#include "hreportnewdlg.h"
#include "hgridreportmgr.h"
#include "hgridctrlhelper.h"
#include "hreporttreewidget.h"
#include "hreportmaiwidget.h"
#include "hgridcelldef.h"
#include "hformatdef.h"
#include "SARibbonBar.h"
#include "SARibbonComboBox.h"
#include "hformatset.h"
#include <QColorDialog>
#include <QInputDialog>
void HReportMainWindow::new_clicked()
{
    if(!m_pReportManager || !m_pReportManager->gridCtrlFile())
        return;
    HReportNewDlg reportNewdlg;
    if(QDialog::Accepted == reportNewdlg.exec())//如果找到名称
    {
        GC_ITEM item;
        item.strReportName = reportNewdlg.strReportName;
        item.nMaxCol = reportNewdlg.nMaxCol+1;//如果不+1，输入的就是包含行列头的
        item.nMaxRow = reportNewdlg.nMaxRow+1;
        item.btType = 0;
        item.wReportID = 0;
        m_pReportManager->gridCtrlFile()->addGridCtrlInfo(&item);
    }
    else
        return;
    m_pReportTreeWidget->addReportTreeWidgetItem();
    m_pReportMainWidget->newReportWidget();
}

void HReportMainWindow::save_clicked()
{
    if(!m_pReportManager)
        return;
    m_pReportManager->saveGridCtrlFile();
}

void HReportMainWindow::Open(const QString&,const int reportID)
{
    if(!m_pReportManager || !m_pReportManager->gridCtrlFile())
        return;
    m_pReportManager->gridCtrlFile()->setGridCtrlInfoById(reportID);
    m_pReportMainWidget->openReportWidget();
}

void HReportMainWindow::Del(const QString&,const int reportID)
{
    if(!m_pReportManager || !m_pReportManager->gridCtrlFile())
        return;
    m_pReportManager->gridCtrlFile()->delGridCtrlInfo(reportID);
    m_pReportMainWidget->delReportWidget();
}

void HReportMainWindow::ImportFile(const QString&)
{

}


void HReportMainWindow::paste_clicked()
{
    if(!m_pReportMainWidget || !m_pReportManager || !m_pReportMainWidget->reportEditorWidget())
        return;
    m_pReportMainWidget->paste();
}

void HReportMainWindow::cut_clicked()
{
    if(!m_pReportMainWidget || !m_pReportManager || !m_pReportMainWidget->reportEditorWidget())
        return;
    m_pReportMainWidget->cut();
}

void HReportMainWindow::copy_clicked()
{
    if(!m_pReportMainWidget || !m_pReportManager || !m_pReportMainWidget->reportEditorWidget())
        return;
    m_pReportMainWidget->copy();
}

void HReportMainWindow::formatPainter_clicked()
{

}

void HReportMainWindow::fontFamilyComboBox_changed(int index)
{
    if(-1 == index || !m_pReportManager || !m_pReportManager->formatSet() || !m_pReportMainWidget)
        return;
    QFont font = m_pReportManager->formatSet()->formatFont();
    QString strFamily = fontFamilyComboBox->currentText();
    font.setFamily(strFamily);
    m_pReportManager->formatSet()->setFormatFont(font);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_FONT);
}

void HReportMainWindow::fontSizeComboBox_changed(int)
{
    if(!m_pReportManager || !m_pReportManager->formatSet() || !m_pReportMainWidget)
        return;
    QFont font = m_pReportManager->formatSet()->formatFont();
    QString strSize = fontSizeComboBox->currentText();
    font.setPointSize(strSize.toUInt());
    m_pReportManager->formatSet()->setFormatFont(font);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_FONT);
}

void HReportMainWindow::bold_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet() || !m_pReportMainWidget)
        return;
    QFont font = m_pReportManager->formatSet()->formatFont();
    bool bBold = boldAct->isChecked();
    font.setBold(bBold);
    m_pReportManager->formatSet()->setFormatFont(font);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_FONT);
}

void HReportMainWindow::italic_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet() || !m_pReportMainWidget)
        return;
    QFont font = m_pReportManager->formatSet()->formatFont();
    bool italic = italicAct->isChecked();
    font.setItalic(italic);
    m_pReportManager->formatSet()->setFormatFont(font);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_FONT);
}

void HReportMainWindow::underline_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet() || !m_pReportMainWidget)
        return;
    QFont font = m_pReportManager->formatSet()->formatFont();
    bool underline = underlineAct->isChecked();
    font.setUnderline(underline);
    m_pReportManager->formatSet()->setFormatFont(font);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_FONT);
}

void HReportMainWindow::fontSizeIncrease_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet() || !m_pReportMainWidget)
        return;
    QFont font = m_pReportManager->formatSet()->formatFont();
    QString strFontSize = fontSizeComboBox->currentText();
    if(strFontSize.toInt() >= 255)
        return;
    int nFontSize = strFontSize.toInt();
    nFontSize++;
    strFontSize = QString("%1").arg(nFontSize);
    fontSizeComboBox->setCurrentText(strFontSize);
    font.setPointSize(nFontSize);
    m_pReportManager->formatSet()->setFormatFont(font);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_FONT);
}

void HReportMainWindow::fontSizeDecrease_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet() || !m_pReportMainWidget)
        return;
    QFont font = m_pReportManager->formatSet()->formatFont();
    QString strFontSize = fontSizeComboBox->currentText();
    if(strFontSize.toInt() <= 1)
        return;
    int nFontSize = strFontSize.toInt();
    nFontSize--;
    strFontSize = QString("%1").arg(nFontSize);
    fontSizeComboBox->setCurrentText(strFontSize);
    font.setPointSize(nFontSize);
    m_pReportManager->formatSet()->setFormatFont(font);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_FONT);
}

void HReportMainWindow::fontColor_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet() || !m_pReportMainWidget)
        return;
    QString strTextClr = m_pReportManager->formatSet()->textColor();
    QColor clr = QColorDialog::getColor(QColor(strTextClr),this,QStringLiteral("选择颜色"));
    strTextClr = clr.name();
    m_pReportManager->formatSet()->setTextColor(strTextClr);
    //m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_COLOR);
}

void HReportMainWindow::fontColorActGroup_clicked(QAction *action)
{
    if(!action) return;
    if(!m_pReportManager || !m_pReportManager->formatSet() || !m_pReportMainWidget)
        return;
    QString strTextClr = action->data().toString();
    m_pReportManager->formatSet()->setTextColor(strTextClr);
     m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_COLOR);
}


void HReportMainWindow::fontBkColor_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    QString strTextBkClr = m_pReportManager->formatSet()->textBkColor();
    QColor clr = QColorDialog::getColor(QColor(strTextBkClr),this,QStringLiteral("选择颜色"));
    strTextBkClr = clr.name();
   //m_pReportManager->formatSet()->setTextBkColor(strTextBkClr);
}

void HReportMainWindow::fontBkColorActGroup_clicked(QAction *action)
{
    if(!action) return;
    if(!m_pReportManager || !m_pReportManager->formatSet() || !m_pReportMainWidget)
        return;
    QString strTextBkClr = action->data().toString();
    m_pReportManager->formatSet()->setTextBkColor(strTextBkClr);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_COLOR);
}

void HReportMainWindow::borderBottom_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    //m_pReportManager->formatSet()->resetEnableBorder();
    m_pReportManager->formatSet()->enableBorderBottom(true);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_BORDER);
}

void HReportMainWindow::borderTop_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    //m_pReportManager->formatSet()->resetEnableBorder();
    m_pReportManager->formatSet()->enableBorderTop(true);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_BORDER);
}

void HReportMainWindow::borderLeft_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    m_pReportManager->formatSet()->enableBorderLeft(true);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_BORDER);
}

void HReportMainWindow::borderRight_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    m_pReportManager->formatSet()->enableBorderRight(true);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_BORDER);
}

void HReportMainWindow::borderNone_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    m_pReportManager->formatSet()->enableBorderOutSide(false);
    m_pReportManager->formatSet()->enableBorderTop(false);
    m_pReportManager->formatSet()->enableBorderBottom(false);
    m_pReportManager->formatSet()->enableBorderLeft(false);
    m_pReportManager->formatSet()->enableBorderRight(false);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_BORDER);
}

void HReportMainWindow::borderAll_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    m_pReportManager->formatSet()->enableBorderTop(true);
    m_pReportManager->formatSet()->enableBorderBottom(true);
    m_pReportManager->formatSet()->enableBorderLeft(true);
    m_pReportManager->formatSet()->enableBorderRight(true);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_BORDER);
}

void HReportMainWindow::borderOutSide_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    m_pReportManager->formatSet()->enableBorderOutSide(true);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_BORDER);
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

void HReportMainWindow::clearAllFormat_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    m_pReportManager->formatSet()->resetAllFormat();
    m_pReportManager->formatSet()->enableResetAllFormat(true);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_RESET);
}

void HReportMainWindow::clearFormats_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    m_pReportManager->formatSet()->resetAllFormat();
    m_pReportManager->formatSet()->enableResetFormat(true);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_RESET);
}

void HReportMainWindow::clearFommating_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    m_pReportManager->formatSet()->resetAllFormat();
    m_pReportManager->formatSet()->enableResetText(true);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_RESET);
}

void HReportMainWindow::alignTop_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    int nFormat = m_pReportManager->formatSet()->format();
    //方法有点low
    bool b = alignTopAct->isChecked();
    if(!b)
    {
        alignTopAct->setChecked(false);
        alignMiddleAct->setChecked(true);
        alignBottomAct->setChecked(false);
        nFormat|= QDT_VCENTER;
        if(QDT_TOP == (nFormat & QDT_TOP))
            nFormat &= ~QDT_TOP;
        if(QDT_BOTTOM == (nFormat & QDT_BOTTOM))
            nFormat &= ~QDT_BOTTOM;
    }
    else
    {
        alignTopAct->setChecked(true);
        alignMiddleAct->setChecked(false);
        alignBottomAct->setChecked(false);
        nFormat|= QDT_TOP;
        if(QDT_VCENTER == (nFormat & QDT_VCENTER))
            nFormat &= ~QDT_VCENTER;
        if(QDT_BOTTOM == (nFormat & QDT_BOTTOM))
            nFormat &= ~QDT_BOTTOM;
    }
    m_pReportManager->formatSet()->setFormat(nFormat);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_ALIGNMENT);
}

void HReportMainWindow::alignMiddle_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    int nFormat = m_pReportManager->formatSet()->format();
    alignTopAct->setChecked(false);
    alignMiddleAct->setChecked(true);
    alignBottomAct->setChecked(false);
    nFormat|= QDT_VCENTER;
    if(QDT_TOP == (nFormat & QDT_TOP))
        nFormat &= ~QDT_TOP;
    if(QDT_BOTTOM == (nFormat & QDT_BOTTOM))
        nFormat &= ~QDT_BOTTOM;
    m_pReportManager->formatSet()->setFormat(nFormat);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_ALIGNMENT);
}

void HReportMainWindow::alignBottom_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    int nFormat = m_pReportManager->formatSet()->format();
    bool b = alignBottomAct->isChecked();
    if(!b)
    {
        alignTopAct->setChecked(false);
        alignMiddleAct->setChecked(true);
        alignBottomAct->setChecked(false);
        nFormat |= QDT_VCENTER;
        if(QDT_TOP == (nFormat & QDT_TOP))
            nFormat &= ~QDT_TOP;
        if(QDT_BOTTOM == (nFormat & QDT_BOTTOM))
            nFormat &= ~QDT_BOTTOM;
    }
    else
    {
        alignTopAct->setChecked(false);
        alignMiddleAct->setChecked(false);
        alignBottomAct->setChecked(true);
        nFormat|= QDT_BOTTOM;
        if(QDT_TOP == (nFormat & QDT_TOP))
            nFormat &= ~QDT_TOP;
        if(QDT_VCENTER == (nFormat & QDT_VCENTER))
            nFormat &= ~QDT_VCENTER;
    }
    m_pReportManager->formatSet()->setFormat(nFormat);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_ALIGNMENT);
}

void HReportMainWindow::alignLeft_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    int nFormat = m_pReportManager->formatSet()->format();
    bool b = alignLeftAct->isChecked();
    if(!b)
    {
        alignLeftAct->setChecked(false);
        if(QDT_LEFT == (nFormat & QDT_LEFT))
            nFormat &= ~QDT_LEFT;
    }
    else
    {
        alignLeftAct->setChecked(true);
        alignCenterAct->setChecked(false);
        alignRightAct->setChecked(false);
        nFormat|= QDT_LEFT;
        if(QDT_HCENTER == (nFormat & QDT_HCENTER))
            nFormat &= ~QDT_HCENTER;
        if(QDT_RIGHT == (nFormat & QDT_RIGHT))
            nFormat &= ~QDT_RIGHT;
    }
    m_pReportManager->formatSet()->setFormat(nFormat);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_ALIGNMENT);
}

void HReportMainWindow::alignCenter_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    int nFormat = m_pReportManager->formatSet()->format();
    bool b = alignCenterAct->isChecked();
    if(!b)
    {
        alignCenterAct->setChecked(false);
        if(QDT_HCENTER == (nFormat & QDT_HCENTER))
            nFormat &= ~QDT_HCENTER;
    }
    else
    {
        alignLeftAct->setChecked(false);
        alignCenterAct->setChecked(true);
        alignRightAct->setChecked(false);
        nFormat|= QDT_HCENTER;
        if(QDT_TOP == (nFormat & QDT_TOP))
            nFormat &= ~QDT_TOP;
        if(QDT_BOTTOM == (nFormat & QDT_BOTTOM))
            nFormat &= ~QDT_BOTTOM;
    }
    m_pReportManager->formatSet()->setFormat(nFormat);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_ALIGNMENT);
}

void HReportMainWindow::alignRight_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    int nFormat = m_pReportManager->formatSet()->format();
    bool b = alignRightAct->isChecked();
    if(!b)
    {
        alignRightAct->setChecked(false);
        if(QDT_RIGHT == (nFormat & QDT_RIGHT))
            nFormat &= ~QDT_RIGHT;
    }
    else
    {
        alignLeftAct->setChecked(false);
        alignCenterAct->setChecked(false);
        alignRightAct->setChecked(true);
        nFormat |= QDT_RIGHT;
        if(QDT_LEFT == (nFormat & QDT_LEFT))
            nFormat &= ~QDT_LEFT;
        if(QDT_HCENTER == (nFormat & QDT_HCENTER))
            nFormat &= ~QDT_HCENTER;
    }
    m_pReportManager->formatSet()->setFormat(nFormat);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_ALIGNMENT);
}

void HReportMainWindow::autoWrapText_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    bool b = autoWrapTextAct->isChecked(); 
    quint32 nFormat = m_pReportManager->formatSet()->format();
    if(b)
    {
        if(QDT_SINGLELINE == (nFormat & QDT_SINGLELINE))
        {
            nFormat&=~QDT_SINGLELINE;
        }
        nFormat |= QDT_WORDBREAK;
    }
    else
    {
        if(QDT_WORDBREAK == (nFormat & QDT_WORDBREAK))
        {
            nFormat&= ~QDT_WORDBREAK;
        }
        nFormat |= QDT_SINGLELINE;
    }
    m_pReportManager->formatSet()->enableAutoWrapText(b);
    m_pReportManager->formatSet()->setFormat(nFormat);
    m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),CELL_TYPE_AUTOWRAPTEXT);
}

void HReportMainWindow::mergeCenter_clicked()
{
    //要获取是否合并，然后合并单元格，如果成功则改状态，如果失败就不改
    //如果只有一个单元格，合并失败
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    bool bok = m_pReportMainWidget->mergeCell();
    m_pReportManager->formatSet()->enableMergeCell(bok);
}

void HReportMainWindow::mergeCells_clicked()
{

}

void HReportMainWindow::mergeSplit_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    bool bok = m_pReportMainWidget->splitCell();
    m_pReportManager->formatSet()->enableMergeCell(!bok);
}

void HReportMainWindow::cellInsert_clicked()
{

}

void HReportMainWindow::gridInsertRow_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    bool bok = m_pReportMainWidget->insertGridRow();
}

void HReportMainWindow::gridInsertCol_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    bool bok = m_pReportMainWidget->insertGridColumn();
}

void HReportMainWindow::cellDelete_clicked()
{

}

void HReportMainWindow::gridRemoveRow_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    bool bok = m_pReportMainWidget->removeGridRow();
}

void HReportMainWindow::gridRemoveCol_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    bool bok = m_pReportMainWidget->removeGridColumn();
}

void HReportMainWindow::cellRowHeight_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    bool ok;
    double d = m_pReportManager->formatSet()->cellRowHeight();
    d = QInputDialog::getDouble(this, QStringLiteral("行高"),QStringLiteral("行高:"), d, -999, 999, 2, &ok);
    if (ok)
    {
        m_pReportManager->formatSet()->setCellRowHeight(d);
        m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),GRID_TYPE_ROW_HEIGHT);
    }
}

void HReportMainWindow::cellAutoRowHeight_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    m_pReportMainWidget->autoSizeRows();
}

void HReportMainWindow::cellColWidth_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    bool ok;
    double d = m_pReportManager->formatSet()->cellColumnWidth();
    d = QInputDialog::getDouble(this, QStringLiteral("列宽"),QStringLiteral("列宽:"), d, -999, 999, 2, &ok);
    if (ok)
    {
        m_pReportManager->formatSet()->setCellColumnWidth(d);
        m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),GRID_TYPE_COL_WIDTH);
    }
}

void HReportMainWindow::cellAutoColWidth_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    m_pReportMainWidget->autoSizeColumns();
}

void HReportMainWindow::cellDefaultColWidth_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    bool ok;
    double d = m_pReportManager->formatSet()->cellColumnWidth();
    d = QInputDialog::getDouble(this, tr("标准列宽"),tr("标准列宽:"), d, -999, 999, 2, &ok);
    if (ok)
        m_pReportManager->formatSet()->setDefaultColumnWidth(d);
}

void HReportMainWindow::cellSetFormat_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    m_pReportMainWidget->autoSizeColumns();
}

void HReportMainWindow::option_clicked()
{
    if(!m_pReportMainWidget || !m_pReportManager)
        return;
    HFormatSetDlg dlg(m_pReportManager);
    dlg.setTabIndex(TAB_ATTR_PRINTSHEET);
    if(QDialog::Accepted == dlg.exec())
    {
        m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),0,true);
    }
}

void HReportMainWindow::baseOption_clicked()
{
    if(!m_pReportMainWidget || !m_pReportManager)
        return;
    HFormatSetDlg dlg(m_pReportManager);
    dlg.setTabIndex(TAB_ATTR_BASE);
    if(QDialog::Accepted == dlg.exec())
    {
        m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),0,true);
    }
}

void HReportMainWindow::fontOption_clicked()
{
    if(!m_pReportMainWidget || !m_pReportManager)
        return;
    HFormatSetDlg dlg(m_pReportManager);
    dlg.setTabIndex(TAB_ATTR_FONT);
    if(QDialog::Accepted == dlg.exec())
    {
        m_pReportMainWidget->setCellFormat(m_pReportManager->formatSet(),0,true);
    }
}

void HReportMainWindow::printOption_clicked()
{

}

void HReportMainWindow::printDialog_clicked()
{
    if(!m_pReportMainWidget || !m_pReportManager)
        return;
    m_pReportMainWidget->printReportWidget();
}

void HReportMainWindow::printPreview_clicked()
{
    if(!m_pReportMainWidget || !m_pReportManager)
        return;
    m_pReportMainWidget->printPreviewReportWidget();
}

void HReportMainWindow::opSheet_clicked()
{

}

void HReportMainWindow::hideRibbon_clicked(bool b)
{
    this->m_ribbonMenuBar->setHideMode(b);
}

void HReportMainWindow::information_clicked()
{

}

void HReportMainWindow::gridCell_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    //刷新界面
    //设置字体
    HFormatSet* pFormatSet = m_pReportManager->formatSet();
    QFont font = pFormatSet->formatFont();
    boldAct->setChecked(font.bold());
    italicAct->setChecked(font.italic());
    underlineAct->setChecked(font.underline());

    int index = fontFamilyComboBox->findText(font.family());
    if(index != (int)-1)
        fontFamilyComboBox->setCurrentIndex(index);
    QString strPointSize = QString("%1").arg(font.pointSize());
    index = fontSizeComboBox->findText(strPointSize);
    if(index == (int)-1)
        fontSizeComboBox->lineEdit()->setText(strPointSize);
    else
        fontSizeComboBox->setCurrentIndex(index);

    //对齐
    quint32 nFormat = pFormatSet->format();
    alignLeftAct->setChecked(false);
    alignCenterAct->setChecked(false);
    alignRightAct->setChecked(false);
    if(QDT_LEFT == (nFormat & QDT_LEFT))
    {
        alignLeftAct->setChecked(true);
    }
    else if(QDT_HCENTER == (nFormat & QDT_HCENTER))
    {
        alignCenterAct->setChecked(true);
    }
    else if(QDT_RIGHT == (nFormat & QDT_RIGHT))
    {
        alignRightAct->setChecked(true);
    }

    alignTopAct->setChecked(false);
    alignMiddleAct->setChecked(false);
    alignBottomAct->setChecked(false);
    if(QDT_TOP == (nFormat & QDT_TOP))
    {
        alignTopAct->setChecked(true);
    }
    else if(QDT_VCENTER == (nFormat & QDT_VCENTER))
    {
        alignMiddleAct->setChecked(true);
    }
    else if(QDT_BOTTOM == (nFormat & QDT_BOTTOM))
    {
        alignBottomAct->setChecked(true);
    }

    if(QDT_WORDBREAK == (nFormat & QDT_WORDBREAK))
    {
        autoWrapTextAct->setChecked(true);
    }
}
