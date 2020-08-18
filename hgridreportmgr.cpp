#include "hgridreportmgr.h"
#include "hgridctrlhelper.h"
#include "hreportprint.h"
#include "hformatset.h"

HReportManager::HReportManager(QObject *parent) : QObject(parent)
{
    //loadSysConfig();//加载配置文件
    m_pGridCtrlFile = new HGridCtrlFile;
    Q_ASSERT(m_pGridCtrlFile);
    m_pFormatSet = new HFormatSet;
    loadGridCtrlFile();
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
    return m_pGridCtrlFile->loadGridCtrlInfoFile();
}

bool HReportManager::saveGridCtrlFile()
{
    if(!m_pGridCtrlFile)
        return false;
    m_pGridCtrlFile->saveGridCtrlFile();
    if(!m_pReportMainWidget)
        return false;
    m_pReportMainWidget->saveReportWidget();
    return true;
}
