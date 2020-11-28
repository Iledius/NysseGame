#include "startdialog.h"
#include "ui_startdialog.h"
#include <iostream>

startDialog::startDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startDialog)
{
    ui->setupUi(this);
}

startDialog::~startDialog()
{
    delete ui;
}

void startDialog::on_buttonBox_2_accepted()
{
    QString new_name = ui->nameEdit->text();
    std::cout << new_name.toStdString().length() << std::endl;
    if(new_name.toStdString().length() > 0)
    {
        player_name = new_name;
    }
    startDialog::accept();
}

void startDialog::on_buttonBox_2_rejected()
{
    startDialog::reject();
}

void startDialog::on_EasyRadioButton_clicked()
{
    std::cout << "Easy" << std::endl;
    setDifficulty(0);
}
void startDialog::on_mediumRadioButton_clicked()
{
    std::cout << "Medium" << std::endl;
    setDifficulty(1);
}

void startDialog::on_hardRadioButton_clicked()
{
    std::cout << "Hard" << std::endl;
    setDifficulty(2);
}

void startDialog::setDifficulty(int d)
{
    this->difficulty = d;
    std::cout << "dif set to " << this->difficulty << std::endl;
}
