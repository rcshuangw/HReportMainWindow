#include "hborderset.h"
#include "ui_hborderset.h"
#include "hformatset.h"
#include "hgridreportmgr.h"
#include "hgridcelldef.h"
#include <QPainter>
#include <QPen>
#include <QStandardItem>
#include <QMouseEvent>
#include <QColorDialog>
#include <QVariant>
typedef struct _tagDefaultColor
{
    QString strClrName;
    int     nClrValue;
}DefaultColor;

DefaultColor sysColorList2[]=
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

QStringList sysColorList1= {
    "#ffffff","#000000","#ff0000","#800000","#00ff00","#008000","#0000ff","#000080","#00ffff","#008080",
    "#ff00ff","#800080","#ffff00","#808000","#a0a0a4", "#808080", "#c0c0c0" };


HBorderSet::HBorderSet(HReportManager *mgr,QWidget *parent) :
    m_pReportManager(mgr),QWidget(parent),
    ui(new Ui::HBorderSet)
{
    ui->setupUi(this);
    m_recentColorList.clear();
    initLineStyleSet();
    initColorSet();
    initBorderSet();
    instanceBorderSet();
}

HBorderSet::~HBorderSet()
{
    m_recentColorList.clear();
    delete ui;
}

void HBorderSet::initBorderSet()
{
    m_bBorderLeft = false;
    m_bBorderTop = false;
    m_bBorderRight = false;
    m_bBorderBottom = false;
    m_strLineColor = "#000000";
    m_strBorderLeftLineColor = "#000000";//边框左线条颜色
    m_strBorderRightLineColor = "#000000";//边框右线条颜色
    m_strBorderTopLineColor = "#000000";//边框上线条颜色
    m_strBorderBottomLineColor = "#000000";//边框下线条颜色
    ui->borderNoBtn->setDefault(false);
    ui->borderAllBtn->setEnabled(false);
    ui->borderHorBtn->setEnabled(false);
    ui->borderVerBtn->setEnabled(false);
    connect(ui->borderLeftBtn,SIGNAL(clicked(bool)),this,SLOT(onBorderLeftBtn_clicked()));
    connect(ui->borderRightBtn,SIGNAL(clicked(bool)),this,SLOT(onBorderRightBtn_clicked()));
    connect(ui->borderTopBtn,SIGNAL(clicked(bool)),this,SLOT(onBorderTopBtn_clicked()));
    connect(ui->borderBottomBtn,SIGNAL(clicked(bool)),this,SLOT(onBorderBottomBtn_clicked()));
    connect(ui->borderNoBtn,SIGNAL(clicked(bool)),this,SLOT(onBorderNoBtn_clicked()));
    connect(ui->borderAllBtn,SIGNAL(clicked(bool)),this,SLOT(onBorderAllBtn_clicked()));
    connect(ui->borderOutSideBtn,SIGNAL(clicked(bool)),this,SLOT(onBorderOutSideBtn_clicked()));
}

QPixmap HBorderSet::createPenStyleIcon(Qt::PenStyle penStyle)
{
    QPixmap pixmap(134,16);
    QPainter painter(&pixmap);
    painter.fillRect(QRect(0,0,134,16),Qt::white);
    QPen pen(penStyle);
    pen.setColor(QColor(m_strLineColor));
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawLine(5,8,129,8);

    return pixmap;
}

void HBorderSet::initLineStyleSet()
{
    ui->lineStyleWidget->verticalHeader()->hide();
    ui->lineStyleWidget->horizontalHeader()->hide();
    ui->lineStyleWidget->verticalHeader()->setDefaultSectionSize(20);
    ui->lineStyleWidget->horizontalHeader()->setDefaultSectionSize(138);
    ui->lineStyleWidget->setShowGrid(false);
    ui->lineStyleWidget->setColumnCount(1);
    ui->lineStyleWidget->setRowCount(7);
    //ui->lineStyleWidget->setStyleSheet("selection-background-color:transparent"); //设置选中背景色
    updateLineStyleSet();
    connect(ui->lineStyleWidget,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(lineColorTableWidget_itemChanged()));

}

