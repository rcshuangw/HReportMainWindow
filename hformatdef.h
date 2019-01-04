#ifndef HFORMATDEF_H
#define HFORMATDEF_H
//定义单元格的相关属性
#define CELL_TYPE_ALIGNMENT       0x01
#define CELL_TYPE_FONT            0x02
#define CELL_TYPE_BORDER          0x03
#define CELL_TYPE_COLOR           0x04
#define CELL_TYPE_AUTOWRAPTEXT    0x05
#define CELL_TYPE_RESET           0x06

//定义表格
#define GRID_TYPE_MERGECELL       0x60
#define GRID_TYPE_SPLITCELL       0x61
#define GRID_TYPE_ROW_HEIGHT      0x62
#define GRID_TYPE_COL_WIDTH       0x63

//插入 删除操作，插入和删除都有行，列，单元格三种
#define GRID_TYPE_INSERT          0x90
#define GRID_TYPE_REMOVE          0x91




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
