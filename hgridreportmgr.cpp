#include "hgridreportmgr.h"
#include "hgridctrlhelper.h"
#include "hreportprint.h"
#include "hformatset.h"
HReportManager::HReportManager(QObject *parent) : QObject(parent)
{
    m_pGridCtrlFile = new HGridCtrlFile;
    Q_ASSERT(m_pGridCtrlFile);
    m_pFormatSet = new HFormatSet;
    //m_pReportMainWidget = new H
}

HGridCtrlFile* HReportManager::gridCtrlFile()
{
    return m_pGridCtrlFile;
}

HFormatSet* HReportManager::formatSet()
{
    return m_pFormatSet;
}

bool HReportManager::loadGridCtrlFile()
{
    if(!m_pGridCtrlFile)
        return false;
    //return m_pGridCtrlFile->loadGridCtrlFile();
}

bool HReportManager::saveGridCtrlFile()
{
    if(!m_pGridCtrlFile)
        return false;
    //return m_pGridCtrlFile->saveGridCtrlFile();
}
