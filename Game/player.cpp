#include "player.hh"
#include <iostream>

Player::Player()
{
    pos_ = {250,250};
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
    pos_={pos_.first+x,pos_.second+y};
}

Interface::Location Player::giveLocation() const {
}

std::pair<int,int> Player::getPos() {
    return pos_;
}

QPolygonF Player::createArrow(){
    QPolygonF arrowCorners;
    arrowCorners.append(QPointF(-1.,0));
    arrowCorners.append(QPointF(0.,-9));
    arrowCorners.append(QPointF(1.,0));
    return arrowCorners;
}
