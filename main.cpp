#include "MainWindow.h"
#include <QApplication>
#include <QTextCodec>
#include "hgridreportmgr.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QElapsedTimer cost;
    //cost.start();
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    HReportManager* m_pReportManager = new HReportManager;
    HReportMainWindow w(m_pReportManager);
    //w.setReportManager(m_pReportManager);
    //qDebug() <<"window build cost:"<<cost.elapsed()<<" ms";
    w.show();

    return a.exec();
}
