#include <QApplication>
#include <QtTest/QTest>
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
        //tällä hetkellä tehty oma funktio, käytetään logic_:in addNysseä jatkossa
        gameWindow.addNysse(1);
    }
    else if(s.result() == 0)
    {

    }
    return a.exec();
}
