#ifndef TAMPERE_HH
#define TAMPERE_HH
#include "interfaces/icity.hh"
#include "actors/nysse.hh"
#include "actors/passenger.hh"
#include "graphics/simpleactoritem.hh"
#include "actors/stop.hh"
#include "interfaces/iactor.hh"
#include "core/location.hh"
#include <algorithm>
#include <map>
#include "player.hh"
#include <QPointF>
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

    /**
     * @brief takeScene
     * Takes scene, in which adds the actors
     * @param sceneToTake
     */
    void takeScene(QGraphicsScene* sceneToTake);

    /**
     * @brief drawActors
     * Adds all the actors on the scene, is called in the game start.
     */
    void drawActors();

    /**
     * @brief movePlayer
     * Moves BetterActorItem to position that corresponds player location.
     */
    void movePlayer();

    /**
     * @brief setArrowAngle
     * set's aim indicators angle
     * @param angle
     * Angle to change arrow angle to
     */
    void setArrowAngle(qreal angle);

    /**
     * @brief drawShot
     * Adds shot to scene
     */
    void drawShot();

    /**
     * @brief moveShots
     * Moves shot a bit forward every tick
     */
    void moveShots();

    /**
     * @brief reloadPressed
     * When reload key(R) is pressed, starts reloading. When finished, refills 6 ammo
     */
    void reloadPressed();

    /**
     * @brief pauseGame
     * Pauses game, BROKEN.
     */
    void pauseGame();

    /**
     * @brief endGame
     * set gameOver to true.
     */
    void endGame();

    /**
     * @brief pickPassengers
     * Removes passengers from map, increases passengers loaded in ship.
     */
    void pickPassengers();

    std::vector<std::shared_ptr<Interface::IStop>> stops;
    std::vector<std::shared_ptr<Interface::IActor>> actors;
    Player* player_;
    Statistics stats;

    int left, right, up, down, aimUp=0, aimDown=0, aimLeft=0, aimRight=0;
    float leftAcc=0, rightAcc=0, upAcc=0, downAcc=0;
    bool paused=false;
    int difficulty=0;
    int bus_health_=2;
    float speed = 0.1;

private:
    void checkCollison(BetterActorItem* item, int Z_VALUE);
    QTime time_;
    QGraphicsScene* scene_;
    BetterActorItem* playerGraphic_;
    std::map<std::shared_ptr<Interface::IActor>,BetterActorItem*> nysseGraphicPairs_;
    std::map<std::shared_ptr<Interface::IActor>,BetterActorItem*> passengerGraphicPairs_;
    QGraphicsPolygonItem* playerArrow_;
    std::map<BetterActorItem*, int> shots_;
    BetterActorItem* shuttle_;
    BetterActorItem* ammoGraphic_;

    int ammo_;
    int acceleration_ = 0;
    int reloadTime_ = 0;
    int passengersPicked_=0;

    bool gameOver_  = false;
    BetterActorItem* ray_;
};

#endif // TAMPERE_HH
