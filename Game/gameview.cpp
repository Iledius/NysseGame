#include "gameview.hh"
#include <QKeyEvent>
#include <QtMath>

GameView::GameView(QWidget *parent)
    : QGraphicsView(parent)
{
    setMouseTracking(true);
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
    case Qt::Key_Space: {city_->setArrowAngle(180);break;}

    default: { qDebug() << "Unhandled"; break; }
    }
}

void GameView::mouseMoveEvent(QMouseEvent *event){

      // calculate angle to aim to mouse pos
      qreal x = - city_->player_->getPos().first;
      qreal y = - city_->player_->getPos().second;
      qreal ang = qAtan2((x+event->x()), (y+event->y()));
      std::cout << -ang*57 << std::endl;
      city_->setArrowAngle(-ang*57+180);

      // set arrow to right pos next to player
      //float new_x = x+ang*
      //float new_y = (90-abs(-ang*57))/90;
      //float new_x = (ang*57/90);
       //     std::cout << new_x+x << std::endl;
      //city_->setArrowPos(QPointF(x+new_x, y+new_y));

}