void HBorderSet::updateLineStyleSet()
{
    ui->lineStyleWidget->clear();

    ui->lineStyleWidget->setIconSize(QSize(134,16));
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setText(QStringLiteral("无"));
    item->setData(Qt::UserRole,QVariant((quint8)QPS_NOPEN));
    ui->lineStyleWidget->setItem(0,0,item);

    item = new QTableWidgetItem;
    item->setIcon(QIcon(createPenStyleIcon(Qt::SolidLine)));
    item->setData(Qt::UserRole,QVariant((quint8)QPS_SOLIDLINE));
    ui->lineStyleWidget->setItem(1,0,item);

    item = new QTableWidgetItem;
    item->setIcon(createPenStyleIcon(Qt::DashLine));
    item->setData(Qt::UserRole,QVariant((quint8)QPS_DASHLINE));
    ui->lineStyleWidget->setItem(2,0,item);

    item = new QTableWidgetItem;
    item->setIcon(createPenStyleIcon(Qt::DotLine));
    item->setData(Qt::UserRole,QVariant((quint8)QPS_DOTLINE));
    ui->lineStyleWidget->setItem(3,0,item);

    item = new QTableWidgetItem;
    item->setIcon(createPenStyleIcon(Qt::DashDotLine));
    item->setData(Qt::UserRole,QVariant((quint8)QPS_DASHDOTLINE));
    ui->lineStyleWidget->setItem(4,0,item);

    item = new QTableWidgetItem;
    item->setIcon(createPenStyleIcon(Qt::DashDotLine));
    item->setData(Qt::UserRole,QVariant((quint8)QPS_NOPEN));
    ui->lineStyleWidget->setItem(5,0,item);

    item = new QTableWidgetItem;
    item->setIcon(createPenStyleIcon(Qt::DashDotDotLine));
    item->setData(Qt::UserRole,QVariant((quint8)QPS_DASHDOTDOTLINE));
    ui->lineStyleWidget->setItem(6,0,item);

    item = new QTableWidgetItem;
    item->setIcon(createPenStyleIcon(Qt::CustomDashLine));
    item->setData(Qt::UserRole,QVariant((quint8)QPS_CUSTOMDASHLINE));
    ui->lineStyleWidget->setItem(7,0,item);
}

void HBorderSet::initColorSet()
{   
    ui->lineColorComboBox->setStyle(new HNoFocusProxyStyle);
    ui->lineColorComboBox->setStyleSheet("selection-background-color:white;"); //设置选中背景色
    ui->lineColorComboBox->setIconSize( QSize( 100, 20 ) );
    ui->lineColorComboBox->setSizeAdjustPolicy( QComboBox::AdjustToContents );
    updateColorListSet();
    QObject::connect(ui->lineColorComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(currentIndexChanged_clicked(int)));
    connect(ui->moreColorBtn,SIGNAL(clicked(bool)),this,SLOT(onMoreColorBtn_clicked()));
}

void HBorderSet::updateColorListSet()
{
    QStandardItemModel *model = (QStandardItemModel *)ui->lineColorComboBox->model();
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
        item->setData(QVariant(clr.name()));
        item->setToolTip(clr.name());
        model->appendRow(item);
    }

    for( int i = 0; i < sysColorList1.count();i++ )
    {
        QString color = sysColorList1[i];
        QColor clr = QColor( color);
        QPixmap pix( QSize( 100, 20 ) );
        pix.fill(clr);
        QStandardItem *item = new QStandardItem(QIcon( pix ), NULL);
        item->setData(QVariant(clr.name()));
        item->setToolTip(clr.name());
        model->appendRow(item);
    }
    ui->lineColorComboBox->setModel(model);
}

