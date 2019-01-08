#ifndef HFORMATSETDLG_H
#define HFORMATSETDLG_H
//tab页的页面 必须和tab实际页面对应起来
#define TAB_ATTR_NUMBER     0x00
#define TAB_ATTR_BASE       0x01
#define TAB_ATTR_FONT       0x02
#define TAB_ATTR_BORDER     0x03
#define TAB_ATTR_PRINTSHEET 0x04
#define TAB_ATTR_PRINT      0x05
//定义tab页
#include <QDialog>
class HReportManager;
class HFontSet;
class HBorderSet;
namespace Ui {
class HFormatSetDlg;
}

class HFormatSetDlg : public QDialog
{
    Q_OBJECT

public:
    explicit HFormatSetDlg(HReportManager* mgr,QWidget *parent = 0);
    ~HFormatSetDlg();

public:
    void setTabIndex(quint8 index);
    quint8 tabIndex()              { return m_nTabIndex;  }
    void initBaseSet();//未单独设置qwidget
    void initDigitalSet();//未单独设置qwidget 数字设置
    void initPrintSheetSet();// 主要是大约操作票的相关设置
    void initPrintSet();//打印相关设置
    void save();
public slots:
    void onCatagoryListWidget_clicked();
    void onHorizontalComboBox_changed();
    void onVeritcalComboBox_changed();
    void okBtn_clicked();
    void cancleBtn_clicked();
private:
    Ui::HFormatSetDlg *ui;
    HReportManager* m_pReportManager;
    HBorderSet* m_borderSet;
    HFontSet* m_fontSet;
    quint32 m_nFormat;
    quint8 m_nTabIndex;

};

#endif // HFORMATSETDLG_H
