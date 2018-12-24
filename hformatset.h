#ifndef HFORMATSET_H
#define HFORMATSET_H

#include <QObject>
//主要是读取和存储设置的相关配置
//界面发生修改后，如何更改到表格或者选择表格后，状态如何改变到界面上？
//界面发生修改后，通过设置HFormatSet对象，然后要设置变化的类型，然后发送到HGridCtrlWidget里的函数，然后函数改变到表格里
//当点击表格后，要把表格状态赋值到HFormatSet对象，然后通过信号一直发送到QMainWindow处，QMainWindow里面要有对应处理函数
class HFormatSet : public QObject
{
    Q_OBJECT
public:
    explicit HFormatSet(QObject *parent = 0);

public:
    void loadDefaultFormatSet(int v,QDataStream* ds);
    void saveDefaultFormatSet(int v,QDataStream* ds);

public:
    //基本
    void setHorizontalAlign(quint32 hAlign);
    quint32 horizontalAlign();
    void setVerticalAlign(quint32 vAlign);
    quint32 verticalAlign();
    void enableAutoWrapText(bool bAutoWrapText);
    bool isAutoWrapText();
    void enableMergeCell(bool bMergCell);
    bool isMergeCell();

    //字体
    void setFontFamily(const QString& fontFamily);
    QString fontFamily();
    void setFontStyle(quint8);
    quint8 fontStyle();
    void setFontSize(quint8);
    quint8 fontSize();
    void enableFontUnderline(bool);
    bool isFontUnderline();
    void enableFontBold(bool);
    bool isFontBold();
    void enableFontItalic(bool);
    bool isFontItalic();
    void setTextColor(const QString&);
    QString textColor();
    void setTextBkColor(const QString&);
    QString textBkColor();

    //边框
    void setBorderPenStyle(quint16);
    quint16 borderPenStyle();
    void setBorderLeftPenStyle(quint16);
    quint16 borderLeftPenStyle();
    void setBorderRightPenStyle(quint16);
    quint16 borderRightPenStyle();
    void setBorderTopPenStyle(quint16);
    quint16 borderTopPenStyle();
    void setBorderBottomPenStyle(quint16);
    quint16 borderBottomPenStyle();
    void enableBorder(bool);
    bool isBorder();
    void enableBorderLeft(bool);
    bool isBorderLeft();
    void enableBorderRight(bool);
    bool isBorderRight();
    void enableBorderTop(bool);
    bool isBorderTop();
    void enableBorderBottom(bool);
    bool isBorderBottom();
    void setBorderLineColor(const QString&);
    QString borderLineColor();
    void setBorderLeftLineColor(const QString&);
    QString borderLeftLineColor();
    void setBorderRightLineColor(const QString&);
    QString borderRightLineColor();
    void setBorderTopLineColor(const QString&);
    QString borderTopLineColor();
    void setBorderBottomLineColor(const QString&);
    QString borderBottomLineColor();

    //表格
    void setCellRowHeight(double);
    double cellRowHeight();
    void setCellColumnWidth(double);
    double cellColumnWidth();

    //打印相关
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


    //打印设置
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

signals:

public slots:

private:

    //基本
    quint32   m_nHorizontalAlign;       //水平对齐
    quint32   m_nVerticalAlign;         //垂直对齐
    bool    m_bAutoWrapText;            //自动换行
    bool    m_bMergeCell;               //合并单元格

    //字体
    QString m_strFontFamily;            //字体
    quint8  m_nFontStyle;               //字体风格
    quint8  m_nFontSize;                //字体大小
    bool    m_bFontUnderline;           //字体下划线
    bool    m_bFontBold;                //字体加粗
    bool    m_bFontItalic;              //字体倾斜
    QString m_strTextColor;             //字体颜色
    QString m_strTextBkColor;           //字体背景颜色

    //边框
    quint16 m_nBorderPenStyle;                 //边框线形
    bool m_bBorderLeft;                  //左边框
    bool m_bBorderTop;                   //上边框
    bool m_bBorderRight;                 //右边框
    bool m_bBorderBottom;                //下边框
    QString m_strBorderLineColor;        //默认边框颜色
    QString m_strBorderLeftLineColor;    //左边框颜色
    QString m_strBorderRightLineColor;   //右边框颜色
    QString m_strBorderTopLineColor;     //上边框颜色
    QString m_strBorderBottomLineColor;  //下边框颜色

    //表格
    double m_dCellRowHeight;                //默认表格行高
    double m_dCellColWidth;                 //默认表格列宽

    //打印显示
    bool m_bSheetNoPrefix;               //票号前缀
    bool m_bSheetNoSuffix;               //票号后缀
    bool m_bSheetNoLength;               //票号长度
    bool m_bSheetTempNo;                 //临时票号
    QString m_strSheetNoPrefix;
    QString m_strSheetNoSuffix;
    QString m_strSheetNoLength;
    QString m_strSheetTempNo;

    quint16 m_nOpTaskWordCount;          //操作任务字符长度
    quint16 m_nOpTermWordCount;          //操作项目字符长度
    quint16 m_nStateChangeWordCount;     //状态转换字符长度
    quint16 m_nSerialNumWordCount;       //流水号字符长度

    //打印设置
    double m_dPageLeftMargin;                //左边距
    double m_dPageRightMargin;               //右边距
    double m_dPageTopMargin;                 //上边距
    double m_dPageBottomMargin;              //下边距
    double m_dPageHeaderHeight;              //头边距
    double m_dPageFooterHeight;              //尾边距

    QString m_strPageHeaderText;             //头文字
    QString m_strPageFooterText;             //尾文字

    bool m_bPageShowGrid;              //显示网格
    bool m_bPageShowCol;               //显示列
    bool m_bPageShowRow;               //显示行
    bool m_bPagePrintColour;           //彩色打印
};

#endif // HFORMATSET_H