void HBorderSet::instanceBorderSet()
{
    if(!m_pReportManager || !m_pReportManager->formatSet())
        return;
    HFormatSet* pFormatSet = m_pReportManager->formatSet();

    //边框
    m_bBorderLeft = pFormatSet->isBorderLeft();
    m_strBorderLeftLineColor = pFormatSet->borderLeftLineColor();
    ui->borderLeftBtn->setChecked(m_bBorderLeft);
    m_bBorderRight = pFormatSet->isBorderRight();
    m_strBorderRightLineColor = pFormatSet->borderRightLineColor();
    ui->borderRightBtn->setChecked(m_bBorderRight);
    m_bBorderTop = pFormatSet->isBorderTop();
    m_strBorderTopLineColor = pFormatSet->borderTopLineColor();
    ui->borderTopBtn->setChecked(m_bBorderTop);
    m_bBorderBottom = pFormatSet->isBorderBottom();
    m_strBorderBottomLineColor = pFormatSet->borderBottomLineColor();
    ui->borderBottomBtn->setChecked(m_bBorderBottom);

    //线形
    m_nBorderLeftPenStyle = pFormatSet->borderLeftPenStyle();
    m_nBorderRightPenStyle = pFormatSet->borderRightPenStyle();
    m_nBorderTopPenStyle = pFormatSet->borderTopPenStyle();
    m_nBorderBottomPenStyle = pFormatSet->borderBottomPenStyle();

    //颜色
    m_strLineColor = m_strBorderLeftLineColor;
    updateLineStyleSet();
    m_nBorderPenStyle = m_nBorderLeftPenStyle;
    for(int i = 0; i < ui->lineStyleWidget->rowCount();i++)
    {
        QTableWidgetItem* item = ui->lineStyleWidget->item(i,0);
        if(item && item->data(Qt::UserRole).toInt() == m_nBorderPenStyle)
        {
            ui->lineStyleWidget->setCurrentItem(item);
            break;
        }
    }
}

void HBorderSet::mousePressEvent(QMouseEvent *event)
{

}

void HBorderSet::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint pt = event->pos();
    QRect rect = ui->viewFrame->geometry();
    QPoint borderPt = ui->groupBox_5->geometry().topLeft();
    QPoint viewFrameTopLeft = ui->viewFrame->geometry().topLeft()+borderPt ;
    QPoint viewFrameTopRight = viewFrameTopLeft+QPoint(rect.width(),0);
    QPoint viewFrameBottomLeft = viewFrameTopLeft+QPoint(0,rect.height());
    QPoint viewFrameBottomRight = viewFrameTopLeft+QPoint(rect.width(),rect.height());
    QRect borderLeftRect = QRect((viewFrameTopLeft + QPoint(0,10)),(viewFrameBottomLeft + QPoint(10,-10)));//ok
    QRect borderRightRect = QRect((viewFrameTopRight + QPoint(-10,10)),(viewFrameBottomRight + QPoint(0,-10)));//ok
    QRect borderTopRect = QRect((viewFrameTopLeft + QPoint(10,0)),(viewFrameTopRight + QPoint(-10,10)));//ok
    QRect borderBottomRect = QRect((viewFrameBottomLeft + QPoint(10,-10)),(viewFrameBottomRight + QPoint(-10,0)));//ok
    if(borderLeftRect.contains(pt))
    {
        if(m_strLineColor != m_strBorderLeftLineColor && m_bBorderLeft)
        {
            m_strBorderLeftLineColor = m_strLineColor;
            m_nBorderLeftPenStyle = m_nBorderPenStyle;
        }
        else
        {
            m_bBorderLeft = !m_bBorderLeft;
            m_strBorderLeftLineColor = m_strLineColor;
            m_nBorderLeftPenStyle = m_nBorderPenStyle;
        }
        ui->borderLeftBtn->setChecked(m_bBorderLeft);
    }
    else if(borderTopRect.contains(pt))
    {
        if(m_strLineColor != m_strBorderTopLineColor && m_bBorderTop)
        {
            m_strBorderTopLineColor = m_strLineColor;
            m_nBorderTopPenStyle = m_nBorderPenStyle;
        }
        else
        {
            m_bBorderTop = !m_bBorderTop;
            m_strBorderTopLineColor = m_strLineColor;
            m_nBorderTopPenStyle = m_nBorderPenStyle;
        }
        ui->borderTopBtn->setChecked(m_bBorderTop);
    }
    else if(borderRightRect.contains(pt))
    {
        if(m_strLineColor != m_strBorderRightLineColor && m_bBorderRight)
        {
            m_strBorderRightLineColor = m_strLineColor;
            m_nBorderRightPenStyle = m_nBorderPenStyle;
        }
        else
        {
            m_bBorderRight = !m_bBorderRight;
            m_strBorderRightLineColor = m_strLineColor;
            m_nBorderRightPenStyle = m_nBorderPenStyle;
        }
        ui->borderRightBtn->setChecked(m_bBorderRight);
    }
    else if(borderBottomRect.contains(pt))
    {
        if(m_strLineColor != m_strBorderBottomLineColor && m_bBorderBottom)
        {
            m_strBorderBottomLineColor = m_strLineColor;
            m_nBorderBottomPenStyle = m_nBorderPenStyle;
        }
        else
        {
            m_bBorderBottom = !m_bBorderBottom;
            m_strBorderBottomLineColor = m_strLineColor;
            m_nBorderBottomPenStyle = m_nBorderPenStyle;
        }
        ui->borderBottomBtn->setChecked(m_bBorderBottom);
    }
    update();
}

