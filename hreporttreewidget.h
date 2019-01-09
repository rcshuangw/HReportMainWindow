#ifndef HREPORTTREEWIDGET_H
#define HREPORTTREEWIDGET_H
#include <QTreeWidget>
class HReportManager;
class HReportTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    HReportTreeWidget(HReportManager* mgr,QWidget *parent = Q_NULLPTR);

public:
    //初始化报表结构
    void initReportTreeWidget();

    //新建报表
    void addReportTreeWidgetItem();

    //删除报表
    void delReportTreeWidgetItem();

    //导入报表
    void importReportTreeWigetItem();

    //根目录右键菜单
    void initReportTreeWidgetMenu(QContextMenuEvent* event);

public slots:

    //重命名报表
    void renameReport();

    //打开报表
    void openReport();

    //删除报表
    void delReport();

    //导入报表文件
    void importReportFile();

    //点击树
    void clickReportItem(QTreeWidgetItem*,int);

    //改变
    void changedReportItem(QTreeWidgetItem*,QTreeWidgetItem*);
signals:
    void reportNew();
    void reportOpen(const QString&,const int graphID);
    void reportDel(const QString&,const int graphID);
    void reportImport(const QString&);
    //void graphImportPath(const QString&);

protected:
    void contextMenuEvent(QContextMenuEvent *event);

protected:
    HReportManager* m_pReportMgr;
    int nPreGraphID;
};

#endif // HREPORTTREEWIDGET_H
