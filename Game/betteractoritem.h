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
    /**
     * @brief setImage
     * change displayed image and boundingrect to imagesize
     * @param image
     */
    void setImage(QImage image);
    /**
     * @brief paint
     * changes the to the image which is given in setImage
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    /**
     * @brief setAngle
     * sets angle based on old pos and new pos, to the direction whcich is it going.
     * @param oldpos
     * @param newpos
     */
    void setAngle(QPoint oldpos, QPoint newpos);
    /**
     * @brief lowerHealth
     * lowers health by 1
     */
    void lowerHealth();
    /**
     * @brief getHealth
     * returns health that is left
     * @return
     */
    int getHealth();
    /**
     * @brief getImage
     * Returns image that the object uses
     * @return
     */
    QImage getImage();
    /**
     * @brief Sets timer to destroy object
     * @param time ( in milliseconds )
     */
    void setDestructTimer(int time);
    /**
     * @brief goingRight
     * Xhecks if object is going right
     * @return
     */
    bool goingRight();

private:
    QImage image_;
    bool right_ = true;
    std::vector<qreal> angHistory_;
    int health_;
    QTimer* destruct_timer_;
};

#endif // BETTERACTORITEM_H