void HBorderSet::moveEvent(QMoveEvent *event)
{

}

void HBorderSet::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect rect = ui->viewFrame->geometry();
    QPoint borderPt = ui->groupBox_5->geometry().topLeft();
    QPoint viewFrameLeft = ui->viewFrame->geometry().topLeft()+borderPt ;
    QPoint viewFrameRight = viewFrameLeft+QPoint(rect.width(),0) ;

    QPoint frameInsideTopLeft = viewFrameLeft + QPoint(10,10);
    QPoint frameInsideTopRight = viewFrameRight + QPoint(-10,10);
    QPoint frameInsideBottomLeft = viewFrameLeft + QPoint(0,rect.height())+QPoint(10,-10);
    QPoint frameInsideBottomRight = viewFrameRight + QPoint(0,rect.height())+QPoint(-10,-10);

    //外框
    painter.setPen(QColor(Qt::black));
    painter.drawRect(QRect(viewFrameLeft,QSize(rect.width(),rect.height())));
    //分隔符
    painter.setPen(QColor(Qt::gray));
    painter.drawLine(frameInsideTopLeft-QPoint(0,5),frameInsideTopLeft);
    painter.drawLine(frameInsideTopLeft-QPoint(5,0),frameInsideTopLeft);
    painter.drawLine(frameInsideTopRight,frameInsideTopRight - QPoint(0,5));
    painter.drawLine(frameInsideTopRight,frameInsideTopRight + QPoint(5,0));
    painter.drawLine(frameInsideBottomLeft+QPoint(0,5),frameInsideBottomLeft);
    painter.drawLine(frameInsideBottomLeft-QPoint(5,0),frameInsideBottomLeft);
    painter.drawLine(frameInsideBottomRight,frameInsideBottomRight + QPoint(0,5));
    painter.drawLine(frameInsideBottomRight,frameInsideBottomRight + QPoint(5,0));

    if(m_bBorderLeft)
    {
        QColor clr(m_strBorderLeftLineColor);
        QPen lpen(clr);
        lpen.setStyle(Qt::PenStyle(m_nBorderLeftPenStyle));
        painter.setPen(lpen);
        painter.drawLine(frameInsideTopLeft,frameInsideBottomLeft);
    }
    if(m_bBorderRight)
    {
        QColor clr(m_strBorderRightLineColor);
        QPen rpen(clr);
        rpen.setStyle(Qt::PenStyle(m_nBorderRightPenStyle));
        painter.setPen(rpen);
        painter.drawLine(frameInsideTopRight,frameInsideBottomRight);
    }
    if(m_bBorderTop)
    {
        QColor clr(m_strBorderTopLineColor);
        QPen tpen(clr);
        tpen.setStyle(Qt::PenStyle(m_nBorderTopPenStyle));
        painter.setPen(tpen);
        painter.drawLine(frameInsideTopLeft,frameInsideTopRight);
    }
    if(m_bBorderBottom)
    {
        QColor clr(m_strBorderBottomLineColor);
        QPen bpen(clr);
        bpen.setStyle(Qt::PenStyle(m_nBorderBottomPenStyle));
        painter.setPen(bpen);
        painter.drawLine(frameInsideBottomLeft,frameInsideBottomRight);
    }
    //painter.drawText();
}

