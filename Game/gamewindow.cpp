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
    scene->setSceneRect(0,0,1095,592);
    scene->setBackgroundBrush(backGround);
    gameView = new QGraphicsView();
    gameView->setParent(this);
    gameView->setScene(scene);

    logic_->setTime(8, 0);

    QString buses_string = ":/offlinedata/offlinedata/final_bus_liteN.json";
    QString stops_string = ":/offlinedata/offlinedata/full_stations_kkj3.json";
    logic_->readOfflineData(buses_string,stops_string);
    logic_->takeCity(city_temp_);
    chooseCity(city_temp_);
    city_temp_=nullptr;
    logic_->finalizeGameStart();

}

void GameWindow::chooseCity(std::shared_ptr<Tampere>& city)
{
    city_ = city;
}

void GameWindow::drawNysses()
{
<<<<<<< HEAD
     //tällä hetkellä tehty oma funktio, käytetään logic_:in addNysseä jatkossa
    CourseSide::SimpleActorItem* nysse = new CourseSide::SimpleActorItem(99,5,1);
    std::vector<std::shared_ptr<Interface::IActor>> kyrpa =  city_->nysseList;
    scene->addItem(nysse);
=======
   // CourseSide::SimpleActorItem* n = city_->nysseList.at(0);
    std::cout << city_ << std::endl;
    for(auto loc : city_->nysseList){
        std::cout << loc.first << std::endl;

        CourseSide::SimpleActorItem* nysse = new CourseSide::SimpleActorItem(loc.first,loc.second,1);
        scene->addItem(nysse);
    }
>>>>>>> refs/remotes/origin/master
}

void GameWindow::moveNysse()

{
}

GameWindow::~GameWindow()
{
    delete ui;
}
