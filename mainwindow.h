#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QTimer>
#include "pcars/pcarsThread.h"
#include "gameData.h"
#include "serialcom/serialcom.h"


#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


private:
    int msSendIntervall;
    void refreshComPortList();


    loopThread *gameThread;


    QTimer *timerSerialLoop;

    QTimer m_timer;
    SerialCom *m_serialCom;
    Game *m_game;
    gameDataStruct m_gameData;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void sendGameData();
    void on_toolButton_clicked();

    void on_pushButton_connect_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
