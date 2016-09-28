#ifndef PCARSTHREAD_H
#define PCARSTHREAD_H

#include <QSharedMemory>

#include "../gameData.h"
#include "pcarssharedmemory.h"
#include "loopthread.h"




class PcarsThread : public loopThread
{

private:
    void processLoop();
    void processStopping();

    gameDataStruct *gameData;
    MemoryMap_Pcars *pcarsData;
    QSharedMemory sharedMemory;


public:

    PcarsThread(gameDataStruct *data);
    static bool isGameRunning();
};






#endif // PCARSTHREAD_H
