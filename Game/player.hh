#ifndef PLAYER_HH
#define PLAYER_HH
#include <interfaces/iactor.hh>
#include <core/location.hh>
#include <map>
#include <QPolygonF>
#include <QGraphicsPolygonItem>

class Player : public Interface::IActor
{
public:
    Player();
    ~Player();
    void remove() override;
    bool isRemoved() const override;
    // Move ja givelocation turhia, koska location luokan käyttö kaatoi jostain syystä
    // siksi käytetään sijainnissa pair<int,int>
    void move(Interface::Location loc) override;
    Interface::Location giveLocation() const override;
    void changePos(int x, int y);
    std::pair<int,int> getPos();
    QPolygonF createArrow();

private:
    std::pair<int,int> pos_;
};

#endif // PLAYER_HH
