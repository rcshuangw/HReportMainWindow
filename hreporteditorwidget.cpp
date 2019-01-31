#include "hreporteditorwidget.h"
#include "hgridreportwidget.h"
#include "hgridreportmgr.h"
#include "hgridctrlhelper.h"
#include "hgridctrlhelper.h"
#include "hformatdef.h"
#include "hformatset.h"
#include "SARibbonMenu.h"
#include "hnamespace.h"
#include "hopsheetvardlg.h"
#include <QHBoxLayout>
HReportEditorWidget::HReportEditorWidget(HReportManager* mgr,QWidget *parent)
   :m_pReportManager(mgr),QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    m_pGridReportWidget = new HGridReportWidget(this);
    m_pGridReportWidget->setEditorGridReportAttr();
    layout->setContentsMargins(3, 3, 3, 3);
    layout->addWidget(m_pGridReportWidget);
    m_pGridReportWidget->hide();
    setLayout(layout);
    connect(m_pGridReportWidget,SIGNAL(gridcellclicked()),this,SIGNAL(gridcellclicked()));
    m_wReportID = (quint16)-1;
}

HReportEditorWidget::~HReportEditorWidget()
{

}

void HReportEditorWidget::newReportWidget(quint16 wReportID)
{
    if(!m_pReportManager || !m_pReportManager->gridCtrlFile())
        return;
    saveReportWidget();
    m_wReportID = wReportID;
    HGridCtrlInfo* pInfo = m_pReportManager->gridCtrlFile()->getGridCtrlInfoById(m_wReportID);
    if(!pInfo) return;
    m_pGridReportWidget->setMaxRow(pInfo->gridReportRow());
    m_pGridReportWidget->setMaxCol(pInfo->gridReportCol());
    m_pGridReportWidget->setNumSheet(1);
    m_pGridReportWidget->init();//此时无文件需用默认值初始化
    m_pGridReportWidget->show();
}

void HReportEditorWidget::openReportWidget(quint16 wReportID)
{
    if(!m_pReportManager || !m_pReportManager->gridCtrlFile())
        return;
    saveReportWidget();
    m_wReportID = wReportID;
    HGridCtrlInfo* pInfo = m_pReportManager->gridCtrlFile()->getGridCtrlInfoById(m_wReportID);
    if(!pInfo) return;
    m_pGridReportWidget->setMaxRow(pInfo->gridReportRow());
    m_pGridReportWidget->setMaxCol(pInfo->gridReportCol());
    m_pReportManager->gridCtrlFile()->loadRelateVarFile(m_wReportID);
    //存表格
    m_pGridReportWidget->setNumSheet(1);
    char szFile[256],szPath[256];
    getDataFilePath(DFPATH_REPORT,szPath);
    sprintf(szFile,"%s%s%06d%s",szPath,"RPT",m_wReportID,".rpt");
    m_pGridReportWidget->setReportFile(szFile);
    m_pGridReportWidget->open();//需要从文件中读取
    for(int i = 0; i < m_pReportManager->gridCtrlFile()->m_pRelateVarList.count();i++)
    {
        HRelateVar* pVar =  m_pReportManager->gridCtrlFile()->m_pRelateVarList.at(i);
        if(!pVar) continue;
        int row = pVar->row();
        int col = pVar->col();
        QString str = pVar->desc();
        m_pGridReportWidget->setText(row,col,str);
        m_pGridReportWidget->enableOnlyRead(row,col,true);
    }
    m_pGridReportWidget->show();
}

void HReportEditorWidget::saveReportWidget()
{
    if(!m_pReportManager || !m_pReportManager->gridCtrlFile() || (quint16)-1 == m_wReportID)
        return;
    //先存变量
    m_pReportManager->gridCtrlFile()->saveRelateVarFile(m_wReportID);
    char szFile[256],szPath[256];
    getDataFilePath(DFPATH_REPORT,szPath);
    sprintf(szFile,"%s%s%06d%s",szPath,"RPT",m_wReportID,".rpt");
    //存表格
    m_pGridReportWidget->save(QString(szFile));
    //存表格信息
    m_pReportManager->gridCtrlFile()->saveGridCtrlInfoFile();
}

