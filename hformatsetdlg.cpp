#include "hformatsetdlg.h"
#include "ui_formatsetdlg.h"
#include "hborderset.h"
#include "hfontset.h"
#include "hgridcelldef.h"
#include "hgridreportmgr.h"
#include "hformatset.h"
#include <QDoubleValidator>

#define HCATAGORY_NORMAL   0
#define HCATAGORY_DATE     1
#define HCATAGORY_TIME     2

//注意具体配置需要从xml里面读取
HFormatSetDlg::HFormatSetDlg(HReportManager *mgr,QWidget *parent) :
    m_pReportManager(mgr),QDialog(parent),
    ui(new Ui::HFormatSetDlg)
{
    ui->setupUi(this);
    initDigitalSet();
    initBaseSet();
    m_fontSet = new HFontSet(m_pReportManager,this);//0
    m_borderSet = new HBorderSet(m_pReportManager,this);//1
    ui->tabWidget->insertTab(TAB_ATTR_FONT,m_fontSet,QStringLiteral("字体"));//2
    ui->tabWidget->insertTab(TAB_ATTR_BORDER,m_borderSet,QStringLiteral("边框"));//3
    initPrintSheetSet();//4
    initPrintSet();//5

    connect(ui->okBtn,SIGNAL(clicked(bool)),this,SLOT(okBtn_clicked()));
    connect(ui->cancleBtn,SIGNAL(clicked(bool)),this,SLOT(cancleBtn_clicked()));
}

HFormatSetDlg::~HFormatSetDlg()
{
    delete ui;
}

void HFormatSetDlg::setTabIndex(quint8 index)
{
    m_nTabIndex = index;
    ui->tabWidget->setCurrentIndex(m_nTabIndex);
}

void HFormatSetDlg::initDigitalSet()
{
    QListWidgetItem* item = new QListWidgetItem(ui->catagoryListWidget);
    item->setText(QStringLiteral("常规"));
    item->setData(Qt::UserRole,QVariant(HCATAGORY_NORMAL));
    item = new QListWidgetItem(ui->catagoryListWidget);
    item->setText(QStringLiteral("日期"));
    item->setData(Qt::UserRole,QVariant(HCATAGORY_DATE));
    item = new QListWidgetItem(ui->catagoryListWidget);
    item->setText(QStringLiteral("时间"));
    item->setData(Qt::UserRole,QVariant(HCATAGORY_TIME));
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
    connect(ui->horizontalComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onHorizontalComboBox_changed()));
    connect(ui->veritcalComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onVeritcalComboBox_changed()));

    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    HFormatSet* pFormatSet = m_pReportManager->formatSet();
    m_nFormat = pFormatSet->format();
    int index = (int)-1;
    if(QDT_LEFT == (m_nFormat & QDT_LEFT))
    {
        index = ui->horizontalComboBox->findData(QDT_LEFT);

    }
    else if(QDT_HCENTER == (m_nFormat & QDT_HCENTER))
    {
        index = ui->horizontalComboBox->findData(QDT_HCENTER);
    }
    else if(QDT_RIGHT == (m_nFormat & QDT_RIGHT))
    {
        index = ui->horizontalComboBox->findData(QDT_RIGHT);
    }
    ui->horizontalComboBox->setCurrentIndex(index);

    if(QDT_TOP == (m_nFormat & QDT_TOP))
    {
        index = ui->veritcalComboBox->findData(QDT_TOP);
    }
    else if(QDT_VCENTER == (m_nFormat & QDT_VCENTER))
    {
        index = ui->veritcalComboBox->findData(QDT_VCENTER);
    }
    else if(QDT_BOTTOM == (m_nFormat & QDT_BOTTOM))
    {
        index = ui->veritcalComboBox->findData(QDT_BOTTOM);
    }
    ui->veritcalComboBox->setCurrentIndex(index);

    if(QDT_WORDBREAK == (m_nFormat & QDT_WORDBREAK))
    {
        ui->autoWrapTextCheckBox->setChecked(true);
    }

    ui->mergeCellCheckBox->setChecked(pFormatSet->isMergeCell());
}

