#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QList>
#include <QDebug>

#include "pcars/pcars.h"


#define CONNECT     "Verbinden"
#define DISCONNECT  "Trennen"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    msSendIntervall = 500;
    m_game = Q_NULLPTR;
    m_serialCom = Q_NULLPTR;
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
    m_game->writeDataTo(&m_gameData);
    m_serialCom->writeData(CMD_GAMEDATA, sizeof(m_gameData), (char*)&m_gameData);
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

void MainWindow::createGameObject()
{
    if(m_game == Q_NULLPTR)
    {
        m_game = new Pcars();
    }
}

void MainWindow::deleteGameObject()
{
    if(m_game != Q_NULLPTR)
    {
        delete m_game;
        m_game = Q_NULLPTR;
    }
}

bool MainWindow::createSerialPort()
{
    if(m_serialCom == Q_NULLPTR)
    {
        QString portName = "";

        portName = ui->comboBox_ComPorList->currentText();
        m_serialCom = new SerialCom(portName);
        m_serialCom->open(QIODevice::ReadWrite);

        return m_serialCom->isOpen();
    }

    return false;

}

void MainWindow::deleteSerialPort()
{
    if(m_serialCom != Q_NULLPTR)
    {
        m_serialCom->close();
        delete m_serialCom;
        m_serialCom = Q_NULLPTR;
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
        if(!createSerialPort())
        {
            deleteSerialPort();
        }
        else
        {
            createGameObject();
            ui->pushButton_connect->setText(DISCONNECT);
            m_timer.start(msSendIntervall);
        }
    }
    else
    {
        m_timer.stop();

        deleteGameObject();
        deleteSerialPort();
        ui->pushButton_connect->setText(CONNECT);
    }
}
