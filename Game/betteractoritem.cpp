#include "betteractoritem.h"

BetterActorItem::BetterActorItem(QImage image, int health): image_(image), health_(health), destruct_timer_(new QTimer)
{
}

void BetterActorItem::setImage(QImage image)
{
    image_ = image;
}

void BetterActorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    QRectF r(0,0,image_.width(), image_.height());
    painter->drawImage(r,image_);
    setRect(0,0,image_.width(), image_.height());
}

void BetterActorItem::setDestructTimer(int time){
    QTimer::singleShot(time,[=](){delete this;});

}

bool BetterActorItem::goingRight()
{
    return right_;
}


QImage BetterActorItem::getImage(){
    return image_;
}

void BetterActorItem::setAngle(QPoint oldpos, QPoint newpos)
{
    if(oldpos.x()-newpos.x()>0){angHistory_.push_back(1);}
    else{angHistory_.push_back(-1);}

    if(accumulate(angHistory_.begin(),angHistory_.end(),0)<1){right_ = 1;}
    else{right_=0;}

    if(angHistory_.size()>10){angHistory_.erase(angHistory_.begin());}
}

void BetterActorItem::lowerHealth()
{
    health_--;
}

int BetterActorItem::getHealth()
{
    return health_;
}


