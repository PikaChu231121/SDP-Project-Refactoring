// Refactored with Composite Pattern

#pragma once
#include "AIComponent.h"
#include "./player/playerData.h"

class ShopRefresh : public AIComponent
{
public:
    void execute() override
    {
        int hero = 0;
        srand((unsigned int)time(0));
        for (int i = 0; i < 5; i++)
        {
            hero = rand() % 7 + 1;
            opPlayerData.heroForBuy[i].buy = false;
            opPlayerData.heroForBuy[i].id = heroList[hero - 1].id;
            opPlayerData.heroForBuy[i].picName = heroList[hero - 1].picName;
            opPlayerData.heroForBuy[i].cost = heroList[hero - 1].cost;
        }
        opPlayerData.deductMoney(2);
        if (opPlayerData.getPlayerMoney() < 0)
            opPlayerData.setPlayerMoney(0);
        CCLOG("ShopRefresh: Refreshed shop.");
    }
};