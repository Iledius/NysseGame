#include "tampere.hh"
#include "iostream"
#include "statistics.h"

QImage BUS_IMAGE("../../etkot-software/Game/images/tank.png");
QImage PASSENGER_IMAGE("../../etkot-software/Game/images/elon.png");
QImage PLAYER_IMAGE("../../etkot-software/Game/images/ufo.png");
QImage SHOT_IMAGE("../../etkot-software/Game/images/laser2.png");
QImage SHUTTLE_IMAGE("../../etkot-software/Game/images/shuttle.png");
QImage EXPLOSION_IMAGE("../../etkot-software/Game/images/explosion.png");


QImage AMMO_6("../../etkot-software/Game/images/6ammo.png");

// Z-levels for different items:
const int PLAYER_Z = 6;
const int BUS_Z = 4;
const int PASSENGER_Z = 3;
const int SHUTTLE_Z = 2;

const int SHOT_RANGE = 100;
const int BUS_HEALTH = 2;
const float SPEED = 0.1;
int AMMO = 5;


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
}

void Tampere::setClock(QTime clock)
{
}

void Tampere::startGame()
{
    drawActors();

    // Player cannon visual
    playerArrow_ = scene_->addPolygon(player_->createArrow());
    scene_->addItem(playerGraphic_);

    // Ammo visuals
    scene_->addItem(ammoGraphic_);
    ammoGraphic_->setParentItem(playerGraphic_);
    ammoGraphic_->setScale(2);

    playerGraphic_->setPos(QPoint(250,250));
    playerArrow_->setPos(player_->getPos().first+16, player_->getPos().second+16);

    playerGraphic_->setZValue(PLAYER_Z);  // player always on top
    playerArrow_->setZValue(PLAYER_Z-1); // aimingarrow under player

    playerGraphic_->setScale(0.5);
    playerArrow_->setScale(3);


    scene_->addItem(shuttle_);
    shuttle_->setZValue(SHUTTLE_Z);
    shuttle_->setPos(300,0);
    shuttle_->setScale(0.5);
    ammo_ = AMMO;

    //jos halutaan hyödyntää drawNysses ja actorMoved funktioita pelaajalle
    //nysse_graphic_pairs.insert({player_,player_graphic_})
}

void Tampere::movePlayer()
{
    // max speed multiplier
    int ACC_LIMIT = 30;

    // moving with acceleration
    if(left==1) {player_->changePos(-SPEED*leftAcc,0);leftAcc=(leftAcc>ACC_LIMIT) ? leftAcc+1:ACC_LIMIT;}
    if(right==1) {player_->changePos(SPEED*rightAcc,0);rightAcc=(rightAcc>ACC_LIMIT) ? rightAcc+1:ACC_LIMIT;}
    if(up==1) {player_->changePos(0,-SPEED*upAcc);upAcc=(upAcc>ACC_LIMIT) ? upAcc+1:ACC_LIMIT;}
    if(down==1) {player_->changePos(0,SPEED*downAcc);downAcc=(downAcc>ACC_LIMIT) ? downAcc+1:ACC_LIMIT;}

   if(left==0&&leftAcc>0){
       leftAcc--;
       if(leftAcc>0){
           player_->changePos(-0.1*leftAcc,0);
       }else leftAcc=0;
   }
   if(right==0&&rightAcc>0){
       rightAcc--;
       if(rightAcc>0){
           player_->changePos(0.1*rightAcc,0);
       }else rightAcc=0;
   }
   if(up==0&&upAcc>0){
       upAcc--;
       if(upAcc>0){
           player_->changePos(0,-0.1*upAcc);
       }else upAcc=0;
   }
   if(down==0&&downAcc>0){
       downAcc--;
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
    playerArrow_->setPos(player_->getPos().first+16, player_->getPos().second+16);

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
    int x = newactor->giveLocation().giveX();
    int y = newactor->giveLocation().giveY();
    std::pair<int,int> coords = {x,y};
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

   // TODO: passengerit liikuu vaan kun ne on nyssessä, nyt kaatuu tällä koska ????

//   std::shared_ptr<CourseSide::Passenger> pass = std::dynamic_pointer_cast<CourseSide::Passenger>(actor);
//   if(pass){
//        if(findActor(pass->getVehicle())){
//            passenger_graphic_pairs.find(actor);
//            if(it != passenger_graphic_pairs.end()){
//                it->second->setPos(QPoint(actor.get()->giveLocation().giveX(),500-actor.get()->giveLocation().giveY()));
//            }
//        }
//   }

}

std::vector<std::shared_ptr<Interface::IActor>> Tampere::getNearbyActors(Interface::Location loc) const {
}

bool Tampere::isGameOver() const {
    return false;
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
            actor_graphic->setPos(bus_coords);
            actor_graphic->setScale(0.4);
            actor_graphic->setZValue(BUS_Z);
        }

        // If actor is a passenger
        else {  BetterActorItem* actor_graphic = new BetterActorItem(PASSENGER_IMAGE);
            passengerGraphicPairs_.insert({iactor, actor_graphic});
            scene_->addItem(actor_graphic);
            actor_graphic->setPos(bus_coords);
            actor_graphic->setZValue(PASSENGER_Z);
            actor_graphic->setScale(0.4);
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

        shot->setRotation(playerArrow_->rotation()+270);
        shot->setPos(player_->getPos().first+13,player_->getPos().second+13);
        shot->setScale(0.9);
        shot->setZValue(BUS_Z);
        shots_.insert({shot, 1});


        std::string imgname = "../../etkot-software/Game/images/"+std::to_string(ammo_)+"ammo.png";
        ammoGraphic_->setImage(QImage(QString::fromStdString(imgname)));
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
        shot.first->setOpacity(0.8);
        if(shot.second >= SHOT_RANGE){
            // TODO: korjaa panoksen poisto
            scene_->removeItem(shot.first);
            delete shot.first;
            shots_.erase(shot.first);
        }
    }
}

