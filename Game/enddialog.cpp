#include "enddialog.h"
#include "ui_enddialog.h"

enddialog::enddialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::enddialog)
{
    ui->setupUi(this);
}

enddialog::~enddialog()
{
    delete ui;
}
