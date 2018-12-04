#include "hfontset.h"
#include "ui_hfontset.h"
#include "hborderset.h"
#include <QFontDatabase>
#include <QPainter>
#include <QStandardItem>
#include <QMouseEvent>
#include <QColorDialog>
typedef struct _tagFontColor
{
    QString strClrName;
    int     nClrValue;
}FontColor;

FontColor sysColorList[]=
{
    //name value
    {QStringLiteral("黑色"),Qt::black},
    {QStringLiteral("白色"),Qt::white},
    {QStringLiteral("红色"),Qt::red},
    {QStringLiteral("深红色"),(Qt::darkRed)},
    {QStringLiteral("绿色"),(Qt::green)},
    {QStringLiteral("深绿色"),(Qt::darkGreen)},
    {QStringLiteral("蓝色"),(Qt::blue)},
    {QStringLiteral("深蓝色"),(Qt::darkBlue)},
    {QStringLiteral("青色"),(Qt::cyan)},
    {QStringLiteral("深青色"),(Qt::darkCyan)},
    {QStringLiteral("洋红色"),(Qt::magenta)},
    {QStringLiteral("深洋红色"),(Qt::darkMagenta)},
    {QStringLiteral("黄色"),(Qt::yellow)},
    {QStringLiteral("深黄色"),(Qt::darkYellow)},
    {QStringLiteral("灰色"),(Qt::gray)},
    {QStringLiteral("深灰色"),(Qt::darkGray)},
    {QStringLiteral("浅灰色"),(Qt::lightGray)}
};




HFontSet::HFontSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HFontSet)
{
    ui->setupUi(this);
    m_recentColorList.clear();
    m_curFont.setFamily(QStringLiteral("宋体"));
    m_curFont.setPointSize(10);
    initFontFamilies();
}

HFontSet::~HFontSet()
{
    m_recentColorList.clear();
    delete ui;
}

void HFontSet::initFontFamilies()
{
    connect(ui->fontFamilyList,SIGNAL(itemSelectionChanged()),this,SLOT(onFontFamilyitemChanged()));
    connect(ui->fontPointSizeList,SIGNAL(itemSelectionChanged()),this,SLOT(onFontSizeitemChanged()));
    connect(ui->fontStyleList,SIGNAL(itemSelectionChanged()),this,SLOT(onFontStyleitemChanged()));
    QFontDatabase fontDB;
    QStringList fontFamiliesList = fontDB.families(QFontDatabase::Any);
    ui->fontFamilyList->addItems(fontFamiliesList);
    QList<QListWidgetItem *>  itemList = ui->fontFamilyList->findItems(QStringLiteral("宋体"),Qt::MatchCaseSensitive|Qt::MatchFixedString);
    ui->fontFamilyList->setCurrentItem(itemList.at(0));

    //字体风格
    QListWidgetItem* item0 = new QListWidgetItem(ui->fontStyleList);
    item0->setText(QStringLiteral("常规"));
    item0->setData(Qt::UserRole,QVariant(StyleNormal));
    QListWidgetItem* item = new QListWidgetItem(ui->fontStyleList);
    item->setText(QStringLiteral("倾斜"));
    item->setData(Qt::UserRole,QVariant(StyleItalic));
    item = new QListWidgetItem(ui->fontStyleList);
    item->setText(QStringLiteral("加粗"));
    item->setData(Qt::UserRole,QVariant(StyleBold));
    item = new QListWidgetItem(ui->fontStyleList);
    item->setText(QStringLiteral("加粗 倾斜"));
    item->setData(Qt::UserRole,QVariant(StyleBoldAndItalic));
    ui->fontStyleList->setCurrentItem(item0);

    //字号
    QStringList fontSizeList = {"6","8","9","10","12","14","16","18","20","22","24","26","28","36","48","72"};
    ui->fontPointSizeList->addItems(fontSizeList);
    QList<QListWidgetItem *>  itemSizeList = ui->fontPointSizeList->findItems(QStringLiteral("10"),Qt::MatchCaseSensitive|Qt::MatchFixedString);
    ui->fontPointSizeList->setCurrentItem(itemSizeList.at(0));

    ui->fontUnderlineComboBox->addItem(QStringLiteral("无下划线"),QVariant(UnderlineNo));
    ui->fontUnderlineComboBox->addItem(QStringLiteral("单下划线"),QVariant(UnderlineNormal));
    connect(ui->fontUnderlineComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onFontUnderlineCurrentIndexChanged(int)));
    //颜色
    ui->fontColorComboBox->setStyle(new HNoFocusProxyStyle);
    ui->fontColorComboBox->setStyleSheet("selection-background-color:white;"); //设置选中背景色
    ui->fontColorComboBox->setIconSize( QSize( 100, 20 ) );
    ui->fontColorComboBox->setSizeAdjustPolicy( QComboBox::AdjustToContents );
    updateColorListSet();
    connect(ui->fontColorComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onFontClrCurrentIndexChanged(int)));
    connect(ui->moreColorBtn,SIGNAL(clicked(bool)),this,SLOT(onMoreColorBtn_clicked()));
   //如果单元格不为空 则这里调整单元格初始化配置
    update();
}

