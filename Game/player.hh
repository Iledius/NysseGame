#ifndef PLAYER_HH
#define PLAYER_HH
#include <interfaces/iactor.hh>
#include <core/location.hh>


class Player : public Interface::IActor
{
public:
    Player();
    ~Player();
    void remove() override;
    bool isRemoved() const override;
    void move(Interface::Location loc) override;
    Interface::Location giveLocation() const override;

private:
    Interface::Location location_;
};

#endif // PLAYER_HH