void HFormatSetDlg::initPrintSheetSet()
{
    //票号格式设置
    ui->prefixCheck->setChecked(false);
    ui->suffixCheck->setChecked(false);
    ui->sheetLencheckBox->setChecked(false);
    ui->tempSheetcheckBox->setChecked(false);

    ui->firstOpTaskCheckBox->setChecked(false);
    ui->opTaskOtherLineEdit->setEnabled(false);
    ui->firststChangeCheckBox->setChecked(false);
    ui->stChangeOtherLineEdit->setEnabled(false);
    QIntValidator *intValidator = new QIntValidator(0,100);
    ui->opTaskLineEdit->setValidator(intValidator);
    ui->opItemLineEdit->setValidator(intValidator);
    ui->stChangeLineEdit->setValidator(intValidator);
    ui->serialNoLineEdit->setValidator(intValidator);

    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;

    //票号格式设置
    HFormatSet* pFormatSet = m_pReportManager->formatSet();
    ui->prefixCheck->setChecked(pFormatSet->isSheetNoPrefix());
    ui->prefixLineEdit->setText(pFormatSet->sheetNoPrefix());
    ui->suffixCheck->setChecked(pFormatSet->isSheetNoSuffix());
    ui->suffixLineEdit->setText(pFormatSet->sheetNoSuffix());
    ui->sheetLencheckBox->setChecked(pFormatSet->isSheetNoLength());
    ui->sheetLenLineEdit->setText(pFormatSet->sheetNoLength());
    ui->tempSheetcheckBox->setChecked(pFormatSet->isSheetTempNo());
    ui->tempSheetLineEdit->setText(pFormatSet->sheetTempNo());

    //任务长度设置
    ui->opTaskLineEdit->setText(QString("%1").arg(pFormatSet->opTaskWordCount()));
    ui->opItemLineEdit->setText(QString("%1").arg(pFormatSet->opTermWordCount()));
    ui->stChangeLineEdit->setText(QString("%1").arg(pFormatSet->stateChangeWordCount()));
    ui->serialNoLineEdit->setText(QString("%1").arg(pFormatSet->serialNumWordCount()));
    //自定义显示
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
    ui->footMargin->setValidator(doubleValidator);

    ui->leftMargin->setText("0");
    ui->rightMargin->setText("0");
    ui->topMargin->setText("0");
    ui->bottomMargin->setText("0");
    ui->headMargin->setText("0");
    ui->footMargin->setText("0");

    ui->gridCheck->setChecked(false);
    ui->rowCheck->setChecked(false);
    ui->colCheck->setChecked(false);
    ui->clrColor->setChecked(false);

    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    HFormatSet* pFormatSet = m_pReportManager->formatSet();
    ui->topMargin->setText(QString("%1").arg(pFormatSet->pageTopMargin(),0,'f',2));
    ui->bottomMargin->setText(QString("%1").arg(pFormatSet->pageBottomMargin(),0,'f',2));
    ui->leftMargin->setText(QString("%1").arg(pFormatSet->pageLeftMargin(),0,'f',2));
    ui->rightMargin->setText(QString("%1").arg(pFormatSet->pageRightMargin(),0,'f',2));
    ui->headMargin->setText(QString("%1").arg(pFormatSet->pageHeaderHeight(),0,'f',2));
    ui->footMargin->setText(QString("%1").arg(pFormatSet->pageFooterHeight(),0,'f',2));
    ui->headText->setText(pFormatSet->pageHeaderText());
    ui->footText->setText(pFormatSet->pageFooterText());
    ui->gridCheck->setChecked(pFormatSet->isPageShowGrid());
    ui->rowCheck->setChecked(pFormatSet->isPageShowRowHeader());
    ui->colCheck->setChecked(pFormatSet->isPageShowColumnHeader());
    ui->clrColor->setChecked(pFormatSet->isPagePrintColour());
}

void HFormatSetDlg::onCatagoryListWidget_clicked()
{
    QListWidgetItem* item = ui->catagoryListWidget->currentItem();
    if(NULL == item)
        return;
    ui->inforLabel->setText(QStringLiteral("类型"));
    if(HCATAGORY_NORMAL == item->data(Qt::UserRole).toUInt())
    {
        ui->inforLabel->setText(QStringLiteral("常规单元格格式不包含任何特定的数字格式。"));
        ui->typeListWidget->hide();
    }
    else if(HCATAGORY_DATE == item->data(Qt::UserRole).toUInt())
    {
        ui->typeListWidget->show();
        ui->typeListWidget->clear();
    }
    else if(HCATAGORY_TIME == item->data(Qt::UserRole).toUInt())
    {
        ui->typeListWidget->show();
        ui->typeListWidget->clear();
    }
}

void HFormatSetDlg::onHorizontalComboBox_changed()
{
    quint32 horizontalAlign = ui->horizontalComboBox->currentData().toInt();
    if(QDT_LEFT == horizontalAlign)
    {
        m_nFormat|= QDT_LEFT;
        if(QDT_HCENTER == (m_nFormat & QDT_HCENTER))
            m_nFormat &= ~QDT_HCENTER;
        if(QDT_RIGHT == (m_nFormat & QDT_RIGHT))
            m_nFormat &= ~QDT_RIGHT;
    }
    else if(QDT_HCENTER == horizontalAlign)
    {
        m_nFormat|= QDT_HCENTER;
        if(QDT_LEFT == (m_nFormat & QDT_LEFT))
            m_nFormat &= ~QDT_LEFT;
        if(QDT_RIGHT == (m_nFormat & QDT_RIGHT))
            m_nFormat &= ~QDT_RIGHT;
    }
    else if(QDT_RIGHT == horizontalAlign)
    {
        m_nFormat|= QDT_RIGHT;
        if(QDT_LEFT == (m_nFormat & QDT_LEFT))
            m_nFormat &= ~QDT_LEFT;
        if(QDT_HCENTER == (m_nFormat & QDT_HCENTER))
            m_nFormat &= ~QDT_HCENTER;
    }
}

