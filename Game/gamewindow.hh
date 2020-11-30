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
#include "enddialog.h"

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
    void setPlayerName(QString s);
    void setDifficulty(int d);
    void endGame();
    QString player_name;
    int difficulty=0;

public Q_SLOTS:
    void advance();

private slots:
    void on_quitButton_pressed();

private:
    void centerCamera();
    void incrementTime();
    Ui::GameWindow *ui_;
    QGraphicsScene *scene_;
    CourseSide::Logic* logic_;
    std::shared_ptr<Tampere> city_;
    QTimer *timer_;
    GameView *gameView_;
    std::vector<std::string> diffs_;
    int score_ = 0;
    std::shared_ptr<Player> player_;
    int current_time_ = 0;
    bool paused_ = false;
    EndDialog endScreen_;

};

#endif // GAMEWINDOW_HH
