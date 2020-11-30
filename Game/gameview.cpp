#include "gameview.hh"

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
    if(event->isAutoRepeat()) {event->ignore();}

    switch(event->key())
    {
    case Qt::Key_D: {city_->right=1; break;}
    case Qt::Key_S: {city_->down=1;break; }
    case Qt::Key_A: {city_->left=1; break; }
    case Qt::Key_W: {city_->up=1; break; }

    case Qt::Key_Up: {city_->aimUp=1; break;}
    case Qt::Key_Down: {city_->aimDown=1;break; }
    case Qt::Key_Left: {city_->aimLeft=1; break; }
    case Qt::Key_Right: {city_->aimRight=1; break; }

    case Qt::Key_Space: {city_->drawShot();break;}
    case Qt::Key_R: {city_->reloadPressed(); break; }
    case Qt::Key_Q: {city_->pickPassengers(); break; }
    case Qt::Key_Escape: {city_->pauseGame();break;}
    }
}

void GameView::keyReleaseEvent(QKeyEvent *event){
    switch(event->key())
    {
    case Qt::Key_D: {city_->right=0; break;}
    case Qt::Key_S: {city_->down=0; break; }
    case Qt::Key_A: {city_->left=0; break; }
    case Qt::Key_W: {city_->up=0; break; }

    case Qt::Key_Up: {city_->aimUp=0; break;}
    case Qt::Key_Down: {city_->aimDown=0;break; }
    case Qt::Key_Left: {city_->aimLeft=0; break; }
    case Qt::Key_Right: {city_->aimRight=0; break; }

    }
}

void GameView::mouseMoveEvent(QMouseEvent *event){

      // calculate angle to aim to mouse pos
      // (540, 365) is about the center of the game area
      qreal x = 540;
      qreal y = 365;
      qreal ang = qAtan2((event->x()-x), (event->y()-y));
      city_->setArrowAngle(-ang*57+180);
}

void GameView::mousePressEvent(QMouseEvent *event){
   city_->drawShot();
}