void HReportEditorWidget::delReportWidget(quint16 wReportID)
{
    if(!m_pReportManager || (quint16)-1 == wReportID)
        return;
    m_pGridReportWidget->clear();
}

void HReportEditorWidget::contextMenuEvent(QContextMenuEvent* event)
{
    QPoint pt = event->pos();
    pt.setY(pt.y() - 30);//27是QLabel和QLineEdit的高度，直接取控件高度好像不准
    QRect cellRect;
    m_pGridReportWidget->selectedRect(cellRect);
    if(!cellRect.contains(pt))
        return;

    SARibbonMenu *subMenu = new SARibbonMenu(this);
    QAction* setVarAct = new QAction(QIcon(":/icon/icon/insertVar.png"),QStringLiteral("设置变量"),this);
    QAction* delVarAct = new QAction(QIcon(":/icon/icon/removeVar.png"),QStringLiteral("删除变量"),this);
    connect(setVarAct,SIGNAL(triggered(bool)),this,SLOT(addGridVar_clicked()));
    connect(delVarAct,SIGNAL(triggered(bool)),this,SLOT(delGridVar_clicked()));
    subMenu->addAction(setVarAct);
    subMenu->addAction(delVarAct);
    subMenu->addSeparator();

    QAction* pasteAct = new QAction(this);
    pasteAct->setIcon(QIcon(":/icon/icon/Paste.png"));
    pasteAct->setText(QStringLiteral("粘贴"));
    QAction* cutAct = new QAction(this);
    cutAct->setIcon(QIcon(":/icon/icon/Cut.png"));
    cutAct->setText(QStringLiteral("剪切"));
    QAction* copyAct = new QAction(this);
    copyAct->setIcon(QIcon(":/icon/icon/Copy.png"));
    copyAct->setText(QStringLiteral("拷贝"));
    subMenu->addAction(cutAct);
    subMenu->addAction(copyAct);
    subMenu->addAction(pasteAct);
    connect(cutAct,SIGNAL(triggered(bool)),this,SLOT(cut()));
    connect(copyAct,SIGNAL(triggered(bool)),this,SLOT(cut()));
    connect(pasteAct,SIGNAL(triggered(bool)),this,SLOT(cut()));
    subMenu->addSeparator();

    SARibbonMenu* insertMenu = subMenu->addRibbonMenu(QIcon(":/icon/icon/sCellsInsertDialog.png"),QStringLiteral("插入"));
    QAction* insertRowAct = new QAction(QIcon(":/icon/icon/InsertRow.png"),QStringLiteral("插入行"),this);
    QAction* insertColAct = new QAction(QIcon(":/icon/icon/InsertColumn.png"),QStringLiteral("插入列"),this);
    insertMenu->addAction(insertRowAct);
    insertMenu->addAction(insertColAct);
    connect(insertRowAct,SIGNAL(triggered(bool)),this,SLOT(gridInsertRow_clicked()));
    connect(insertColAct,SIGNAL(triggered(bool)),this,SLOT(gridInsertCol_clicked()));
    SARibbonMenu* removeMenu = subMenu->addRibbonMenu(QIcon(":/icon/icon/sCellsDelete.png"),QStringLiteral("删除"));
    QAction* removeRowAct = new QAction(QIcon(":/icon/icon/RemoveRow.png"),QStringLiteral("删除行"),this);
    QAction* removeColAct = new QAction(QIcon(":/icon/icon/RemoveColumn.png"),QStringLiteral("删除列"),this);
    removeMenu->addAction(removeRowAct);
    removeMenu->addAction(removeColAct);
    connect(removeRowAct,SIGNAL(triggered(bool)),this,SLOT(gridRemoveRow_clicked()));
    connect(removeColAct,SIGNAL(triggered(bool)),this,SLOT(gridRemoveCol_clicked()));
    QAction *clearFormatingAct = new QAction(QIcon(":/icon/icon/ClearFormatting.png"),QStringLiteral("清除内容"),this);
    connect(clearFormatingAct,SIGNAL(triggered(bool)),this,SLOT(clearFommating_clicked()));
    subMenu->addRibbonMenu(insertMenu);
    subMenu->addRibbonMenu(removeMenu);
    subMenu->addAction(clearFormatingAct);
    subMenu->addSeparator();

    bool bHasRelateVar = false;
    int row1,col1,row2,col2;
    m_pGridReportWidget->selectedRowCol(row1,col1,row2,col2);
    for(int row = row1;row <= row2;row++)
        for(int col = col1;col <= col2;col++)
        {
            if(m_pReportManager->gridCtrlFile()->hasRelateVar(row,col,row,col))
            {
                bHasRelateVar = true;
            }
        }
    delVarAct->setEnabled(bHasRelateVar);
    subMenu->popup(event->globalPos());
}

