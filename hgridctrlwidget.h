#ifndef HREPORTWIDGET_H
#define HREPORTWIDGET_H

#include <QWidget>
#include "hgridglobal.h"
class HGridCtrl;
class QLabel;
class QLineEdit;
class HGridCtrlInfo;
class HGridCell;
class HReportManager;
//tab页的具体内容
class  HGridCtrlWidget : public QWidget
{
    Q_OBJECT
public:
    HGridCtrlWidget(HReportManager* mgr,QWidget* parent = 0);
    ~HGridCtrlWidget();

    void initReportWidget(quint8 type);
    void setGridCtrlItem(HGridCtrlInfo* pItem);
    void getGridCtrlItem(HGridCtrlInfo* pItem);

signals:
    void gridcellclickded(HGridCell*);
public slots:
    void gridCell_clicked(HGridCell*);
private:
    HReportManager* m_pReportManager;
    HGridCtrl* m_pGridCtrl;
    long m_nNumSheets;
    QLabel* m_rowColLabel;
    QLineEdit* m_inputLineEdit;
    quint8 m_uGridReportType;
    HGridCtrlInfo* m_pGridCtrlInfo;
};

#endif // HREPORTWIDGET_H
