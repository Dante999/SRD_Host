#include "serialthread.h"
#include <QDebug>


SerialThread::SerialThread(QString portName) : loopThread(500)
{
    comPort = new SerialCom(portName, this);
    comPort->setParent(this);
    comPort->open();

}



void SerialThread::processLoop()
{
    qDebug() << "Writing data...";
    comPort->writeData(SYNC_BYTE, 2, "AB");
}

void SerialThread::processStopping()
{
    qDebug() << "Stopping serialThread";
    comPort->close();
    delete comPort;
}
