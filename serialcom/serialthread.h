#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include "loopthread.h"
#include "serialcom/serialcom.h"

class SerialThread : public loopThread
{




private:
    SerialCom *comPort;

    void processLoop();
    void processStopping();



public:
    SerialThread(QString portName);
};

#endif // SERIALTHREAD_H