void Tampere::reloadPressed()
{
    reloadTime_=80;
    qDebug() << "reloading....";
}





void Tampere::checkShotCollison(BetterActorItem* item, int Z_VALUE=BUS_Z){
    if (!item->collidingItems().empty()){
        for (auto collidingitem : scene_->collidingItems(item)){
          if(collidingitem->zValue()==BUS_Z&&Z_VALUE==BUS_Z){
                BetterActorItem* hit_nysse = static_cast<BetterActorItem*>(collidingitem);


            BetterActorItem* hit_image = new BetterActorItem(EXPLOSION_IMAGE);
            hit_image->setTransform(collidingitem->transform());
            hit_image->setPos(hit_nysse->pos());
            hit_image->setZValue(BUS_Z+1);
            scene_->addItem(hit_image);

            hit_image->setDestructTimer(100);

            // Remove nysse if HP = 0
            if(hit_nysse->getHealth()==0){
                for(auto it = nysseGraphicPairs_.begin(); it != nysseGraphicPairs_.end(); ++it)
                    if(it->second==collidingitem)
                       removeActor(it->first);

                int scoreForBus = 10;
                stats.incrementScore(scoreForBus);
                QString asd = "Martti";
                //stats.saveScores(asd);
                score+=10;
            }
            hit_nysse->lowerHealth();
            scene_->removeItem(item);
            shots_.erase(shots_.find(item));
            break;
        }
      if(collidingitem->zValue()==PASSENGER_Z&&Z_VALUE==PASSENGER_Z&&passengers_picked_<10){
          BetterActorItem* passenger = static_cast<BetterActorItem*>(passenger);
          passengers_picked_++;
          qDebug() <<passengers_picked_;
          for(auto it = passengerGraphicPairs_.begin(); it != passengerGraphicPairs_.end(); ++it)
              if(it->second==collidingitem)
                 removeActor(it->first);
      }

      if(passengers_picked_>=10 && collidingitem->zValue()==SHUTTLE_Z && Z_VALUE==SHUTTLE_Z){
          stats.incrementScore(passengers_picked_*10);
          passengers_picked_=0;

         }
      }
   }
}

void Tampere::pickPassengers()
{
    checkShotCollison(playerGraphic_, PASSENGER_Z);
    checkShotCollison(playerGraphic_, SHUTTLE_Z);
}



Tampere::~Tampere(){

};
