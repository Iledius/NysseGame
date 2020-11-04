#ifndef TAMPERE_HH
#define TAMPERE_HH
#include "interfaces/icity.hh"
#include <QMainWindow>
#include "actors/nysse.hh"
#include "actors/passenger.hh"
#include "actors/stop.hh"

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
private:
    QTime time_;
    QMainWindow gamewindow_;
};

#endif // TAMPERE_HH
