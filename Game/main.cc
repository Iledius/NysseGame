#include <QApplication>
#include <QtTest/QTest>
#include <unistd.h>
#include <time.h>
#include <iostream>
#include "gamewindow.hh"
#include "startdialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);
    StartDialog s;
    s.exec();
    GameWindow gameWindow;
    if(s.result() == 1)
    {
        gameWindow.setDifficulty(s.difficulty);
        gameWindow.show();
        gameWindow.setPlayerName(s.player_name);
        return a.exec();
    }
    if(s.result() == 0)
    {
        QApplication::exit();
    }

}
