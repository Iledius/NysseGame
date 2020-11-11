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

    std::shared_ptr<Tampere> city_temp_ = std::make_shared<Tampere>();

    ui->setupUi(this);
    QBrush backGround(*backImg);
    scene->setSceneRect(-100,-100,500,500);
    scene->setBackgroundBrush(backGround);
    gameView = new QGraphicsView();
    gameView->setParent(this);
    gameView->setScene(scene);

    logic_->setTime(8, 0);

    QString buses_string = ":/offlinedata/offlinedata/final_bus_liteN.json";
    QString stops_string = ":/offlinedata/offlinedata/full_stations_kkj3.json";
    logic_->readOfflineData(buses_string,stops_string);
    // tää cityn säätö pointterista referenssiks saa aikaan mystisiä ongelmia
    // https://manski.net/2012/02/cpp-references-and-inheritance/ tuolla selitetty
    logic_->takeCity(city_temp_);
    takeCity(city_temp_);
    city_temp_=nullptr;
    logic_->finalizeGameStart();
    city_->takeScene(scene);
}

void GameWindow::takeCity(std::shared_ptr<Tampere>& city)
{
    city_ = city;
}

void GameWindow::drawNysses()
{
    for(auto loc : city_->nysses){
        //CourseSide::SimpleActorItem* nysse = new CourseSide::SimpleActorItem(loc.first,loc.second,255);
        //scene->addItem(nysse);
    }
}


void GameWindow::drawStops()
{
    for(auto loc : city_->stopList){
        std::cout << loc.first << "asd:D" << std::endl;
        CourseSide::SimpleActorItem* stop = new CourseSide::SimpleActorItem(loc.first,loc.second,0);
        scene->addItem(stop);
    }
}



void GameWindow::moveNysse()
{

}

GameWindow::~GameWindow()
{
    delete ui;
}
