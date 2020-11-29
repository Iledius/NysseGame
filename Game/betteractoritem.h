#ifndef BETTERACTORITEM_H
#define BETTERACTORITEM_H
#include "QGraphicsItem"
#include "qpen.h"
#include <QPainter>
#include <QtMath>
#include <QtDebug>
#include "iostream"
#include <QTimer>


class BetterActorItem : public QGraphicsRectItem
{
public:
    BetterActorItem(QImage image, int health=2);
    void setImage(QImage image);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setAng(QPoint oldpos, QPoint newpos);
    void lowerHealth();
    int getHealth();
    QImage getImage();
    void setDestructTimer(int time);
    bool goingRight();

private:
    QImage image_;
    bool right_ = true;
    std::vector<qreal> angHistory_;
    int health_;
    QTimer* destruct_timer_;
};

#endif // BETTERACTORITEM_H
