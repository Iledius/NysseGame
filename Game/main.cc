#include <QApplication>
#include <QtTest/QTest>
#include "mainwindow.h"
#include "gamewindow.hh"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);
    MainWindow w;
    GameWindow gameWindow;
    w.show();
    gameWindow.show();

    return a.exec();
}
