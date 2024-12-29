// Refactored with Composite Pattern

#pragma once
#include "AIComponent.h"
#include "player/playerData.h"

class CheckIfBuyExp : public AIComponent
{
public:
    void execute() override
    {
        int expGap = myPlayerData.getPlayerExp() - opPlayerData.getPlayerExp();

        if (expGap > 5 && opPlayerData.getPlayerMoney() >= 4)
        {
            opPlayerData.setPlayerMoney(opPlayerData.getPlayerMoney() - 4);
            opPlayerData.setPlayerExp(opPlayerData.getPlayerExp() + 4);
            opPlayerData.calExp();
            expGap = myPlayerData.getPlayerExp() - opPlayerData.getPlayerExp();
            if (opPlayerData.getPlayerMoney() < 0)
                opPlayerData.setPlayerMoney(0);
        }
    }
};