void HFormatSetDlg::onVeritcalComboBox_changed()
{
    quint32 veritcalAlign = ui->veritcalComboBox->currentData().toInt();
    if(QDT_TOP == veritcalAlign)
    {
        m_nFormat|= QDT_TOP;
        if(QDT_VCENTER == (m_nFormat & QDT_VCENTER))
            m_nFormat &= ~QDT_VCENTER;
        if(QDT_BOTTOM == (m_nFormat & QDT_BOTTOM))
            m_nFormat &= ~QDT_BOTTOM;
    }
    else if(QDT_VCENTER == veritcalAlign)
    {
        m_nFormat|= QDT_VCENTER;
        if(QDT_TOP == (m_nFormat & QDT_TOP))
            m_nFormat &= ~QDT_TOP;
        if(QDT_BOTTOM == (m_nFormat & QDT_BOTTOM))
            m_nFormat &= ~QDT_BOTTOM;
    }
    else if(QDT_BOTTOM == veritcalAlign)
    {
        m_nFormat|= QDT_BOTTOM;
        if(QDT_TOP == (m_nFormat & QDT_TOP))
            m_nFormat &= ~QDT_TOP;
        if(QDT_VCENTER == (m_nFormat & QDT_VCENTER))
            m_nFormat &= ~QDT_VCENTER;
    }
}

