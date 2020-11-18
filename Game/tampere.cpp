#include "tampere.hh"
#include "iostream"

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
    std::cout << "starting game, size of nysselist " << nysses.size() << std::endl;
    drawNysses();
    player_ = new Player;
    std::cout << player_->getPos().first<< std::endl;
    player_graphic_ = new CourseSide::SimpleActorItem(0,0,255);
    scene->addItem(player_graphic_);
    player_graphic_->setPos(QPoint(0,0));
    player_graphic_->setZValue(1);
    //jos halutaan hyödyntää drawNysses ja actorMoved funktioita pelaajalle
    //nysse_graphic_pairs.insert({player_,player_graphic_})
}

void Tampere::movePlayer(int x_diff, int y_diff)
{
    int x = player_->getPos().first;
    int y = player_->getPos().second;
    player_->changePos(x+x_diff,y+y_diff);
    int x_new = player_->getPos().first;
    int y_new = player_->getPos().second;
    player_graphic_->setPos(QPoint(x_new,y_new));
}

std::string Tampere::debug(int x){
    std::cout << x << std::endl;
    return "debug: got out of tampere";
}

void Tampere::addStop(std::shared_ptr<Interface::IStop> stop)
{
    int x = stop->getLocation().giveX();
    int y = stop->getLocation().giveY();
    stopList.push_back(stop);
    CourseSide::SimpleActorItem* stop_interf = new CourseSide::SimpleActorItem(stop->getLocation().giveX(),
                                                                          stop->getLocation().giveY(),255);
    //scene->addItem(stop_interf);
    //stop_interf->setPos(QPoint(x,y));
}

void Tampere::addActor(std::shared_ptr<Interface::IActor> newactor)
{
    int x = newactor->giveLocation().giveX();
    int y = newactor->giveLocation().giveY();
    std::pair<int,int> coords = {x,y};
    nysses.push_back(newactor);
}

void Tampere::removeActor(std::shared_ptr<Interface::IActor> actor)
{
    std::map<std::shared_ptr<Interface::IActor>,CourseSide::SimpleActorItem*>::iterator it;
    it=nysse_graphic_pairs.begin();
    if(it != nysse_graphic_pairs.end()){
         scene->removeItem(it->second);
         nysse_graphic_pairs.erase(it);
    }
}

void Tampere::actorRemoved(std::shared_ptr<Interface::IActor> actor){

}

bool Tampere::findActor(std::shared_ptr<Interface::IActor> actor) const {
   std::map<std::shared_ptr<Interface::IActor>,CourseSide::SimpleActorItem*>::const_iterator it;
   it=nysse_graphic_pairs.begin();
   if(it != nysse_graphic_pairs.end())
        return true;
   return false;
}

void Tampere::actorMoved(std::shared_ptr<Interface::IActor> actor){
   std::map<std::shared_ptr<Interface::IActor>,CourseSide::SimpleActorItem*>::iterator it;
   it = nysse_graphic_pairs.find(actor);
   if(it != nysse_graphic_pairs.end()){
        it->second->setPos(QPoint(actor.get()->giveLocation().giveX(),actor.get()->giveLocation().giveY()));
   }
}
std::vector<std::shared_ptr<Interface::IActor>> Tampere::getNearbyActors(Interface::Location loc) const {

}

bool Tampere::isGameOver() const {
    return false;
}



void Tampere::drawNysses(){

    for(std::shared_ptr<Interface::IActor> bus : nysses){
        QPoint coords = QPoint(bus->giveLocation().giveX(),bus->giveLocation().giveY());
        CourseSide::SimpleActorItem* actor = new CourseSide::SimpleActorItem(0,0,0);
        nysse_graphic_pairs.insert({bus, actor});
        scene->addItem(actor);
        actor->setPos(coords);
    }
}

void Tampere::takeScene(QGraphicsScene* sceneToTake){
    scene=sceneToTake;
}


Tampere::~Tampere(){

};
