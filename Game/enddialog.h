#ifndef ENDDIALOG_H
#define ENDDIALOG_H

#include <QDialog>

namespace Ui {
class endDialog;
}

class endDialog : public QDialog
{
    Q_OBJECT

public:
    void setElons(int s);
    void setNyssesDestoyed(int s);
    void setTotalScore(int s);
    void setNewHsLabel();
    void setPlayerName(QString name = "");
    void setDifficulty(int d);
    explicit endDialog(QWidget *parent = nullptr);
    ~endDialog();
    QString newPlayerName = "";
    int difficulty = 0;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_EasyRadioButton_clicked();

    void on_mediumRadioButton_clicked();

    void on_hardRadioButton_clicked();

private:
    Ui::endDialog *ui;
    int elonsSaved = 0;
    int nyssesDestroyed = 0;
    int totalScore = 0;
    QString playerName;
    bool isNewHs = false;
    //QString newPlayerName;
};

#endif // ENDDIALOG_H
