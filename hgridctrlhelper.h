#ifndef HGRIDCTRLINFO_H
#define HGRIDCTRLINFO_H
//定义表格
#include <QObject>
#include "hgridglobal.h"
#include "hgridcelldef.h"
class HGridCellInfo;
//表格控件信息
class  HGridCtrlInfo
{
public:
    HGridCtrlInfo();
    ~HGridCtrlInfo();
public:
    void loadGridCtrlData(int v,QDataStream* ds);
    void saveGridCtrlData(int v,QDataStream* ds);

    HGridCtrlInfo& operator =(const HGridCtrlInfo&);
public:
    GC_ITEM m_GridCtrlItem;
    QList<HGridCellInfo*> m_pGridCellItemList;
};

//表格信息
class  HGridCellInfo
{
public:
    HGridCellInfo();
    ~HGridCellInfo();
public:
    //gvItem初始化必须要赋值
    void loadGridCellData(int v,QDataStream* ds);
    void saveGridCellData(int v,QDataStream* ds);
public:
    GV_ITEM m_GridCellItem;
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
    HGridCtrlInfo* addGridCtrlInfo(GC_ITEM*);
    bool delGridCtrlInfo(int id);
    bool findGridCtrlInfo(int id);
    HGridCtrlInfo*  getGridCtrlInfoById(int id);//通过模板ID来获取对应的表格控件信息
    void setGridCtrlInfoById(int id, HGridCtrlInfo *);
    HGridCtrlInfo*  getCurGridCtrlInfo(){return m_pCurGridCtrlInfo;}

public:
    QList<HGridCtrlInfo*> m_pGridCtrlInfoList;

private:
    HGridCtrlInfo* m_pCurGridCtrlInfo;

};



#endif // HGRIDCTRLINFO_H
