#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::string difficulty;
    std::string player_name;
    bool started = false;

private slots:
    
    void on_easyButton_toggled(bool checked);

    void on_mediumButton_toggled(bool checked);

    void on_hardButton_toggled(bool checked);

private slots:


    void on_startButton_released();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
