#include "mainwindow.h"
#include <QTextEdit>
#include <QAbstractButton>
#include "SARibbonBar.h"
#include "SARibbonCategory.h"
#include <QPushButton>
#include "SARibbonPannel.h"
#include "SARibbonToolButton.h"
#include "SARibbonApplicationButton.h"
#include "SARibboniconstyle.h"
#include <QAction>
#include <QMenu>
#include <QDebug>
#include <QElapsedTimer>
#include <QFile>
#include "FramelessHelper.h"
#include "SARibbonMenu.h"
#include "SARibbonComboBox.h"
#include "SARibbonLineEdit.h"
#include "SARibbonGallery.h"
#include "SARibbonCheckBox.h"
#include "SARibbonQuickAccessBar.h"
#include "SARibbonButtonGroupWidget.h"
#include "hreportmaiwidget.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QStatusBar>
HReportMainWindow::HReportMainWindow(QWidget *par):QMainWindow(par),m_currentRibbonTheme(RibbonTheme::NormalTheme)
{
    setWindowTitle(QStringLiteral("报表设计"));



    QSplitter* splitter =new QSplitter(this);

    //树
    QTreeWidget *tree = new QTreeWidget(this);
    splitter->addWidget(tree);
    //这里应该是一个表格控件
    m_pReportMainWidget = new HReportMaiWidget(this);
    splitter->addWidget(m_pReportMainWidget);
    splitter->setStretchFactor(0,3);
    splitter->setStretchFactor(1,7);
    //初始化工具栏
    initSARibbonBar();
    m_ribbonMenuBar->quickAccessBar()->addButton(hideRibbonAct);
    m_ribbonMenuBar->quickAccessBar()->addButton(newAct);
    m_ribbonMenuBar->quickAccessBar()->addButton(closeAct);
    m_ribbonMenuBar->quickAccessBar()->addButton(informationAct);

    statusBar()->showMessage(QStringLiteral("报表设计"));
    setCentralWidget(splitter);
    showMaximized();

}

//
void HReportMainWindow::initSARibbonBar()
{
    setRibbonTheme(ribbonTheme());
    m_ribbonMenuBar = new SARibbonBar(this);
    setMenuWidget(m_ribbonMenuBar);
    m_ribbonMenuBar->installEventFilter(this);
    FramelessHelper *pHelper = new FramelessHelper(this);
    pHelper->setTitleHeight(m_ribbonMenuBar->titleBarHeight());  //设置窗体的标题栏高度
    QFont f = m_ribbonMenuBar->font();
    f.setFamily("微软雅黑");
    m_ribbonMenuBar->setFont(f);

    SARibbonCategory* categoryMain = m_ribbonMenuBar->addCategoryPage(QStringLiteral("开始"));
    createCategoryMain(categoryMain);
    SARibbonCategory* categoryPrint = m_ribbonMenuBar->addCategoryPage(QStringLiteral("打印"));
    createCategoryPrint(categoryPrint);
    SARibbonCategory* categoryOther = m_ribbonMenuBar->addCategoryPage(QStringLiteral("测试"));
    createCategoryOther(categoryOther);
    createCategoryMenu();


    //m_contextCategory = m_ribbonMenuBar->addContextCategory(QStringLiteral("context"),Qt::red,1);
    //SARibbonCategory* contextCategoryPage1 = m_contextCategory->addCategoryPage(QStringLiteral("Page1"));
    //SARibbonCategory* contextCategoryPage2 = m_contextCategory->addCategoryPage(QStringLiteral("Page1"));
}


void HReportMainWindow::onShowContextCategory(bool on)
{
    m_ribbonMenuBar->setContextCategoryVisible(m_contextCategory,on);
}

void HReportMainWindow::onWpsStyle(bool on)
{
    if(on)
        m_ribbonMenuBar->setRibbonStyle(SARibbonBar::WpsLiteStyle);
    else
        m_ribbonMenuBar->setRibbonStyle(SARibbonBar::OfficeStyle);
    update();
}

