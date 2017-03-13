#ifndef PCARS_H
#define PCARS_H

#include <QSharedMemory>
#include "../game.h"
#include "../gameData.h"
#include "pcarssharedmemory.h"

class Pcars : public Game
{
private:
    MemoryMap_Pcars *m_pcarsData;
    QSharedMemory m_sharedMemory;

public:
    Pcars();

    bool writeDataTo(gameDataStruct *gameData);
    bool isRunning();


};

#endif // PCARS_H
