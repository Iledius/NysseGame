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
}
void Tampere::addStop(std::shared_ptr<Interface::IStop> stop)
{
    int x = stop->getLocation().giveX();
    int y = stop->getLocation().giveY();
    std::pair<int,int> coords = {x,y};
    stopList.push_back(coords);
}
void Tampere::addActor(std::shared_ptr<Interface::IActor> newactor)
{
    nysses.push_back(newactor);
}
void Tampere::removeActor(std::shared_ptr<Interface::IActor> actor)
{

}
void Tampere::actorRemoved(std::shared_ptr<Interface::IActor> actor){

}
bool Tampere::findActor(std::shared_ptr<Interface::IActor> actor) const {
   return false;
}
void Tampere::actorMoved(std::shared_ptr<Interface::IActor> actor){
    // iteraattorilla ettiminen saa kaatuman, siksi forloop
    //std::vector<std::shared_ptr<Interface::IActor>>::iterator pos;
    //pos = std::find(nysses.begin(), nysses.end(), actor);
    CourseSide::SimpleActorItem* nysse = new CourseSide::SimpleActorItem(actor->giveLocation().giveX(),
                                                                         actor->giveLocation().giveY(),1);
   std::map<std::shared_ptr<Interface::IActor>,CourseSide::SimpleActorItem*>::iterator it;
   it = nysse_graphic_pairs.find(actor);
   if(it != nysse_graphic_pairs.end()){
        scene->removeItem(it->second);
        it->second = nysse;
        scene->addItem(nysse);
   }
}
std::vector<std::shared_ptr<Interface::IActor>> Tampere::getNearbyActors(Interface::Location loc) const {

}
bool Tampere::isGameOver() const {
    return false;
}

void Tampere::drawNysses(){
    //std::cout << city_ << std::endl;
    for(std::shared_ptr<Interface::IActor> bus : nysses){
        CourseSide::SimpleActorItem* nysse = new CourseSide::SimpleActorItem(bus->giveLocation().giveX(),
                                                                             bus->giveLocation().giveY(),1);
        nysse_graphic_pairs.insert({bus, nysse});
        scene->addItem(nysse);
        break;
    }
}

void Tampere::takeScene(QGraphicsScene* sceneToTake){
    scene=sceneToTake;
}


Tampere::~Tampere(){

};
