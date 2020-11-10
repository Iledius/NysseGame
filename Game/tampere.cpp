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

    for(unsigned long i = 0;i < nysses.size();i++)
    {
        if(nysses.at(i)==actor){
            //scene->removeItem()
        }
    }

    // todo: muuttuja, joka kertoo mitkä liikkuneet. Gamewindow katsoo tätä ja piirtää uusiksi.
    // Gamewindowin siis saatava myös tieto busseista!

}
std::vector<std::shared_ptr<Interface::IActor>> Tampere::getNearbyActors(Interface::Location loc) const {

}
bool Tampere::isGameOver() const {
    return false;
}

void Tampere::drawNysses(){
    //std::cout << city_ << std::endl;
    for(auto bus : nysses){
        CourseSide::SimpleActorItem* nysse = new CourseSide::SimpleActorItem(bus->giveLocation().giveX(),
                                                                             bus->giveLocation().giveY(),1);
        scene->addItem(nysse);
        break;
    }
}

void Tampere::takeScene(QGraphicsScene* sceneToTake){
    scene=sceneToTake;
}


Tampere::~Tampere(){

};
