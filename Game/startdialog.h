#ifndef STARTDIALOG_H
#define STARTDIALOG_H
#include <QDialog>
#include <QDebug>

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
    int difficulty;

private slots:
    /**
     * @brief on_buttonBox_2_accepted
     * Accept button, starts game
     */
    void on_buttonBox_2_accepted();

    /**
     * @brief on_buttonBox_2_rejected
     * Reject button, closes
     */
    void on_buttonBox_2_rejected();

    void on_EasyRadioButton_clicked();

    void on_mediumRadioButton_clicked();

    void on_hardRadioButton_clicked();

    void setDifficulty(int d);

private:
    Ui::StartDialog *ui_;
};

#endif // STARTDIALOG_H
