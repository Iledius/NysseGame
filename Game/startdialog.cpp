#include "startdialog.h"
#include "ui_startdialog.h"
#include <iostream>

StartDialog::StartDialog(QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::StartDialog)
{
    ui_->setupUi(this);
}

StartDialog::~StartDialog()
{
    delete ui_;
}

void StartDialog::on_buttonBox_2_accepted()
{
    QString new_name = ui_->nameEdit->text();
    if(new_name.toStdString().length() > 0)
    {
        player_name = new_name;
    }
    StartDialog::accept();
}

void StartDialog::on_buttonBox_2_rejected()
{
    StartDialog::reject();
}

void StartDialog::on_EasyRadioButton_clicked()
{
    setDifficulty(0);
}
void StartDialog::on_mediumRadioButton_clicked()
{
    setDifficulty(1);
}

void StartDialog::on_hardRadioButton_clicked()
{
    setDifficulty(2);
}

void StartDialog::setDifficulty(int d)
{
    this->difficulty = d;
}
