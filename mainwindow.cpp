#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QList>
#include <QDebug>



#define CONNECT     "Verbinden"
#define DISCONNECT  "Trennen"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    msSendIntervall = 500;
    ui->pushButton_connect->setText(CONNECT);

    refreshComPortList();

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(sendGameData()));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::sendGameData()
{    
    //m_serialCom->writeData(CMD_GAMEDATA, sizeof(m_gameData), (char*)&m_gameData);
    static int i = 0;

    qDebug() << "sending..." << i;
    i++;
}


void MainWindow::refreshComPortList()
{
    ui->comboBox_ComPorList->clear();                                           // delete all old ComPorts in the list

    QList<QSerialPortInfo> comPortList = QSerialPortInfo::availablePorts();     // get a list with all available ones

    for(int i=0; i < comPortList.count(); i++)                                  // add every ComPort to the comboBox
    {        
        ui->comboBox_ComPorList->addItem(comPortList.at(i).portName());
    }
}


void MainWindow::on_toolButton_clicked()
{
    refreshComPortList();
}


void MainWindow::on_pushButton_connect_clicked()
{
    if(ui->pushButton_connect->text() == CONNECT)
    {
        ui->pushButton_connect->setText(DISCONNECT);
        m_timer.start(msSendIntervall);
    }
    else
    {
        ui->pushButton_connect->setText(CONNECT);
        m_timer.stop();
    }
}
