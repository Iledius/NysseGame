#include "gamewindow.hh"
#include <iostream>
#include "ui_gamewindow.h"
#include "startdialog.h"
#include <QString>
#include "statistics.h"
#include "enddialog.h"

#include <QKeyEvent>

QImage TAMPERE_MAP = QImage(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
QImage SATELLITE_MAP = QImage("../../etkot-software/Game/images/mapUHD.png");

const int GAME_TIME = 4280;
const int UPDATE_RATE = 10;
const int CAMERA_SMOOTHNESS = 11;

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow),
    scene(new QGraphicsScene(this)),
    logic_(new CourseSide::Logic(this)),
    timer(new QTimer(this)),
    gameView(new GameView(this))
{

    QString buses_string = ":/offlinedata/offlinedata/final_bus_liteN.json";
    QString stops_string = ":/offlinedata/offlinedata/full_stations_kkj3.json";
    ui->setupUi(this);

    // Mouse tracking for GameView
    centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);
    setMouseTracking(true);

    connect(timer, &QTimer::timeout, this, &GameWindow::advance);
    timer->start(UPDATE_RATE);

    QBrush backGround(SATELLITE_MAP);

    gameView->setParent(this);
    gameView->resize(1000,650);
    gameView->setScene(scene);

    scene->setSceneRect(0,0,3729,3564);
    gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setBackgroundBrush(backGround);

    std::shared_ptr<Tampere> city_temp_ = std::make_shared<Tampere>();
    takeCity(city_temp_);
    gameView->takeCity(city_temp_);
    logic_->takeCity(city_temp_);

    //Set highscore display
    std::multimap<int, QString>::reverse_iterator it;
    int n = 1;
    for(it = city_->stats.highScores.rbegin(); it != city_->stats.highScores.rend(); it++)
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
    if(!city_->isGameOver()){
        incrementTime();
        ui->timeDisplay->display((GAME_TIME-current_time)/(700/UPDATE_RATE));
        ui->scoreDisplay->display(city_->stats.currentScore);
        centerCamera();

        city_->movePlayer();
        city_->moveShots();
    }
    else{
        //setMouseTracking(false);
    }
}

void GameWindow::incrementTime(){
    if(current_time>GAME_TIME){
       endGame();
    }
    current_time++;
}

void GameWindow::endGame(){
    timer->stop();
    city_->endGame();
    qDebug() << "GAME FINISHED";
    city_->stats.saveScores(player_name);

    endScreen.setElons(city_->stats.elonsSaved);
    endScreen.setNyssesDestoyed(city_->stats.nyssesDestroyed);
    endScreen.setTotalScore(city_->stats.currentScore);
    endScreen.setPlayerName(player_name);
    endScreen.setDifficulty(difficulty);

    int score = city_->stats.currentScore;
    bool hs = city_->stats.isNewHighScore(score);
    if(hs)
    {
        endScreen.setNewHsLabel();
    }
    endScreen.show();
    if(endScreen.result() == 1)
    {
        city_->startGame();
    }
}

void GameWindow::centerCamera(){
    QPointF sceneCenter = gameView->mapToScene( gameView->viewport()->rect().center() );
    qreal delta_x = -sceneCenter.x()+city_->player_->getPos().first;
    qreal delta_y = -sceneCenter.y()+city_->player_->getPos().second;

    gameView->centerOn(sceneCenter + QPointF(delta_x/CAMERA_SMOOTHNESS,delta_y/CAMERA_SMOOTHNESS));
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::on_quitButton_pressed()
{
    QApplication::closeAllWindows();
    delete this;
}
