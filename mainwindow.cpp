#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QList>
#include <QDebug>

#include "pcars/pcars.h"


#define CONNECT     "Verbinden"
#define DISCONNECT  "Trennen"


/*******************************************************************************
 * @brief   constructor
 *
 * initializes all members of the class.
 *
 * @param   *parent     parent of the QMainWindow
 *
 * @return  none
 *
*******************************************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    msSendIntervall = 200;
    m_game = Q_NULLPTR;
    m_serialCom = Q_NULLPTR;
    ui->pushButton_connect->setText(CONNECT);

    refreshComPortList();

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(sendGameData()));
}


/*******************************************************************************
 * @brief   destructor of the class
 *
 * little cleanup
 *
 * @param   none
 *
 * @return  none
 *
*******************************************************************************/
MainWindow::~MainWindow()
{
    delete ui;
}


/*******************************************************************************
 * @brief   slot which sends the gameData structure to the client
 *
 * @param   none
 *
 * @return  none
 *
*******************************************************************************/
void MainWindow::sendGameData()
{    
    m_game->writeDataTo(&m_gameData);
    m_serialCom->writeData(CMD_GAMEDATA, sizeof(m_gameData), (char*)&m_gameData);
}


/*******************************************************************************
 * @brief   refreshes the list of available ComPorts
 *
 * searches for all available ComPorts an shows them in the comboBox of the
 * gui
 *
 * @param   none
 *
 * @return  none
 *
*******************************************************************************/
void MainWindow::refreshComPortList()
{
    ui->comboBox_ComPorList->clear();                                           // delete all old ComPorts in the list

    QList<QSerialPortInfo> comPortList = QSerialPortInfo::availablePorts();     // get a list with all available ones

    for(int i=0; i < comPortList.count(); i++)                                  // add every ComPort to the comboBox
    {        
        ui->comboBox_ComPorList->addItem(comPortList.at(i).portName());
    }
}


/*******************************************************************************
 * @brief   creates a object of the selected game
 *
 * @param   none
 *
 * @return  none
 *
*******************************************************************************/
void MainWindow::createGameObject()
{
    if(m_game == Q_NULLPTR)
    {
        m_game = new Pcars();
    }
}


/*******************************************************************************
 * @brief   deletes the game object
 *
 * @param   none
 *
 * @return  none
 *
*******************************************************************************/
void MainWindow::deleteGameObject()
{
    if(m_game != Q_NULLPTR)
    {
        delete m_game;
        m_game = Q_NULLPTR;
    }
}


/*******************************************************************************
 * @brief   creates the selected ComPort
 *
 * creates a ComPort depending on the selected one in the comboBox of the gui.
 *
 * @param   none
 *
 * @return  true    ComPort successfully opened
 *          false   ComPort opening failed
 *
*******************************************************************************/
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


/*******************************************************************************
 * @brief   deletes the created ComPort object
 *
 * @param   none
 *
 * @return  none
 *
*******************************************************************************/
void MainWindow::deleteSerialPort()
{
    if(m_serialCom != Q_NULLPTR)
    {
        m_serialCom->close();
        delete m_serialCom;
        m_serialCom = Q_NULLPTR;
    }
}


/*******************************************************************************
 * @brief   slot which is called when refresh ComPorts is clicked
 *
 * @param   none
 *
 * @return  none
 *
*******************************************************************************/
void MainWindow::on_toolButton_clicked()
{
    refreshComPortList();
}


/*******************************************************************************
 * @brief   slot which is called when connect button is clicked
 *
 * @param   none
 *
 * @return  none
 *
*******************************************************************************/
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
