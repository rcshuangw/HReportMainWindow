#ifndef HOPSHEETVARDLG_H
#define HOPSHEETVARDLG_H

#include <QDialog>

namespace Ui {
class HOpSheetVarDlg;
}

class HOpSheetVarDlg : public QDialog
{
    Q_OBJECT

public:
    explicit HOpSheetVarDlg(QWidget *parent = 0);
    ~HOpSheetVarDlg();
    void initSheetVarDlg();

protected:
    void closeEvent(QCloseEvent *);
public slots:
    void okBtn();
public:
    quint16 m_nOpSheetVarType;
private:
    Ui::HOpSheetVarDlg *ui;
};

#endif // HOPSHEETVARDLG_H
