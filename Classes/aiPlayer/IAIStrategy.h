#pragma once
#include "player/playerData.h"

class IAIStrategy
{
public:
    virtual ~IAIStrategy() = default;
    virtual void execute(playerData &opPlayerData, playerData &myPlayerData) = 0;
};