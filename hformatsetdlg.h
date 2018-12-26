#ifndef HFORMATSETDLG_H
#define HFORMATSETDLG_H

#include <QDialog>
class HReportManager;
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
    void initBaseSet();//未单独设置qwidget
    void initDigitalSet();//未单独设置qwidget 数字设置
    void initPrintSheetSet();// 主要是大约操作票的相关设置
    void initPrintSet();//打印相关设置

public slots:
    void onCatagoryListWidget_clicked();
private:
    Ui::HFormatSetDlg *ui;
    HReportManager* m_pReportManager;
};

#endif // HFORMATSETDLG_H
