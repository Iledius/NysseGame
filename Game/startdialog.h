#ifndef STARTDIALOG_H
#define STARTDIALOG_H
#include <QString>
#include <QDialog>

namespace Ui {
class StartDialog;
}

class StartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartDialog(QWidget *parent = nullptr);
    ~StartDialog();
    QString player_name = "Tero Default";
    int difficulty = 0;

private slots:
    void on_buttonBox_2_accepted();

    void on_buttonBox_2_rejected();

    void on_EasyRadioButton_clicked();

    void on_mediumRadioButton_clicked();

    void on_hardRadioButton_clicked();

    void setDifficulty(int d);

private:
    Ui::StartDialog *ui;
};

#endif // STARTDIALOG_H
