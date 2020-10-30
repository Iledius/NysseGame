#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class startDialog; }
QT_END_NAMESPACE

class startDialog : public QDialog
{
    Q_OBJECT

public:
    startDialog(QWidget *parent = nullptr);
    ~startDialog();

private slots:
    void on_startButton_released();

private:
    Ui::startDialog *ui;
};
#endif // STARTDIALOG_H
