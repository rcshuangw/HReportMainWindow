#ifndef HFORMATSET_H
#define HFORMATSET_H

#include <QObject>
//主要是读取和存储设置的相关配置
class HFormatSet : public QObject
{
    Q_OBJECT
public:
    explicit HFormatSet(QObject *parent = 0);

signals:

public slots:

public:

    //基本
    quint32   m_nHorizontalAlign;       //水平对齐
    quint32   m_nVerticalAlign;         //垂直对齐
    bool    m_bAutoWrapText;            //自动换行
    bool    m_bMergeCell;               //合并单元格

    //字体
    QString m_strFontFamily;            //字体
    quint8  m_nFontStyle;               //字体风格
    quint8  m_nFontSize;                //字体大小
    quint8  m_nFontUnderline;           //字体下划线
    QString m_strFontColor;             //字体颜色

    //边框
    quint16 m_nPenStyle;                 //边框线形
    bool m_bBorderLeft;                  //左边框
    bool m_bBorderTop;                   //上边框
    bool m_bBorderRight;                 //右边框
    bool m_bBorderBottom;                //下边框
    QString m_strDefaultLineColor;       //默认边框颜色
    QString m_strBorderLeftLineColor;    //左边框颜色
    QString m_strBorderRightLineColor;   //右边框颜色
    QString m_strBorderTopLineColor;     //上边框颜色
    QString m_strBorderBottomLineColor;  //下边框颜色

    //打印显示
    bool m_bSheetNoPrefix;               //票号前缀
    bool m_bSheetNoSuffix;               //票号后缀
    bool m_bSheetNoLength;               //票号长度
    bool m_bSheetTempNo;                 //临时票号
    QString m_strSheetNoPrefix;
    QString m_strSheetNoSuffix;
    QString m_strSheetNoLength;
    QString m_strSheetTempNo;

    quint16 m_strOpTaskWordCount;        //操作任务字符长度
    quint16 m_nOpTermWordCount;          //操作项目字符长度
    quint16 m_nStateChangeWordCount;     //状态转换字符长度
    quint16 m_nSerialNumWordCount;       //流水号字符长度

    //打印设置
    double m_dLeftMargin;                //左边距
    double m_dRightMargin;               //右边距
    double m_dTopMargin;                 //上边距
    double m_dBottomMargin;              //下边距
    double m_dHeadMargin;                //头边距
    double m_dTailMargin;                //尾边距

    QString m_strPageHead;               //头文字
    QString m_strPageTail;               //尾文字

    bool m_bEnableShowGrid;              //显示网格
    bool m_bEnableShowCol;               //显示列
    bool m_bEnableShowRow;               //显示行
    bool m_bEnableShowColor;             //彩色打印


};

#endif // HFORMATSET_H
