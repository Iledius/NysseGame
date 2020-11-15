#ifndef GAMEWINDOW_HH
#define GAMEWINDOW_HH

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QImage>
#include "graphics/simpleactoritem.hh"
#include "core/logic.hh"
#include "core/location.hh"
#include "tampere.hh"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void drawNysses();
    void takeCity(std::shared_ptr<Tampere>& city);
    void drawStops();
    void setPlayerName(QString s);
    void setDifficulty(int d);
    QString player_name;
    int difficulty;


private:
    Ui::GameWindow *ui;
    QGraphicsScene *scene;
    CourseSide::Logic* logic_;
    std::shared_ptr<Tampere> city_;
    QGraphicsView *gameView;
};

#endif // GAMEWINDOW_HH
