#ifndef ENDDIALOG_H
#define ENDDIALOG_H

#include <QDialog>

namespace Ui {
class endDialog;
}

class EndDialog : public QDialog
{
    Q_OBJECT

public:
    void setElons(int s);
    void setNyssesDestoyed(int s);
    void setTotalScore(int s);
    void setNewHsLabel();
    void setPlayerName(QString name = "");
    void setDifficulty(int d);
    explicit EndDialog(QWidget *parent = nullptr);
    ~EndDialog();
    QString newPlayerName = "";
    int difficulty = 0;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_EasyRadioButton_clicked();

    void on_mediumRadioButton_clicked();

    void on_hardRadioButton_clicked();

private:
    Ui::endDialog *ui_;
    int elonsSaved_ = 0;
    int nyssesDestroyed_ = 0;
    int totalScore_ = 0;
    QString playerName_;
    bool isNewHs_ = false;
};

#endif // ENDDIALOG_H
