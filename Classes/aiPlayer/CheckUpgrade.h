// Refactored with Composite Pattern

#pragma once
#include "AIComponent.h"
#include "hero/HeroCreator.h"
#include "player/playerData.h"

class CheckUpgrade : public AIComponent
{
public:
    void execute() override
    {
        CCLOG("Executing CheckUpgrade logic...");
        // 使用 HeroCreator 的 canPurchaseHero 函数检查是否可以购买英雄
        HeroCreator::canPurchaseHero(0, opPlayerData);
    }

private:
    bool aiBuy(int id)
    {
        if (HeroCreator::canPurchaseHero(opPlayerData.heroForBuy[id].cost, opPlayerData))
        {
            return HeroCreator::processHeroPurchase(opPlayerData, opPlayerData.heroForBuy[id].id, opPlayerData.heroForBuy[id].cost);
        }
        return false;
    }
};