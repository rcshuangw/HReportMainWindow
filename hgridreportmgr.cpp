#include "hgridreportmgr.h"
#include "hgridctrlhelper.h"
HGridReportMgr::HGridReportMgr(QObject *parent) : QObject(parent)
{
    m_pGridCtrlFile = new HGridCtrlFile;
    Q_ASSERT(m_pGridCtrlFile);
    //m_pReportMainWidget = new H
}

HGridCtrlFile* HGridReportMgr::gridCtrlFile() const
{
    return m_pGridCtrlFile;
}

bool HGridReportMgr::loadGridCtrlFile()
{
    if(!m_pGridCtrlFile)
        return false;
    return m_pGridCtrlFile->loadGridCtrlFile();
}

bool HGridReportMgr::saveGridCtrlFile()
{
    if(!m_pGridCtrlFile)
        return false;
    return m_pGridCtrlFile->saveGridCtrlFile();
}
