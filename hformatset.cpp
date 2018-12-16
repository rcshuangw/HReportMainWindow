#include "hformatset.h"

HFormatSet::HFormatSet(QObject *parent) : QObject(parent)
{

}

void HFormatSet::loadDefaultFormatSet(int v,QDataStream* ds)
{
    if(!ds) return;
    quint32 n32;
    *ds>>n32;
    m_nHorizontalAlign = n32;
    *ds>>n32;
    m_nVerticalAlign = n32;
    bool b;
    *ds>>b;
    m_bAutoWrapText = b;
    *ds>>b;
    m_bMergeCell = b;

    //字体
    QString s;
    *ds>>s;
    m_strFontFamily = s;
    quint8 n8;
    *ds>>n8;
    m_nFontStyle = n8;
    *ds>>n8;
    m_nFontSize = n8;
    *ds>>b;
    m_bFontUnderline = b;
    *ds>>b;
    m_bFontBold = b;
    *ds>>b;
    m_bFontItalic = b;
    *ds>>s;
    m_strTextColor = s;
    *ds>>s;
    m_strTextBkColor = s;

    //边框
    quint16 n16;
    *ds>>n16;
    m_nBorderPenStyle = n16;
    *ds>>b;
    m_bBorderLeft = b;
    *ds>>b;
    m_bBorderTop = b;
    *ds>>b;
    m_bBorderRight = b;
    *ds>>b;
    m_bBorderBottom = b;
    *ds>>s;
    m_strBorderLineColor = s;
    *ds>>s;
    m_strBorderLeftLineColor = s;
    *ds>>s;
    m_strBorderRightLineColor = s;
    *ds>>s;
    m_strBorderTopLineColor = s;
    *ds>>s;
    m_strBorderBottomLineColor = s;

    //表格
    double db;
    *ds>>db;
    m_dCellRowHeight = db;
    *ds>>db;
    m_dCellColWidth =db;

    //打印显示
    *ds>>b;
    m_bSheetNoPrefix = b;
    *ds>>b;
    m_bSheetNoSuffix = b;
    *ds>>b;
    m_bSheetNoLength = b;
    *ds>>b;
    m_bSheetTempNo = b;
    *ds>>s;
    m_strSheetNoPrefix = s;
    *ds>>s;
    m_strSheetNoSuffix = s;
    *ds>>s;
    m_strSheetNoLength = s;
    *ds>>s;
    m_strSheetTempNo = s;

    *ds>>n16;
    m_nOpTaskWordCount = n16;
    *ds>>n16;
    m_nOpTermWordCount = n16;
    *ds>>n16;
    m_nStateChangeWordCount = n16;
    *ds>>n16;
    m_nSerialNumWordCount = n16;

    //打印设置
    *ds>>db;
    m_dPageLeftMargin = db;
    *ds>>db;
    m_dPageRightMargin = db;
    *ds>>db;
    m_dPageTopMargin = db;
    *ds>>db;
    m_dPageBottomMargin = db;
    *ds>>db;
    m_dPageHeaderHeight = db;
    *ds>>db;
    m_dPageFooterHeight = db;

    *ds>>s;
    m_strPageHeaderText = s;
    *ds>>s;
    m_strPageFooterText = s;

    *ds>>b;
    m_bPageShowGrid = b;
    *ds>>b;
    m_bPageShowCol = b;
    *ds>>b;
    m_bPageShowRow = b;
    *ds>>b;
    m_bPagePrintColour = b;
}

