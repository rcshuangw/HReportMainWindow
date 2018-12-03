#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
class SARibbonBar;
class SARibbonCategory;
class SARibbonContextCategory;
class QTextEdit;
class HGridReportMgr;
class HReportMaiWidget;
//报表窗口
class HReportMainWindow : public QMainWindow
{
    Q_OBJECT

public:

    enum RibbonTheme{
        NormalTheme  ///< 普通主题
          };
public:
    HReportMainWindow(QWidget* par=nullptr);

public:
    void initSARibbonBar();
    void setGridReportMgr(HGridReportMgr* mgr);
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
private:
    SARibbonContextCategory* m_contextCategory;
    SARibbonBar* m_ribbonMenuBar;
    RibbonTheme m_currentRibbonTheme;
public:
    HGridReportMgr* m_pGridReportMgr;
    HReportMaiWidget* m_pReportMainWidget;


public slots:
    void paste_click();
    void cut_click();
    void copy_click();
    void formatPainter_click();
    void bold_click();
    void italic_click();
    void underline_click();
    void fontColor_click();
    void fontbkColor_click();
    void borderBottom_click();
    void borderTop_click();
    void borderLeft_click();
    void borderRight_click();
    void borderNone_click();
    void borderAll_click();
    void borderOutSide_click();
    void borderInside_click();
    void borderInsideHor_click();
    void borderInsideVer_click();
    void fontSizeIncrease_click();
    void fontSizeDecrease_click();
    void clearAllFormat_click();
    void clearFormats_click();
    void clearFommating_click();
    void alignTop_click();
    void alignMiddle_click();
    void alignBottom_click();
    void alignLeft_click();
    void alignCenter_click();
    void alignRight_click();
    void autoWrapText_click();
    void mergeCenter_click();
    void mergeCells_click();
    void mergeSplit_click();
    void cellInsert_click();
    void cellInsertRow_click();
    void cellInsertCol_click();
    void cellDelete_click();
    void cellRemoveRow_click();
    void cellRemoveCol_click();
    void cellRowHeight_click();
    void cellAutoRowHeight_click();
    void cellColWidth_click();
    void cellAutoColWidth_click();
    void cellDefaultColWidth_click();
    void cellSetFormat_click();
    void option_click();
    void printDialog_click();
    void printOption_click();
    void printPreview_click();
    void opSheet_click();
    void hideRibbon_click();
    void information_click();

public:

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
    QAction* optAct;

    //打印
    QAction* printDialogAct;
    QAction* printOptionAct;
    QAction* printPreviewAct;

    //显示设置
    QAction* opSheetAct;

    //隐藏工具栏
    QAction* hideRibbonAct;
    QAction* informationAct;

};

#endif // MAINWINDOW_H