void HReportMainWindow::createCategoryMenu()
{
   // m_ribbonMenuBar->applitionButton()->setText(QStringLiteral("文件"));//menu
    hideRibbonAct = new QAction(QIcon(":/icon/icon/HideRibbon.png"),QStringLiteral("折叠功能区"),this);
    informationAct = new QAction(QIcon(":/icon/icon/information.png"),QStringLiteral("信息"),this);

    newAct = new QAction(QIcon(":/icon/icon/FileNew.png"),QStringLiteral("新建"),this);
    openAct = new QAction(QIcon(":/icon/icon/FileOpen.png"),QStringLiteral("打开"),this);
    saveAct = new QAction(QIcon(":/icon/icon/FileSave.png"),QStringLiteral("保存"),this);
    saveAsAct = new QAction(QIcon(":/icon/icon/FileSaveAs.png"),QStringLiteral("另存为"),this);
    closeAct = new QAction(QIcon(":/icon/icon/FileClose.png"),QStringLiteral("关闭"),this);

    SARibbonApplicationButton *btn = new SARibbonApplicationButton(this);
    btn->setStyleSheet("QPushButton::menu-indicator{image:None;}");
    btn->setText(QStringLiteral("文件"));
    btn->resize(56,30);
    SARibbonMenu* fileMenu = new SARibbonMenu(this);//不能用
    fileMenu->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    SARibbonIconStyle * iconSytle = new SARibbonIconStyle();
    iconSytle->setIconSize(QSize(32,32));
    fileMenu->setStyle(iconSytle);
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(printDialogAct);
    fileMenu->addAction(printOptionAct);
    fileMenu->addAction(printPreviewAct);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAct);
    btn->setMenu(fileMenu);
    m_ribbonMenuBar->setApplitionButton(btn);
}

