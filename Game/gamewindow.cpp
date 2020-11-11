#include "gamewindow.hh"
#include <iostream>
#include "ui_gamewindow.h"


GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    std::vector<CourseSide::SimpleActorItem*> nysses;
    scene = new QGraphicsScene(this);
    QImage* backImg = new QImage(":/offlinedata/offlinedata/kartta_pieni_500x500.png");
    logic_ = new CourseSide::Logic(this);

    std::shared_ptr<Tampere> city_temp_ = std::make_shared<Tampere>();

    ui->setupUi(this);
    QBrush backGround(*backImg);
    scene->setSceneRect(0,0,500,500);
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
    city_->takeScene(scene);
    logic_->finalizeGameStart();

}

void GameWindow::takeCity(std::shared_ptr<Tampere>& city)
{
    city_ = city;
}

void GameWindow::drawNysses()
{
   // tästä tuli turha? poista ehkä
    //city_->drawNysses();
}


void GameWindow::drawStops()
{
    //tapahtuu nykyään tamepreessa, säilytetään jos tulee ongelmia

    //for(auto loc : city_->stopList){
    //    std::cout << loc.first << std::endl;
    //    CourseSide::SimpleActorItem* nysse = new CourseSide::SimpleActorItem(loc.first,loc.second,0);
    //    scene->addItem(nysse);
    //}
}

GameWindow::~GameWindow()
{
    delete ui;
}
