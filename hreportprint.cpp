#include "hreportprint.h"
#include <QPrinter>
#include <QPainter>
#include <QPrintPreviewDialog>
HReportPrint::HReportPrint()
{

}

void HReportPrint::onPrintBegin(QPainter *p, CPrintInfo *pInfo)
{

}

void HReportPrint::onPrint(QPainter *p, CPrintInfo *pInfo)
{

}

void HReportPrint::onPrintEnd(QPainter *p, CPrintInfo *pInfo)
{

}

void HReportPrint::printHeader(QPainter *p, CPrintInfo *pInfo)
{

}

void HReportPrint::printFooter(QPainter *p, CPrintInfo *pInfo)
{

}

void HReportPrint::printPage(QPainter* p,HGridCtrl* pGridCtrl,int pageNumber)
{

}

void HReportPrint::printPriview()
{
    QPrinter printer;
    QPrintPreviewDialog dlg(&printer,NULL);
    connect(&dlg, SIGNAL(paintRequested(QPrinter*)),this,SLOT(printPreview(QPrinter*)));
    dlg.exec();
}

void HReportPrint::printPriview(QPrinter* p)
{

}
