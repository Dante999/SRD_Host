#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QSharedMemory>
#include <QList>
#include <QDebug>

#include "pcars/pcarsThread.h"
#include "serialcom/serialthread.h"





#define CONNECT     "Verbinden"
#define DISCONNECT  "Trennen"
#define CONNECTED   "Verbunden"
#define DISCONNECTED "Getrennt"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    connectedGame = false;
    connectedClient = false;




    ui->pushButton_connectGame->setText(CONNECT);
    ui->pushButton_connectClient->setText(CONNECT);

    ui->label_connectStatus->setText(DISCONNECTED);
    ui->label_gameStatus->setText(DISCONNECTED);


    //comPort = Q_NULLPTR;

    refreshComPortList();
}

MainWindow::~MainWindow()
{
    delete ui;
}



/**
 * @brief Searching for available ComPorts
 */
void MainWindow::refreshComPortList()
{
    QString portnames = "";

    qDebug() << "Looking for available ComPorts...";

    ui->comboBox_ComPorList->clear();                                           // delete all old ComPorts in the list

    QList<QSerialPortInfo> comPortList = QSerialPortInfo::availablePorts();     // get a list with all available ones


    for(int i=0; i < comPortList.count(); i++)                                  // add every ComPort to the comboBox
    {
        portnames += comPortList.at(i).portName() + " | ";
        ui->comboBox_ComPorList->addItem(comPortList.at(i).portName());
    }

    qDebug() << "Found: " << portnames;

}



void MainWindow::on_pushButton_connectGame_clicked()
{
    qDebug() << "------ connectGame clicked -----";


    if(connectedGame == false)
    {
        qDebug() << "currently not connected with game";
        ui->pushButton_connectGame->setText(CONNECT);
        ui->label_gameStatus->setText(DISCONNECT);

        if(PcarsThread::isGameRunning() == true)
        {
            qDebug() << "Game is running";
            ui->pushButton_connectGame->setText(DISCONNECT);
            ui->label_gameStatus->setText(CONNECTED);

            qDebug() << "starting gameThread";
            gameThread = new PcarsThread(&gameData);
            gameThread->start();
            connectedGame = true;
        }
        else
        {
            qDebug() << "Game is not running";
            ui->pushButton_connectGame->setText(CONNECT);
            ui->label_gameStatus->setText("Pcars nicht aktiv!");
        }
    }
    else
    {
        qDebug() << "currently connected with game";
        ui->pushButton_connectGame->setText(CONNECT);
        ui->label_gameStatus->setText(DISCONNECTED);

        qDebug() << "exiting gameThread";
        gameThread->stopLoop();

        while(gameThread->isRunning() == true)
        {
            // Wait for the Thread to end
        }

        delete gameThread;
        connectedGame = false;
    }
}





void MainWindow::on_pushButton_connectClient_clicked()
{
    QString portName = ui->comboBox_ComPorList->currentText();

    qDebug() << "------ connectClient clicked -----";

    if(connectedClient == false)
    {
        qDebug() << "currently not connected with client";

        qDebug() << "creating serialThread";
        comThread = new SerialThread(portName);
        comThread->start();

        ui->pushButton_connectClient->setText(DISCONNECT);
        ui->label_connectStatus->setText(CONNECTED);

        connectedClient = true;
    }
    else
    {
        comThread->stopLoop();

        while(comThread->isRunning() == true)
        {
            // Wait for the Thread to end
        }

        qDebug() << "deleting serialThread";
        delete comThread;



        connectedClient = false;
        ui->pushButton_connectClient->setText(CONNECT);
        ui->label_connectStatus->setText(DISCONNECTED);

    }





    //comThread = new SerialThread(comPort);
    //comThread->start();




}
