#include "hgridctrlhelper.h"
#include "hgridcelldef.h"
#include "hfileapi.h"
#include <QFileInfoList>
#include <QDir>
HRelateVar::HRelateVar()
{
    m_pRelateVar.nRow = -1;
    m_pRelateVar.nCol = -1;
    m_pRelateVar.btType = (quint8)-1;
    m_pRelateVar.btSubType = 0;
    m_pRelateVar.wNo = (quint8)-1;
    m_pRelateVar.szDesc = "";
}

HRelateVar::HRelateVar( long nRow, long nCol, quint8 btType, quint8 btNum, quint16 wNo, QString szDesc )
{
    m_pRelateVar.nRow = nRow;
    m_pRelateVar.nCol = nCol;
    m_pRelateVar.btType = btType;
    m_pRelateVar.btSubType = btNum;
    m_pRelateVar.wNo = wNo;
    m_pRelateVar.szDesc = szDesc;
}

HRelateVar::HRelateVar( HRelateVar* pRelateVar )
{
    if(!pRelateVar) return;
    setRelateVar(&pRelateVar->m_pRelateVar);
}

HRelateVar::~HRelateVar()
{

}

/*
bool QRelateVar::ReadFromDB( int nFile, WORD wOrder )
{

}

bool QRelateVar::WriteToDB( int nFile, WORD wOrder )
{

}*/
bool HRelateVar::loadRelateVar(int v,QDataStream* ds)
{
    return true;
}

bool HRelateVar::saveRelateVar(int v,QDataStream* ds)
{
    return false;
}

void HRelateVar::getRelateVar( RELATEVAR* pRelateVar )
{
    if(!pRelateVar) return;
    memcpy(pRelateVar,&m_pRelateVar,sizeof(RELATEVAR));
}

void HRelateVar::setRelateVar( RELATEVAR* pRelateVar )
{
    if(!pRelateVar) return;
    memcpy(&m_pRelateVar,pRelateVar,sizeof(RELATEVAR));
}

void HRelateVar::copy( RELATEVAR *pCopyInfo )
{
    getRelateVar(pCopyInfo);
}

