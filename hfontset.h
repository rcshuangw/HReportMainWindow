#ifndef HFONTSET_H
#define HFONTSET_H

#include <QWidget>
#include <QProxyStyle>
#include <QFont>
#include <QListWidgetItem>
namespace Ui {
class HFontSet;
}

class HFontSet : public QWidget
{
    Q_OBJECT
    enum fontStyle
    {
        StyleNormal = 0,
        StyleItalic = 1,
        StyleBold = 2,
        StyleBoldAndItalic = 3
    };

    enum fontUnderline
    {
        UnderlineNo = 0,
        UnderlineNormal = 1
    };

public:
    explicit HFontSet(QWidget *parent = 0);
    ~HFontSet();
public:
    void initFontFamilies();
    virtual void paintEvent(QPaintEvent *event);
    void updateColorListSet();
public slots:
    void onFontFamilyitemChanged();
    void onFontSizeitemChanged();
    void onFontStyleitemChanged();
    void onFontUnderlineCurrentIndexChanged(int index);
    void onFontClrCurrentIndexChanged(int index);
    void onMoreColorBtn_clicked();
private:
    Ui::HFontSet *ui;
    QFont m_curFont;
    QString m_strFontColor;
    QStringList m_recentColorList;//最近列表
};

#endif // HFONTSET_H
