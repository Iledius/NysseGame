#ifndef BETTERACTORITEM_H
#define BETTERACTORITEM_H
#include "QGraphicsItem"
#include "qpen.h"
#include <QPainter>
#include <QtMath>
#include <QtDebug>
#include "iostream"


class BetterActorItem : public QGraphicsRectItem
{
public:
    BetterActorItem(QImage image, int health=2);
    void setImage(QImage image);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setAng(QPoint oldpos, QPoint newpos);
    void lowerHealth();
    int getHealth();
private:
    QImage image_;
    std::vector<qreal> angHistory;
    int health_;
};

#endif // BETTERACTORITEM_H