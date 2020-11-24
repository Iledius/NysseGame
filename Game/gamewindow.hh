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
#include "player.hh"
#include <QTimer>
#include "gameview.hh"
#include "statistics.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void movePlayer(int x_diff, int y_diff);
    void takeCity(std::shared_ptr<Tampere>& city);
    void drawStops();
    void setPlayerName(QString s);
    void setDifficulty(int d);
    void busHit();

    QString player_name;
    int difficulty;


private slots:
    void on_pushButton_released();
public Q_SLOTS:
    void advance();


private:
    Ui::GameWindow *ui;
    QGraphicsScene *scene;
    CourseSide::Logic* logic_;
    std::shared_ptr<Tampere> city_;
    QTimer *timer;
    GameView *gameView;
    std::vector<std::string> diffs;
    int score;
    std::shared_ptr<Player> player_;
    Statistics stats;
    void incrementScore();

};

#endif // GAMEWINDOW_HH
