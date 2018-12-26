#include "mainwindow.h"
#include "hformatsetdlg.h"
#include "hreportnewdlg.h"
#include "hgridreportmgr.h"
#include "hgridctrlhelper.h"
#include "hreporttreewidget.h"
#include "hreportmaiwidget.h"
#include "hgridcelldef.h"
#include "SARibbonComboBox.h"
#include "hformatset.h"
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
    if(-1 == index || !m_pReportManager)
        return;
    QString strFamily = fontFamilyComboBox->currentText();
    m_pReportManager->formatSet()->setFontFamily(strFamily);
}

void HReportMainWindow::fontSizeComboBox_changed(int)
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
    QString strFontSize = fontSizeComboBox->currentText();
    if(strFontSize.toInt() >= 255)
        return;
    int nFontSize = strFontSize.toInt();
    nFontSize++;
    strFontSize = QString("%1").arg(nFontSize);
    fontSizeComboBox->setCurrentText(strFontSize);
}

void HReportMainWindow::fontSizeDecrease_clicked()
{
    QString strFontSize = fontSizeComboBox->currentText();
    if(strFontSize.toInt() <= 1)
        return;
    int nFontSize = strFontSize.toInt();
    nFontSize--;
    strFontSize = QString("%1").arg(nFontSize);
    fontSizeComboBox->setCurrentText(strFontSize);
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
    bool b = alignTopAct->isChecked();
    if(!b)
    {
        alignTopAct->setChecked(false);
    }
    else
    {
        alignTopAct->setChecked(true);
        alignMiddleAct->setChecked(false);
        alignBottomAct->setChecked(false);
    }
}

void HReportMainWindow::alignMiddle_clicked()
{
    bool b = alignMiddleAct->isChecked();
    if(!b)
    {
        alignMiddleAct->setChecked(false);
    }
    else
    {
        alignTopAct->setChecked(false);
        alignMiddleAct->setChecked(true);
        alignBottomAct->setChecked(false);
    }
}

void HReportMainWindow::alignBottom_clicked()
{
    bool b = alignBottomAct->isChecked();
    if(!b)
    {
        alignBottomAct->setChecked(false);
    }
    else
    {
        alignTopAct->setChecked(false);
        alignMiddleAct->setChecked(false);
        alignBottomAct->setChecked(true);
    }
}

void HReportMainWindow::alignLeft_clicked()
{
    //方法有点low
    bool b = alignLeftAct->isChecked();
    if(!b)
    {
        alignLeftAct->setChecked(false);
        alignCenterAct->setChecked(true);
        alignRightAct->setChecked(false);
    }
    else
    {
        alignLeftAct->setChecked(true);
        alignCenterAct->setChecked(false);
        alignRightAct->setChecked(false);
    }
}

void HReportMainWindow::alignCenter_clicked()
{
    //bool b = alignCenterAct->isChecked();
    //if(!b)
    {
        alignLeftAct->setChecked(false);
        alignCenterAct->setChecked(true);
        alignRightAct->setChecked(false);
    }
    //else
    //{
        //alignLeftAct->setChecked(true);
      //  alignCenterAct->setChecked(true);
        //alignRightAct->setChecked(false);
    //}
}

void HReportMainWindow::alignRight_clicked()
{
    bool b = alignRightAct->isChecked();
    if(!b)
    {
        alignLeftAct->setChecked(false);
        alignCenterAct->setChecked(true);
        alignRightAct->setChecked(false);
    }
    else
    {
        alignLeftAct->setChecked(false);
        alignCenterAct->setChecked(false);
        alignRightAct->setChecked(true);
    }
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

void HReportMainWindow::hideRibbon_clicked()
{

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
    if(QDT_LEFT == (nFormat & QDT_LEFT))
    {
        alignLeftAct->setChecked(true);
        alignTop_clicked();
    }
    else if(QDT_HCENTER == (nFormat & QDT_HCENTER))
    {
        alignCenterAct->setChecked(true);
        alignCenter_clicked();
    }
    else if(QDT_RIGHT == (nFormat & QDT_RIGHT))
    {
        alignRightAct->setChecked(true);
        alignRight_clicked();
    }

    if(QDT_TOP == (nFormat & QDT_TOP))
    {
        alignTopAct->setChecked(true);
        alignTop_clicked();
    }
    else if(QDT_VCENTER == (nFormat & QDT_VCENTER))
    {
        alignMiddleAct->setChecked(true);
        alignMiddle_clicked();
    }
    else if(QDT_BOTTOM == (nFormat & QDT_BOTTOM))
    {
        alignBottomAct->setChecked(true);
        alignBottom_clicked();
    }

    if(QDT_WORDBREAK == (nFormat & QDT_WORDBREAK))
    {
        autoWrapTextAct->setChecked(true);
    }
}
