#ifndef HGRIDCTRLINFO_H
#define HGRIDCTRLINFO_H
//定义表格
#include <QObject>
#include "hgridglobal.h"
#include "hgridcelldef.h"
#include "hfileapi.h"
class HGridReportWidget;
//操作票\工作票模板前景点定义
typedef struct _tagRelateVar
{
    int nRow;
    int nCol;
    quint8 btType;
    quint8 btSubType; //操作票：同类型前景点的个数；工作票:前景点子类型
    quint16 wNo;
    QString szDesc;
} RELATEVAR;

class HGridCellInfo;
//变量
class HRelateVar : public QObject
{
public:
    HRelateVar();
    HRelateVar( long nRow, long nCol, quint8 btType, quint8 btNum, quint16 wNo, QString szFrontDesc );
    HRelateVar( HRelateVar* pFrontDef );
    virtual ~HRelateVar();

protected:
    RELATEVAR m_pRelateVar;

public:
    bool loadRelateVar(int v,QDataStream* ds);
    bool saveRelateVar(int v,QDataStream* ds);

    void getRelateVar( RELATEVAR* pFrontDef );
    void setRelateVar( RELATEVAR* pFrontDef );

    virtual void copy( RELATEVAR *pClipInfo );
    virtual void copyFrom( RELATEVAR *pClipInfo );

    void setRowCol( long nRow,  long nCol ) { m_pRelateVar.nRow = nRow; m_pRelateVar.nCol = nCol; }
    void rowCol( long &nRow, long &nCol ){ nRow = m_pRelateVar.nRow; nCol = m_pRelateVar.nCol; }

    quint8 type() { return m_pRelateVar.btType; }
    void setType( quint8 btType ) { m_pRelateVar.btType = btType; }

    quint8 num() { return m_pRelateVar.btSubType; }
    void setNum( quint8 btNum ) { m_pRelateVar.btSubType = btNum; }

    long row() { return m_pRelateVar.nRow; }
    void setRow( int nRow ) { m_pRelateVar.nRow = nRow; }

    long col() { return m_pRelateVar.nCol; }
    void setCol( int nCol ) { m_pRelateVar.nCol = nCol; }

    quint16 no() { return m_pRelateVar.wNo; }
    void setNo( quint16 wNo ) { m_pRelateVar.wNo = wNo; }

    virtual QString desc() { return QString( m_pRelateVar.szDesc ); }
    void setDesc( QString szDesc)
    {
        m_pRelateVar.szDesc = szDesc;
    }
};

//表格信息
class  HGridCtrlInfo
{
public:
    HGridCtrlInfo();
    ~HGridCtrlInfo();
public:
    bool loadGridCtrlInfo(int index);
    bool saveGridCtrlInfo(int index);

    HGridCtrlInfo& operator =(const HGridCtrlInfo&);
    void saveGCItemInfo(GRIDPREPORT* item);
    void seGridReportType(quint8 type) {m_GridCtrlItem.btType = type;}
    quint16 reportType(){return m_GridCtrlItem.btType;}
    void seGridReportID(quint16 id) {m_GridCtrlItem.wReportID = id;}
    quint16 reportID(){return m_GridCtrlItem.wReportID;}
    void setGridReportRow(quint32 row){m_GridCtrlItem.nMaxRow = row;}
    quint32 gridReportRow(){return m_GridCtrlItem.nMaxRow;}
    void setGridReportCol(quint32 col){m_GridCtrlItem.nMaxCol = col;}
    quint32 gridReportCol(){return m_GridCtrlItem.nMaxCol;}
    void setGridReportName(const char* s){ qstrcpy(m_GridCtrlItem.szReportName,s); }
    QString gridReportName(){return QString(m_GridCtrlItem.szReportName);}
protected:
    GRIDPREPORT m_GridCtrlItem;
};


//表格文件，不是报表文件
class HGridCtrlFile
{
public:
    HGridCtrlFile();
    ~HGridCtrlFile();

public:
    bool loadGridCtrlFile();
    bool saveGridCtrlFile();


    //保存操作
    //存储表格报表文件(包含表格文件+关联变量文件)
    bool loadRelateVarFile(int nReportID);
    bool saveRelateVarFile(int nReportID);

    //存储表格基本信息文件
    bool loadGridCtrlInfoFile();
    bool saveGridCtrlInfoFile();

    //表格属性操作
    void clearGridCtrlInfoFile();
    HGridCtrlInfo* addGridCtrlInfo(GRIDPREPORT*);
    bool delGridCtrlInfo(int id);
    bool findGridCtrlInfo(int id);
    bool renameGridCtrlInfo(int id,const QString&);
    HGridCtrlInfo*  getGridCtrlInfoById(int id);//通过模板ID来获取对应的表格控件信息
    void setGridCtrlInfoById(int id);
    HGridCtrlInfo*  getCurGridCtrlInfo(){return m_pCurGridCtrlInfo;}

    //关联变量操作(必须放到此处因为浏览框和编辑框都需要)
    void clearRelateVarList();
    HRelateVar *findRelateVar( long nRow,long nCol );
    int indexOfRelateVar( long nRow, long nCol );
    bool hasRelateVar( long row1, long col1, long row2, long col2 );
    void deleteRelateVar( long row1, long co1, long row2, long col2 );
    bool isTime( long nRow, long nCol );

    //表格控件操作：只针对编辑框
    void setGridReportWidget(HGridReportWidget* widget);
    HGridReportWidget* gridReportWidget();

public:
    QList<HRelateVar*>  m_pRelateVarList;//变量列表，注意变量列表始终只显示当前的表格变量
    QList<HGridCtrlInfo*> m_pGridCtrlInfoList;

private:
    HGridCtrlInfo* m_pCurGridCtrlInfo;
    HGridReportWidget* m_pGridReport;

};



#endif // HGRIDCTRLINFO_H