void HReportEditorWidget::paste()
{
    m_pGridReportWidget->paste();
}

void HReportEditorWidget::cut()
{

}

void HReportEditorWidget::copy()
{

}

void HReportEditorWidget::addGridVar_clicked()
{
    HOpSheetVarDlg dlg;
    if(QDialog::Accepted == dlg.exec())
    {
        quint16 type = dlg.m_nOpSheetVarType;
        addGridVarByType(type);
    }
}

void HReportEditorWidget::addGridVarByType(quint8 btType)
{
    if(!m_pReportManager || !m_pReportManager->gridCtrlFile())
        return;
    int row1,col1,row2,col2;
    if(HVarFlags::varSheetStepNo == btType || HVarFlags::varSheetStep == btType || HVarFlags::varSheetStepTime == btType ||
       HVarFlags::varSheetStepHour == btType || HVarFlags::varSheetStepMin == btType || HVarFlags::varSheetRemark == btType ||
       HVarFlags::varSheetLockType == btType || HVarFlags::varLockNO == btType || HVarFlags::varSheetDescribe == btType || HVarFlags::varStateChange == btType)
    {
        m_pGridReportWidget->selectedRowCol(row1,col1,row2,col2);
        if(m_pReportManager->gridCtrlFile()->hasRelateVar(row1,col1,row2,col2))
        {
            return;
        }
        int nCount = 1;
        for(int row = row1; row <= row2;row++)
        {
            m_pGridReportWidget->setFocusCell(row,col1);
            m_pReportManager->gridCtrlFile()->deleteRelateVar(row,col1,row,col1);
            HRelateVar* pVar = new HRelateVar;
            pVar->setRowCol(row,col1);
            pVar->setType(btType);
            pVar->setNo(nCount);
            pVar->setNum(row2-row1+1);
            QString strDesc = getGridVarName(btType);
            strDesc = QString("%1(%2)").arg(strDesc).arg(nCount);
            pVar->setDesc(strDesc);
            m_pGridReportWidget->setText(row,col1,strDesc);
            m_pGridReportWidget->setTextColor(row,col1,Qt::red);
            m_pReportManager->gridCtrlFile()->m_pRelateVarList.append(pVar);
            nCount++;
            m_pGridReportWidget->enableOnlyRead(row,col1,true);
        }
    }
    else
    {
        m_pGridReportWidget->selectedRowCol(row1,col1,row2,col2);
        if(m_pReportManager->gridCtrlFile()->hasRelateVar(row1,col1,row2,col2))
        {
            return;
        }
        for(int row = row1;row <= row2;row++)
        {
            for(int col = col1;col <= col2;col++)
            {
                m_pGridReportWidget->setFocusCell(row,col);
                m_pReportManager->gridCtrlFile()->deleteRelateVar(row,col,row,col);
                HRelateVar* pVar = new HRelateVar;
                pVar->setRowCol(row,col1);
                pVar->setType(btType);
                QString strDesc = getGridVarName(btType);
                pVar->setDesc(strDesc);
                m_pGridReportWidget->setText(row,col1,strDesc);
                m_pGridReportWidget->setTextColor(row,col1,Qt::red);
                m_pGridReportWidget->enableOnlyRead(row,col,true);
                m_pReportManager->gridCtrlFile()->m_pRelateVarList.append(pVar);
            }
        }
    }
}

