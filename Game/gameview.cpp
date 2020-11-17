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

void GameView::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_Space: { qDebug() << "Space"; break; }
    case Qt::Key_Left: { qDebug() << "Left"; break; }
    case Qt::Key_Right: { qDebug() << "Right"; break; }
    default: { qDebug() << "Unhandled"; break; }
    }
}
