#include <QApplication>
#include <QtTest/QTest>
#include <unistd.h>
#include <time.h>
#include "gamewindow.hh"
#include "startdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);
    GameWindow gameWindow;
    startDialog s;
    s.exec();
    if(s.result() == 1)
    {
        gameWindow.show();
        //gameWindow.drawNysses();
        //gameWindow.drawStops();
    }
    else if(s.result() == 0)
    {

    }
    return a.exec();
}
