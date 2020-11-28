#include "tampere.hh"
#include "iostream"
#include "statistics.h"

QImage BUS_IMAGE("../../etkot-software/Game/images/tank.png");
QImage PASSENGER_IMAGE("../../etkot-software/Game/images/elon.png");
QImage PLAYER_IMAGE("../../etkot-software/Game/images/ufo.png");
QImage RAY("../../etkot-software/Game/images/ray.png");
QImage SHOT_IMAGE("../../etkot-software/Game/images/laser2.png");
QImage SHUTTLE_IMAGE("../../etkot-software/Game/images/shuttle.png");
QImage EXPLOSION_IMAGE("../../etkot-software/Game/images/explosion.png");



QImage AMMO_6("../../etkot-software/Game/images/6ammo.png");

// Z-levels for different items:
const int PLAYER_Z = 7;
const int BUS_Z = 3;
const int PASSENGER_Z = 2;
const int SHUTTLE_Z = 4;

const int ACC_LIMIT = 60;
const float DECELERATION_MULT = 1.07; // 1 = never slows down

const int SHOT_RANGE = 100;
const int BUS_HEALTH = 2;
const float SPEED = 0.1;

const int PASSENGER_STORAGE = 100;
const int SCORE_FOR_BUS = 100;
const int SCORE_FOR_PASSENGER = 3;

int AMMO = 6;


Tampere::Tampere() :
    player_(new Player),
    time_(QTime::currentTime().hour(),
          QTime::currentTime().minute(),
          QTime::currentTime().second()),
    playerGraphic_(new BetterActorItem(PLAYER_IMAGE)),
    shuttle_(new BetterActorItem(SHUTTLE_IMAGE)),
    ammoGraphic_(new BetterActorItem(AMMO_6))
{
}

void Tampere::setBackground(QImage &basicbackground, QImage &bigbackground)
{
    // FILLEREITÄ VAROTUKSIA VARTEN
    //TODO: jotain tällä funktiolla?? pitää implementoida ettei oo virtual
    basicbackground.setColor(1,0);
    bigbackground.setColor(1,0);
}

void Tampere::setClock(QTime clock)
{
    // FILLEREITÄ VAROTUKSIA VARTEN
    //TODO: jotain tällä funktiolla?? pitää implementoida ettei oo virtual
    this->time_.setHMS(clock.hour(),clock.minute(),clock.second());
}

void Tampere::startGame()
{
    drawActors();

    // Player cannon and player visuals
    playerArrow_ = scene_->addPolygon(player_->createArrow());
    scene_->addItem(playerGraphic_);
    // Visual that displays how much ammo left
    scene_->addItem(ammoGraphic_);
    ammoGraphic_->setParentItem(playerGraphic_);
    ammoGraphic_->setScale(2);

    playerGraphic_->setPos(QPoint(250,250));
    playerArrow_->setPos(player_->getPos().first+23, player_->getPos().second+23);

    playerGraphic_->setZValue(PLAYER_Z);  // player always on top
    playerArrow_->setZValue(PLAYER_Z-1); // aimingarrow under player

    playerGraphic_->setScale(0.75);
    playerArrow_->setScale(4.5);

    // Shuttle visual, where we drop our Elon clones
    scene_->addItem(shuttle_);
    shuttle_->setZValue(SHUTTLE_Z);
    shuttle_->setPos(400,400);
    shuttle_->setScale(1);
    ammo_ = AMMO;


    ray = new BetterActorItem(RAY);
    scene_->addItem(ray);
    ray->setOpacity(0);
    ray->setZValue(PLAYER_Z-2);
}

