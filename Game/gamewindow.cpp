#include "gamewindow.hh"
#include <iostream>
#include "ui_gamewindow.h"
#include "startdialog.h"
#include <QString>

#include <QKeyEvent>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    std::vector<CourseSide::SimpleActorItem*> nysses;
    scene = new QGraphicsScene(this);
    QImage* backImg = new QImage(":/offlinedata/offlinedata/kartta_pieni_500x500.png");
    logic_ = new CourseSide::Logic(this);
    gameView = new GameView();

    std::shared_ptr<Tampere> city_temp_ = std::make_shared<Tampere>();

    ui->setupUi(this);
    QBrush backGround(*backImg);
    // asetetaan gameview oikeaan kokoon, ei tule scrollbareja
    QRect rcontent = gameView->contentsRect();


    scene->setSceneRect(0,0,rcontent.width(),rcontent.height());
    scene->setBackgroundBrush(backGround);
    gameView->setParent(this);
    gameView->setScene(scene);

    logic_->setTime(8, 0);
    gameView->scale(-1,-1);


    QString buses_string = ":/offlinedata/offlinedata/final_bus_liteN.json";
    QString stops_string = ":/offlinedata/offlinedata/full_stations_kkj3.json";
    logic_->readOfflineData(buses_string,stops_string);
    // tää cityn säätä pointterista referenssiks saa aikaan mystisiä ongelmia
    // https://manski.net/2012/02/cpp-references-and-inheritance/ tuolla selitetty
    logic_->takeCity(city_temp_);
    takeCity(city_temp_);
    gameView->takeCity(city_temp_);
    city_temp_=nullptr;
    city_->takeScene(scene);
    logic_->finalizeGameStart();
}

void GameWindow::takeCity(std::shared_ptr<Tampere>& city)
{
    city_ = city;
}

void GameWindow::drawStops()
{
}

void GameWindow::setPlayerName(QString s)
{
    player_name = s;
    ui->playerNameLabel->setText(player_name);
}

void GameWindow::setDifficulty(int d)
{
    this->difficulty = d;
    std::vector<std::string> diffs = {"Easy", "Medium", "Hard"};
    ui->difficultyLabel->setText(QString::fromStdString(diffs.at(d)));
}

GameWindow::~GameWindow()
{
    delete ui;
}
