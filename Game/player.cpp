#include "player.hh"

Player::Player()
{
}

Player::~Player(){
}

void Player::remove(){

}
bool Player::isRemoved() const{
    return false;
}
void Player::move(Interface::Location loc) {
    location_ = loc;
}
Interface::Location Player::giveLocation() const {
    return location_;
}
