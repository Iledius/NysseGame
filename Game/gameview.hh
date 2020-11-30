#ifndef GAMEVIEW_HH
#define GAMEVIEW_HH


#include <QGraphicsView>
#include <QGraphicsScale>
#include <tampere.hh>
#include <iostream>
#include <QKeyEvent>

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = nullptr);
    GameView(QGraphicsScene *scene, QWidget *parent = nullptr);
    ~GameView();
    /**
     * @brief takeCity
     * takes city, on which it applies the effects from keypressevents.
     * @param city
     */
    void takeCity(std::shared_ptr<Tampere> city);

private:
    std::shared_ptr<Tampere> city_;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif
