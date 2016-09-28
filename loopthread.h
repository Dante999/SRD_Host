#ifndef GAMEDATAHARVESTER_H
#define GAMEDATAHARVESTER_H

#include <QThread>


class loopThread : public QThread
{

protected:
    void run();
    virtual void processLoop() = 0;
    virtual void processStopping() = 0;

private:
    bool loop;
    unsigned long msDelay;

public:
    loopThread(unsigned long ms);

    void stopLoop();
};

#endif // GAMEDATAHARVESTER_H
