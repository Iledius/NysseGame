#ifndef GAMEVIEW_HH
#define GAMEVIEW_HH


#include <QGraphicsView>
#include <QGraphicsScale>
#include <tampere.hh>

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = nullptr);
    GameView(QGraphicsScene *scene, QWidget *parent = nullptr);
    void takeCity(std::shared_ptr<Tampere> city);
private:
    std::shared_ptr<Tampere> city_;
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif
