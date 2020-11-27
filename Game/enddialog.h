#ifndef ENDDIALOG_H
#define ENDDIALOG_H

#include <QDialog>

namespace Ui {
class enddialog;
}

class enddialog : public QDialog
{
    Q_OBJECT

public:
    explicit enddialog(QWidget *parent = nullptr);
    ~enddialog();

private:
    Ui::enddialog *ui;
};

#endif // ENDDIALOG_H
