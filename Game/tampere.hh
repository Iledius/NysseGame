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
#include <map>  // ei ehkä tarvii
#include "player.hh"
#include <QTimeLine> // ei ehkä tarvii
#include <QPointF> // ei ehkä tarvii
#include "betteractoritem.h"
#include <QtDebug>
#include <vector>
#include "statistics.h"
#include <QTimer>

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
    void drawActors();
    void movePlayer();
    void setArrowAngle(qreal angle);
    void drawShot();
    void moveShots();
    void reloadPressed();
    void pauseGame();
    void endGame();

    std::vector<std::shared_ptr<Interface::IStop>> stops;
    std::vector<std::shared_ptr<Interface::IActor>> actors;
    Player* player_;
    int left, right, up, down, aimUp=0, aimDown=0, aimLeft=0, aimRight=0;
    float leftAcc=0, rightAcc=0, upAcc=0, downAcc=0;
    int score = 0;
    Statistics stats;
    void pickPassengers();
    std::vector<BetterActorItem*> hit_items;
    bool paused=false;
    int advanced_amount = 0;

private:
    void checkShotCollison(BetterActorItem* item, int Z_VALUE);

    QTime time_;
    QGraphicsScene* scene_;
    BetterActorItem* playerGraphic_;
    std::map<std::shared_ptr<Interface::IActor>,BetterActorItem*> nysseGraphicPairs_;
    std::map<std::shared_ptr<Interface::IActor>,BetterActorItem*> passengerGraphicPairs_;
    QGraphicsPolygonItem* playerArrow_;
    int ammo_;
    std::map<BetterActorItem*, int> shots_;
    BetterActorItem* shuttle_;
    BetterActorItem* ammoGraphic_;
    int acceleration_ = 0;
    int reloadTime_ = 0;
    QTimer pickingTimer_;
    bool gameOver_  = false;
    BetterActorItem* ray;
    int passengersPicked_=0;


};

#endif // TAMPERE_HH