void HBorderSet::currentIndexChanged_clicked(int index)
{
    if((int)-1 == index)
        return;
    QStandardItemModel *model  = (QStandardItemModel *)ui->lineColorComboBox->model();
    if(model)
    {
        m_strLineColor = model->item(index,0)->data().toString();
        //m_strLineColor = QColor(Qt::GlobalColor(clrValue)).name();
    }
    updateLineStyleSet();
}

void HBorderSet::onBorderLeftBtn_clicked()
{
    if(m_strLineColor != m_strBorderLeftLineColor && m_bBorderLeft)
    {
        m_strBorderLeftLineColor = m_strLineColor;
    }
    else
    {
        m_bBorderLeft = !m_bBorderLeft;
        m_strBorderLeftLineColor = m_strLineColor;
    }
    ui->borderLeftBtn->setChecked(m_bBorderLeft);
    update();
}

void HBorderSet::onBorderVerBtn_clicked()
{

}

void HBorderSet::onBorderRightBtn_clicked()
{

    if(m_strLineColor != m_strBorderRightLineColor && m_bBorderRight)
    {
        m_strBorderRightLineColor = m_strLineColor;
    }
    else
    {
        m_bBorderRight = !m_bBorderRight;
        m_strBorderRightLineColor = m_strLineColor;
    }
    ui->borderRightBtn->setChecked(m_bBorderRight);
    update();
}

void HBorderSet::onBorderTopBtn_clicked()
{
    if(m_strLineColor != m_strBorderTopLineColor && m_bBorderTop)
    {
        m_strBorderTopLineColor = m_strLineColor;
    }
    else
    {
        m_bBorderTop = !m_bBorderTop;
        m_strBorderTopLineColor = m_strLineColor;
    }
    ui->borderTopBtn->setChecked(m_bBorderTop);
    update();

}

void HBorderSet::onBorderHorBtn_clicked()
{

}

void HBorderSet::onBorderBottomBtn_clicked()
{
    if(m_strLineColor != m_strBorderBottomLineColor && m_bBorderBottom)
    {
        m_strBorderBottomLineColor = m_strLineColor;
    }
    else
    {
        m_bBorderBottom = !m_bBorderBottom;
        m_strBorderBottomLineColor = m_strLineColor;
    }
    ui->borderBottomBtn->setChecked(m_bBorderBottom);
    update();

}

void HBorderSet::onBorderNoBtn_clicked()
{
    m_bBorderLeft = m_bBorderBottom = m_bBorderTop = m_bBorderRight = false;
    ui->borderLeftBtn->setChecked(m_bBorderLeft);
    ui->borderBottomBtn->setChecked(m_bBorderBottom);
    ui->borderTopBtn->setChecked(m_bBorderTop);
    ui->borderRightBtn->setChecked(m_bBorderRight);
    update();
}

void HBorderSet::onBorderAllBtn_clicked()
{

}

void HBorderSet::onBorderOutSideBtn_clicked()
{
    m_bBorderLeft = m_bBorderBottom = m_bBorderTop = m_bBorderRight = true;
    ui->borderLeftBtn->setChecked(m_bBorderLeft);
    ui->borderBottomBtn->setChecked(m_bBorderBottom);
    ui->borderTopBtn->setChecked(m_bBorderTop);
    ui->borderRightBtn->setChecked(m_bBorderRight);
    m_strBorderLeftLineColor = m_strLineColor;
    m_strBorderRightLineColor = m_strLineColor;
    m_strBorderTopLineColor = m_strLineColor;
    m_strBorderBottomLineColor = m_strLineColor;
    update();
}

void HBorderSet::onMoreColorBtn_clicked()
{
    QColor clr = QColorDialog::getColor(QColor(m_strLineColor),this,QStringLiteral("选择颜色"));
    while(m_recentColorList.count() > 5)
        m_recentColorList.removeLast();
    if((int)-1 == m_recentColorList.indexOf(clr.name()))
        m_recentColorList.push_front(clr.name());
    updateColorListSet();
    m_strLineColor = clr.name();
    updateLineStyleSet();
    update();
}

void HBorderSet::lineColorTableWidget_itemChanged()
{
    QTableWidgetItem* item = ui->lineStyleWidget->currentItem();
    if(NULL == item) return;
    m_nBorderPenStyle = item->data(Qt::UserRole).toUInt();
}

