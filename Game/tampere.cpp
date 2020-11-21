#include "tampere.hh"
#include "iostream"

QImage BUS_IMAGE("../../etkot-software/Game/images/bussi.png");
QImage PASSENGER_IMAGE("../../etkot-software/Game/images/elon.png");
QImage PLAYER_IMAGE("../../etkot-software/Game/images/ufo.png");



Tampere::Tampere() :
    time_(QTime::currentTime().hour(), QTime::currentTime().minute(), QTime::currentTime().second())
{

}

void Tampere::setBackground(QImage &basicbackground, QImage &bigbackground)
{
}

void Tampere::setClock(QTime clock)
{
}

void Tampere::startGame()
{
    std::cout << "starting game, size of nysselist " << actors.size() << std::endl;
    drawNysses();
    player_ = new Player;
    playerArrow_ = scene->addPolygon(player_->createArrow());
    player_graphic_ = new BetterActorItem(PLAYER_IMAGE);
    scene->addItem(player_graphic_);
    player_graphic_->setScale(0.5);
    player_graphic_->setPos(QPoint(250,250));
    playerArrow_->setPos(player_->getPos().first+16, player_->getPos().second+16);
    player_graphic_->setZValue(1);
    playerArrow_->setScale(3);
    //jos halutaan hyödyntää drawNysses ja actorMoved funktioita pelaajalle
    //nysse_graphic_pairs.insert({player_,player_graphic_})
}

void Tampere::movePlayer()
{
    if(left==1) {player_->changePos(-2,0);}
    if(right==1) {player_->changePos(2,0);}
    if(up==1) {player_->changePos(0,-2);}
    if(down==1) {player_->changePos(0,2);}

    if(aimUp && aimLeft) {playerArrow_->setRotation(-45);}
    else if(aimUp && aimRight){playerArrow_->setRotation(45);}
    else if(aimDown && aimLeft){playerArrow_->setRotation(225);}
    else if(aimDown && aimRight){playerArrow_->setRotation(135);}
    else if(aimUp){playerArrow_->setRotation(0);}
    else if(aimDown){playerArrow_->setRotation(180);}
    else if(aimLeft){playerArrow_->setRotation(-90);}
    else if(aimRight){playerArrow_->setRotation(90);}

    int x_new = player_->getPos().first;
    int y_new = player_->getPos().second;
    player_graphic_->setPos(QPoint(x_new,y_new));
    playerArrow_->setPos(player_->getPos().first+16, player_->getPos().second+16);
}

void Tampere::addStop(std::shared_ptr<Interface::IStop> stop)
{
    int x = stop->getLocation().giveX();
    int y = stop->getLocation().giveY();
    stops.push_back(stop);
    CourseSide::SimpleActorItem* stop_interf = new CourseSide::SimpleActorItem(stop->getLocation().giveX(),
                                                                          stop->getLocation().giveY(),255);
    scene->addItem(stop_interf);
    stop_interf->setPos(QPoint(x,490-y));
    stop_interf->setScale(0.4);
}

void Tampere::addActor(std::shared_ptr<Interface::IActor> newactor)
{
    int x = newactor->giveLocation().giveX();
    int y = newactor->giveLocation().giveY();
    std::pair<int,int> coords = {x,y};
    actors.push_back(newactor);
}

void Tampere::removeActor(std::shared_ptr<Interface::IActor> actor)
{
    std::map<std::shared_ptr<Interface::IActor>,BetterActorItem*>::iterator it;
    it=nysse_graphic_pairs.begin();
    if(it != nysse_graphic_pairs.end()){
         scene->removeItem(it->second);
         nysse_graphic_pairs.erase(it);
    }
}

void Tampere::actorRemoved(std::shared_ptr<Interface::IActor> actor){

}

bool Tampere::findActor(std::shared_ptr<Interface::IActor> actor) const {
   std::map<std::shared_ptr<Interface::IActor>,BetterActorItem*>::const_iterator it;
   it=nysse_graphic_pairs.begin();
   if(it != nysse_graphic_pairs.end())
        return true;
   return false;
}

void Tampere::actorMoved(std::shared_ptr<Interface::IActor> actor){
   std::map<std::shared_ptr<Interface::IActor>,BetterActorItem*>::iterator it;
   it = nysse_graphic_pairs.find(actor);
   if(it != nysse_graphic_pairs.end()){
        //it->second->setAng(QPoint(it->second->x(), it->second->y()), QPoint(actor.get()->giveLocation().giveX(), 490-actor.get()->giveLocation().giveY()));
        it->second->setPos(QPoint(actor.get()->giveLocation().giveX(),500-actor.get()->giveLocation().giveY()));
   }
}

std::vector<std::shared_ptr<Interface::IActor>> Tampere::getNearbyActors(Interface::Location loc) const {
}

bool Tampere::isGameOver() const {
    return false;
}


void Tampere::drawNysses(){

    for(std::shared_ptr<Interface::IActor> bus : actors){
        QPoint coords = QPoint(bus->giveLocation().giveX(),bus->giveLocation().giveY());
        std::shared_ptr<Interface::IVehicle> isBus = std::dynamic_pointer_cast<Interface::IVehicle>(bus);
        if(isBus){
            BetterActorItem* actor = new BetterActorItem(BUS_IMAGE);
            nysse_graphic_pairs.insert({bus, actor});
            scene->addItem(actor);
            actor->setPos(coords);
            actor->setScale(0.3);
        }
        else {  BetterActorItem* actor = new BetterActorItem(PASSENGER_IMAGE);
            nysse_graphic_pairs.insert({bus, actor});
            scene->addItem(actor);
            actor->setPos(coords);
            actor->setScale(0.3);
        }

    }
}

void Tampere::takeScene(QGraphicsScene* sceneToTake){
    scene=sceneToTake;
}

void Tampere::setArrowAngle(qreal angle){
    playerArrow_->setRotation(angle);
}

void Tampere::drawShot(){
    BetterActorItem* shot = new BetterActorItem(PLAYER_IMAGE);
    scene->addItem(shot);
    shot->setRect(player_->getPos().first, player_->getPos().second, 10, 1);
    shot->setRotation(playerArrow_->rotation()+90);
    shots_.insert({shot, 0});
}

void Tampere::moveShots(){
    for(auto shot: shots_){
        //shot.first
    }
}

Tampere::~Tampere(){

};
