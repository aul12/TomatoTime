#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QSystemTrayIcon>
#include <QMediaPlayer>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSettings settings("timeSettings", QSettings::NativeFormat, this);
    ui->sliderBreakTime->setValue(settings.value("breakTime", 5).toInt());
    ui->sliderWorkTime->setValue(settings.value("workTime", 25).toInt());

    ui->labelWorkTime->setText("Work Time: "+QString::number(ui->sliderWorkTime->value())+"min");
    ui->labelBreakTime->setText("Break Time: "+QString::number(ui->sliderBreakTime->value())+"min");

    ui->lcdNumber->display(settings.value("workTime", 25).toString());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update(){
    if(time > 0){
        time--;
    }else{
        if(work){
            time = ui->sliderBreakTime->value();
        }else{
            time = ui->sliderWorkTime->value();
        }
        work = !work;

        QSystemTrayIcon systemTrayIcon(this);
        systemTrayIcon.setVisible(true);
        systemTrayIcon.showMessage(work?"WORK":"BREAK", "", QSystemTrayIcon::Warning);

        QMediaPlayer *player = new QMediaPlayer(this, QMediaPlayer::LowLatency	);
        player->setMedia(QUrl::fromLocalFile("/home/paul/Programmieren/C++/QT/Timer/gong.wav"));
        player->setVolume(100);
        player->play();
    }

    ui->labelActivity->setText(work?"WORK!":"BREAK!");
    ui->lcdNumber->display(QString::number(time));
}

void MainWindow::on_startButton_clicked()
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    if(!timerRunning)
        timer->start(1000*60);

    work = true;
    time = ui->sliderWorkTime->value();

    ui->lcdNumber->display(time);
    ui->labelActivity->setText("WORK!");
}

void MainWindow::on_sliderWorkTime_valueChanged(int value)
{
    QSettings settings("timeSettings", QSettings::NativeFormat, this);
    settings.setValue("workTime", value);
    ui->labelWorkTime->setText("Work Time: "+QString::number(value)+"min");
}

void MainWindow::on_sliderBreakTime_valueChanged(int value)
{
    QSettings settings("timeSettings", QSettings::NativeFormat, this);
    settings.setValue("breakTime", value);
    ui->labelBreakTime->setText("Break Time: "+QString::number(value)+"min");
}
