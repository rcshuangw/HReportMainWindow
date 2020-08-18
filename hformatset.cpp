#include "hformatset.h"
#include "hconfigapi.h"
#include <QDataStream>
HFormatSet::HFormatSet(QObject *parent) : QObject(parent)
{
    m_bPageShowGrid = false;
    m_bPageShowCol = false;
    m_bPageShowRow = false;
    m_bPagePrintColour = false;

    m_strText = "";
    m_nFormatAlign = 0;

    m_bAutoWrapText = false;
    m_bMergeCell = false;

    //边框

    m_bBorderOutSide = false;
    m_bBorderLeft = false;                  //左边框
    m_bBorderTop = false;                   //上边框
    m_bBorderRight = false;                 //右边框
    m_bBorderBottom = false;                //下边框

    initPrintFormat();
}

void HFormatSet::initPrintFormat()
{
    /*
    QVariant var;
    getSettingValue(SYS_SET_PRINT,PRINT_TOP_MARGIN,var);
    setPageTopMargin(var.toDouble());
    getSettingValue(SYS_SET_PRINT,PRINT_BOTTOM_MARGIN,var);
    setPageBottomMargin(var.toDouble());
    getSettingValue(SYS_SET_PRINT,PRINT_LEFT_MARGIN,var);
    setPageLeftMargin(var.toDouble());
    getSettingValue(SYS_SET_PRINT,PRINT_RIGHT_MARGIN,var);
    setPageRightMargin(var.toDouble());
    getSettingValue(SYS_SET_PRINT,PRINT_HEAD_MARGIN,var);
    setPageHeaderHeight(var.toDouble());
    getSettingValue(SYS_SET_PRINT,PRINT_FOOT_MARGIN,var);
    setPageFooterHeight(var.toDouble());

    getSettingValue(SYS_SET_PRINT,PRINT_HEAD_TEXT,var);
    setPageHeaderText(var.toString());
    getSettingValue(SYS_SET_PRINT,PRINT_FOOT_TEXT,var);
    setPageFooterText(var.toString());

    getSettingValue(SYS_SET_PRINT,PRINT_SHOW_GRIDLINE,var);
    enablePageShowGrid(var.toBool());
    getSettingValue(SYS_SET_PRINT,PRINT_HORIZONTAL_HEAD,var);
    enablePageShowRowHeader(var.toBool());
    getSettingValue(SYS_SET_PRINT,PRINT_VERTICVAL_HEAD,var);
    enablePageShowColumnHeader(var.toBool());
    getSettingValue(SYS_SET_PRINT,PRINT_SHOW_COLOR,var);
    enablePagePrintColour(var.toBool());


    //QVariant var;
    getSettingValue(SYS_SET_PRINT,PRINT_SHEETNO_PREFIX,var);
    enableSheetNoPrefix(var.toBool());
    getSettingValue(SYS_SET_PRINT,PRINT_SHEETNO_PREFIX_TEXT,var);
    setSheetNoPrefix(var.toString());
    getSettingValue(SYS_SET_PRINT,PRINT_SHEETNO_SUFFIX,var);
    enableSheetNoSuffix(var.toBool());
    getSettingValue(SYS_SET_PRINT,PRINT_SHEETNO_SUFFIX_TEXT,var);
    setSheetNoSuffix(var.toString());
    getSettingValue(SYS_SET_PRINT,PRINT_SHEETNO_LENGTH,var);
    enableSheetNoLength(var.toBool());
    getSettingValue(SYS_SET_PRINT,PRINT_SHEETNO_LENGTH_TEXT,var);
    setSheetNoLength(var.toString());
    getSettingValue(SYS_SET_PRINT,PRINT_SHEET_TEMPNO,var);
    enableSheetTempNo(var.toBool());
    getSettingValue(SYS_SET_PRINT,PRINT_SHEET_TEMPNO_TEXT,var);
    setSheetTempNo(var.toString());
    //任务长度设置

    getSettingValue(SYS_SET_PRINT,PRINT_OPTASK_LENGTH,var);
    setOpTaskWordCount(var.toUInt());
    getSettingValue(SYS_SET_PRINT,PRINT_OPITEM_LENGTH,var);
    setOpTermWordCount(var.toUInt());
    getSettingValue(SYS_SET_PRINT,PRINT_STATECHANGE_LENGTH,var);
    setStateChangeWordCount(var.toUInt());
    getSettingValue(SYS_SET_PRINT,PRINT_SERIALNO_LENGTH,var);
    setSerialNumWordCount(var.toUInt());*/

}

void HFormatSet::enableAutoWrapText(bool bAutoWrapText)
{
    m_bAutoWrapText = bAutoWrapText;
}

bool HFormatSet::isAutoWrapText()
{
    return m_bAutoWrapText;
}

void HFormatSet::enableMergeCell(bool bMergCell)
{
    m_bMergeCell = bMergCell;
}

bool HFormatSet::isMergeCell()
{
    return m_bMergeCell;
}

