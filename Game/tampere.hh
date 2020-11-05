#ifndef TAMPERE_HH
#define TAMPERE_HH
#include "interfaces/icity.hh"
#include "actors/nysse.hh"
#include "actors/passenger.hh"
#include "graphics/simpleactoritem.hh"
#include "actors/stop.hh"
#include "interfaces/iactor.hh"
#include "core/location.hh"


class Tampere : public Interface::ICity
{
public:
    Tampere();
    ~Tampere();

    void setBackground(QImage &basicbackground, QImage &bigbackground) override;
    void setClock(QTime clock) override;
    void startGame() override;
    void addStop(std::shared_ptr<Interface::IStop> stop) override;
    void addActor(std::shared_ptr<Interface::IActor> newactor) override;
    void removeActor(std::shared_ptr<Interface::IActor> actor) override;
    void actorRemoved(std::shared_ptr<Interface::IActor> actor) override;
    bool findActor(std::shared_ptr<Interface::IActor> actor) const override;
    void actorMoved(std::shared_ptr<Interface::IActor> actor) override;
    std::vector<std::shared_ptr<Interface::IActor>> getNearbyActors(Interface::Location loc) const override;
    bool isGameOver() const override;
    std::vector<CourseSide::SimpleActorItem*> nysses;

private:
    QTime time_;

};

#endif // TAMPERE_HH
