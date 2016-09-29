#include "serialthread.h"
#include <QDebug>
#include <QSerialPort>


SerialThread::SerialThread(QString portName) : loopThread(500)
{
    comPort = new SerialCom(portName);
    comPort->setParent(this);
    comPort->open();
}

SerialThread::~SerialThread()
{
    if(comPort->isOpen())
    {
        comPort->close();
    }

    delete comPort;
}



void SerialThread::processLoop()
{
    qDebug() << "Writing data...";
    //comPort->writeData(SYNC_BYTE, 2, "AB");
    comPort->writeCommand(CMD_ACK);
}

void SerialThread::processStopping()
{
    qDebug() << "Stopping serialThread";
    comPort->close();
    delete comPort;
}
