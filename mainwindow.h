#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "pcars/pcarsThread.h"
#include "gameData.h"
#include "serialcom/serialcom.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


private:
    void refreshComPortList();

    bool connectedGame;
    bool connectedClient;


    loopThread *gameThread;
    loopThread *comThread;


    gameDataStruct gameData;
    //SerialCom *comPort;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:

    void on_pushButton_connectGame_clicked();    


    void on_pushButton_connectClient_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