void Tampere::movePlayer()
{
    // max speed multiplier


    // moving with acceleration
    if(left==1) {player_->changePos(-SPEED*leftAcc,0);leftAcc=(leftAcc>ACC_LIMIT) ? leftAcc+1:ACC_LIMIT;}
    if(right==1) {player_->changePos(SPEED*rightAcc,0);rightAcc=(rightAcc>ACC_LIMIT) ? rightAcc+1:ACC_LIMIT;}
    if(up==1) {player_->changePos(0,-SPEED*upAcc);upAcc=(upAcc>ACC_LIMIT) ? upAcc+1:ACC_LIMIT;}
    if(down==1) {player_->changePos(0,SPEED*downAcc);downAcc=(downAcc>ACC_LIMIT) ? downAcc+1:ACC_LIMIT;}

   if(left==0&&leftAcc>0){
       leftAcc=leftAcc/DECELERATION_MULT;
       if(leftAcc>0){
           player_->changePos(-0.1*leftAcc,0);
       }else leftAcc=0;
   }
   if(right==0&&rightAcc>0){
       rightAcc=rightAcc/DECELERATION_MULT;
       if(rightAcc>0){
           player_->changePos(0.1*rightAcc,0);
       }else rightAcc=0;
   }
   if(up==0&&upAcc>0){
       upAcc=upAcc/DECELERATION_MULT;
       if(upAcc>0){
           player_->changePos(0,-0.1*upAcc);
       }else upAcc=0;
   }
   if(down==0&&downAcc>0){
       downAcc=downAcc/DECELERATION_MULT;
       if(downAcc>0){
           player_->changePos(0,0.1*downAcc);
       }else downAcc=0;
   }


    // Had to be done in this very manual way because of qt:s way of processing keypresses.
    if(aimUp && aimLeft) {playerArrow_->setRotation(315);}
    else if(aimUp && aimRight){playerArrow_->setRotation(45);}
    else if(aimDown && aimLeft){playerArrow_->setRotation(225);}
    else if(aimDown && aimRight){playerArrow_->setRotation(135);}
    else if(aimUp){playerArrow_->setRotation(0);}
    else if(aimDown){playerArrow_->setRotation(180);}
    else if(aimLeft){playerArrow_->setRotation(270);}
    else if(aimRight){playerArrow_->setRotation(90);}

    int x_new = player_->getPos().first;
    int y_new = player_->getPos().second;
    playerGraphic_->setPos(QPoint(x_new,y_new));
    playerArrow_->setPos(player_->getPos().first+23, player_->getPos().second+23);

    // Reload timer
    if(reloadTime_>0){
        reloadTime_--;
    }
    if(reloadTime_==1){
        ammo_=6;
        ammoGraphic_->setImage(AMMO_6);
        ammoGraphic_->update();
        qDebug()<< "reloaded 6 shots";
    }

    if(ray) ray->setPos(playerGraphic_->pos()+QPointF(-35,-35));

}

void Tampere::addStop(std::shared_ptr<Interface::IStop> stop)
{
    int x = stop->getLocation().giveX();
    int y = stop->getLocation().giveY();
    stops.push_back(stop);
    CourseSide::SimpleActorItem* stop_interf = new CourseSide::SimpleActorItem(stop->getLocation().giveX(),
                                                                          stop->getLocation().giveY(),255);
    scene_->addItem(stop_interf);
    stop_interf->setPos(QPoint(x,490-y));
    stop_interf->setScale(0.4);
}

void Tampere::addActor(std::shared_ptr<Interface::IActor> newactor)
{
    actors.push_back(newactor);
}

void Tampere::removeActor(std::shared_ptr<Interface::IActor> actor)
{
    std::map<std::shared_ptr<Interface::IActor>,BetterActorItem*>::iterator it;
    it=nysseGraphicPairs_.find(actor);
    if(it != nysseGraphicPairs_.end() && it->second->scene() != nullptr){
         scene_->removeItem(it->second);
         delete it->second;
         nysseGraphicPairs_.erase(it);
         return;
    }
    it=passengerGraphicPairs_.find(actor);
    if(it != passengerGraphicPairs_.end() && it->second->scene() != nullptr){
         scene_->removeItem(it->second);
         delete it->second;
         passengerGraphicPairs_.erase(it);
    }
}