void HFormatSet::setTextColor(const QString& clr)
{
    m_strTextColor = clr;
}

QString HFormatSet::textColor()
{
    return m_strTextColor;
}

void HFormatSet::setTextBkColor(const QString& clr)
{
    m_strTextBkColor = clr;
}

QString HFormatSet::textBkColor()
{
    return m_strTextBkColor;
}

//边框
void HFormatSet::setBorderPenStyle(quint16 penStyle)
{
    m_nBorderPenStyle = penStyle;
}

quint16 HFormatSet::borderPenStyle()
{
    return m_nBorderPenStyle;
}

void HFormatSet::setBorderLeftPenStyle(quint16 v)
{
    m_nBorderLeftPenStyle = v;
}

quint16 HFormatSet::borderLeftPenStyle()
{
    return m_nBorderLeftPenStyle;
}

void HFormatSet::setBorderRightPenStyle(quint16 v)
{
    m_nBorderRightPenStyle = v;
}

quint16 HFormatSet::borderRightPenStyle()
{
    return m_nBorderRightPenStyle;
}

void HFormatSet::setBorderTopPenStyle(quint16 v)
{
    m_nBorderTopPenStyle = v;
}

quint16 HFormatSet::borderTopPenStyle()
{
    return m_nBorderTopPenStyle;
}

void HFormatSet::setBorderBottomPenStyle(quint16 v)
{
    m_nBorderBottomPenStyle = v;
}

quint16 HFormatSet::borderBottomPenStyle()
{
    return m_nBorderBottomPenStyle;
}

void HFormatSet::resetEnableBorder()
{
    m_bBorderLeft = m_bBorderRight = m_bBorderTop = m_bBorderBottom = false;
}

void HFormatSet::enableBorderLeft(bool b)
{
    m_bBorderLeft = b;
}

bool HFormatSet::isBorderOutSide()
{
    return m_bBorderOutSide;
}

void HFormatSet::enableBorderOutSide(bool b)
{
    m_bBorderOutSide = b;
}

bool HFormatSet::isBorderLeft()
{
    return m_bBorderLeft;
}

void HFormatSet::enableBorderRight(bool b)
{
    m_bBorderRight = b;
}

bool HFormatSet::isBorderRight()
{
    return m_bBorderRight;
}

void HFormatSet::enableBorderTop(bool b)
{
    m_bBorderTop = b;
}

bool HFormatSet::isBorderTop()
{
    return m_bBorderTop;
}

void HFormatSet::enableBorderBottom(bool b)
{
    m_bBorderBottom = b;
}

bool HFormatSet::isBorderBottom()
{
    return m_bBorderBottom;
}

void HFormatSet::setBorderLineColor(const QString& clr)
{
    m_strBorderLineColor = clr;
}

QString HFormatSet::borderLineColor()
{
    return m_strBorderLineColor;
}

void HFormatSet::setBorderLeftLineColor(const QString& clr)
{
    m_strBorderLeftLineColor = clr;
}

QString HFormatSet::borderLeftLineColor()
{
    return m_strBorderLeftLineColor;
}

void HFormatSet::setBorderRightLineColor(const QString& clr)
{
    m_strBorderRightLineColor = clr;
}

QString HFormatSet::borderRightLineColor()
{
    return m_strBorderRightLineColor;
}

void HFormatSet::setBorderTopLineColor(const QString& clr)
{
    m_strBorderTopLineColor = clr;
}

QString HFormatSet::borderTopLineColor()
{
    return m_strBorderTopLineColor;
}

void HFormatSet::setBorderBottomLineColor(const QString& clr)
{
    m_strBorderBottomLineColor = clr;
}

QString HFormatSet::borderBottomLineColor()
{
    return m_strBorderBottomLineColor;
}

//清除
void HFormatSet::resetAllFormat()
{
    m_bResetAllFormat = false;
    m_bResetCellFormat = false;
    m_bResetText = false;
}

void HFormatSet::enableResetFormat(bool b)
{
    m_bResetCellFormat = b;
}

bool HFormatSet::isResetFormat()
{
    return m_bResetCellFormat;
}

void HFormatSet::enableResetText(bool b)
{
    m_bResetText = b;
}

bool HFormatSet::isResetText()
{
    return m_bResetText;
}

void HFormatSet::enableResetAllFormat(bool b)
{
    m_bResetAllFormat = b;
}

bool HFormatSet::isResetAllFormat()
{
    return m_bResetAllFormat;
}

//表格
void HFormatSet::setCellRowHeight(double d)
{
    m_fCellRowHeight = d;
}

double HFormatSet::cellRowHeight()
{
    return m_fCellRowHeight;
}

void HFormatSet::setCellColumnWidth(double d)
{
    m_fCellColWidth = d;
}

double HFormatSet::cellColumnWidth()
{
    return m_fCellColWidth;
}

void HFormatSet::setDefaultColumnWidth(double d)
{
    m_fDefaultColWidth = d;
}

double HFormatSet::defaultColumnWidth()
{
    return m_fDefaultColWidth;
}

