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
        gameWindow.show();
        gameWindow.setPlayerName(s.player_name);
        gameWindow.setDifficulty(s.difficulty);
    }
    if(s.result() == 0)
    {
        QApplication::exit();
    }
    return a.exec();
}
