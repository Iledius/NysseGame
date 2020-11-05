#include "gamewindow.hh"
#include "ui_gamewindow.h"



GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    std::vector<CourseSide::SimpleActorItem*> nysses;
    scene = new QGraphicsScene(this);
    QImage* backImg = new QImage("../Game/images/water.png");
    logic_ = new CourseSide::Logic(this);

    // Ei toimi, ilmeisesti koska luokka Tampere on abstrakti, eli funktioita ei ole implementoitu? en y,,ärrä
    // ps. ctrl + klikkaamalla luokkaa pääsee kätevästi hyppimään filujen välillä :D
    //std::shared_ptr<Tampere> city_ = std::make_shared<Tampere>();

    ui->setupUi(this);
    QBrush backGround(*backImg);
    scene->setSceneRect(0,0,600,400);
    scene->setBackgroundBrush(backGround);
    gameView = new QGraphicsView();
    gameView->setParent(this);
    gameView->setScene(scene);

    logic_->setTime(8, 0);

    // Jotta logic sadaan käyttöön, täytyy ajaa finalizeGameStart().
    // Jotta finalizegamestart() toimisi, pitää tehdä ajaa funktio takeCity().
    //logic_->addNewBuses();
    logic_->takeCity(city_);
    //logic_->finalizeGameStart();
}


void GameWindow::addNysse(unsigned int line)
{
     //tällä hetkellä tehty oma funktio, käytetään logic_:in addNysseä jatkossa

    CourseSide::SimpleActorItem* nysse = new CourseSide::SimpleActorItem(3,5,1);
    scene->addItem(nysse);
    nysses.push_back(nysse);
}


GameWindow::~GameWindow()
{
    delete ui;
}