//打印相关
void HFormatSet::enableSheetNoPrefix(bool b)
{
    m_bSheetNoPrefix = b;
}

bool HFormatSet::isSheetNoPrefix()
{
    return m_bSheetNoPrefix;
}

void HFormatSet::enableSheetNoSuffix(bool b)
{
    m_bSheetNoSuffix = b;
}

bool HFormatSet::isSheetNoSuffix()
{
    return m_bSheetNoSuffix;
}

void HFormatSet::enableSheetNoLength(bool b)
{
    m_bSheetNoLength = b;
}

bool HFormatSet::isSheetNoLength()
{
    return m_bSheetNoLength;
}

void HFormatSet::enableSheetTempNo(bool b)
{
    m_bSheetTempNo = b;
}

bool HFormatSet::isSheetTempNo()
{
    return m_bSheetTempNo;
}

void HFormatSet::setSheetNoPrefix(const QString& prefix)
{
    m_strSheetNoPrefix = prefix;
}

QString HFormatSet::sheetNoPrefix()
{
    return m_strSheetNoPrefix;
}

void HFormatSet::setSheetNoSuffix(const QString& suffix)
{
    m_strSheetNoSuffix = suffix;
}

QString HFormatSet::sheetNoSuffix()
{
    return m_strSheetNoSuffix;
}

void HFormatSet::setSheetNoLength(const QString& length)
{
    m_strSheetNoLength = length;
}

QString HFormatSet::sheetNoLength()
{
    return m_strSheetNoLength;
}

void HFormatSet::setSheetTempNo(const QString& no)
{
    m_strSheetTempNo = no;
}

QString HFormatSet::sheetTempNo()
{
    return m_strSheetTempNo;
}

void HFormatSet::setOpTaskWordCount(quint16 count)
{
    m_nOpTaskWordCount = count;
}

quint16 HFormatSet::opTaskWordCount()
{
    return m_nOpTaskWordCount;
}

void HFormatSet::setOpTermWordCount(quint16 count)
{
    m_nOpTermWordCount = count;
}

quint16 HFormatSet::opTermWordCount()
{
    return m_nOpTermWordCount;
}

void HFormatSet::setStateChangeWordCount(quint16 count)
{
    m_nStateChangeWordCount = count;
}

quint16 HFormatSet::stateChangeWordCount()
{
    return m_nStateChangeWordCount;
}

void HFormatSet::setSerialNumWordCount(quint16 count)
{
    m_nSerialNumWordCount = count;
}

quint16 HFormatSet::serialNumWordCount()
{
    return m_nSerialNumWordCount;
}

//打印设置
void HFormatSet::setPageLeftMargin(double d)
{
    m_dPageLeftMargin = d;
}

double HFormatSet::pageLeftMargin()
{
    return m_dPageLeftMargin;
}

void HFormatSet::setPageRightMargin(double d)
{
    m_dPageRightMargin = d;
}

double HFormatSet::pageRightMargin()
{
    return m_dPageRightMargin;
}

void HFormatSet::setPageTopMargin(double d)
{
    m_dPageTopMargin = d;
}

double HFormatSet::pageTopMargin()
{
    return m_dPageTopMargin;
}

void HFormatSet::setPageBottomMargin(double d)
{
    m_dPageBottomMargin = d;
}

double HFormatSet::pageBottomMargin()
{
    return m_dPageBottomMargin;
}

void HFormatSet::setPageHeaderHeight(double d)
{
    m_dPageHeaderHeight = d;
}

double HFormatSet::pageHeaderHeight()
{
    return m_dPageHeaderHeight;
}

void HFormatSet::setPageFooterHeight(double d)
{
    m_dPageFooterHeight = d;
}

double HFormatSet::pageFooterHeight()
{
    return m_dPageFooterHeight;
}

void HFormatSet::setPageHeaderText(const QString& text)
{
    m_strPageHeaderText = text;
}

QString HFormatSet::pageHeaderText()
{
    return m_strPageHeaderText;
}

void HFormatSet::setPageFooterText(const QString& text)
{
    m_strPageFooterText = text;
}

QString HFormatSet::pageFooterText()
{
    return m_strPageFooterText;
}

void HFormatSet::enablePageShowGrid(bool b)
{
    m_bPageShowGrid = b;
}

bool HFormatSet::isPageShowGrid()
{
    return m_bPageShowGrid;
}

void HFormatSet::enablePageShowColumnHeader(bool b)
{
    m_bPageShowCol = b;
}

bool HFormatSet::isPageShowColumnHeader()
{
    return m_bPageShowCol;
}

void HFormatSet::enablePageShowRowHeader(bool b)
{
    m_bPageShowRow = b;
}

bool HFormatSet::isPageShowRowHeader()
{
    return m_bPageShowRow;
}

void HFormatSet::enablePagePrintColour(bool b)
{
    m_bPagePrintColour = b;
}

bool HFormatSet::isPagePrintColour()
{
    return m_bPagePrintColour;
}
