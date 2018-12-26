#include "hformatsetdlg.h"
#include "ui_formatsetdlg.h"
#include "hborderset.h"
#include "hfontset.h"
#include "hgridcelldef.h"
#include "hgridreportmgr.h"
#include "hformatset.h"
#include <QDoubleValidator>


#define QCATAGORY_NORMAL   0
#define QCATAGORY_DATE     1
#define QCATAGORY_TIME     2

//注意具体配置需要从xml里面读取
HFormatSetDlg::HFormatSetDlg(HReportManager *mgr,QWidget *parent) :
    m_pReportManager(mgr),QDialog(parent),
    ui(new Ui::HFormatSetDlg)
{
    ui->setupUi(this);
    initDigitalSet();
    initBaseSet();
    HFontSet* font = new HFontSet(m_pReportManager,this);
    HBorderSet* border = new HBorderSet(m_pReportManager,this);
    ui->tabWidget->insertTab(2,font,QStringLiteral("字体"));
    ui->tabWidget->insertTab(3,border,QStringLiteral("边框"));
    initPrintSheetSet();
    initPrintSet();
}

HFormatSetDlg::~HFormatSetDlg()
{
    delete ui;
}

void HFormatSetDlg::initDigitalSet()
{
    QListWidgetItem* item = new QListWidgetItem(ui->catagoryListWidget);
    item->setText(QStringLiteral("常规"));
    item->setData(Qt::UserRole,QVariant(QCATAGORY_NORMAL));
    item = new QListWidgetItem(ui->catagoryListWidget);
    item->setText(QStringLiteral("日期"));
    item->setData(Qt::UserRole,QVariant(QCATAGORY_DATE));
    item = new QListWidgetItem(ui->catagoryListWidget);
    item->setText(QStringLiteral("时间"));
    item->setData(Qt::UserRole,QVariant(QCATAGORY_TIME));
    connect(ui->catagoryListWidget,SIGNAL(itemSelectionChanged()),this,SLOT(onCatagoryListWidget_clicked()));
}

void HFormatSetDlg::initBaseSet()
{
    ui->veritcalComboBox->addItem(QIcon(":/icon/icon/AlignTop.png"),QStringLiteral("顶端对齐"),QVariant(QDT_TOP));
    ui->veritcalComboBox->addItem(QIcon(":/icon/icon/AlignMiddle.png"),QStringLiteral("垂直居中"),QVariant(QDT_VCENTER));
    ui->veritcalComboBox->addItem(QIcon(":/icon/icon/AlignBottom.png"),QStringLiteral("底端对齐"),QVariant(QDT_BOTTOM));
    ui->horizontalComboBox->addItem(QIcon(":/icon/icon/AlignLeft.png"),QStringLiteral("左对齐"),QVariant(QDT_LEFT));
    ui->horizontalComboBox->addItem(QIcon(":/icon/icon/AlignCenter.png"),QStringLiteral("水平居中"),QVariant(QDT_HCENTER));
    ui->horizontalComboBox->addItem(QIcon(":/icon/icon/AlignRight.png"),QStringLiteral("右对齐"),QVariant(QDT_RIGHT));

    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    HFormatSet* pFormatSet = m_pReportManager->formatSet();
    quint32 nFormat = pFormatSet->format();
    int index = (int)-1;
    if(QDT_LEFT == (nFormat & QDT_LEFT))
    {
        index = ui->veritcalComboBox->findData(QDT_TOP);

    }
    else if(QDT_HCENTER == (nFormat & QDT_HCENTER))
    {
        index = ui->veritcalComboBox->findData(QDT_HCENTER);
    }
    else if(QDT_RIGHT == (nFormat & QDT_RIGHT))
    {
        index = ui->veritcalComboBox->findData(QDT_RIGHT);
    }
    ui->veritcalComboBox->setCurrentIndex(index);

    if(QDT_TOP == (nFormat & QDT_TOP))
    {
        index = ui->horizontalComboBox->findData(QDT_TOP);
    }
    else if(QDT_VCENTER == (nFormat & QDT_VCENTER))
    {
        index = ui->horizontalComboBox->findData(QDT_VCENTER);
    }
    else if(QDT_BOTTOM == (nFormat & QDT_BOTTOM))
    {
        index = ui->horizontalComboBox->findData(QDT_BOTTOM);
    }
    ui->horizontalComboBox->setCurrentIndex(index);

    if(QDT_WORDBREAK == (nFormat & QDT_WORDBREAK))
    {
        ui->autoWrapTextCheckBox->setChecked(true);
    }

    //缺少一个合并单元格
}

void HFormatSetDlg::initPrintSheetSet()
{

}

void HFormatSetDlg::initPrintSet()
{
    QDoubleValidator *doubleValidator = new QDoubleValidator(0,50,2);
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);
    ui->leftMargin->setValidator(doubleValidator);
    ui->rightMargin->setValidator(doubleValidator);
    ui->topMargin->setValidator(doubleValidator);
    ui->bottomMargin->setValidator(doubleValidator);
    ui->headMargin->setValidator(doubleValidator);
    ui->tailMargin->setValidator(doubleValidator);

    ui->leftMargin->setText("0");
    ui->rightMargin->setText("0");
    ui->topMargin->setText("0");
    ui->bottomMargin->setText("0");
    ui->headMargin->setText("0");
    ui->tailMargin->setText("0");

    ui->gridCheck->setChecked(false);
    ui->rowCheck->setChecked(false);
    ui->colCheck->setChecked(false);
    ui->clrColor->setChecked(false);
}

void HFormatSetDlg::onCatagoryListWidget_clicked()
{
    QListWidgetItem* item = ui->catagoryListWidget->currentItem();
    if(NULL == item)
        return;
    ui->inforLabel->setText(QStringLiteral("类型"));
    if(QCATAGORY_NORMAL == item->data(Qt::UserRole).toUInt())
    {
        ui->inforLabel->setText(QStringLiteral("常规单元格格式不包含任何特定的数字格式。"));
        ui->typeListWidget->hide();
    }
    else if(QCATAGORY_DATE == item->data(Qt::UserRole).toUInt())
    {
        ui->typeListWidget->show();
        ui->typeListWidget->clear();
    }
    else if(QCATAGORY_TIME == item->data(Qt::UserRole).toUInt())
    {
        ui->typeListWidget->show();
        ui->typeListWidget->clear();
    }

}