void HFormatSet::saveDefaultFormatSet(int v,QDataStream* ds)
{
    if(!ds) return;
    *ds<<(quint32)m_nHorizontalAlign;
    *ds<<(quint32)m_nVerticalAlign;
    *ds<<(bool)m_bAutoWrapText;
    *ds<<(bool)m_bMergeCell;

    //字体
    *ds<<(QString)m_strFontFamily;
    *ds<<(quint8)m_nFontStyle;
    *ds<<(quint8)m_nFontSize;
    *ds<<(bool)m_bFontUnderline;
    *ds<<(bool)m_bFontBold;
    *ds<<(bool)m_bFontItalic;
    *ds<<(QString)m_strTextColor;
    *ds<<(QString)m_strTextBkColor;

    //边框
    *ds<<(quint16)m_nBorderPenStyle;
    *ds<<(bool)m_bBorderLeft;
    *ds<<(bool)m_bBorderTop;
    *ds<<(bool)m_bBorderRight;
    *ds<<(bool)m_bBorderBottom;
    *ds<<(QString)m_strBorderLineColor;
    *ds<<(QString)m_strBorderLeftLineColor;
    *ds<<(QString)m_strBorderRightLineColor;
    *ds<<(QString)m_strBorderTopLineColor;
    *ds<<(QString)m_strBorderBottomLineColor;

    //表格
    *ds<<(double)m_dCellRowHeight;
    *ds<<(double)m_dCellColWidth;

    //打印显示
    *ds<<(bool)m_bSheetNoPrefix;
    *ds<<(bool)m_bSheetNoSuffix;
    *ds<<(bool)m_bSheetNoLength;
    *ds<<(bool)m_bSheetTempNo;
    *ds<<(QString)m_strSheetNoPrefix;
    *ds<<(QString)m_strSheetNoSuffix;
    *ds<<(QString)m_strSheetNoLength;
    *ds<<(QString)m_strSheetTempNo;

    *ds<<(quint16)m_nOpTaskWordCount;
    *ds<<(quint16)m_nOpTermWordCount;
    *ds<<(quint16)m_nStateChangeWordCount;
    *ds<<(quint16)m_nSerialNumWordCount;

    //打印设置
    *ds<<(double)m_dPageLeftMargin;
    *ds<<(double)m_dPageRightMargin;
    *ds<<(double)m_dPageTopMargin;
    *ds<<(double)m_dPageBottomMargin;
    *ds<<(double)m_dPageHeaderHeight;
    *ds<<(double)m_dPageFooterHeight;

    *ds<<(QString)m_strPageHeaderText;
    *ds<<(QString)m_strPageFooterText;

    *ds<<(bool)m_bPageShowGrid;
    *ds<<(bool)m_bPageShowCol;
    *ds<<(bool)m_bPageShowRow;
    *ds<<(bool)m_bPagePrintColour;
}

//基本
void HFormatSet::setHorizontalAlign(quint32 hAlign)
{
    m_nHorizontalAlign = hAlign;
}

quint32 HFormatSet::horizontalAlign()
{
    return m_nHorizontalAlign;
}

void HFormatSet::setVerticalAlign(quint32 vAlign)
{
    m_nVerticalAlign = vAlign;
}

quint32 HFormatSet::verticalAlign()
{
    return m_nVerticalAlign;
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

//字体
void HFormatSet::setFontFamily(const QString& fontFamily)
{
    m_strFontFamily = fontFamily;
}

QString HFormatSet::fontFamily()
{
    return m_strFontFamily;
}

void HFormatSet::setFontStyle(quint8 fontStyle)
{
    m_nFontStyle = fontStyle;
}

quint8 HFormatSet::fontStyle()
{
    return m_nFontStyle;
}

void HFormatSet::setFontSize(quint8 fontSize)
{
    m_nFontSize = fontSize;
}

quint8 HFormatSet::fontSize()
{
    return m_nFontSize;
}

void HFormatSet::enableFontUnderline(bool b)
{
    m_bFontUnderline = b;
}

bool HFormatSet::isFontUnderline()
{
    return m_bFontUnderline;
}

void HFormatSet::enableFontBold(bool b)
{
    m_bFontBold = b;
}

bool HFormatSet::isFontBold()
{
    return m_bFontBold;
}

void HFormatSet::enableFontItalic(bool b)
{
    m_bFontItalic = b;
}

bool HFormatSet::isFontItalic()
{
    return m_bFontItalic;
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

void HFormatSet::enableBorderLeft(bool b)
{
    m_bBorderLeft = b;
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
    m_strBorderLineColor;
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

//表格
void HFormatSet::setCellRowHeight(double d)
{
    m_dCellRowHeight = d;
}

double HFormatSet::cellRowHeight()
{
    return m_dCellRowHeight;
}

void HFormatSet::setCellColumnWidth(double d)
{
    m_dCellColWidth = d;
}

double HFormatSet::cellColumnWidth()
{
    return m_dCellColWidth;
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

void HFormatSet::setPageRightMarin(double d)
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

void HFormatSet::setPageShowColumnHeader(bool b)
{
    m_bPageShowCol = b;
}

bool HFormatSet::isPageShowColumnHeader()
{
    return m_bPageShowCol;
}

void HFormatSet::setPageShowRowHeader(bool b)
{
    m_bPageShowRow = b;
}

bool HFormatSet::isPageShowRowHeader()
{
    return m_bPageShowRow;
}

void HFormatSet::setPagePrintColour(bool b)
{
    m_bPagePrintColour = b;
}

bool HFormatSet::isPagePrintColour()
{
    return m_bPagePrintColour;
}
