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
    ui(new Ui::GameWindow),
    scene(new QGraphicsScene(this)),
    logic_(new CourseSide::Logic(this)),
    timer(new QTimer(this)),
    gameView(new GameView(this))
{
    //:/offlinedata/offlinedata/kartta_iso_1095x592.png
    //:/offlinedata/offlinedata/kartta_pieni_500x500.png

    QString buses_string = ":/offlinedata/offlinedata/final_bus_liteN.json";
    QString stops_string = ":/offlinedata/offlinedata/full_stations_kkj3.json";
    ui->setupUi(this);

    // Mouse tracking for GameView
    centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);
    setMouseTracking(true);

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

    //Set highscore display
    std::multimap<int, QString>::reverse_iterator it;
    int n = 1;
    for(it = stats.highScores.rbegin(); it != stats.highScores.rend(); it++)
    {
        QString name = it->second;
        QString qstScore = QString::number(it->first);
        QString delimitter = " - ";
        QString toAppend= QString::number(n) + ". " + name + delimitter + qstScore;
        n++;
        ui->highScoreBrowser->append(toAppend);
    }

    logic_->setTime(7, 30);
    logic_->readOfflineData(buses_string,stops_string);

    // tää säätö koska joku shared pointer ongelma joka korjautu kun annetaan referenssinä tälle luokalle se
    // https://manski.net/2012/02/cpp-references-and-inheritance/ tuolla selitetty muistaakseni

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

void GameWindow::advance()
{
    city_->movePlayer();
    city_->moveShots();
    ui->scoreDisplay->display(city_->stats.currentScore);
}

GameWindow::~GameWindow()
{
    delete ui;
    // TODO: kokeile tarviiko deletee kaikki erikseen
//    delete scene;
//    delete logic_;
//    delete gameView;
//    delete timer;
}

