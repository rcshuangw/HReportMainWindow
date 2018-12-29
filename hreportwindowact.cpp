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
    QFont font = m_pReportManager->formatSet()->formatFont();
    QString strFamily = fontFamilyComboBox->currentText();
    font.setFamily(strFamily);
    m_pReportManager->formatSet()->setFormatFont(font);
}

void HReportMainWindow::fontSizeComboBox_changed(int)
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    QFont font = m_pReportManager->formatSet()->formatFont();
    QString strSize = fontSizeComboBox->currentText();
    font.setPointSize(strSize.toUInt());
    m_pReportManager->formatSet()->setFormatFont(font);
}

void HReportMainWindow::bold_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    QFont font = m_pReportManager->formatSet()->formatFont();
    bool bBold = boldAct->isChecked();
    font.setBold(bBold);
    m_pReportManager->formatSet()->setFormatFont(font);
}

void HReportMainWindow::italic_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    QFont font = m_pReportManager->formatSet()->formatFont();
    bool italic = italicAct->isChecked();
    font.setBold(italic);
    m_pReportManager->formatSet()->setFormatFont(font);
}

void HReportMainWindow::underline_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    QFont font = m_pReportManager->formatSet()->formatFont();
    bool underline = underlineAct->isChecked();
    font.setBold(underline);
    m_pReportManager->formatSet()->setFormatFont(font);
}

void HReportMainWindow::fontSizeIncrease_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
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
}

void HReportMainWindow::fontSizeDecrease_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
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
}

void HReportMainWindow::fontColor_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    QString strTextClr = m_pReportManager->formatSet()->textColor();
    QColor clr = QColorDialog::getColor(QColor(strTextClr),this,QStringLiteral("选择颜色"));
    strTextClr = clr.name();
    m_pReportManager->formatSet()->setTextColor(strTextClr);
}

void HReportMainWindow::fontColorActGroup_clicked(QAction *action)
{
    if(!action) return;
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    QString strTextClr = action->data().toString();
    m_pReportManager->formatSet()->setTextColor(strTextClr);
}


void HReportMainWindow::fontBkColor_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    QString strTextBkClr = m_pReportManager->formatSet()->textBkColor();
    QColor clr = QColorDialog::getColor(QColor(strTextBkClr),this,QStringLiteral("选择颜色"));
    strTextBkClr = clr.name();
    m_pReportManager->formatSet()->setTextBkColor(strTextBkClr);
}

void HReportMainWindow::fontBkColorActGroup_clicked(QAction *action)
{
    if(!action) return;
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    QString strTextBkClr = action->data().toString();
    m_pReportManager->formatSet()->setTextBkColor(strTextBkClr);
}

void HReportMainWindow::borderBottom_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    m_pReportManager->formatSet()->enableBorderBottom(true);
}

void HReportMainWindow::borderTop_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    m_pReportManager->formatSet()->enableBorderTop(true);
}

void HReportMainWindow::borderLeft_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    m_pReportManager->formatSet()->enableBorderLeft(true);
}

void HReportMainWindow::borderRight_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    m_pReportManager->formatSet()->enableBorderRight(true);
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

void HReportMainWindow::clearAllFormat_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    m_pReportManager->formatSet()->enableResetAllFormat(true);
}

void HReportMainWindow::clearFormats_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    m_pReportManager->formatSet()->enableResetFormat(true);
}

