#ifndef PLAYER_HH
#define PLAYER_HH
#include <interfaces/iactor.hh>
#include <core/location.hh>
#include <map>
#include <QPolygonF>
#include <QGraphicsPolygonItem>

class Player
{
public:
    Player();
    ~Player();
    /**
     * @brief changePos
     * Adds params x and y to player coordinates x and y
     * @param x
     * @param y
     */
    void changePos(int x, int y);

    /**
     * @brief getPos
     * returns the pos of player
     */
    std::pair<int,int> getPos();

    /**
     * @brief createArrow
     * Creates QPolygonF based on which the aim arrow is created
     */
    QPolygonF createArrow();

private:
    std::pair<int,int> pos_;
};

#endif // PLAYER_HH
