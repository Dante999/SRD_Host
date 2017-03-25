#ifndef SERIALCOM_H
#define SERIALCOM_H

#include <QtSerialPort/QSerialPort>
#include "stdint.h"

#define SYNC_BYTE       0x00

typedef struct
{
    uint8_t cmd;
    uint8_t length;
    char data[256];
} serialPackage;

enum serialCommands
{
    CMD_REQUEST = 1,
    CMD_ACK,
    CMD_GAMEDATA,
};



class SerialCom : public QSerialPort
{
    Q_OBJECT

private:

    enum parseState
    {
        WAITFOR_SYNC,
        WAITFOR_CMD,
        WAITFOR_LENGTH,
        WAITFOR_DATA
    };

    parseState m_state;
    serialPackage m_received;

    void parseSingleByte(char byte);

public:

    SerialCom(QString portName, qint32 baudRate = QSerialPort::Baud19200);
    void writeData(serialCommands cmd, uint8_t dataLength, const char *data);

signals:
    void parsingComplete(serialPackage dataPackage);

private slots:
    void parseAllReceivedBytes();

};

#endif // SERIALCOM_H
