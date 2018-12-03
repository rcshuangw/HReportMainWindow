#ifndef HREPORTBROWSERWIDGET_H
#define HREPORTBROWSERWIDGET_H
#include <QWidget>
#include "hgridctrl.h"
//表格预览窗口
class HReportBrowserWidget : public QWidget
{
public:
    HReportBrowserWidget(QWidget* parent = 0);


protected:
    HGridCtrl* m_pGridCtrl;
};

#endif // HREPORTBROWSERWIDGET_H
