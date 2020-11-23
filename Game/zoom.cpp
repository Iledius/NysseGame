#include "zoom.hh"

Zoom::Zoom(GameView *view) : QObject(view), view_(view)
{
}
void Zoom::takeTarget(QGraphicsItem *object){
    target_=object;
}

void Zoom::zoom_on_target(){
    target_viewport_pos = target_->pos();
    //target_scene_pos = view_->mapToScene(target_->pos());
}