void Tampere::actorRemoved(std::shared_ptr<Interface::IActor> actor)
{
    removeActor(actor);
}

bool Tampere::findActor(std::shared_ptr<Interface::IActor> actor) const {
   std::map<std::shared_ptr<Interface::IActor>,BetterActorItem*>::const_iterator it;
   it=nysseGraphicPairs_.find(actor);
   if(it != nysseGraphicPairs_.end())
        return true;
   return false;
}

void Tampere::actorMoved(std::shared_ptr<Interface::IActor> actor){
    std::map<std::shared_ptr<Interface::IActor>,BetterActorItem*>::iterator it;
      it = nysseGraphicPairs_.find(actor);
      if(it != nysseGraphicPairs_.end()){
           it->second->setAng(QPoint(it->second->x(), it->second->y()), QPoint(actor.get()->giveLocation().giveX(), 490-actor.get()->giveLocation().giveY()));
           it->second->setPos(QPoint(actor.get()->giveLocation().giveX(),500-actor.get()->giveLocation().giveY()));
           return;
      }

    // TODO: korjaa passengerit kulkemaan!!
//   std::shared_ptr<Interface::IPassenger> pass = std::dynamic_pointer_cast<Interface::IPassenger>(actor);
//   if(pass){
//        if(findActor(pass->getVehicle())){
//            passengerGraphicPairs_.find(actor);
//            if(it != passengerGraphicPairs_.end()){
//                it->second->setPos(QPoint(actor.get()->giveLocation().giveX(),500-actor.get()->giveLocation().giveY()));
//            }
//        }
//   }

}

std::vector<std::shared_ptr<Interface::IActor>> Tampere::getNearbyActors(Interface::Location loc) const {
    // TODO:: käytä jotenkin? halusin tällä vaan varotukset pois
    qDebug() << loc.giveX();
    std::vector<std::shared_ptr<Interface::IActor>> asd;
    return asd;
}

void Tampere::endGame(){
    gameOver_=true;
}

bool Tampere::isGameOver() const {
    if(!gameOver_)return false;
    else return true;
}


void Tampere::drawActors(){
    for(std::shared_ptr<Interface::IActor> iactor : actors){
           QPoint bus_coords = QPoint(iactor->giveLocation().giveX(),iactor->giveLocation().giveY());
           std::shared_ptr<Interface::IVehicle> isBus = std::dynamic_pointer_cast<Interface::IVehicle>(iactor);

           // If actor is a bus
           if(isBus){
               BetterActorItem* actor_graphic = new BetterActorItem(BUS_IMAGE,BUS_HEALTH);
               nysseGraphicPairs_.insert({iactor, actor_graphic});
               scene_->addItem(actor_graphic);
               actor_graphic->setPos(bus_coords+QPoint());
               actor_graphic->setScale(0.8);
               actor_graphic->setZValue(BUS_Z);
           }

           // If actor is a passenger
           else {  BetterActorItem* actor_graphic = new BetterActorItem(PASSENGER_IMAGE);
               passengerGraphicPairs_.insert({iactor, actor_graphic});
               scene_->addItem(actor_graphic);
               actor_graphic->setPos(bus_coords);
               actor_graphic->setZValue(PASSENGER_Z);
               actor_graphic->setScale(0.8);
           }
       }

}

void Tampere::takeScene(QGraphicsScene* sceneToTake){
    scene_=sceneToTake;
}

void Tampere::setArrowAngle(qreal angle){
    playerArrow_->setRotation(angle);
}

void Tampere::drawShot(){
    if(ammo_!=0){
        ammo_--;

        BetterActorItem* shot = new BetterActorItem(SHOT_IMAGE);
        scene_->addItem(shot);

        // Set shot to the right angle
        shot->setRotation(playerArrow_->rotation()+270);
        shot->setPos(player_->getPos().first+13,player_->getPos().second+13);
        shot->setZValue(BUS_Z);
        shots_.insert({shot, 1});
        ammoGraphic_->setImage(QImage(QString::fromStdString("../../etkot-software/Game/images/"+std::to_string(ammo_)+"ammo.png")));
        ammoGraphic_->update();
    }
}


