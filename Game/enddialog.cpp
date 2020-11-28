#include "enddialog.h"
#include "ui_enddialog.h"
#include <iostream>

void endDialog::setElons(int s)
{
    this->elonsSaved = s;
    ui->elonCountLabel->setNum(s);
    //QString::number(elonsSaved)
}

void endDialog::setNyssesDestoyed(int s)
{
    this->nyssesDestroyed = s;
    ui->busCountLabel->setNum(s);
}

void endDialog::setTotalScore(int s)
{
    this->totalScore = s;
    ui->totalScoreLabel->setNum(s);
}

void endDialog::setNewHsLabel()
{
    QString str = "NEW HIGH SCORE!";
    ui->newHsLablel->setText(str);
}

endDialog::endDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::endDialog)
{
    ui->setupUi(this);
}

endDialog::~endDialog()
{
    delete ui;
}

void endDialog::on_buttonBox_accepted()
{
    //Aloita peli alusta
}

void endDialog::on_buttonBox_rejected()
{
    QApplication::exit();
}
