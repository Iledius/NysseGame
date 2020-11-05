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
        //tällä hetkellä tehty oma funktio, käytetään logic_:in addNysseä jatkossa
        gameWindow.addNysse(1);
        for(int i=0; i<10; i++){
            gameWindow.moveNysse();
        }
    }
    else if(s.result() == 0)
    {
        return 0;
    }
    return a.exec();
}
