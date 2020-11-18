#include "player.hh"
#include <iostream>

Player::Player()
{
    pos_ = {0,0};
}

Player::~Player(){
}

void Player::remove(){

}
bool Player::isRemoved() const{
    return false;
}
void Player::move(Interface::Location loc) {
    pos_={loc.giveX(),loc.giveY()};
}

void Player::changePos(int x, int y){
    pos_={x,y};
}

Interface::Location Player::giveLocation() const {
}

std::pair<int,int> Player::getPos() {
    return pos_;
}
