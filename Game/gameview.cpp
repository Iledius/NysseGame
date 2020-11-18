#include "gameview.hh"
#include <QKeyEvent>

GameView::GameView(QWidget *parent)
    : QGraphicsView(parent)
{
}

GameView::GameView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{
}

GameView::~GameView(){

}

void GameView::takeCity(std::shared_ptr<Tampere> city){
    city_ = city;
}

void GameView::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_D: {city_->movePlayer(3,0); break;}
    case Qt::Key_S: { city_->movePlayer(0,3); break; }
    case Qt::Key_A: { city_->movePlayer(-3,0); break; }
    case Qt::Key_W: { city_->movePlayer(0,-3); break; }
    case Qt::Key_Space: {}
    default: { qDebug() << "Unhandled"; break; }
    }
}
