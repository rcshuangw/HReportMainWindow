#include "hgridreportmgr.h"
#include "hgridctrlhelper.h"
HReportManager::HReportManager(QObject *parent) : QObject(parent)
{
    m_pGridCtrlFile = new HGridCtrlFile;
    Q_ASSERT(m_pGridCtrlFile);
    //m_pReportMainWidget = new H
}

HGridCtrlFile* HReportManager::gridCtrlFile() const
{
    return m_pGridCtrlFile;
}

bool HReportManager::loadGridCtrlFile()
{
    if(!m_pGridCtrlFile)
        return false;
    return m_pGridCtrlFile->loadGridCtrlFile();
}

bool HReportManager::saveGridCtrlFile()
{
    if(!m_pGridCtrlFile)
        return false;
    return m_pGridCtrlFile->saveGridCtrlFile();
}
