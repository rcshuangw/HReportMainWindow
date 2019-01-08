#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QAction>
class SARibbonBar;
class SARibbonCategory;
class SARibbonContextCategory;
class SARibbonComboBox;
class QTextEdit;
class HReportManager;
class HReportMaiWidget;
class HReportTreeWidget;
//报表窗口
class HReportMainWindow : public QMainWindow
{
    Q_OBJECT

public:

    enum RibbonTheme{
        NormalTheme  ///< 普通主题
          };
public:
    HReportMainWindow(HReportManager* mgr,QWidget* par=nullptr);

public:
    void initReportConnect();
    void initSARibbonBar();
    void setReportManager(HReportManager* mgr);
private slots:
    void onShowContextCategory(bool on);
    void onWpsStyle(bool on);
private:
    void createCategoryMenu();
    void createCategoryMain(SARibbonCategory* page);
    void createCategoryPrint(SARibbonCategory* page);
    void createCategoryOther(SARibbonCategory* page);
private slots:
    void onMenuButtonPopupCheckableTest(bool b);
    void onInstantPopupCheckableTest(bool b);
    void onDelayedPopupCheckableTest(bool b);

    void onMenuButtonPopupCheckabletriggered(bool b);
    void onInstantPopupCheckabletriggered(bool b);
    void onDelayedPopupCheckabletriggered(bool b);

    void setRibbonTheme(RibbonTheme theme);
    RibbonTheme ribbonTheme() const;

protected:
    void loadTheme(const QString &themeFile);
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *e);
    void setAttrPage(quint8);


private:
    SARibbonContextCategory* m_contextCategory;
    SARibbonBar* m_ribbonMenuBar;
    RibbonTheme m_currentRibbonTheme;
public:
    HReportManager* m_pReportManager;
    HReportMaiWidget* m_pReportMainWidget;
    HReportTreeWidget* m_pReportTreeWidget;


public slots:

    void new_clicked();
    void save_clicked();
    void Open(const QString&,const int graphID);
    void Del(const QString&,const int graphID);
    void ImportFile(const QString&);

    void fontFamilyComboBox_changed(int);
    void fontSizeComboBox_changed(int);
    //action
    void paste_clicked();
    void cut_clicked();
    void copy_clicked();
    void formatPainter_clicked();
    void bold_clicked();
    void italic_clicked();
    void underline_clicked();

    //
    void fontColor_clicked();
    void fontBkColor_clicked();
    void fontColorActGroup_clicked(QAction*);
    void fontBkColorActGroup_clicked(QAction*);
    //
    void borderBottom_clicked();
    void borderTop_clicked();
    void borderLeft_clicked();
    void borderRight_clicked();
    void borderNone_clicked();
    void borderAll_clicked();
    void borderOutSide_clicked();
    void borderInside_clicked();
    void borderInsideHor_clicked();
    void borderInsideVer_clicked();
    void fontSizeIncrease_clicked();
    void fontSizeDecrease_clicked();
    void clearAllFormat_clicked();
    void clearFormats_clicked();
    void clearFommating_clicked();
    void alignTop_clicked();
    void alignMiddle_clicked();
    void alignBottom_clicked();
    void alignLeft_clicked();
    void alignCenter_clicked();
    void alignRight_clicked();
    void autoWrapText_clicked();
    void mergeCenter_clicked();
    void mergeCells_clicked();
    void mergeSplit_clicked();
    void cellInsert_clicked();
    void gridInsertRow_clicked();
    void gridInsertCol_clicked();
    void cellDelete_clicked();
    void gridRemoveRow_clicked();
    void gridRemoveCol_clicked();
    void cellRowHeight_clicked();
    void cellAutoRowHeight_clicked();
    void cellColWidth_clicked();
    void cellAutoColWidth_clicked();
    void cellDefaultColWidth_clicked();
    void cellSetFormat_clicked();
    void option_clicked();
    void baseOption_clicked();
    void fontOption_clicked();
    void printDialog_clicked();
    void printOption_clicked();
    void printPreview_clicked();
    void opSheet_clicked();
    void hideRibbon_clicked(bool);
    void information_clicked();

    //表格选择
    void gridCell_clicked();

public:
    SARibbonComboBox* fontFamilyComboBox;
    SARibbonComboBox* fontSizeComboBox;
    //QAction
    //文件
    QAction* newAct;
    QAction* openAct;
    QAction* saveAct;
    QAction* saveAsAct;
    QAction* closeAct;

    //剪切板
    QAction* pasteAct;
    QAction* cutAct;
    QAction* copyAct;
    QAction* formatPainterAct;

    //字体设置
    QAction* boldAct;
    QAction* italicAct;
    QAction* underlineAct;

    //字体颜色
    QAction* fontColorAct;
    QAction* fontBkColorAct;
    QActionGroup* fontColorActGroup;
    QActionGroup* fontBkColorActGroup;

    //边框设置
    QAction* borderBottomAct;
    QAction* borderTopAct;
    QAction* borderLeftAct;
    QAction* borderRightAct;
    QAction* borderNoneAct;
    QAction* borderAllAct;
    QAction* borderOutSideAct;
    QAction* borderInsideAct;
    QAction* borderInsideHorAct;
    QAction* borderInsideVerAct;

    //字体大小设置
    QAction* fontSizeIncreaseAct;
    QAction* fontSizeDecreaseAct;

    //字体格式
    QAction* clockFormatAct;
    QAction* clearAllFormatsAct;//清除所有
    QAction* clearFormatsAct; //清楚格式
    QAction* clearFormatingAct;//清除内容

    //字体对齐
    QAction* alignTopAct;
    QAction* alignMiddleAct;
    QAction* alignBottomAct;
    QAction* alignLeftAct;
    QAction* alignCenterAct;
    QAction* alignRightAct;

    //自动换行
    QAction* autoWrapTextAct;//自动换行

    //合并单元格
    QAction* mergeCenterAct;
    QAction* mergeCellsAct;
    QAction* mergeSplitAct;

    //单元格插入
    QAction* cellInsertAct;
    QAction* cellInsertRowAct;
    QAction* cellRemoveRowAct;

    //单元格删除
    QAction* cellDeleteAct;
    QAction* cellInsertColAct;
    QAction* cellRemoveColAct;

    //单元格格式
    QAction* cellRowHeightAct;
    QAction* cellAutoRowHeightAct;
    QAction* cellColWidthAct;
    QAction* cellAutoColWidthAct;
    QAction* cellDefaultColWidthAct;
    QAction* cellSetFormatAct;

    //格式
    QAction* baseOptAct;
    QAction* fontOptAct;

    //显示格式
    QAction* opSheetAct;

    //打印
    QAction* printDialogAct;
    QAction* printOptionAct;
    QAction* printPreviewAct;



    //隐藏工具栏
    QAction* hideRibbonAct;
    QAction* informationAct;

};

#endif // MAINWINDOW_H
