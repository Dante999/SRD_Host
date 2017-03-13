#ifndef GAME_H
#define GAME_H

#include "gameData.h"

enum gameStatus
{
    GAME_IS_OK,
    GAME_NOT_RUNNING,
    GAME_DATA_CANT_BE_READ
};


class Game
{
public:
    Game();
    virtual  ~Game();
    virtual bool writeDataTo(gameDataStruct *gameData) = 0;
    virtual bool isRunning() = 0;
};

#endif // GAME_H
