// Refactored with Composite Pattern

#pragma once
#include "AIComponent.h"
#include "player/playerData.h"

class GoldManagement : public AIComponent
{
public:
    void execute() override
    {
        opPlayerData.setPlayerMoney(opPlayerData.getPlayerMoney() + 2);
    }
};
