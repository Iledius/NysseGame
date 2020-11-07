#include "gamewindow.hh"
#include <iostream>
#include "ui_gamewindow.h"


GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    std::vector<CourseSide::SimpleActorItem*> nysses;
    scene = new QGraphicsScene(this);
    QImage* backImg = new QImage(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
    logic_ = new CourseSide::Logic(this);

     std::shared_ptr<Tampere> city_ = std::make_shared<Tampere>();

    ui->setupUi(this);
    QBrush backGround(*backImg);
    scene->setSceneRect(0,0,1095,592);
    scene->setBackgroundBrush(backGround);
    gameView = new QGraphicsView();
    gameView->setParent(this);
    gameView->setScene(scene);

    logic_->setTime(8, 0);

    QString buses_string = ":/offlinedata/offlinedata/final_bus_liteN.json";
    QString stops_string = ":/offlinedata/offlinedata/full_stations_kkj3.json";
    logic_->readOfflineData(buses_string,stops_string);
    logic_->takeCity(city_);
    logic_->finalizeGameStart();

}


void GameWindow::drawNysses()
{
     //tällä hetkellä tehty oma funktio, käytetään logic_:in addNysseä jatkossa
    CourseSide::SimpleActorItem* nysse = new CourseSide::SimpleActorItem(99,5,1);
    std::cout << city_->nysseList.at(0) << std::endl;
    scene->addItem(nysse);
}

void GameWindow::moveNysse()
{
}

GameWindow::~GameWindow()
{
    delete ui;
}