void HFormatSetDlg::save()
{
    //1.数字
    //2.基本
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    /*
    HFormatSet* pFormatSet = m_pReportManager->formatSet();
    pFormatSet->setFormat(m_nFormat);
    pFormatSet->enableAutoWrapText(ui->autoWrapTextCheckBox->isChecked());
    pFormatSet->enableMergeCell(ui->mergeCellCheckBox->isChecked());

    //操作票打印显示设置
    bool b = ui->prefixCheck->isChecked();
    setSettingValue(SYS_SET_PRINT,PRINT_SHEETNO_PREFIX,QVariant(b),QStringLiteral("票号带前缀"));
    pFormatSet->enableSheetNoPrefix(b);
    QString strText = ui->prefixLineEdit->text();
    if(strText.isNull())
        strText = "";
    pFormatSet->setSheetNoPrefix(strText);
    setSettingValue(SYS_SET_PRINT,PRINT_SHEETNO_PREFIX_TEXT,QVariant(strText),QStringLiteral("票号前缀"));

    b = ui->suffixCheck->isChecked();
    setSettingValue(SYS_SET_PRINT,PRINT_SHEETNO_SUFFIX,QVariant(b),QStringLiteral("票号带后缀"));
    pFormatSet->enableSheetNoSuffix(b);
    strText = ui->suffixLineEdit->text();
    if(strText.isNull())
        strText = "";
    pFormatSet->setSheetNoSuffix(strText);
    setSettingValue(SYS_SET_PRINT,PRINT_SHEETNO_SUFFIX_TEXT,QVariant(strText),QStringLiteral("票号后前缀"));

    b = ui->sheetLencheckBox->isChecked();
    setSettingValue(SYS_SET_PRINT,PRINT_SHEETNO_LENGTH,QVariant(b),QStringLiteral("设置票号长度"));
    pFormatSet->enableSheetNoLength(b);
    strText = ui->sheetLenLineEdit->text();
    if(strText.isNull())
        strText = "";
    pFormatSet->setSheetNoLength(strText);
    setSettingValue(SYS_SET_PRINT,PRINT_SHEETNO_LENGTH_TEXT,QVariant(strText),QStringLiteral("票号长度"));

    b = ui->tempSheetcheckBox->isChecked();
    setSettingValue(SYS_SET_PRINT,PRINT_SHEET_TEMPNO,QVariant(strText),QStringLiteral("设置临时票号"));
    pFormatSet->enableSheetTempNo(b);
    strText = ui->tempSheetLineEdit->text();
    if(strText.isNull())
        strText = "";
    pFormatSet->setSheetTempNo(strText);
    setSettingValue(SYS_SET_PRINT,PRINT_SHEET_TEMPNO_TEXT,QVariant(strText),QStringLiteral("设置临时票号"));


    //任务长度设置
    quint16 lengthSet = ui->opTaskLineEdit->text().toUInt();
    pFormatSet->setOpTaskWordCount(lengthSet);
    setSettingValue(SYS_SET_PRINT,PRINT_OPTASK_LENGTH,QVariant(lengthSet),QStringLiteral("操作任务字符长度"));
    lengthSet = ui->opItemLineEdit->text().toUInt();
    pFormatSet->setOpTermWordCount(lengthSet);
    setSettingValue(SYS_SET_PRINT,PRINT_OPITEM_LENGTH,QVariant(lengthSet),QStringLiteral("操作项目字符长度"));
    lengthSet = ui->stChangeLineEdit->text().toUInt();
    pFormatSet->setStateChangeWordCount(lengthSet);
    setSettingValue(SYS_SET_PRINT,PRINT_STATECHANGE_LENGTH,QVariant(lengthSet),QStringLiteral("状态转换字符长度"));
    lengthSet = ui->serialNoLineEdit->text().toUInt();
    pFormatSet->setSerialNumWordCount(lengthSet);
    setSettingValue(SYS_SET_PRINT,PRINT_SERIALNO_LENGTH,QVariant(lengthSet),QStringLiteral("流水号字符长度"));

    //打印设置
    double dMargin = ui->leftMargin->text().toDouble();
    pFormatSet->setPageLeftMargin(dMargin);
    setSettingValue(SYS_SET_PRINT,PRINT_LEFT_MARGIN,QVariant(dMargin),QStringLiteral("左边距"));
    dMargin = ui->rightMargin->text().toDouble();
    pFormatSet->setPageRightMargin(dMargin);
    setSettingValue(SYS_SET_PRINT,PRINT_RIGHT_MARGIN,QVariant(dMargin),QStringLiteral("右边距"));
    dMargin = ui->topMargin->text().toDouble();
    pFormatSet->setPageTopMargin(dMargin);
    setSettingValue(SYS_SET_PRINT,PRINT_TOP_MARGIN,QVariant(dMargin),QStringLiteral("上边距"));
    dMargin = ui->bottomMargin->text().toDouble();
    pFormatSet->setPageBottomMargin(dMargin);
    setSettingValue(SYS_SET_PRINT,PRINT_BOTTOM_MARGIN,QVariant(dMargin),QStringLiteral("下边距"));
    dMargin = ui->headMargin->text().toDouble();
    pFormatSet->setPageHeaderHeight(dMargin);
    setSettingValue(SYS_SET_PRINT,PRINT_HEAD_MARGIN,QVariant(dMargin),QStringLiteral("头边距"));
    dMargin = ui->footMargin->text().toDouble();
    pFormatSet->setPageFooterHeight(dMargin);
    setSettingValue(SYS_SET_PRINT,PRINT_FOOT_MARGIN,QVariant(dMargin),QStringLiteral("尾边距"));

    strText = ui->headText->toPlainText();
    if(strText.isNull())
        strText = "";
    pFormatSet->setPageHeaderText(strText);
    setSettingValue(SYS_SET_PRINT,PRINT_HEAD_TEXT,QVariant(strText),QStringLiteral("页头"));
    strText = ui->footText->toPlainText();
    if(strText.isNull())
        strText = "";
    pFormatSet->setPageFooterText(strText);
    setSettingValue(SYS_SET_PRINT,PRINT_FOOT_TEXT,QVariant(strText),QStringLiteral("页尾"));

    b = ui->gridCheck->isChecked();
    pFormatSet->enablePageShowGrid(b);
    setSettingValue(SYS_SET_PRINT,PRINT_SHOW_GRIDLINE,QVariant(b),QStringLiteral("打印表格"));
    b = ui->rowCheck->isChecked();
    pFormatSet->enablePageShowColumnHeader(b);
    setSettingValue(SYS_SET_PRINT,PRINT_HORIZONTAL_HEAD,QVariant(b),QStringLiteral("打印显示行头"));
    b = ui->colCheck->isChecked();
    pFormatSet->enablePageShowRowHeader(b);
    setSettingValue(SYS_SET_PRINT,PRINT_VERTICVAL_HEAD,QVariant(b),QStringLiteral("打印显示列头"));
    b = ui->clrColor->isChecked();
    pFormatSet->enablePagePrintColour(b);
    setSettingValue(SYS_SET_PRINT,PRINT_SHOW_COLOR,QVariant(b),QStringLiteral("彩色打印"));

    saveSysConfig();*/
}

void HFormatSetDlg::okBtn_clicked()
{
    save();
    m_fontSet->save();
    m_borderSet->save();
    QDialog::accept();

}

void HFormatSetDlg::cancleBtn_clicked()
{
    QDialog::reject();
}