void HFontSet::onFontFamilyitemChanged()
{
    QListWidgetItem* item = ui->fontFamilyList->currentItem();
    if(!item) return;
    QString strText = item->text();
    ui->curFontFamily->setText(strText);
    m_curFont.setFamily(strText);
    update();
}

void HFontSet::onFontSizeitemChanged()
{
    QListWidgetItem* item = ui->fontPointSizeList->currentItem();
    if(!item) return;
    QString strText = item->text();
    ui->curFontPointSize->setText(strText);
    m_curFont.setPointSize(strText.toInt());
    update();
}

void HFontSet::onFontStyleitemChanged()
{
    QListWidgetItem* item = ui->fontStyleList->currentItem();
    if(!item) return;
    QString strText = item->text();
    ui->curFontStyle->setText(strText);
    quint8 nStyle = item->data(Qt::UserRole).toUInt();
    if(nStyle == StyleNormal)
    {
        m_curFont.setStyle(QFont::StyleNormal);
        m_curFont.setItalic(false);
        m_curFont.setBold(false);
    }
    else if(nStyle == StyleItalic)
    {
        //m_curFont.setStyle(QFont::StyleNormal);
        m_curFont.setItalic(true);
        m_curFont.setBold(false);
    }
    else if(nStyle == StyleBold)
    {
        //m_curFont.setStyle(QFont::StyleNormal);
        m_curFont.setBold(true);
        m_curFont.setItalic(false);
    }
    else if(nStyle == StyleBoldAndItalic)
    {
        //m_curFont.setStyle(QFont::StyleNormal);
        m_curFont.setBold(true);
        m_curFont.setItalic(true);
    }
    update();
}

void HFontSet::onFontUnderlineCurrentIndexChanged(int index)
{
    if(index == (int)-1)
        return;
    quint8 nUnderline = ui->fontUnderlineComboBox->itemData(index).toUInt();
    if(nUnderline == UnderlineNormal)
        m_curFont.setUnderline(true);
    else
        m_curFont.setUnderline(false);
    update();
}

void HFontSet::onFontClrCurrentIndexChanged(int index)
{
    if((int)-1 == index)
        return;
    QStandardItemModel *model  = (QStandardItemModel *)ui->fontColorComboBox->model();
    if(model)
    {
        int clrValue = model->item(index,0)->data().toInt();
        m_strFontColor = QColor(Qt::GlobalColor(clrValue)).name();
    }
    update();
}

void HFontSet::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect rect = ui->fontPreview->geometry();
    QPoint borderPt = ui->groupBox_3->geometry().topLeft();
    QPoint viewFrameLeft = ui->fontPreview->geometry().topLeft()+borderPt ;
    QRect fontPreviewRect = QRect(viewFrameLeft,QSize(rect.width(),rect.height())) ;
    painter.setFont(m_curFont);
    painter.setPen(QColor(m_strFontColor));
    painter.drawText(fontPreviewRect,Qt::AlignCenter,QStringLiteral("中文Test"));

}

void HFontSet::updateColorListSet()
{
    QStandardItemModel *model = (QStandardItemModel *)ui->fontColorComboBox->model();
    if(model == NULL)
    {
        model = new QStandardItemModel();//添加提示tootip

    }
    model->clear();
    for( int i = 0; i < m_recentColorList.count();i++)
    {
        QString strClr = m_recentColorList[i];//strClr就是color的名称 #000000
        QColor clr = QColor(strClr);
        QPixmap pix( QSize( 100, 20 ) );
        pix.fill( clr);
        QStandardItem *item = new QStandardItem(QIcon( pix ), NULL);
        item->setData(QVariant(clr.value()));
        item->setToolTip(clr.name());
        model->appendRow(item);
    }

    for( int i = 0; i < sizeof(sysColorList)/sizeof(FontColor);i++ )
    {
        FontColor color = sysColorList[i];
        QPixmap pix( QSize( 100, 20 ) );
        pix.fill( QColor( Qt::GlobalColor(color.nClrValue) ) );
        QStandardItem *item = new QStandardItem(QIcon( pix ), NULL);
        item->setData(QVariant(color.nClrValue));
        item->setToolTip(color.strClrName);
        model->appendRow(item);
    }
    ui->fontColorComboBox->setModel(model);
}

void HFontSet::onMoreColorBtn_clicked()
{
    QColor clr = QColorDialog::getColor(QColor(m_strFontColor),this,QStringLiteral("选择颜色"));
    while(m_recentColorList.count() > 5)
        m_recentColorList.removeLast();
    if((int)-1 == m_recentColorList.indexOf(clr.name()))
        m_recentColorList.push_front(clr.name());
    updateColorListSet();
    m_strFontColor = clr.name();
    update();
}
