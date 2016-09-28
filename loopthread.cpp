#include "loopthread.h"

loopThread::loopThread(unsigned long ms)
{
    msDelay = ms;
    loop = true;
}

void loopThread::stopLoop()
{
    loop = false;
}

void loopThread::run()
{
    while(loop == true)
    {
        processLoop();
        msleep(msDelay);
    }

    processStopping();
}