void HRelateVar::copyFrom( RELATEVAR *pClipInfo )
{
    setRelateVar(pClipInfo);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
HGridCtrlInfo::HGridCtrlInfo()
{

}

HGridCtrlInfo::~HGridCtrlInfo()
{

}

HGridCtrlInfo& HGridCtrlInfo::operator =(const HGridCtrlInfo& info)
{
    if(this == &info) return *this;
    m_GridCtrlItem.wReportID = info.m_GridCtrlItem.wReportID;
    m_GridCtrlItem.nMaxCol = info.m_GridCtrlItem.nMaxCol;
    m_GridCtrlItem.nMaxRow = info.m_GridCtrlItem.nMaxRow;
    m_GridCtrlItem.btType = info.m_GridCtrlItem.btType;
    m_GridCtrlItem.strReportName = info.m_GridCtrlItem.strReportName;
    return *this;
}

/*
void HGridCtrlInfo::newGridCellData(int nMaxRow, int nMaxCol)
{
    for(int row = 0; row < nMaxRow;row++)
    {
        for(int col = 0; col < nMaxCol; col++)
        {
            HGridCellInfo* pCellInfo = new HGridCellInfo;
            pCellInfo->m_GridCellItem.row = row;
            pCellInfo->m_GridCellItem.col = col;
            m_pGridCellItemList.append(pCellInfo);
        }
    }
}

void HGridCtrlInfo::loadGridCtrlData(int v,QDataStream* ds)
{
    if(!ds) return;
    quint8 n8;
    *ds>>n8;
    m_GridCtrlItem.btType = n8;
    quint32 l;
    *ds>>l;
    m_GridCtrlItem.nMaxCol = l;
    *ds>>l;
    m_GridCtrlItem.nMaxRow = l;
    quint32 n32;
    *ds>>n32;
    m_GridCtrlItem.wReportID = n32;
    QString s;
    *ds>>s;
    m_GridCtrlItem.strReportName = s;
    int n;
    *ds>>n;
    for(int i = 0; i < n;i++)
    {
        HGridCellInfo* pInfo = new HGridCellInfo;
        pInfo->loadGridCellData(v,ds);
        m_pGridCellItemList.append(pInfo);
    }
}

void HGridCtrlInfo::saveGridCtrlData(int v,QDataStream* ds)
{
    if(!ds) return;
    *ds<<v;
    *ds<<(quint8)m_GridCtrlItem.btType;
    *ds<<(quint32)m_GridCtrlItem.nMaxCol;
    *ds<<(quint32)m_GridCtrlItem.nMaxRow;
    *ds<<(quint32)m_GridCtrlItem.wReportID;
    *ds<<(QString)m_GridCtrlItem.strReportName;
    *ds<<(int)m_pGridCellItemList.count();
    for(int i = 0; i < m_pGridCellItemList.count();i++)
    {
        HGridCellInfo* pInfo = (HGridCellInfo*)m_pGridCellItemList[i];
        pInfo->saveGridCellData(v,ds);
    }
}*/

bool HGridCtrlInfo::loadGridCtrlInfo(int index)
{
    if((int)-1 == loadDBRecord(FILE_TYPE_REPORT,index,&m_GridCtrlItem))
        return false;
    return true;
}

bool HGridCtrlInfo::saveGridCtrlInfo(int index)
{
    if((int)-1 == saveDBRecord(FILE_TYPE_REPORT,index,&m_GridCtrlItem))
        return false;
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
HGridCellInfo::HGridCellInfo()
{
    m_GridCellItem.strText  = "";
    m_GridCellItem.nImage   = -1;
    m_GridCellItem.nFormat = QDT_LEFT|QDT_VCENTER|QDT_SINGLELINE|QDT_NOPREFIX;
    m_GridCellItem.crBkClr = QColor(Qt::white);
    m_GridCellItem.crFgClr = QColor(Qt::black);
    m_GridCellItem.nMargin = (uint)-1;
    m_GridCellItem.lfFont = QFont(QStringLiteral("宋体"),11, QFont::Normal);
    m_GridCellItem.lParam  = quint32(0);
    m_GridCellItem.bLeftBorder   = false;
    m_GridCellItem.bTopBorder    = false;
    m_GridCellItem.bRightBorder  = false;
    m_GridCellItem.bBottomBorder = false;
    m_GridCellItem.nLeftBorderStyle   = Qt::SolidLine;
    m_GridCellItem.nTopBorderStyle    = Qt::SolidLine;
    m_GridCellItem.nRightBorderStyle  = Qt::SolidLine;
    m_GridCellItem.nBottomBorderStyle = Qt::SolidLine;
    m_GridCellItem.crLeftBoderClr   = QColor(Qt::black);
    m_GridCellItem.crTopBoderClr    = QColor(Qt::black);
    m_GridCellItem.crRightBoderClr  = QColor(Qt::black);
    m_GridCellItem.crBottomBoderClr = QColor(Qt::black);
    m_GridCellItem.nState  = 0;
    m_GridCellItem.bShow = true;
    m_GridCellItem.MergeCellID.row = -1;
    m_GridCellItem.MergeCellID.col = -1;
    m_GridCellItem.MergeRange.set();
}

HGridCellInfo::~HGridCellInfo()
{

}

//gvItem初始化必须要赋值
void HGridCellInfo::loadGridCellData(int v,QDataStream* ds)
{
    if(!ds) return;
    int n;
    *ds>>n; //version
    //version = n;
    *ds>>n;
    m_GridCellItem.row = n;
    *ds>>n;
    m_GridCellItem.col = n;
    uint un;
    *ds>>un;
    m_GridCellItem.mask = n;
    *ds>>un;
    m_GridCellItem.nState = n;
    quint32 n32;
    *ds>>n32;
    m_GridCellItem.nFormat = n32;
    *ds>>n;
    m_GridCellItem.nImage = n;
    QColor clr;
    *ds>>clr;
    m_GridCellItem.crBkClr = clr;
    *ds>>clr;
    m_GridCellItem.crFgClr = clr;
    quint32 l;
    *ds>>l;
    m_GridCellItem.lParam = l;
    QFont ft;
    *ds>>ft;
    m_GridCellItem.lfFont = ft;
    *ds>>un;
    m_GridCellItem.nMargin = un;
    QString s;
    *ds>>s;
    m_GridCellItem.strText = s;

    bool b;
    *ds>>b;
    m_GridCellItem.bLeftBorder = b;
    *ds>>b;
    m_GridCellItem.bTopBorder = b;
    *ds>>b;
    m_GridCellItem.bRightBorder = b;
    *ds>>b;
    m_GridCellItem.bBottomBorder = b;

    short sn;
    *ds>>sn;
    m_GridCellItem.nLeftBorderStyle = sn;
    *ds>>sn;
    m_GridCellItem.nTopBorderStyle = sn;
    *ds>>sn;
    m_GridCellItem.nRightBorderStyle = sn;
    *ds>>sn;
    m_GridCellItem.nBottomBorderStyle = sn;

    *ds>>clr;
    m_GridCellItem.crLeftBoderClr = clr;
    *ds>>clr;
    m_GridCellItem.crTopBoderClr = clr;
    *ds>>clr;
    m_GridCellItem.crRightBoderClr = clr;
    *ds>>clr;
    m_GridCellItem.crBottomBoderClr = clr;

    *ds>>n;
    m_GridCellItem.MergeCellID.row = n;
    *ds>>n;
    m_GridCellItem.MergeCellID.col = n;
    *ds>>b;
    m_GridCellItem.bShow = b;

    m_GridCellItem.MergeRange.set();
    *ds>>m_GridCellItem.MergeRange;
}

void HGridCellInfo::saveGridCellData(int v,QDataStream* ds)
{
    if(!ds) return;
    *ds<<v;
    *ds<<(int)m_GridCellItem.row;
    *ds<<(int)m_GridCellItem.col;
    *ds<<(uint)m_GridCellItem.mask;
    *ds<<(uint)m_GridCellItem.nState;
    *ds<<(quint32)m_GridCellItem.nFormat;
    *ds<<(int)m_GridCellItem.nImage;
    *ds<<(QColor)m_GridCellItem.crBkClr;
    *ds<<(QColor)m_GridCellItem.crFgClr;
    *ds<<(quint32)m_GridCellItem.lParam;
    *ds<<(QFont)m_GridCellItem.lfFont;
    *ds<<(uint)m_GridCellItem.nMargin;
    *ds<<(QString)m_GridCellItem.strText;
    *ds<<(bool)m_GridCellItem.bLeftBorder;
    *ds<<(bool)m_GridCellItem.bTopBorder;
    *ds<<(bool)m_GridCellItem.bRightBorder;
    *ds<<(bool)m_GridCellItem.bBottomBorder;

    *ds<<(short)m_GridCellItem.nLeftBorderStyle;
    *ds<<(short)m_GridCellItem.nTopBorderStyle;
    *ds<<(short)m_GridCellItem.nRightBorderStyle;
    *ds<<(short)m_GridCellItem.nBottomBorderStyle;

    *ds<<(QColor)m_GridCellItem.crLeftBoderClr;
    *ds<<(QColor)m_GridCellItem.crTopBoderClr;
    *ds<<(QColor)m_GridCellItem.crRightBoderClr;
    *ds<<(QColor)m_GridCellItem.crBottomBoderClr;
    *ds<<(int)m_GridCellItem.MergeCellID.row;
    *ds<<(int)m_GridCellItem.MergeCellID.col;
    *ds<<(bool)m_GridCellItem.bShow;
    *ds<<(HCellRange)m_GridCellItem.MergeRange;
}
*/

//表格文件，不是报表文件

HGridCtrlFile::HGridCtrlFile()
{
    m_pCurGridCtrlInfo = NULL;
}

HGridCtrlFile::~HGridCtrlFile()
{

}

/*

//从文件路径加载报表文件
bool HGridCtrlFile::loadGridCtrlFile()
{
    QString strReportPath;
    QDir dirReportsFilePath(strReportPath);
    if(!dirReportsFilePath.exists())
        return false;
    QStringList filters;
    filters<<"*.rpt";
    dirReportsFilePath.setNameFilters(filters);
    QFileInfoList iconsFileInfoList = dirReportsFilePath.entryInfoList(QDir::Files);
    foreach(QFileInfo info,iconsFileInfoList)
    {
        QString strReportFile = strReportPath + "/" + info.fileName();
        QFile file(strReportFile);
        if(!file.open(QIODevice::ReadOnly))
            continue;
        QDataStream in(&file);
        int v;
        HGridCtrlInfo *pGridCtrlInfo = new HGridCtrlInfo;
        pGridCtrlInfo->loadGridCtrlData(v,&in);
        m_pGridCtrlInfoList.append(pGridCtrlInfo);
    }

    return true;
}

//存储报表文件
bool HGridCtrlFile::saveGridCtrlFile()
{
    QString strReportPath;
    QDir dirReportsFilePath(strReportPath);
    if(!dirReportsFilePath.exists())
        return false;
    for(int i = 0; i < m_pGridCtrlInfoList.count();i++)
    {
        HGridCtrlInfo* pInfo = m_pGridCtrlInfoList[i];
        if(!pInfo) continue;
        int ID = (int)pInfo->m_GridCtrlItem.wReportID;
        QString strID = QString("%1").arg(ID,10,10,QChar('0'));
        QString strReportFile = strReportPath + "/" + strID;
        QFile file(strReportFile);
        if(!file.open(QIODevice::WriteOnly))
            continue;
        QDataStream out(&file);
        int v;
        pInfo->saveGridCtrlData(v,&out);
    }
    return true;
}

bool HGridCtrlFile::saveGridCtrlFile()
{
    QString strReportPath;
    QDir dirReportsFilePath(strReportPath);
    if(!dirReportsFilePath.exists())
        return false;
    for(int i = 0; i < m_pGridCtrlInfoList.count();i++)
    {
        HGridCtrlInfo* pInfo = m_pGridCtrlInfoList[i];
        if(!pInfo) continue;
        int ID = (int)pInfo->m_GridCtrlItem.wReportID;
        QString strID = QString("%1").arg(ID,10,10,QChar('0'));
        QString strReportFile = strReportPath + "/" + strID;
        QFile file(strReportFile);
        if(!file.open(QIODevice::WriteOnly))
            continue;
        QDataStream out(&file);
        int v;
        pInfo->saveGridCtrlData(v,&out);
    }
    return true;
}
*/

bool HGridCtrlFile::loadGridCtrlInfoFile()
{
    int	fd = openDB( FILE_TYPE_REPORT);
    if( -1 == fd ) return false;
    DATAFILEHEADER  Header;
    loadDataFileHeader( fd, &Header );

    //ClearList();

    for( quint16 i = 0; i < Header.wTotal; i++ )
    {
        HGridCtrlInfo* pInfo = new HGridCtrlInfo();
        if( !pInfo )
        {
            return false;
        }
        if( !pInfo->loadGridCtrlInfo(i+1) )
        {
            delete pInfo;
            continue;
        }
        quint16 wID;
        wID = pInfo->m_GridCtrlItem.wReportID;
        if( findGridCtrlInfo(wID))
        {
            delete pInfo;
            continue;
        }
        m_pGridCtrlInfoList.append(pInfo);
    }

    return true;
}

bool HGridCtrlFile::saveGridCtrlInfoFile()
{
    int fd = createDB(FILE_TYPE_REPORT);
    if((int)-1 == fd) return false;

    DATAFILEHEADER Header;
    if( -1 == fd )
    {
        return false;
    }
    else
    {
        loadDataFileHeader( fd, &Header );
        if( (quint16)0xFFFF == Header.wTotal )
        {
            //AfxMessageBox( ID_ERR_TOOMANYREPORT, MB_OK|MB_ICONSTOP );
            closeDB( FILE_TYPE_REPORT );
            return NULL;
        }
        Header.wTotal = m_pGridCtrlInfoList.count();
        saveDataFileHeader( fd, &Header );
    }

    for(int i = 0; i < m_pGridCtrlInfoList.count();i++)
    {
        HGridCtrlInfo* pInfo = m_pGridCtrlInfoList[i];
        if(!pInfo) continue;
        if(!pInfo->saveGridCtrlInfo(i))
            return false;
    }
    closeDB(FILE_TYPE_REPORT);
    return true;
}


bool HGridCtrlFile::loadRelateVarFile(int nReportID)
{
    HGridCtrlInfo* pInfo = getGridCtrlInfoById(nReportID);
    if(!pInfo) return false;
    clearRelateVarList();
    int ID = (int)pInfo->m_GridCtrlItem.wReportID;
    char szFile[256],szPath[256];
    getDataFilePath(DFPATH_REPORT,szPath);
    sprintf(szFile,"%s%s%6u%s",szPath,"VAR",ID,".var");
    QFile file(szFile);
    if(!file.open(QIODevice::ReadOnly))
        return false;
    QDataStream in(&file);
    int v;
    for(int i = 0; i < m_pRelateVarList.count();i++)
    {
        HRelateVar* pVar = m_pRelateVarList[i];
        if(!pVar) continue;
        if(!pVar->loadRelateVar(v,&in))
            return false;
    }
    return true;
}

bool HGridCtrlFile::saveRelateVarFile(int nReportID)
{
    HGridCtrlInfo* pInfo = getGridCtrlInfoById(nReportID);
    if(!pInfo) return false;
    int ID = (int)pInfo->m_GridCtrlItem.wReportID;
    char szFile[256],szPath[256];
    getDataFilePath(DFPATH_REPORT,szPath);
    sprintf(szFile,"%s%s%6u%s",szPath,"VAR",ID,".var");
    QFile file(szFile);
    if(!file.open(QIODevice::WriteOnly))
        return false;
    QDataStream out(&file);
    int v;
    for(int i = 0; i < m_pRelateVarList.count();i++)
    {
        HRelateVar* pVar = m_pRelateVarList[i];
        if(!pVar) continue;
        if(!pVar->saveRelateVar(v,&out))
            return false;
    }
    return true;
}





HGridCtrlInfo* HGridCtrlFile::addGridCtrlInfo(GRIDPREPORT* pItem)
{
    if(NULL == pItem)
        return NULL;
    quint16 reportID = 0;
    while(findGridCtrlInfo(reportID))
        reportID++;
    HGridCtrlInfo* pInfo = new HGridCtrlInfo;
    pInfo->m_GridCtrlItem.wReportID = reportID;
    pInfo->m_GridCtrlItem.nMaxCol = pItem->nMaxCol;
    pInfo->m_GridCtrlItem.nMaxRow = pItem->nMaxRow;
    pInfo->m_GridCtrlItem.btType = pItem->btType;
    pInfo->m_GridCtrlItem.strReportName = pItem->strReportName;
    m_pGridCtrlInfoList.append(pInfo);
    m_pCurGridCtrlInfo = pInfo;
    return pInfo;
}

bool HGridCtrlFile::delGridCtrlInfo(int id)
{
    bool bok = findGridCtrlInfo(id);
    if(!bok) return false;
    HGridCtrlInfo* pInfo = getGridCtrlInfoById(id);
    if(pInfo)
    {
        m_pGridCtrlInfoList.removeOne(pInfo);
        delete pInfo;
        pInfo = NULL;
    }
    m_pCurGridCtrlInfo = NULL;
    return true;
}

bool HGridCtrlFile::findGridCtrlInfo(int id)
{
    if(id > m_pGridCtrlInfoList.count())
        return false;
    for(int i = 0;i < m_pGridCtrlInfoList.count();i++)
    {
        HGridCtrlInfo* pInfo = m_pGridCtrlInfoList[i];
        if(pInfo && pInfo->m_GridCtrlItem.wReportID == id)
            return true;
    }
    return false;
}


bool HGridCtrlFile::renameGridCtrlInfo(int id,const QString& name)
{
    bool bok = findGridCtrlInfo(id);
    if(!bok) return false;
    HGridCtrlInfo* pInfo = getGridCtrlInfoById(id);
    if(pInfo)
    {
        pInfo->m_GridCtrlItem.strReportName = name;
    }
    return true;
}

//通过模板ID来获取对应的表格控件信息
HGridCtrlInfo*  HGridCtrlFile::getGridCtrlInfoById(int id)
{
    if(id > m_pGridCtrlInfoList.count())
        return false;
    HGridCtrlInfo* pInfo = NULL;
    for(int i = 0;i < m_pGridCtrlInfoList.count();i++)
    {
        pInfo = m_pGridCtrlInfoList[i];
        if(pInfo && pInfo->m_GridCtrlItem.wReportID == id)
            break;
    }
    return pInfo;
}

void HGridCtrlFile::setGridCtrlInfoById(int id)
{
    bool bok = findGridCtrlInfo(id);
    if(!bok) return;
    m_pCurGridCtrlInfo = getGridCtrlInfoById(id);
}

void HGridCtrlFile::clearRelateVarList()
{
    while(!m_pRelateVarList.isEmpty())
        delete (HRelateVar*)m_pRelateVarList.takeFirst();
    m_pRelateVarList.clear();
}

HRelateVar* HGridCtrlFile::findRelateVar( long nRow,long nCol )
{
    if(nRow < 0 || nCol < 0) return NULL;
    for(int i = 0; i < m_pRelateVarList.count();i++)
    {
        HRelateVar* pVar = (HRelateVar*)m_pRelateVarList.at(i);
        if(!pVar) continue;
        if(pVar->row() == nRow && pVar->col() == nCol)
        {
            return pVar;
        }
    }
    return NULL;
}

int HGridCtrlFile::indexOfRelateVar( long nRow, long nCol )
{
    if(nRow < 0 || nCol < 0) return -1;
    int index = (int)-1;
    for(int i = 0; i < m_pRelateVarList.count();i++)
    {
        HRelateVar* pVar = (HRelateVar*)m_pRelateVarList.at(i);
        if(!pVar) continue;
        if(pVar->row() == nRow && pVar->col() == nCol)
        {    index = i; break;}
    }
    return index;
}

bool HGridCtrlFile::hasRelateVar( long row1, long col1, long row2, long col2 )
{
    if(row1 < 0 || col1 < 0 || row2 < 0 || col2 < 0 || row1 > row2 || col1 > col2)
        return false;
    int index = (int)-1;
    for( int i = row1; i <= row2; i++ )
    {
        for( int j = col1; j <= col2; j++ )
        {
           index = indexOfRelateVar( i, j );
           if( index >= 0)
               return true;
        }
    }
    return false;
}

void HGridCtrlFile::deleteRelateVar( long row1, long col1, long row2, long col2 )
{
    if(row1 < 0 || col1 < 0 || row2 < 0 || col2 < 0 || row1 > row2 || col1 > col2)
        return;
    for( int i = row1; i <= row2; i++ )
    {
        for( int j = col1; j <= col2; j++ )
        {
           HRelateVar* pVar = findRelateVar( i, j );
           if(!pVar) continue;
           m_pRelateVarList.removeOne(pVar);
           delete pVar;
           pVar = NULL;
        }
    }
}

bool HGridCtrlFile::isTime( long nRow, long nCol )
{
    return false;
}
