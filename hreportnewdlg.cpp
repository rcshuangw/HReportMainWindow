#include "hreportnewdlg.h"
#include "ui_hreportnewdlg.h"
#include <QIntValidator>
HReportNewDlg::HReportNewDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HReportNewDlg)
{
    ui->setupUi(this);
    ui->reportLineEdit->setText(QStringLiteral("新模板"));
    ui->rowLineEdit->setText("40");
    ui->rowLineEdit->setValidator(new QIntValidator(0, 1000, this));
    ui->colLineEdit->setText("15");
    ui->colLineEdit->setValidator(new QIntValidator(0, 1000, this));
    connect(ui->okBtn,SIGNAL(clicked(bool)),this,SLOT(okBtn_clicked()));
    connect(ui->cancelBtn,SIGNAL(clicked(bool)),this,SLOT(cancelBtn_clicked()));
}

HReportNewDlg::~HReportNewDlg()
{
    delete ui;
}

void HReportNewDlg::okBtn_clicked()
{
    strReportName = ui->reportLineEdit->text();
    nMaxRow = ui->rowLineEdit->text().toUInt();
    nMaxCol = ui->colLineEdit->text().toUInt();
    QDialog::accept();
}

void HReportNewDlg::cancelBtn_clicked()
{
    QDialog::reject();
}
