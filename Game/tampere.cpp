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
    std::cout << stop << std::endl;
}
void Tampere::addActor(std::shared_ptr<Interface::IActor> newactor)
{
}
void Tampere::removeActor(std::shared_ptr<Interface::IActor> actor)
{
}

Tampere::~Tampere(){

};
