// Refactored with Composite Pattern

#pragma once
#include "AIComponent.h"
#include "player/playerData.h"
#include "hero/HeroCreator.h"

class CheckIfBuyHero : public AIComponent
{
public:
    void execute() override
    {
        if (checkLimit() && checkHighGoldHero() && opPlayerData.getPlayerMoney() >= 2) // 不超过人数限制且购买了高费英雄
            refresh();                                                                 // 刷新商店
    }

private:
    bool checkLimit()
    {
        int totalHero = opPlayerData.waitingArray->num + opPlayerData.battleArray->num;
        if (totalHero <= opPlayerData.getPlayerLevel() && opPlayerData.getPlayerMoney() > 5)
        {
            int tmpMoney = 0, tmpId = -1;
            for (int i = 0; i < 5; i++)
            {
                if (opPlayerData.heroForBuy[i].cost >= tmpMoney && opPlayerData.heroForBuy[i].buy == false)
                {
                    tmpMoney = opPlayerData.heroForBuy[i].cost;
                    tmpId = i;
                }
            }
            if (tmpId != -1)
                if (aiBuy(tmpId))
                    return true;
                else
                    return false;
        }
        return false;
    }

    bool checkHighGoldHero()
    {
        int tmpMoney = 0, tmpId = -1;
        for (int i = 0; i < 5; i++)
        {
            if (opPlayerData.heroForBuy[i].cost >= tmpMoney && !opPlayerData.heroForBuy[i].buy)
            {
                tmpMoney = opPlayerData.heroForBuy[i].cost;
                tmpId = i;
            }
        }
        if (aiBuy(tmpId))
            return true;
        return false;
    }

    bool aiBuy(int id)
    {
        if (HeroCreator::canPurchaseHero(opPlayerData.heroForBuy[id].cost, opPlayerData))
        {
            return HeroCreator::processHeroPurchase(opPlayerData, opPlayerData.heroForBuy[id].id, opPlayerData.heroForBuy[id].cost);
        }
        return false;
    }

    void refresh()
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
        opPlayerData.setPlayerMoney(opPlayerData.getPlayerMoney() - 2);
        if (opPlayerData.getPlayerMoney() < 0)
            opPlayerData.setPlayerMoney(0);
    }
};
