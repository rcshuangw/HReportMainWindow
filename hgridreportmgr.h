#ifndef HGRIDREPORTMGR_H
#define HGRIDREPORTMGR_H

#include <QObject>
class HGridCtrlFile;
//class HReportMainWidget;
class HReportManager : public QObject
{
    Q_OBJECT
public:
    explicit HReportManager(QObject *parent = 0);

public:
    HGridCtrlFile* gridCtrlFile() ;
    //HReportMainWidget *reportMainWidget() ;
public:
    bool loadGridCtrlFile();
    bool saveGridCtrlFile();
signals:

public slots:

private:
    HGridCtrlFile* m_pGridCtrlFile;
    //HReportMainWidget* m_pReportMainWidget;
};

#endif // HGRIDREPORTMGR_H
