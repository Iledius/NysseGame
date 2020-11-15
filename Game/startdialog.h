#ifndef STARTDIALOG_H
#define STARTDIALOG_H
#include <QString>
#include <QDialog>

namespace Ui {
class startDialog;
}

class startDialog : public QDialog
{
    Q_OBJECT

public:
    explicit startDialog(QWidget *parent = nullptr);
    ~startDialog();
    QString player_name = "Tero Default";
    int difficulty = 0;

private slots:
    void on_buttonBox_2_accepted();

    void on_buttonBox_2_rejected();

    void on_EasyRadioButton_clicked();

    void on_mediumRadioButton_clicked();

    void on_hardRadioButton_clicked();

private:
    Ui::startDialog *ui;
};

#endif // STARTDIALOG_H
