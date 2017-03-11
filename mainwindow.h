#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void update();

    void on_startButton_clicked();

    void on_sliderWorkTime_valueChanged(int value);

    void on_sliderBreakTime_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    bool work = true;
    int time = 0;
    bool timerRunning = false;
};

#endif // MAINWINDOW_H