void HReportEditorWidget::delGridVar_clicked()
{
    if(!m_pReportManager || !m_pReportManager->gridCtrlFile())
        return;
    if(m_pReportManager->gridCtrlFile()->m_pRelateVarList.count() == 0) return;
    int row1,col1,row2,col2;
    m_pGridReportWidget->selectedRowCol(row1,col1,row2,col2);
    for(int row = row1;row <= row2;row++)
        for(int col = col1;col <= col2;col++)
        {
            if(m_pReportManager->gridCtrlFile()->hasRelateVar(row,col,row,col))
            {
                m_pReportManager->gridCtrlFile()->deleteRelateVar(row,col,row,col);
                m_pGridReportWidget->setText(row,col,"");
                m_pGridReportWidget->setTextColor(row,col,Qt::black);
                m_pGridReportWidget->enableOnlyRead(row,col,false);
            }
        }
}

void HReportEditorWidget::gridInsertRow_clicked()
{

}

void HReportEditorWidget::gridInsertCol_clicked()
{

}

void HReportEditorWidget::gridRemoveRow_clicked()
{

}

void HReportEditorWidget::gridRemoveCol_clicked()
{

}

void HReportEditorWidget::clearFommating_clicked()
{

}

//设置编辑框单项
void HReportEditorWidget::setCellFormat(HFormatSet* pFormatSet,uint formatType,bool bAll)
{
    if(!pFormatSet)
        return;

    //以下部分必须是单独设置
    if(CELL_TYPE_RESET == formatType)
    {
        if(pFormatSet->isResetFormat())
        {
            m_pGridReportWidget->enableResetFormat(true);
        }
        else if(pFormatSet->isResetText())
        {
            m_pGridReportWidget->enableResetText(true);
        }
        else if(pFormatSet->isResetAllFormat())
        {
            m_pGridReportWidget->enableResetAllFormat(true);
        }
        return;
    }
    else if((formatType == GRID_TYPE_ROW_HEIGHT))
    {
        m_pGridReportWidget->setRowHeight(pFormatSet->cellRowHeight());
        return;
    }

    else if(formatType == GRID_TYPE_COL_WIDTH)
    {
        m_pGridReportWidget->setColumnWidth(pFormatSet->cellColumnWidth());
        return;
    }

    //带all的
    if((CELL_TYPE_ALIGNMENT == formatType) |(CELL_TYPE_AUTOWRAPTEXT == formatType)| bAll)
    {
        m_pGridReportWidget->setFormat(pFormatSet->format());
    }

    if((CELL_TYPE_FONT == formatType) | bAll)
    {
        m_pGridReportWidget->setFont(pFormatSet->formatFont());
    }

    if((CELL_TYPE_BORDER == formatType) | bAll)
    {
        GV_BORDER_ITEM borderItem;
        borderItem.bBorderOutSide = pFormatSet->isBorderOutSide();
        borderItem.bBorderLeft = pFormatSet->isBorderLeft();
        borderItem.bBorderTop = pFormatSet->isBorderTop();
        borderItem.bBorderRight = pFormatSet->isBorderRight();
        borderItem.bBorderBottom = pFormatSet->isBorderBottom();
        borderItem.nLeftBorderStyle = pFormatSet->borderLeftPenStyle();
        borderItem.strLeftBoderClr = pFormatSet->borderLeftLineColor();
        borderItem.nRightBorderStyle = pFormatSet->borderRightPenStyle();
        borderItem.strRightBoderClr = pFormatSet->borderRightLineColor();
        borderItem.nTopBorderStyle = pFormatSet->borderTopPenStyle();
        borderItem.strTopBoderClr = pFormatSet->borderTopLineColor();
        borderItem.nBottomBorderStyle = pFormatSet->borderBottomPenStyle();
        borderItem.strBottomBoderClr = pFormatSet->borderBottomLineColor();
        m_pGridReportWidget->setBorder(&borderItem);
    }

    if((CELL_TYPE_COLOR == formatType) | bAll)
    {
        m_pGridReportWidget->setTextColor(pFormatSet->textColor());
        m_pGridReportWidget->setTextBkColor(pFormatSet->textBkColor());
    }
}

