#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include "loopthread.h"
#include "serialcom/serialcom.h"

class SerialThread : public loopThread
{




private:
    SerialCom *comPort;
    QSerialPort *testPort;

    void processLoop();
    void processStopping();



public:
    SerialThread(QString portName);
    ~SerialThread();
};

#endif // SERIALTHREAD_H
