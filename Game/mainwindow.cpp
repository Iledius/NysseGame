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

void MainWindow::on_pushButton_clicked()
{
    //aloita peli
}

void MainWindow::on_pushButton_5_clicked()
{
    //Näytä high scoret
}

void MainWindow::on_pushButton_6_clicked()
{
    //Avaa settings
}

void MainWindow::on_pushButton_7_clicked()
{
    //Poistu
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
}