void HReportMainWindow::createCategoryMain(SARibbonCategory *page)
{
    ///////////////////////////////////////////剪贴板//////////////////////////////////////////
    SARibbonToolButton * btn = NULL;
    SARibbonPannel* pannel = page->addPannel(QStringLiteral("剪贴板"));
    pasteAct = new QAction(this);
    pasteAct->setIcon(QIcon(":/icon/icon/Paste.png"));
    pasteAct->setText(QStringLiteral("粘贴"));
    pannel->addLargeAction(pasteAct);

    cutAct = new QAction(this);
    cutAct->setIcon(QIcon(":/icon/icon/Cut.png"));
    cutAct->setText(QStringLiteral("剪切"));
    pannel->addSmallAction(cutAct);

    copyAct = new QAction(this);
    copyAct->setIcon(QIcon(":/icon/icon/Copy.png"));
    copyAct->setText(QStringLiteral("拷贝"));
    pannel->addSmallAction(copyAct);

    formatPainterAct = new QAction(this);
    formatPainterAct->setIcon(QIcon(":/icon/icon/FormatPainter.png"));
    formatPainterAct->setText(QStringLiteral("格式刷"));
    formatPainterAct->setCheckable(true);
    formatPainterAct->setChecked(false);
    btn = pannel->addSmallAction(formatPainterAct);


    ////////////////////////////////////////////字体设置///////////////////////////////////////////
    //字体格式设置
    SARibbonPannel* fontPannel = page->addPannel(QStringLiteral("字体"));
    SARibbonComboBox* com = new SARibbonComboBox(this);//设置字体
    com->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    com->setEditable(true);
    fontPannel->addWidget(com,0,3);

    SARibbonButtonGroupWidget* btnGroup = new SARibbonButtonGroupWidget(fontPannel);
    btnGroup->setFrameShape(QFrame::NoFrame);
    boldAct = new QAction(QIcon(":/icon/icon/Bold.png"),"",this);
    boldAct->setToolTip(QStringLiteral("粗体"));
    italicAct = new QAction(QIcon(":/icon/icon/Italic.png"),"",this);
    italicAct->setToolTip(QStringLiteral("倾斜"));
    underlineAct = new QAction(QIcon(":/icon/icon/Underline.png"),"",this);
    underlineAct->setToolTip(QStringLiteral("下划线"));
    btnGroup->addButton(boldAct);
    btnGroup->addButton(italicAct);
    btnGroup->addButton(underlineAct);

    //字体背景颜色
    SARibbonMenu* clrmenu = new SARibbonMenu(this);
    fontBkColorAct = clrmenu->addAction(QIcon(":/icon/icon/fontbkcolor.png"),QStringLiteral("color"));
    clrmenu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1"));
    clrmenu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("11"));
    btn = btnGroup->addButton(fontBkColorAct);
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setToolButtonStyle(Qt::ToolButtonIconOnly);
    btn->setMenu(clrmenu);
    btn->setFixedWidth(32);
    btnGroup->addWidget(btn);

    //字体颜色
    SARibbonMenu* clrmenu2 = new SARibbonMenu(this);
    QPixmap pix(QSize(40,40));
    pix.fill(QColor(Qt::black));
    QAction* clrAct = new QAction(QIcon(pix),QStringLiteral("黑色"));
    clrmenu2->addAction(clrAct);
    pix.fill(QColor(Qt::white));
    clrAct = new QAction(QIcon(pix),QStringLiteral("白色"));
    clrmenu2->addAction(clrAct);
    pix.fill(QColor(Qt::red));
    clrAct = new QAction(QIcon(pix),QStringLiteral("红色"));
    clrmenu2->addAction(clrAct);
    pix.fill(QColor(Qt::green));
    clrAct = new QAction(QIcon(pix),QStringLiteral("绿色"));
    clrmenu2->addAction(clrAct);
    pix.fill(QColor(Qt::blue));
    clrAct = new QAction(QIcon(pix),QStringLiteral("蓝色"));
    clrmenu2->addAction(clrAct);
    pix.fill(QColor(Qt::yellow));
    clrAct = new QAction(QIcon(pix),QStringLiteral("黄色"));
    clrmenu2->addAction(clrAct);
    pix.fill(QColor(Qt::darkRed));
    clrAct = new QAction(QIcon(pix),QStringLiteral("深红色"));
    clrmenu2->addAction(clrAct);
    pix.fill(QColor(Qt::darkGreen));
    clrAct = new QAction(QIcon(pix),QStringLiteral("深绿色"));
    clrmenu2->addAction(clrAct);
    pix.fill(QColor(Qt::darkBlue));
    clrAct = new QAction(QIcon(pix),QStringLiteral("深绿色"));
    clrmenu2->addAction(clrAct);
    pix.fill(QColor(Qt::cyan));
    clrAct = new QAction(QIcon(pix),QStringLiteral("深蓝色"));
    clrmenu2->addAction(clrAct);
    fontColorAct = clrmenu2->addAction(QIcon(":/icon/icon/fontcolor.png"),QStringLiteral("字体颜色"));

    btn = btnGroup->addButton(fontColorAct);
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setToolButtonStyle(Qt::ToolButtonIconOnly);
    btn->setMenu(clrmenu2);
    btn->setFixedWidth(32);
    btnGroup->addWidget(btn);
    fontPannel->addWidget(btnGroup,3,3);
    fontPannel->addSeparator();

    //字体大小格式
    com = new SARibbonComboBox(this);
    com->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    com->setEditable(true);
    fontPannel->addWidget(com,0,3);
    btnGroup = new SARibbonButtonGroupWidget(fontPannel);
    btnGroup->setFrameShape(QFrame::NoFrame);
    SARibbonMenu* bordermenu = new SARibbonMenu(this);
    borderBottomAct = bordermenu->addAction(QIcon(":/icon/icon/BorderBottom.png"),QStringLiteral("下框线"));
    borderTopAct = bordermenu->addAction(QIcon(":/icon/icon/BorderTop.png"),QStringLiteral("上框线"));
    borderLeftAct = bordermenu->addAction(QIcon(":/icon/icon/BorderLeft.png"),QStringLiteral("左框线"));
    borderRightAct = bordermenu->addAction(QIcon(":/icon/icon/BorderRight.png"),QStringLiteral("右框线"));
    bordermenu->addSeparator();

    borderNoneAct = bordermenu->addAction(QIcon(":/icon/icon/BorderNone.png"),QStringLiteral("无框线"));
    borderAllAct = bordermenu->addAction(QIcon(":/icon/icon/BorderAll.png"),QStringLiteral("所有框线"));
    borderOutSideAct = bordermenu->addAction(QIcon(":/icon/icon/BorderOutside.png"),QStringLiteral("外侧框线"));
    borderInsideAct = bordermenu->addAction(QIcon(":/icon/icon/BorderInside.png"),QStringLiteral("内部框线"));
    bordermenu->addSeparator();
    borderInsideHorAct = bordermenu->addAction(QIcon(":/icon/icon/BorderInsideHorizontal.png"),QStringLiteral("内部竖框线"));
    borderInsideVerAct = bordermenu->addAction(QIcon(":/icon/icon/BorderInsideVertical.png"),QStringLiteral("内部横框线"));
    //如果单纯QAction就不需要下面操作，如果QAction变成菜单样式就需要借助SARibbonToolButton控件
    btn = btnGroup->addButton(borderBottomAct);
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setToolButtonStyle(Qt::ToolButtonIconOnly);
    btn->setMenu(bordermenu);
    btn->setFixedWidth(30);
    QAction* noneAct = new QAction(this);
    noneAct->setEnabled(false);
    btnGroup->addButton(noneAct);
    clearAllFormatsAct = new QAction(QIcon(":/icon/icon/Clear.png"),"",this);
    clearAllFormatsAct->setToolTip(QStringLiteral("全部清除"));
    btn = btnGroup->addButton(clearAllFormatsAct);
    fontPannel->addWidget(btnGroup,3,3);

    //调整字体设置
    btnGroup = new SARibbonButtonGroupWidget(fontPannel);
    btnGroup->setFrameShape(QFrame::NoFrame);
    fontSizeIncreaseAct = new QAction(QIcon(":/icon/icon/FontSizeIncrease.png"),"",this);
    fontSizeIncreaseAct->setToolTip(QStringLiteral("增大字号"));
    fontSizeDecreaseAct = new QAction(QIcon(":/icon/icon/FontSizeDecrease.png"),"",this);
    fontSizeDecreaseAct->setToolTip(QStringLiteral("减小字号"));
    btn = btnGroup->addButton(fontSizeIncreaseAct);
    btn = btnGroup->addButton(fontSizeDecreaseAct);
    fontPannel->addWidget(btnGroup,0,3);
    btnGroup = new SARibbonButtonGroupWidget(fontPannel);
    clearFormatsAct = new QAction(QIcon(":/icon/icon/ClearFormats.png"),"",this);
    clearFormatsAct->setToolTip(QStringLiteral("清除格式"));
    clearFormatingAct = new QAction(QIcon(":/icon/icon/ClearFormatting.png"),"",this);
    clearFormatingAct->setToolTip(QStringLiteral("清除内容"));
    btn = btnGroup->addButton(clearFormatsAct);
    btn = btnGroup->addButton(clearFormatingAct);
    fontPannel->addWidget(btnGroup,3,3);

    ////////////////////////////////////////////对齐设置/////////////////////////////////////////////////
    SARibbonPannel* aligPannel = page->addPannel(QStringLiteral("对齐"));
    SARibbonButtonGroupWidget* btnGroup1 = new SARibbonButtonGroupWidget(aligPannel);
    btnGroup1->setFrameShape(QFrame::NoFrame);
    alignTopAct = new QAction(QIcon(":/icon/icon/AlignTop.png"),"",this);
    alignTopAct->setToolTip(QStringLiteral("顶端对齐"));
    alignMiddleAct = new QAction(QIcon(":/icon/icon/AlignMiddle.png"),"",this);
    alignMiddleAct->setToolTip(QStringLiteral("垂直居中"));
    alignBottomAct = new QAction(QIcon(":/icon/icon/AlignBottom.png"),"",this);
    alignBottomAct->setToolTip(QStringLiteral("底端对齐"));
    btnGroup1->addButton(alignTopAct);
    btnGroup1->addButton(alignMiddleAct);
    btnGroup1->addButton(alignBottomAct);
    aligPannel->addWidget(btnGroup1,0,3);
    btnGroup = new SARibbonButtonGroupWidget(aligPannel);
    btnGroup->setFrameShape(QFrame::NoFrame);
    alignLeftAct = new QAction(QIcon(":/icon/icon/AlignLeft.png"),"",this);
    alignLeftAct->setToolTip(QStringLiteral("左对齐"));
    alignCenterAct = new QAction(QIcon(":/icon/icon/AlignCenter.png"),"",this);
    alignCenterAct->setToolTip(QStringLiteral("居中"));
    alignRightAct = new QAction(QIcon(":/icon/icon/AlignRight.png"),"",this);
    alignRightAct->setToolTip(QStringLiteral("右对齐"));
    btnGroup->addButton(alignLeftAct);
    btnGroup->addButton(alignCenterAct);
    btnGroup->addButton(alignRightAct);
    aligPannel->addWidget(btnGroup,2,3);
    aligPannel->addSeparator();

    //设置自动换行
    autoWrapTextAct = new QAction(this);
    autoWrapTextAct->setIcon(QIcon(":/icon/icon/WrapText.png"));
    autoWrapTextAct->setText(QStringLiteral("自动换行"));
    btn = aligPannel->addSmallAction(autoWrapTextAct);
    aligPannel->addWidget(btn,0,3);
    //合并单元格
    SARibbonMenu* mergemenu = new SARibbonMenu(this);
    mergeCenterAct = mergemenu->addAction(QIcon(":/icon/icon/MergeCenter.png"),QStringLiteral("合并后居中"));
    mergeCellsAct = mergemenu->addAction(QIcon(":/icon/icon/MergeCells.png"),QStringLiteral("合并单元格"));
    mergeSplitAct = mergemenu->addAction(QIcon(":/icon/icon/MergeOrSplitCells.png"),QStringLiteral("取消合并单元格"));
    btn = aligPannel->addSmallAction(mergeCenterAct);
    btn->setIcon(QIcon(":/icon/icon/MergeCenter.png"));
    btn->setText(QStringLiteral("合并后居中"));
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    btn->setMenu(mergemenu);
    aligPannel->addWidget(btn,2,3);


    //////////////////////////////////////////////////////单元格///////////////////////////////////////////
    SARibbonPannel* cellPannel = page->addPannel(QStringLiteral("单元格"));
    //插入单元格
    SARibbonMenu* cellmenu = new SARibbonMenu(this);
    cellInsertAct = cellmenu->addAction(QIcon(":/icon/icon/sCellsInsertDialog.png"),QStringLiteral("插入单元格"));
    cellmenu->addSeparator();
    cellInsertRowAct = cellmenu->addAction(QIcon(":/icon/icon/InsertRow.png"),QStringLiteral("插入工作表行"));
    cellInsertColAct = cellmenu->addAction(QIcon(":/icon/icon/RemoveRow.png"),QStringLiteral("插入工作表列"));
    btn = cellPannel->addLargeAction(cellInsertAct);
    btn->setIcon(QIcon(":/icon/icon/CellsInsertDialog.png"));
    btn->setText(QStringLiteral("插入"));
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn->setMenu(cellmenu);
    cellPannel->addWidget(btn);
    //删除单元格
    cellmenu = new SARibbonMenu(this);
    cellDeleteAct = cellmenu->addAction(QIcon(":/icon/icon/sCellsDelete.png"),QStringLiteral("删除单元格"));
    cellmenu->addSeparator();
    cellRemoveRowAct = cellmenu->addAction(QIcon(":/icon/icon/InsertColumn.png"),QStringLiteral("删除工作表行"));
    cellRemoveColAct = cellmenu->addAction(QIcon(":/icon/icon/RemoveColumn.png"),QStringLiteral("删除工作表列"));
    btn = cellPannel->addLargeAction(cellDeleteAct);
    btn->setIcon(QIcon(":/icon/icon/CellsDelete.png"));
    btn->setText(QStringLiteral("删除"));
    btn->setToolTip(QStringLiteral("格式"));
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn->setMenu(cellmenu);
    cellPannel->addWidget(btn);

    //格式化单元格
    cellmenu = new SARibbonMenu(this);
    cellRowHeightAct = cellmenu->addAction(QIcon(":/icon/icon/RowHeight.png"),QStringLiteral("行高"));
    cellAutoRowHeightAct = cellmenu->addAction(QStringLiteral("自动调整行高"));
    cellmenu->addSeparator();
    cellColWidthAct = cellmenu->addAction(QIcon(":/icon/icon/ColumnWidth.png"),QStringLiteral("列宽"));
    cellAutoColWidthAct = cellmenu->addAction(QStringLiteral("自动调整列宽"));
    cellDefaultColWidthAct = cellmenu->addAction(QStringLiteral("默认列宽"));
    cellmenu->addSeparator();
    cellSetFormatAct = cellmenu->addAction(QIcon(":/icon/icon/CellsFormat.png"),QStringLiteral("设置单元格格式"));
    btn = cellPannel->addLargeAction(cellRowHeightAct);
    btn->setIcon(QIcon(":/icon/icon/CellStylesGallery.png"));
    btn->setText(QStringLiteral("格式"));
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn->setMenu(cellmenu);
    cellPannel->addWidget(btn);

    /////////////////////////////////////////操作票设置///////////////////////////////////////////////////////////////
    SARibbonPannel* opSheetPannel = page->addPannel(QStringLiteral("操作票设置"));
    opSheetAct = new QAction(QIcon(":/icon/icon/OpSheet.png"),QStringLiteral("操作票设置"));
    connect(opSheetAct,&QAction::triggered,this,&HReportMainWindow::option_click);
    opSheetPannel->addLargeAction(opSheetAct);


    optAct = new QAction(this);
    connect(optAct,&QAction::triggered,this,&HReportMainWindow::option_click);
    optAct->setToolTip(QStringLiteral("单元格格式"));
    pannel->addOptionAction(optAct);
    fontPannel->addOptionAction(optAct);
    aligPannel->addOptionAction(optAct);
    cellPannel->addOptionAction(optAct);

    return;
    //btn->setPopupMode(QToolButton::MenuButtonPopup);

    //act = new QAction(this);
    //act->setIcon(QIcon(":/icon/icon/Bold.png"));
    //act->setText(QStringLiteral("test 3"));
    //act->setMenu(menu);
    //btn = fontPannel->addSmallAction(act);
    //btn->setPopupMode(QToolButton::MenuButtonPopup);

    //act = new QAction(this);
    //act->setIcon(QIcon(":/icon/icon/Italic.png"));
    //act->setText(QStringLiteral("test 4"));
    //act->setMenu(menu);
    //btn = fontPannel->addSmallAction(act);
    //btn->setPopupMode(QToolButton::InstantPopup);

    //act = new QAction(this);
    //act->setIcon(QIcon(":/icon/icon/Underline.png"));
    //act->setText(QStringLiteral("test 4"));
    //act->setMenu(menu);
    //btn = fontPannel->addSmallAction(act);
    //btn->setPopupMode(QToolButton::InstantPopup);



    return;
    /*
    pannel->addSeparator();

    act = new QAction(this);
    act->setIcon(QIcon(":/icon/icon/folder.png"));
    act->setText(QStringLiteral("DelayedPopup"));
    act->setMenu(menu);
    btn = pannel->addLargeAction(act);
    btn->setPopupMode(QToolButton::DelayedPopup);
    connect(act,&QAction::triggered,this,&MainWindow::onDelayedPopupCheckabletriggered);

    act = new QAction(this);
    act->setIcon(QIcon(":/icon/icon/folder.png"));
    act->setText(QStringLiteral("MenuButtonPopup"));
    act->setMenu(menu);
    btn = pannel->addLargeAction(act);
    btn->setPopupMode(QToolButton::MenuButtonPopup);
    connect(act,&QAction::triggered,this,&MainWindow::onMenuButtonPopupCheckabletriggered);

    act = new QAction(this);
    act->setIcon(QIcon(":/icon/icon/Graph-add.png"));
    act->setText(QStringLiteral("InstantPopup"));
    act->setMenu(menu);
    btn = pannel->addLargeAction(act);
    btn->setPopupMode(QToolButton::InstantPopup);
    connect(act,&QAction::triggered,this,&MainWindow::onInstantPopupCheckabletriggered);

    act = new QAction(this);
    act->setCheckable(true);
    act->setIcon(QIcon(":/icon/icon/folder.png"));
    act->setText(QStringLiteral("DelayedPopup"));
    act->setMenu(menu);
    btn = pannel->addLargeAction(act);
    btn->setPopupMode(QToolButton::DelayedPopup);
    btn->setCheckable(true);
    connect(act,&QAction::triggered,this,&MainWindow::onDelayedPopupCheckableTest);

    act = new QAction(this);
    act->setCheckable(true);
    act->setIcon(QIcon(":/icon/icon/folder.png"));
    act->setText(QStringLiteral("MenuButtonPopup\n checkable"));
    act->setMenu(menu);
    btn = pannel->addLargeAction(act);
    btn->setPopupMode(QToolButton::MenuButtonPopup);
    btn->setCheckable(true);
    connect(act,&QAction::triggered,this,&MainWindow::onMenuButtonPopupCheckableTest);

    act = new QAction(this);
    act->setCheckable(true);
    act->setIcon(QIcon(":/icon/icon/Graph-add.png"));
    act->setText(QStringLiteral("InstantPopup"));
    act->setMenu(menu);
    btn = pannel->addLargeAction(act);
    btn->setCheckable(true);
    btn->setPopupMode(QToolButton::InstantPopup);
    connect(act,&QAction::triggered,this,&MainWindow::onInstantPopupCheckableTest);

    SARibbonPannel* panne2 = page->addPannel(QStringLiteral("pannel 2"));
    act = new QAction(this);
    act->setCheckable(true);
    act->setIcon(QIcon(":/icon/icon/Graph-add.png"));
    act->setText(QStringLiteral("show\nContext"));
    btn = panne2->addLargeAction(act);
    btn->setCheckable(true);
    //btn->setPopupMode(QToolButton::InstantPopup);
    connect(act,&QAction::triggered,this,[this](bool on){
        if(on)
            m_ribbonMenuBar->showContextCategory(this->m_contextCategory);
        else
            m_ribbonMenuBar->hideContextCategory(this->m_contextCategory);
    });

    act = new QAction(this);
    act->setCheckable(true);
    act->setIcon(QIcon(":/icon/icon/Graph-add.png"));
    act->setText(QStringLiteral("unactive"));
    act->setMenu(menu);
    btn = panne2->addLargeAction(act);
    btn->setCheckable(true);
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setEnabled(false);




    com = new SARibbonComboBox(this);
    com->setSizePolicy(QSizePolicy::Expanding,
                       QSizePolicy::Fixed);
    com->setWindowIcon(QIcon(":/icon/icon/folder.png"));
    com->setWindowTitle("ComboBox Editable");
    for (int i=0;i<40;++i)
        com->addItem("111111111111");
    pannel->addWidget(com);

    SARibbonLineEdit* lineEdit = new SARibbonLineEdit(this);
    lineEdit->setSizePolicy(QSizePolicy::Expanding,
                       QSizePolicy::Fixed);
    lineEdit->setWindowIcon(QIcon(":/icon/icon/folder.png"));
    lineEdit->setWindowTitle("Line Edit");
    lineEdit->setText("SARibbonLineEdit");
    pannel->addWidget(lineEdit);
QWidget* w = lineEdit->parentWidget();
while(w)
{
    qDebug() << w->metaObject()->className();
    w = w->parentWidget();
}
    SARibbonCheckBox* checkBox = new SARibbonCheckBox(this);
    checkBox->setSizePolicy(QSizePolicy::Expanding,
                       QSizePolicy::Fixed);
    checkBox->setWindowIcon(QIcon(":/icon/icon/folder.png"));
    checkBox->setText("checkBox");
    pannel->addWidget(checkBox);*/

    //pannel->setExpanding();
    //QAction* optAct = new QAction(this);
    //pannel->addOptionAction(optAct);
}