void Tampere::moveShots(){
    for(auto shot: shots_){
        shots_.at(shot.first)++;
        qreal ang = (qDegreesToRadians(shot.first->rotation()));
        shot.first->rotation();
        shot.first->moveBy(qCos(ang)*6, qSin(ang)*6);
        checkShotCollison(shot.first,BUS_Z);

        if(shot.second >= SHOT_RANGE){
            scene_->removeItem(shot.first);
            delete shot.first;
            shots_.erase(shot.first);
        }
    }
}

void Tampere::reloadPressed()
{
    // If not already reloading and not max ammo, start reloading.
    if(reloadTime_==0&&ammo_!=AMMO){
        reloadTime_=80;
        qDebug() << "reloading....";
    }
}

void Tampere::pauseGame()
{
    if(!paused){paused=true;}
    else paused=false;
}


void Tampere::checkShotCollison(BetterActorItem* item, int Z_VALUE=BUS_Z){
    if (!item->collidingItems().empty()){
        for (auto collidingitem : scene_->collidingItems(item)){
          if(collidingitem->zValue()==BUS_Z&&Z_VALUE==BUS_Z){
                BetterActorItem* hit_nysse = static_cast<BetterActorItem*>(collidingitem);

            // Add explosion image to scene, and set destruct timer to 0.1 seconds
            BetterActorItem* hit_image = new BetterActorItem(EXPLOSION_IMAGE);
            hit_image->setTransform(collidingitem->transform());
            hit_image->setPos(hit_nysse->pos());
            hit_image->setZValue(BUS_Z+1);
            scene_->addItem(hit_image);
            hit_image->setDestructTimer(100);


            // Remove nysse if HP = 0. If not, lower hp by 1
            if(hit_nysse->getHealth()==0){
                for(auto it = nysseGraphicPairs_.begin(); it != nysseGraphicPairs_.end(); ++it)
                    if(it->second==collidingitem)
                       removeActor(it->first);

                stats.incrementScore(SCORE_FOR_BUS);
                stats.nyssesDestroyed += 1;
            }
            hit_nysse->lowerHealth();
            scene_->removeItem(item);
            shots_.erase(shots_.find(item));
            break;
        }

      // if Q pressed while on passengers(elons) remove them from scene and increase passengers_picked
      if(collidingitem->zValue()==PASSENGER_Z&&Z_VALUE==PASSENGER_Z&&passengers_picked_<PASSENGER_STORAGE){
          BetterActorItem* passenger = static_cast<BetterActorItem*>(passenger);
          passengers_picked_++;
          qDebug() <<passengers_picked_;
          for(auto it = passengerGraphicPairs_.begin(); it != passengerGraphicPairs_.end(); ++it)
              if(it->second==collidingitem)
                 removeActor(it->first);
      }

      // If Q pressed while on shuttle, add score and empty passengers to shuttle
      if(collidingitem->zValue()==SHUTTLE_Z && Z_VALUE==SHUTTLE_Z){
          stats.incrementScore(passengers_picked_*SCORE_FOR_PASSENGER);
          stats.elonsSaved += passengers_picked_;
          qDebug() << "ELONS LOADED";
          passengers_picked_=0;
          std::cout << "elonit turvas" << std::endl;

         }
      }
   }
}

void Tampere::pickPassengers()
{

    ray->setOpacity(255);
    QTimer::singleShot(150,[&](){ray->setOpacity(0);});

    checkShotCollison(ray, PASSENGER_Z);
    checkShotCollison(playerGraphic_, SHUTTLE_Z);
}

Tampere::~Tampere(){

};