void HReportMainWindow::clearFommating_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    m_pReportManager->formatSet()->enableResetText(true);
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
            nFormat |= ~QDT_TOP;
        if(QDT_BOTTOM == (nFormat & QDT_BOTTOM))
            nFormat |= ~QDT_BOTTOM;
    }
    else
    {
        alignTopAct->setChecked(true);
        alignMiddleAct->setChecked(false);
        alignBottomAct->setChecked(false);
        nFormat|= QDT_TOP;
        if(QDT_VCENTER == (nFormat & QDT_VCENTER))
            nFormat |= ~QDT_VCENTER;
        if(QDT_BOTTOM == (nFormat & QDT_BOTTOM))
            nFormat |= ~QDT_BOTTOM;
    }
    m_pReportManager->formatSet()->setFormat(nFormat);
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
        nFormat |= ~QDT_TOP;
    if(QDT_BOTTOM == (nFormat & QDT_BOTTOM))
        nFormat |= ~QDT_BOTTOM;
    m_pReportManager->formatSet()->setFormat(nFormat);
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
            nFormat |= ~QDT_TOP;
        if(QDT_BOTTOM == (nFormat & QDT_BOTTOM))
            nFormat |= ~QDT_BOTTOM;
    }
    else
    {
        alignTopAct->setChecked(false);
        alignMiddleAct->setChecked(false);
        alignBottomAct->setChecked(true);
        nFormat|= QDT_BOTTOM;
        if(QDT_TOP == (nFormat & QDT_TOP))
            nFormat |= ~QDT_TOP;
        if(QDT_VCENTER == (nFormat & QDT_VCENTER))
            nFormat |= ~QDT_VCENTER;
    }
    m_pReportManager->formatSet()->setFormat(nFormat);
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
            nFormat |= ~QDT_LEFT;
    }
    else
    {
        alignLeftAct->setChecked(true);
        alignCenterAct->setChecked(false);
        alignRightAct->setChecked(false);
        nFormat|= QDT_LEFT;
        if(QDT_HCENTER == (nFormat & QDT_HCENTER))
            nFormat |= ~QDT_HCENTER;
        if(QDT_RIGHT == (nFormat & QDT_RIGHT))
            nFormat |= ~QDT_RIGHT;
    }
    m_pReportManager->formatSet()->setFormat(nFormat);
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
            nFormat |= ~QDT_HCENTER;
    }
    else
    {
        alignLeftAct->setChecked(false);
        alignCenterAct->setChecked(true);
        alignRightAct->setChecked(false);
        nFormat|= QDT_HCENTER;
        if(QDT_TOP == (nFormat & QDT_TOP))
            nFormat |= ~QDT_TOP;
        if(QDT_BOTTOM == (nFormat & QDT_BOTTOM))
            nFormat |= ~QDT_BOTTOM;
    }
    m_pReportManager->formatSet()->setFormat(nFormat);
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
            nFormat |= ~QDT_RIGHT;
    }
    else
    {
        alignLeftAct->setChecked(false);
        alignCenterAct->setChecked(false);
        alignRightAct->setChecked(true);
        nFormat |= QDT_RIGHT;
        if(QDT_LEFT == (nFormat & QDT_LEFT))
            nFormat |= ~QDT_LEFT;
        if(QDT_HCENTER == (nFormat & QDT_HCENTER))
            nFormat |= ~QDT_HCENTER;
    }
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
            nFormat = nFormat & ~QDT_SINGLELINE;
        }
        nFormat |= QDT_WORDBREAK;
    }
    else
    {
        if(QDT_WORDBREAK == (nFormat & QDT_WORDBREAK))
        {
            nFormat = nFormat & ~QDT_WORDBREAK;
        }
        nFormat |= QDT_SINGLELINE;
    }
    m_pReportManager->formatSet()->enableAutoWrapText(b);
    m_pReportManager->formatSet()->setFormat(nFormat);
}

void HReportMainWindow::mergeCenter_clicked()
{
    //要获取是否合并，然后合并单元格，如果成功则改状态，如果失败就不改
    //如果只有一个单元格，合并失败

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
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    bool ok;
    double d = m_pReportManager->formatSet()->cellRowHeight();
    d = QInputDialog::getDouble(this, tr("行高"),tr("行高:"), d, -999, 999, 2, &ok);
    if (ok)
        m_pReportManager->formatSet()->setCellRowHeight(d);
}

void HReportMainWindow::cellAutoRowHeight_clicked()
{

}

void HReportMainWindow::cellColWidth_clicked()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    bool ok;
    double d = m_pReportManager->formatSet()->cellColumnWidth();
    d = QInputDialog::getDouble(this, tr("列宽"),tr("列宽:"), d, -999, 999, 2, &ok);
    if (ok)
        m_pReportManager->formatSet()->setCellColumnWidth(d);
}

void HReportMainWindow::cellAutoColWidth_clicked()
{

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

}

void HReportMainWindow::option_clicked()
{
    HFormatSetDlg dlg(m_pReportManager);
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
