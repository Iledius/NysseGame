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
    drawNysses();
}

void Tampere::addStop(std::shared_ptr<Interface::IStop> stop)
{
    int x = stop->getLocation().giveX();
    int y = stop->getLocation().giveY();
    //std::pair<int,int> coords = {x,y};
    stopList.push_back(stop);

    CourseSide::SimpleActorItem* stop_interf = new CourseSide::SimpleActorItem(stop->getLocation().giveX(),
                                                                          stop->getLocation().giveY(),1);
    scene->addItem(stop_interf);
}

void Tampere::addActor(std::shared_ptr<Interface::IActor> newactor)
{
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
   //CourseSide::SimpleActorItem* nysse = new CourseSide::SimpleActorItem(actor->giveLocation().giveX(),
   //                                                                      actor->giveLocation().giveY(),1);
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
        CourseSide::SimpleActorItem* nysse = new CourseSide::SimpleActorItem(0,0,255);
        nysse_graphic_pairs.insert({bus, nysse});
        scene->addItem(nysse);
        nysse->setPos(coords);
    }
}

void Tampere::takeScene(QGraphicsScene* sceneToTake){
    scene=sceneToTake;
}


Tampere::~Tampere(){

};