void HReportMainWindow::createCategoryOther(SARibbonCategory *page)
{
    SARibbonMenu* menu = new SARibbonMenu(this);
    QAction * item = menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("22221111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1111111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1111111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1111111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1111111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1111111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1111111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1111111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1111111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1111111"));

    SARibbonPannel* pannel = page->addPannel(QStringLiteral("pannel 1"));
    SARibbonButtonGroupWidget* btnGroup = new SARibbonButtonGroupWidget(pannel);
    btnGroup->setFrameShape(QFrame::Box);
    btnGroup->addButton(new QAction(QIcon(":/icon/icon/figureIcon.png"),"",this));
    btnGroup->addButton(new QAction(QIcon(":/icon/icon/information.png"),"",this));
    pannel->addWidget(btnGroup,0,3);

    SARibbonToolButton* btn;
    btn = pannel->addLargeAction(item);
    btn->setIcon(QIcon(":/icon/icon/folder.png"));
    btn->setText(QStringLiteral("un format\nicon"));
    btn->setPopupMode(QToolButton::DelayedPopup);
    btn->setFixedHeight(78);
    btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn->setMenu(menu);
    pannel->addWidget(btn);

    btn = pannel->addLargeAction(item);
    btn->setIcon(QIcon(":/icon/icon/folder.png"));
    btn->setText(QStringLiteral("change page\ntest"));
    btn->setPopupMode(QToolButton::MenuButtonPopup);
    btn->setFixedHeight(78);
    btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn->setMenu(menu);
    pannel->addWidget(btn);

    btn = pannel->addLargeAction(item);
    btn->setIcon(QIcon(":/icon/icon/folder.png"));
    btn->setText(QStringLiteral("LargeBtn"));
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setFixedHeight(78);
    btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn->setMenu(menu);
    pannel->addWidget(btn);

    SARibbonGallery* gallery = pannel->addGallery();
    SARibbonGalleryGroup*group = gallery->addGalleryGroup();
    for(int i=0;i<100;++i)
    {
        group->addItem(QIcon(":/icon/icon/folder.png"));
    }
    QAction* optAct = new QAction(this);
    pannel->addOptionAction(optAct);
    pannel->setObjectName("debug");

}