//获取cell表格的属性
void HReportEditorWidget::cellFormat(HFormatSet* pFormatSet)
{
    if(!pFormatSet)
        return;

    //pFormatSet->setText(pCell->text());
    //字体 + 字体颜色
    pFormatSet->setFormatFont(m_pGridReportWidget->font());
    pFormatSet->setTextColor(m_pGridReportWidget->textColor());
    pFormatSet->setTextBkColor(m_pGridReportWidget->textBkColor());

    //边框
    GV_BORDER_ITEM item;
    m_pGridReportWidget->getBorder(&item);
    pFormatSet->setBorderLeftPenStyle(item.nLeftBorderStyle);
    pFormatSet->setBorderRightPenStyle(item.nRightBorderStyle);
    pFormatSet->setBorderTopPenStyle(item.nTopBorderStyle);
    pFormatSet->setBorderBottomPenStyle(item.nBottomBorderStyle);

    pFormatSet->enableBorderLeft(item.bBorderLeft);
    pFormatSet->enableBorderRight(item.bBorderRight);
    pFormatSet->enableBorderTop(item.bBorderTop);
    pFormatSet->enableBorderBottom(item.bBorderBottom);

    pFormatSet->setBorderLeftLineColor(item.strLeftBoderClr);
    pFormatSet->setBorderRightLineColor(item.strRightBoderClr);
    pFormatSet->setBorderTopLineColor(item.strTopBoderClr);
    pFormatSet->setBorderBottomLineColor(item.strBottomBoderClr);

    //对齐
    pFormatSet->setFormat(m_pGridReportWidget->format());

    //行高列宽
    pFormatSet->setCellRowHeight(m_pGridReportWidget->rowHeight());
    pFormatSet->setCellColumnWidth(m_pGridReportWidget->columnWidth());

    //合并单元格
    pFormatSet->enableMergeCell(m_pGridReportWidget->isMerged());
    //打印相关设置
}

//操作
bool HReportEditorWidget::mergeCell()
{
    return m_pGridReportWidget->mergeCell();
}

bool HReportEditorWidget::splitCell()
{
    return m_pGridReportWidget->splitCell();
}

bool HReportEditorWidget::insertGridRow()
{
    return m_pGridReportWidget->insertGridRow();
}

bool HReportEditorWidget::insertGridColumn()
{
    return m_pGridReportWidget->insertGridColumn();
}

bool HReportEditorWidget::removeGridRow()
{
    return m_pGridReportWidget->removeGridRow();
}

bool HReportEditorWidget::removeGridColumn()
{
    return m_pGridReportWidget->removeGridColumn();
}

void HReportEditorWidget::autoSizeRows()
{
    m_pGridReportWidget->autoSizeRows();
}

void HReportEditorWidget::autoSizeColumns()
{
    m_pGridReportWidget->autoSizeColumns();
}

