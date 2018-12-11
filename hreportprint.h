#ifndef HREPORTPRINT_H
#define HREPORTPRINT_H
//打印类
#include <QObject>
#include <QRect>
#include <QFont>
#include <QSize>
class QPrinter;
class QPainter;
class HGridCtrl;
class HGridReportWidget;
struct HPrintInfo // Printing information structure
{
    HPrintInfo();
    ~HPrintInfo();
/*
    CPrintDialog* m_pPD;     // pointer to print dialog

    BOOL m_bDocObject;       // TRUE if printing by IPrint interface
    BOOL m_bPreview;         // TRUE if in preview mode
    BOOL m_bDirect;          // TRUE if bypassing Print Dialog
    BOOL m_bContinuePrinting;// set to FALSE to prematurely end printing
    UINT m_nCurPage;         // Current page
    UINT m_nNumPreviewPages; // Desired number of preview pages
    CString m_strPageDesc;   // Format string for page number display
    LPVOID m_lpUserData;     // pointer to user created struct

    int m_nJobNumber;			 // job number (after StartDoc)

    // these only valid if m_bDocObject
    uint m_nOffsetPage;      // offset of first page in combined IPrint job
    quint32 m_dwFlags;         // flags passed to IPrint::Print

    void SetMinPage(UINT nMinPage);
    void SetMaxPage(UINT nMaxPage);
    UINT GetMinPage() const;
    UINT GetMaxPage() const;
    UINT GetFromPage() const;
    UINT GetToPage() const;
    UINT GetOffsetPage() const;*/
    uint m_nCurPage;         // Current page
    HGridCtrl* m_pGridCtrl;
    QRect m_rectDraw;        // rectangle defining current usable page area
};

class HReportPrint : QObject
{
    Q_OBJECT
public:
    HReportPrint();

public:
    void onPrintBegin(QPainter *p, HPrintInfo *pInfo);
    void onPrint(QPainter *p, HPrintInfo *pInfo);
    void onPrintEnd(QPainter *p, HPrintInfo *pInfo);
    void printHeader(QPainter *p, HPrintInfo *pInfo);
    void printFooter(QPainter *p, HPrintInfo *pInfo);
    void PrintColumnHeadings(QPainter *p, HPrintInfo *pInfo);

    void printPage(QPainter* p);
public slots:
    void printPriview();//外部调用
    void printPriview(QPrinter*); //内部调用 打印预览
    void printPages(QPrinter*); //直接打印

public:
    HGridReportWidget *m_pGridReportWidget;
    HGridCtrl* m_pCurGridCtrl;
    HPrintInfo m_PrintInfo;

    QFont       m_PrinterFont;  // for the printer
    int         m_nHeaderHeight, m_nFooterHeight, m_nLeftMargin,m_nRightMargin, m_nTopMargin, m_nBottomMargin, m_nGap;
    QSize       m_CharSize;
    int         m_nPageHeight;
    QSize       m_LogicalPageSize,      // Page size in gridctrl units.
               m_PaperSize;            // Page size in device units.
    // additional properties to support Wysiwyg printing
    int         m_nPageWidth;
    int         m_nPrintColumn;
    int         m_nCurrPrintRow;
    int         m_nNumPages;
    int         m_nPageMultiplier;

};

#endif // HREPORTPRINT_H
