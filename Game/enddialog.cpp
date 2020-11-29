#include "enddialog.h"
#include "ui_enddialog.h"
#include <iostream>

void endDialog::setElons(int s)
{
    this->elonsSaved_ = s;
    ui_->elonCountLabel->setNum(s);
}

void endDialog::setNyssesDestoyed(int s)
{
    this->nyssesDestroyed_ = s;
    ui_->busCountLabel->setNum(s);
}

void endDialog::setTotalScore(int s)
{
    this->totalScore_ = s;
    ui_->totalScoreLabel->setNum(s);
}

void endDialog::setNewHsLabel()
{
    QString str = "NEW HIGH SCORE!";
    ui_->newHsLablel->setText(str);
}

void endDialog::setPlayerName(QString name)
{
    newPlayerName = name;
}

void endDialog::setDifficulty(int d)
{
    this->difficulty = d;
}

endDialog::endDialog(QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::endDialog)
{
    ui_->setupUi(this);
}

endDialog::~endDialog()
{
    delete ui_;
}

void endDialog::on_buttonBox_accepted()
{
    QString newName = ui_->newPlayerNameLine->text();
    if(newName.length() > 0)
    {
        newPlayerName = ui_->newPlayerNameLine->text();
    }
}

void endDialog::on_buttonBox_rejected()
{
    QApplication::exit();
}

void endDialog::on_EasyRadioButton_clicked()
{
    setDifficulty(0);
}
void endDialog::on_mediumRadioButton_clicked()
{
    setDifficulty(1);
}

void endDialog::on_hardRadioButton_clicked()
{
    setDifficulty(2);
}

