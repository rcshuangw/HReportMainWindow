#ifndef HBORDERSET_H
#define HBORDERSET_H

#include <QWidget>
#include <QProxyStyle>
class HReportManager;
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
    explicit HBorderSet(HReportManager *mgr,QWidget *parent = 0);
    ~HBorderSet();

public:
    void initLineStyleSet();
    void initBorderSet();
    void initColorSet();
    QPixmap createPenStyleIcon(Qt::PenStyle capStyle);
    void updateLineStyleSet();
    void updateColorListSet();

public slots:
    void currentIndexChanged_clicked(int index);
    void onBorderLeftBtn_clicked();
    void onBorderVerBtn_clicked();
    void onBorderRightBtn_clicked();
    void onBorderTopBtn_clicked();
    void onBorderHorBtn_clicked();
    void onBorderBottomBtn_clicked();
    void onBorderNoBtn_clicked();
    void onBorderAllBtn_clicked();
    void onBorderOutSideBtn_clicked();
    void onMoreColorBtn_clicked();
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void moveEvent(QMoveEvent *event);
    virtual void paintEvent(QPaintEvent *event);

private:
    Ui::HBorderSet *ui;
    HReportManager* m_pReportManager;
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