QString HReportEditorWidget::getGridVarName(quint8 btType)
{
    QString strVarName;
    switch (btType) {
    default:
        break;
    case HVarFlags::varStName:
        strVarName = QStringLiteral("厂站名称");
        break;
    case HVarFlags::varSheetNo:
        strVarName = QStringLiteral("操作票号");
        break;
    case HVarFlags::varSheetTitle:
        strVarName = QStringLiteral("操作票标题");
        break;
    case HVarFlags::varSheetDescribe:
        strVarName = QStringLiteral("任务描述");
        break;
    case HVarFlags::varOrderNo:
        strVarName = QStringLiteral("调度指令号");
        break;
    case HVarFlags::varSheetType:
        strVarName = QStringLiteral("操作票类型");
        break;
    case HVarFlags::varTaskType:
        strVarName = QStringLiteral("任务类型");
        break;
    case HVarFlags::varOpStepNum:
        strVarName = QStringLiteral("操作总步数");
        break;
    case HVarFlags::varSheetPageNum:
        strVarName = QStringLiteral("页数");
        break;
    case HVarFlags::varSheetPageNo:
        strVarName = QStringLiteral("页号");
        break;
    case HVarFlags::varPrintInput:
        strVarName = QStringLiteral("打印输入");
        break;
    case HVarFlags::varSheetPrevPage:
        strVarName = QStringLiteral("接上页");
        break;
    case HVarFlags::varSheetNextPage:
        strVarName = QStringLiteral("接下页");
        break;
    case HVarFlags::varOperator:
        strVarName = QStringLiteral("操作人");
        break;
    case HVarFlags::varGuardian:
        strVarName = QStringLiteral("监护人");
        break;
    case HVarFlags::varEditor:
        strVarName = QStringLiteral("操作票生成人");
        break;
    case HVarFlags::varStartTime:
        strVarName = QStringLiteral("操作开始时间");
        break;
    case HVarFlags::varSheetStepTime:
        strVarName = QStringLiteral("每步操作时间");
        break;
    case HVarFlags::varSheetMakeTime:
        strVarName = QStringLiteral("操作票生成时间");
        break;
    case HVarFlags::varNowTime:
        strVarName = QStringLiteral("当前时间");
        break;
    case HVarFlags::varSheetEneTime:
        strVarName = QStringLiteral("操作结束时间");
        break;
    case HVarFlags::varSheetStepHour:
        strVarName = QStringLiteral("每步操作时间(时)");
        break;
    case HVarFlags::varSheetStepMin:
        strVarName = QStringLiteral("每步操作时间(分)");
        break;
    case HVarFlags::varSheetStepNo:
        strVarName = QStringLiteral("操作序号");
        break;
    case HVarFlags::varSheetStep:
        strVarName = QStringLiteral("操作项目");
        break;
    case HVarFlags::varSheetRemark:
        strVarName = QStringLiteral("操作备注");
        break;
    case HVarFlags::varSheetStepType:
        strVarName = QStringLiteral("操作类型");
        break;
    case HVarFlags::varSheetLockType:
        strVarName = QStringLiteral("锁类型");
        break;
    case HVarFlags::varLockNO:
        strVarName = QStringLiteral("锁号");
        break;
    case HVarFlags::varOperatTeamNo:
        strVarName = QStringLiteral("班次");
        break;
    case HVarFlags::varStateChange:
        strVarName = QStringLiteral("状态转换");
        break;
    case HVarFlags::varLastSheetNo:
        strVarName = QStringLiteral("上接票号");
        break;
    case HVarFlags::varNextSheetNo:
        strVarName = QStringLiteral("下接票号");
        break;
    case HVarFlags::varSheetEndDesc:
        strVarName = QStringLiteral("结束语");
        break;
    case HVarFlags::varBitmap:
        strVarName = QStringLiteral("位图");
        break;
    case HVarFlags::varTextEdit:
        strVarName = QStringLiteral("字符输入");
        break;
    case HVarFlags::varDeivceState:
        strVarName = QStringLiteral("设备状态");
        break;
    case HVarFlags::varSheetOperatrNo:
        strVarName = QStringLiteral("操作编号");
        break;
    case HVarFlags::varRunningNo:
        strVarName = QStringLiteral("流水号");
        break;
    case HVarFlags::varDate:
        strVarName = QStringLiteral("显示日期");
        break;
    }
    return strVarName;
}
