#ifndef HREPORTNEWDLG_H
#define HREPORTNEWDLG_H

#include <QDialog>

namespace Ui {
class HReportNewDlg;
}

class HReportNewDlg : public QDialog
{
    Q_OBJECT

public:
    explicit HReportNewDlg(QWidget *parent = 0);
    ~HReportNewDlg();

public slots:
    void okBtn_clicked();
    void cancelBtn_clicked();

public:
    QString strReportName;
    quint32 nMaxCol;
    quint32 nMaxRow;
private:
    Ui::HReportNewDlg *ui;
};

#endif // HREPORTNEWDLG_H
