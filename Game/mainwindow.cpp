#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player_name = "Tero Default";
    difficulty = "easy";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_easyButton_toggled(bool checked)
{
    if (checked)
    {
        difficulty = "easy";
    }
}

void MainWindow::on_mediumButton_toggled(bool checked)
{
    if(checked)
    {
        difficulty = "medium";
    }
}


void MainWindow::on_hardButton_toggled(bool checked)
{
    if(checked)
    {
        difficulty = "hard";
    }
   //MainWindow::started = true;
}

void MainWindow::on_startButton_released()
{
    std::string new_name = ui->nameEdit->text().toStdString();
    if(new_name.length() > 0)
    {
        player_name = new_name;
    }
    started = true;
    std::cout << player_name << started << std::endl;

    MainWindow::started = true;
}
