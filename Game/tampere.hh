#ifndef TAMPERE_HH
#define TAMPERE_HH
#include "interfaces/icity.hh"
#include "actors/nysse.hh"
#include "actors/passenger.hh"
#include "graphics/simpleactoritem.hh"
#include "actors/stop.hh"
#include "interfaces/iactor.hh"
#include "core/location.hh"
#include <algorithm>    // std::find
#include <map>
#include "player.hh"
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QPointF>
#include "betteractoritem.h"

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

    void takeScene(QGraphicsScene* sceneToTake);
    void drawNysses();
    void movePlayer(int x_diff, int y_diff);
    void setArrowAngle(qreal angle);
    void drawShot();

    std::vector<std::shared_ptr<Interface::IStop>> stopList;
    std::vector<std::shared_ptr<Interface::IActor>> nysses;
    std::vector<std::pair<int,int>> nysseList;
    Player* player_;


private:
    QTime time_;
    QGraphicsScene* scene;
    //QTimeLine *timer_;
    //QGraphicsItemAnimation *animation_;
    CourseSide::SimpleActorItem* player_graphic_;
    std::map<std::shared_ptr<Interface::IActor>,BetterActorItem*> nysse_graphic_pairs;
    QGraphicsPolygonItem* playerArrow_;
};

#endif // TAMPERE_HH
