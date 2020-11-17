#ifndef GAMEVIEW_HH
#define GAMEVIEW_HH


#include <QGraphicsView>
#include <QGraphicsScale>

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = nullptr);
    GameView(QGraphicsScene *scene, QWidget *parent = nullptr);
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif
