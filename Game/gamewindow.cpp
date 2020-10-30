#include "gamewindow.hh"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    QImage* backImg = new QImage("/home/ilari/Desktop/nyssepeli_main");
    QBrush backGround(*backImg);
    scene->setSceneRect(0,0,600,400);
    scene->setBackgroundBrush(backGround);
    gameView = new QGraphicsView;
    gameView->setParent(this);
    gameView->setScene(scene);


}

GameWindow::~GameWindow()
{
    delete ui;
}