void HReportMainWindow::createCategoryPrint(SARibbonCategory* page)
{
    SARibbonPannel* printpannel = page->addPannel(QStringLiteral("打印设置"));


    printDialogAct = new QAction(this);
    printDialogAct->setIcon(QIcon(":/icon/icon/PrintDialogAccess.png"));
    printDialogAct->setText(QStringLiteral("快速打印"));
    printpannel->addLargeAction(printDialogAct);

    printOptionAct = new QAction(this);
    printOptionAct->setIcon(QIcon(":/icon/icon/PrintOptionsMenuWord.png"));
    printOptionAct->setText(QStringLiteral("打印选项"));
    printpannel->addLargeAction(printOptionAct);

    printPreviewAct = new QAction(this);
    printPreviewAct->setIcon(QIcon(":/icon/icon/PrintPreviewZoomMenu.png"));
    printPreviewAct->setText(QStringLiteral("打印预览"));
    printpannel->addLargeAction(printPreviewAct);

}

void HReportMainWindow::onMenuButtonPopupCheckableTest(bool b)
{
    //m_edit->append(QStringLiteral("MenuButtonPopupCheckableTest : %1").arg(b));
}

void HReportMainWindow::onInstantPopupCheckableTest(bool b)
{
   // m_edit->append(QStringLiteral("InstantPopupCheckableTest : %1").arg(b));
}

