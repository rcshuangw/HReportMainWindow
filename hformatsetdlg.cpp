#include "hformatsetdlg.h"
#include "ui_formatsetdlg.h"
#include "hborderset.h"
#include "hfontset.h"
#define QDT_TOP                      Qt::AlignTop
#define QDT_LEFT                     Qt::AlignLeft
#define QDT_HCENTER                  Qt::AlignHCenter
#define QDT_CENTER                   QDT_VCENTER|QDT_HCENTER
#define QDT_RIGHT                    Qt::AlignRight
#define QDT_VCENTER                  Qt::AlignVCenter
#define QDT_BOTTOM                   Qt::AlignBottom
#define QDT_WORDBREAK                Qt::TextWordWrap
#define QDT_SINGLELINE               Qt::TextSingleLine
#define QDT_EXPANDTABS               Qt::TextExpandTabs
#define QDT_NOPREFIX                 Qt::TextHideMnemonic

#define QCATAGORY_NORMAL   0
#define QCATAGORY_DATE     1
#define QCATAGORY_TIME     2

//注意具体配置需要从xml里面读取
HFormatSetDlg::HFormatSetDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HFormatSetDlg)
{
    ui->setupUi(this);
    initDigitalSet();
    initBaseSet();
    HFontSet* font = new HFontSet(this);
    HBorderSet* border = new HBorderSet(this);
    ui->tabWidget->insertTab(3,font,QStringLiteral("字体"));
    ui->tabWidget->insertTab(4,border,QStringLiteral("边框"));
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
}

void HFormatSetDlg::initPrintSheetSet()
{

}

void HFormatSetDlg::initPrintSet()
{

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
