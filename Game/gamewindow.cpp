#include "gamewindow.hh"
#include <iostream>
#include "ui_gamewindow.h"
#include "startdialog.h"
#include <QString>
#include "statistics.h"

#include <QKeyEvent>

QImage TAMPERE_MAP = QImage(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
QImage SATELLITE_MAP = QImage("../../etkot-software/Game/images/satellitemap.png");

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    //:/offlinedata/offlinedata/kartta_iso_1095x592.png
    //:/offlinedata/offlinedata/kartta_pieni_500x500.png

    QString buses_string = ":/offlinedata/offlinedata/final_bus_liteN.json";
    QString stops_string = ":/offlinedata/offlinedata/full_stations_kkj3.json";
    logic_ = new CourseSide::Logic(this);
    gameView = new GameView(this);
    scene = new QGraphicsScene(this);
    ui->setupUi(this);

    // Mouse tracking for GameView
    centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);
    setMouseTracking(true);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::advance);
    timer->start(10);

    QBrush backGround(SATELLITE_MAP);

    gameView->setParent(this);
    gameView->resize(1095,592);
    gameView->setScene(scene);


    // asetetaan scene oikeaan kokoon, ei tule scrollbareja
    QRect rcontent = gameView->contentsRect();
    scene->setSceneRect(0,0,rcontent.width(),rcontent.height());
    scene->setBackgroundBrush(backGround);

    this->resize(1295,592);

    std::shared_ptr<Tampere> city_temp_ = std::make_shared<Tampere>();
    takeCity(city_temp_);
    gameView->takeCity(city_temp_);
    logic_->takeCity(city_temp_);

    logic_->setTime(7, 30);
    logic_->readOfflineData(buses_string,stops_string);
    // tää säätö koska joku shared pointer ongelma joka korjautu kun annetaan referenssinä tälle luokalle se
    // https://manski.net/2012/02/cpp-references-and-inheritance/ tuolla selitetty muistaakseni

    //city_temp_=nullptr;
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

void GameWindow::busHit()
{
    //Bussiin osuu, tehään eka vaan pisteiden lisäystä varten
    incrementScore();
    stats.nyssesDestroyed = stats.nyssesDestroyed + 1;
}

void GameWindow::advance()
{
    city_->movePlayer();
    city_->moveShots();
    ui->scoreDisplay->display(city_->stats.currentScore);
}

GameWindow::~GameWindow()
{
    delete ui;
    delete scene;
    delete logic_;
    delete gameView;
    delete timer;
}

void GameWindow::on_pushButton_released()
{
    //Tallennetaan pelaajan tiedot
    std::cout << "ASD" << std::endl;
    city_->stats.saveScores(player_name);

}

void GameWindow::incrementScore()
{
    stats.incrementScore(5);
    std::cout << stats.currentScore << std::endl;
}
