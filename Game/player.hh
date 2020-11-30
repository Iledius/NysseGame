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

    void changePos(int x, int y);
    std::pair<int,int> getPos();
    QPolygonF createArrow();

private:
    std::pair<int,int> pos_;
};

#endif // PLAYER_HH
