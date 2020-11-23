#include "betteractoritem.h"

BetterActorItem::BetterActorItem(QImage image): image_(image)
{
}

void BetterActorItem::setImage(QImage image)
{
    image_ = image;
}

void BetterActorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //QPen pen(Qt::black, 3);
    painter->setPen(Qt::NoPen);
    QRectF r;
    r.setRect(0,0,image_.width(), image_.height());
    painter->drawImage(r,image_);
    this->setRect(0,0,image_.width(), image_.height());
    // this->setTransformOriginPoint(-30,-30);
}

void BetterActorItem::setAng(QPoint oldpos, QPoint newpos)
{
//    qreal ang = qAtan2((oldpos.y()-newpos.y()), (oldpos.x()-newpos.x()));
//    angHistory.push_back(ang);
//    qreal angAvg = 0;
//    int amount = 0;
//    for (qreal angle: angHistory){
//        angAvg+= angle;
//        qDebug() << angle*57;
//        amount++;
//        if(amount == 6){
//            angHistory.erase(angHistory.begin());
//            break;
//        }
//    }
//    setRotation(-angAvg/amount*57);
    if(oldpos.x()-newpos.x()>0){angHistory.push_back(1);}
    else{angHistory.push_back(-1);}

    if(accumulate(angHistory.begin(),angHistory.end(),0)<1){setTransform(QTransform::fromScale(1,1));}
    else{setTransform(QTransform::fromScale(-1,1));}

    if(angHistory.size()>10){angHistory.erase(angHistory.begin());}
}
