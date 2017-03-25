#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "gameData.h"
#include "serialcom.h"
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
    void createGameObject();
    void deleteGameObject();
    bool createSerialPort();
    void deleteSerialPort();

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
