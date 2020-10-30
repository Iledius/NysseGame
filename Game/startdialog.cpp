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
    std::string new_name = ui->nameEdit->text().toStdString();
    if(new_name.length() > 0)
    {
        player_name = new_name;
    }
    std::cout << player_name << std::endl;
    startDialog::accept();
}

void startDialog::on_buttonBox_2_rejected()
{

}
