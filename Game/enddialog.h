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
    explicit endDialog(QWidget *parent = nullptr);
    ~endDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

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
