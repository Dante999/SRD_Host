#ifndef GAME_H
#define GAME_H

#include "gameData.h"

class Game
{
public:
    Game();
    virtual  ~Game();
    virtual bool writeDataTo(gameDataStruct *gameData) = 0;
    virtual bool isRunning() = 0;
};

#endif // GAME_H
