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

}
void Tampere::addActor(std::shared_ptr<Interface::IActor> newactor)
{
<<<<<<< HEAD
    nysseList.push_back(newactor);

=======
    int x = newactor->giveLocation().giveX();
    int y = newactor->giveLocation().giveY();
    std::pair<int,int> coords = {x,y};
    nysseList.push_back(coords);
>>>>>>> refs/remotes/origin/master
}
void Tampere::removeActor(std::shared_ptr<Interface::IActor> actor)
{

}
void Tampere::actorRemoved(std::shared_ptr<Interface::IActor> actor){

}
bool Tampere::findActor(std::shared_ptr<Interface::IActor> actor) const {
   return true;
}
void Tampere::actorMoved(std::shared_ptr<Interface::IActor> actor){

}
std::vector<std::shared_ptr<Interface::IActor>> Tampere::getNearbyActors(Interface::Location loc) const {

}
bool Tampere::isGameOver() const {

}


Tampere::~Tampere(){

};
