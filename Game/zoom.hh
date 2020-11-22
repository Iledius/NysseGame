#ifndef ZOOM_HH
#define ZOOM_HH

#include <QObject>
#include <QGraphicsItem>
#include "gameview.hh"

class Zoom : public QObject
{
    Q_OBJECT
public:
    Zoom(GameView* view);
    void takeTarget(QGraphicsItem* object);
    void zoom_on_target();
private:
    QGraphicsItem* target_;
    GameView* view_;
    QPointF target_viewport_pos, target_scene_pos;
signals:


};

#endif // ZOOM_HH
