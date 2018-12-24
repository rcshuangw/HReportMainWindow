#ifndef HFORMATDEF_H
#define HFORMATDEF_H
//定义表格的相关属性
#define CELL_TYPE_HORIZONTAL      0x01
#define CELL_TYPE_VERTICAL        0x02
#define CELL_TYPE_AUTOWRAPTEXT    0x03
#define CELL_TYPE_MERGECELL       0x04

#define CELL_TYPE_FONT_FAMILY     0x05
#define CELL_TYPE_FONT_STYLE      0x06
#define CELL_TYPE_FONT_SIZE       0x07
#define CELL_TYPE_FONT_UNDERLINE  0x08
#define CELL_TYPE_FONT_BOLD       0x09
#define CELL_TYPE_FONT_ITALIC     0x0A
#define CELL_TYPE_TEXT_COLOR      0x0B
#define CELL_TYPE_TEXTBK_COLOE    0x0C

//边框只要1个就行了
#define CELL_TYPE_BORDER_All            0x0D

#define GRID_TYPE_ROW_HEIGHT            0x14
#define GRID_TYPE_COL_WIDTH             0x15


  /*  //打印相关
    void enableSheetNoPrefix(bool);
    bool isSheetNoPrefix();
    void enableSheetNoSuffix(bool);
    bool isSheetNoSuffix();
    void enableSheetNoLength(bool);
    bool isSheetNoLength();
    void enableSheetTempNo(bool);
    bool isSheetTempNo();
    void setSheetNoPrefix(const QString&);
    QString sheetNoPrefix();
    void setSheetNoSuffix(const QString&);
    QString sheetNoSuffix();
    void setSheetNoLength(const QString&);
    QString sheetNoLength();
    void setSheetTempNo(const QString&);
    QString sheetTempNo();

    void setOpTaskWordCount(quint16);
    quint16 opTaskWordCount();
    void setOpTermWordCount(quint16);
    quint16 opTermWordCount();
    void setStateChangeWordCount(quint16);
    quint16 stateChangeWordCount();
    void setSerialNumWordCount(quint16);
    quint16 serialNumWordCount();

*/
    //打印设置
#define GRID_TYPE_PRINT_MARGIN 0x 20
/*
    void setPageLeftMargin(double);
    double pageLeftMargin();
    void setPageRightMarin(double);
    double pageRightMargin();
    void setPageTopMargin(double);
    double pageTopMargin();
    void setPageBottomMargin(double);
    double pageBottomMargin();
    void setPageHeaderHeight(double);
    double pageHeaderHeight();
    void setPageFooterHeight(double);
    double pageFooterHeight();

    void setPageHeaderText(const QString&);
    QString pageHeaderText();
    void setPageFooterText(const QString&);
    QString pageFooterText();

    void enablePageShowGrid(bool);
    bool isPageShowGrid();
    void setPageShowColumnHeader(bool);
    bool isPageShowColumnHeader();
    void setPageShowRowHeader(bool);
    bool isPageShowRowHeader();
    void setPagePrintColour(bool);
    bool isPagePrintColour();
*/



#endif // HFORMATDEF_H
