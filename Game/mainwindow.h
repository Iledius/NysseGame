#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::string difficulty;
    std::string player_name;


private slots:
    void on_pushButton_clicked();
    
    void on_pushButton_5_clicked();
    
    void on_pushButton_6_clicked();
    
    void on_pushButton_7_clicked();
    
    void on_easyButton_toggled(bool checked);

    void on_mediumButton_toggled(bool checked);

    void on_hardButton_toggled(bool checked);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
