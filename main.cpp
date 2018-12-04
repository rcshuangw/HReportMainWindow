#include "MainWindow.h"
#include <QApplication>
#include "hgridreportmgr.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QElapsedTimer cost;
    //cost.start();
    HReportManager* m_pReportManager = new HReportManager;
    HReportMainWindow w(m_pReportManager);
    //w.setReportManager(m_pReportManager);
    //qDebug() <<"window build cost:"<<cost.elapsed()<<" ms";
    w.show();

    return a.exec();
}
