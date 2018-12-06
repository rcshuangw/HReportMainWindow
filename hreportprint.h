#ifndef HREPORTPRINT_H
#define HREPORTPRINT_H
//打印类
#include <QObject>
class QPrinter;
class QPainter;
class HGridCtrl;

struct CPrintInfo // Printing information structure
{
    CPrintInfo();
    ~CPrintInfo();
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
    CRect m_rectDraw;        // rectangle defining current usable page area
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
};

class HReportPrint : QObject
{
    Q_OBJECT
public:
    HReportPrint();

public:
    void onPrintBegin(QPainter *p, CPrintInfo *pInfo);
    void onPrint(QPainter *p, CPrintInfo *pInfo);
    void onPrintEnd(QPainter *p, CPrintInfo *pInfo);
    void printHeader(QPainter *p, CPrintInfo *pInfo);
    void printFooter(QPainter *p, CPrintInfo *pInfo);

    void printPage(QPainter* p,HGridCtrl* pGridCtrl,int pageNumber);
public slots:
    void printPriview();//外部调用
    void printPriview(QPrinter*); //内部调用

};

#endif // HREPORTPRINT_H
