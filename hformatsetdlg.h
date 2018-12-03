#ifndef HFORMATSETDLG_H
#define HFORMATSETDLG_H

#include <QDialog>

namespace Ui {
class HFormatSetDlg;
}

class HFormatSetDlg : public QDialog
{
    Q_OBJECT

public:
    explicit HFormatSetDlg(QWidget *parent = 0);
    ~HFormatSetDlg();

public:
    void initBaseSet();//未单独设置qwidget
    void initDigitalSet();//未单独设置qwidget 数字设置

public slots:
    void onCatagoryListWidget_click();
private:
    Ui::HFormatSetDlg *ui;
};

#endif // HFORMATSETDLG_H
