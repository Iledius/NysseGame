#include "enddialog.h"
#include "ui_enddialog.h"
#include <iostream>

EndDialog::EndDialog(QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::endDialog)
{
    ui_->setupUi(this);
}

EndDialog::~EndDialog()
{
    delete ui_;
}

void EndDialog::setElons(int s)
{
    this->elonsSaved_ = s;
    ui_->elonCountLabel->setNum(s);
}

void EndDialog::setNyssesDestoyed(int s)
{
    this->nyssesDestroyed_ = s;
    ui_->busCountLabel->setNum(s);
}

void EndDialog::setTotalScore(int s)
{
    this->totalScore_ = s;
    ui_->totalScoreLabel->setNum(s);
}

void EndDialog::setNewHsLabel()
{
    QString str = "NEW HIGH SCORE!";
    ui_->newHsLablel->setText(str);
}

void EndDialog::setPlayerName(QString name)
{
    newPlayerName = name;
}

void EndDialog::setDifficulty(int d)
{
    this->difficulty = d;
}

void EndDialog::on_buttonBox_accepted()
{
    QString newName = ui_->newPlayerNameLine->text();
    if(newName.length() > 0)
    {
        newPlayerName = ui_->newPlayerNameLine->text();
    }
}

void EndDialog::on_buttonBox_rejected()
{
    QApplication::exit();
}

void EndDialog::on_EasyRadioButton_clicked()
{
    setDifficulty(0);
}
void EndDialog::on_mediumRadioButton_clicked()
{
    setDifficulty(1);
}

void EndDialog::on_hardRadioButton_clicked()
{
    setDifficulty(2);
}

