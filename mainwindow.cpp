#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QSharedMemory>
#include <QList>
#include <QDebug>

#include "pcars/pcarsworker.h"
#include "dashboard/dashboard.h"




#define CONNECT     "Verbinden"
#define DISCONNECT  "Trennen"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton_connectGame->setText(CONNECT);


    refreshComPortList();
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::refreshComPortList()
{
    ui->comboBox_ComPorList->clear();

    QList<QSerialPortInfo> comPortList = QSerialPortInfo::availablePorts();


    for(int i=0; i < comPortList.count(); i++)
    {
        ui->comboBox_ComPorList->addItem(comPortList.at(i).portName());
    }

}



void MainWindow::on_pushButton_connectGame_clicked()
{

    if(ui->pushButton_connectGame->text() == CONNECT)
    {
        if(PcarsWorker::isGameRunning() == true)
        {
            ui->label_gameStatus->setText("Verbunden");
            ui->pushButton_connectGame->setText(DISCONNECT);

            // start thread
            qDebug() << "starting thread";

            gameThread = new QThread;

            pworker = new PcarsWorker(gameThread, &clientData);

            pworker->moveToThread(gameThread);

            connect(gameThread, SIGNAL (started()), pworker, SLOT (process()));
            connect(pworker, SIGNAL (finished()), gameThread, SLOT (quit()));
            connect(pworker, SIGNAL (finished()), pworker, SLOT (deleteLater()));
            connect(gameThread, SIGNAL (finished()), gameThread, SLOT (deleteLater()));

            gameThread->start();





        }
        else
        {
            ui->label_gameStatus->setText("Fehler");
            ui->pushButton_connectGame->setText(CONNECT);
        }
    }

    else if(ui->pushButton_connectGame->text() == DISCONNECT)
    {
        ui->label_gameStatus->setText("Getrennt");
        ui->pushButton_connectGame->setText(CONNECT);


        qDebug() << "exiting thread";

        pworker->exitLoop();
        //delete readerThread;

    }

    else ui->pushButton_connectGame->setText(CONNECT);

}

void MainWindow::on_pushButton_clientDemo_clicked()
{
    dashboard = new Dashboard(&clientData);

    dashboard->resize(1024, 600);
    dashboard->show();

    dashboardThread = new DashboardThread(dashboard);

    connect(dashboard, SIGNAL(destroyed(QObject*)), this, SLOT(dashboardDemoClosed()));


    dashboardThread->start();
/*
    dashboardThread = new QThread;

    dworker = new DashboardWorker(dashboardThread, dashboard);

    dworker->moveToThread(dashboardThread);

    connect(dashboardThread, SIGNAL (started()), dworker, SLOT (process()));
    connect(dworker, SIGNAL (finished()), dashboardThread, SLOT (quit()));
    connect(dworker, SIGNAL (finished()), dworker, SLOT (deleteLater()));
    connect(dashboardThread, SIGNAL (finished()), dashboardThread, SLOT (deleteLater()));

    //dashboardThread->start();


*/



}

void MainWindow::dashboardDemoClosed()
{
    dashboardThread->stopLoop();

    delete dashboard;
    delete dashboardThread;
}
