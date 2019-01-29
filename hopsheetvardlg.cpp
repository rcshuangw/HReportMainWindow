#include "hopsheetvardlg.h"
#include "ui_hopsheetvardlg.h"
#include "hnamespace.h"
#include <QCloseEvent>
HOpSheetVarDlg::HOpSheetVarDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HOpSheetVarDlg)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    m_nOpSheetVarType = (quint16)-1;
    initSheetVarDlg();
}

HOpSheetVarDlg::~HOpSheetVarDlg()
{
    delete ui;
}

void HOpSheetVarDlg::initSheetVarDlg()
{
    QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
    item->setText(QStringLiteral("厂站名称"));
    item->setData(Qt::UserRole,QVariant(HVarFlags::varStName));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varSheetNo));
    item->setText(QStringLiteral("操作票号"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varSheetTitle));
    item->setText(QStringLiteral("操作票标题"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varSheetDescribe));
    item->setText(QStringLiteral("任务描述"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varOrderNo));
    item->setText(QStringLiteral("调度指令号"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varSheetType));
    item->setText(QStringLiteral("操作票类型"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varTaskType));
    item->setText(QStringLiteral("任务类型"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varOpStepNum));
    item->setText(QStringLiteral("操作总步数"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varSheetPageNum));
    item->setText(QStringLiteral("页数"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varSheetPageNo));
    item->setText(QStringLiteral("页号"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varPrintInput));
    item->setText(QStringLiteral("打印输入"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varSheetPrevPage));
    item->setText(QStringLiteral("接上页"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varSheetNextPage));
    item->setText(QStringLiteral("接下页"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varOperator));
    item->setText(QStringLiteral("操作人"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varGuardian));
    item->setText(QStringLiteral("监护人"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varEditor));
    item->setText(QStringLiteral("操作票生成人"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varStartTime));
    item->setText(QStringLiteral("操作开始时间"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varSheetStepTime));
    item->setText(QStringLiteral("每步操作时间"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varSheetMakeTime));
    item->setText(QStringLiteral("操作票生成时间"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varNowTime));
    item->setText(QStringLiteral("当前时间"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varSheetEneTime));
    item->setText(QStringLiteral("操作结束时间"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varSheetStepHour));
    item->setText(QStringLiteral("每步操作时间(时)"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varSheetStepMin));
    item->setText(QStringLiteral("每步操作时间(分)"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varSheetStepNo));
    item->setText(QStringLiteral("操作序号"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varSheetStep));
    item->setText(QStringLiteral("操作项目"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varSheetRemark));
    item->setText(QStringLiteral("操作备注"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varSheetStepType));
    item->setText(QStringLiteral("操作类型"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varSheetLockType));
    item->setText(QStringLiteral("锁类型"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varLockNO));
    item->setText(QStringLiteral("锁号"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varOperatTeamNo));
    item->setText(QStringLiteral("班次"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varStateChange));
    item->setText(QStringLiteral("状态转换"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varLastSheetNo));
    item->setText(QStringLiteral("上接票号"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varNextSheetNo));
    item->setText(QStringLiteral("下接票号"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varSheetEndDesc));
    item->setText(QStringLiteral("结束语"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varBitmap));
    item->setText(QStringLiteral("位图"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varTextEdit));
    item->setText(QStringLiteral("字符输入"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varDeivceState));
    item->setText(QStringLiteral("设备状态"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varSheetOperatrNo));
    item->setText(QStringLiteral("操作编号"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varRunningNo));
    item->setText(QStringLiteral("流水号"));
    item = new QListWidgetItem(ui->listWidget);
    item->setData(Qt::UserRole,QVariant(HVarFlags::varDate));
    item->setText(QStringLiteral("显示日期"));
}

void HOpSheetVarDlg::okBtn()
{
    QListWidgetItem* item = ui->listWidget->currentItem();
    if(!item) return;
    m_nOpSheetVarType = item->data(Qt::UserRole).toUInt();
    QDialog::accept();
}

void HOpSheetVarDlg::closeEvent(QCloseEvent *e)
{
     e->accept();
}
