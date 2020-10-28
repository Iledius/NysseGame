#include <QApplication>
#include <QtTest/QTest>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);
    MainWindow w;
    w.show();
    return a.exec();
}
