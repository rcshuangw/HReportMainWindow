#ifndef HREPORTBROWSERWIDGET_H
#define HREPORTBROWSERWIDGET_H
#include <QWidget>
class HReportManager;
class HGridReportWidget;
class HFormatSet;
//表格预览窗口
class HReportBrowserWidget : public QWidget
{
    Q_OBJECT
public:
    HReportBrowserWidget(HReportManager* mgr,QWidget* parent = 0);

public:

    void newReportWidget(quint16 wReportID);
    void openReportWidget(quint16 wReportID = (quint16)-1);
    void delReportWidget(quint16 wReportID);

    void printReportWidget();
    void printPreviewReportWidget();

    void setCellFormat(HFormatSet* pFormatSet,uint formatType,bool bAll = false);
    void loadSheetNo(quint16 sheetNo);



signals:
    //void gridcellclicked(HGridCell*);
public slots:
    //void gridCell_clicked(HGridCell*);
    void loadSheet();
    void loadPrevSheet();
    void loadNextSheet();

    void refreshReportWidget();
protected:
    void contextMenuEvent(QContextMenuEvent *event);
private:
    quint16 m_wReportID;
    quint16 m_wSheetNo;
public:
    HGridReportWidget* m_pGridReportWidget;
    HReportManager* m_pReportManager;
};

#endif // HREPORTBROWSERWIDGET_H