void HReportMainWindow::onDelayedPopupCheckableTest(bool b)
{
    //m_edit->append(QStringLiteral("DelayedPopupCheckableTest : %1").arg(b));
}

void HReportMainWindow::onMenuButtonPopupCheckabletriggered(bool b)
{
    //m_edit->append(QStringLiteral("MenuButtonPopupCheckabletriggered : %1").arg(b));
}

void HReportMainWindow::onInstantPopupCheckabletriggered(bool b)
{
    //m_edit->append(QStringLiteral("InstantPopupCheckabletriggered : %1").arg(b));
}

void HReportMainWindow::onDelayedPopupCheckabletriggered(bool b)
{
    //m_edit->append(QStringLiteral("DelayedPopupCheckabletriggered : %1").arg(b));
}


/*
SARibbonBar *MainWindow::ribbonBar()
{
    return m_ribbonMenuBar;
}*/

void HReportMainWindow::setRibbonTheme(RibbonTheme theme)
{
    switch(theme)
    {
    case NormalTheme:
        loadTheme("resource/default.qss");
        break;
    default:
        loadTheme(":/theme/resource/default.qss");
        break;
    }
}

HReportMainWindow::RibbonTheme HReportMainWindow::ribbonTheme() const
{
    return m_currentRibbonTheme;
}

void HReportMainWindow::resizeEvent(QResizeEvent *event)
{
    if(m_ribbonMenuBar)
    {
        if(m_ribbonMenuBar->size().width() != this->size().width())
        {
            m_ribbonMenuBar->setFixedWidth(this->size().width());
        }
    }
    QMainWindow::resizeEvent(event);
}

bool HReportMainWindow::eventFilter(QObject *obj, QEvent *e)
{//
    /*if(obj == m_d->ribbonBar)
    {
        switch (e->type())
        {
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseMove:
        case QEvent::Leave:
        case QEvent::HoverMove:
        case QEvent::MouseButtonDblClick:
            QApplication::sendEvent(this,e);
        default:
            break;
        }
    }*/
    return QMainWindow::eventFilter(obj,e);
}


void HReportMainWindow::loadTheme(const QString& themeFile)
{
    QFile file(themeFile);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
     return;
    }
    QString str = file.readAll();
    setStyleSheet(str);
    file.close();
}

