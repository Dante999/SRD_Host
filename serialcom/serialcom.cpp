#include "serialcom.h"
#include <QDebug>








SerialCom::SerialCom(QString portName, QObject *parent, qint32 baudRate)
{
    qDebug() << "creating serialport: " << portName;
    qDebug() << "baudrate: " << baudRate;

    //sPort = new QSerialPort(portName, this);
    sPort.setParent(parent);
    sPort.setPortName(portName);
    sPort.setBaudRate(baudRate);
    sPort.setDataBits(QSerialPort::Data8);
    sPort.setParity(QSerialPort::NoParity);
    sPort.setStopBits(QSerialPort::OneStop);
    sPort.setFlowControl(QSerialPort::NoFlowControl);

    connect(&sPort, SIGNAL(readyRead()), this, SLOT(readData()));


}



void SerialCom::writeData(uint8_t cmd, uint8_t dataLength, const char *data)
{
    QByteArray syncByte(1, SYNC_BYTE);
    QByteArray cmdByte(1, cmd);
    QByteArray lengthByte(1, dataLength);

    qDebug() << "writeData-SerialPort";    

    sPort.write(syncByte);
    sPort.write(cmdByte);
    sPort.write(lengthByte);
    sPort.write(data, dataLength);
}

void SerialCom::open()
{

    qDebug() << "opening SerialPort...";


    try
    {
        //if(sPort == Q_NULLPTR) throw (QString)"serialPort is not defined!";
        if(sPort.isOpen())    throw (QString)"serialPort is already open!";

        if(sPort.open(QIODevice::ReadWrite) == true)
        {
            qDebug() << "serialPort opened successfully";
            return;
        }

        else
        {
            throw (QString)"unable to open SerialPort";
        }
    }

    catch(QString msg)
    {
        qDebug() << "[E] " << msg;
    }


}

void SerialCom::close()
{

    try
    {
        //if(sPort == Q_NULLPTR)
        //{
        //    throw (QString)"serialPort isn't initialized!";
        //}
        if(sPort.isOpen() == false)
        {
            throw (QString)"serialPort is already closed";
        }
        else
        {
            sPort.close();

            qDebug() << "serialPort closed!";
        }
    }
    catch(QString msg)
    {
        qDebug() << "[E] " << msg;
    }
}





void SerialCom::readData()
{
    while(sPort.bytesAvailable() > 0)
    {
        stateMachine();
    }
}



void SerialCom::stateMachine()
{
    static uint8_t iterator = 0;

    switch(state)
    {
        case WAITFOR_SYNC:
                    uint8_t byte;
                    sPort.read((char*)&byte, 1);

                    if( byte == SYNC_BYTE )
                    {
                        iterator = 0;
                        state = WAITFOR_CMD;
                    }
            break;

        case WAITFOR_CMD:
                sPort.read((char*)&received.cmd, 1);
                state = WAITFOR_LENGTH;
            break;

        case WAITFOR_LENGTH:
                sPort.read((char*)&received.length, 1);
                state = WAITFOR_DATA;
            break;

        case WAITFOR_DATA:

                if(iterator < received.length)
                {
                    sPort.read((char*)&received.data[iterator], 1);
                    iterator++;
                }

                if(iterator >= received.length)
                {
                    state = WAITFOR_SYNC;
                    iterator = 0;

                    emit dataReceived(received);

                    qDebug() << "Received data complete!";
                }

            break;
    }
}





