#ifndef HBORDERSET_H
#define HBORDERSET_H

#include <QWidget>
#include <QProxyStyle>
//颜色列表
class HNoFocusProxyStyle : public QProxyStyle
{
public:
    virtual void drawPrimitive(PrimitiveElement element, const QStyleOption * option,
        QPainter * painter, const QWidget * widget = 0) const
    {
        if (PE_FrameFocusRect == element)
        {
            //这里不做任何操作，Qt默认是绘制矩形虚线框
        }
        else
        {
            QProxyStyle::drawPrimitive(element, option,painter, widget);
        }
    }
};

namespace Ui {
class HBorderSet;
}

class HBorderSet : public QWidget
{
    Q_OBJECT

public:
    explicit HBorderSet(QWidget *parent = 0);
    ~HBorderSet();

public:
    void initLineStyleSet();
    void initBorderSet();
    void initColorSet();
    QPixmap createPenStyleIcon(Qt::PenStyle capStyle);
    void updateLineStyleSet();
    void updateColorListSet();

public slots:
    void currentIndexChanged_click(int index);
    void onBorderLeftBtn_click();
    void onBorderVerBtn_click();
    void onBorderRightBtn_click();
    void onBorderTopBtn_click();
    void onBorderHorBtn_click();
    void onBorderBottomBtn_click();
    void onBorderNoBtn_click();
    void onBorderAllBtn_click();
    void onBorderOutSideBtn_click();
    void onMoreColorBtn_click();
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void moveEvent(QMoveEvent *event);
    virtual void paintEvent(QPaintEvent *event);

private:
    Ui::HBorderSet *ui;
    QString m_strLineColor;
    QString m_strBorderLeftLineColor;//边框左线条颜色
    QString m_strBorderRightLineColor;//边框右线条颜色
    QString m_strBorderTopLineColor;//边框上线条颜色
    QString m_strBorderBottomLineColor;//边框下线条颜色
    //还有中间线条颜色 这个针对多个单元格而言，对一个单元格是没有中间线条的
    bool m_bBorderLeft;
    bool m_bBorderTop;
    bool m_bBorderRight;
    bool m_bBorderBottom;

    QStringList m_recentColorList;//最近列表
};



#endif // HBORDERSET_H
