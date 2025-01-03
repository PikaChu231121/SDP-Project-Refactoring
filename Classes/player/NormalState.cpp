// Refactored with State Pattern
#include "NormalState.h"
#include "playerData.h"
#include <iostream>

void NormalState::updateMoneyAndExp(playerData *player)
{
    player->setPlayerMoney(player->getPlayerMoney() + std::min(player->getPlayerMoney() / 10 + 5, 12));
    player->addExp(2);
    player->calExp();
}

void NormalState::calExp(playerData *player)
{
    int playerExp = player->getPlayerExp();
    for (int i = 0; i < 100; i++)
    {
        int thisLevelExp = i * i * i * 2 / 5 + 2 * i;
        int nextLevelExp = (i + 1) * (i + 1) * (i + 1) * 2 / 5 + 2 * (i + 1);
        if (playerExp >= thisLevelExp && playerExp < nextLevelExp)
        {
            player->playerLevel = i + 1;
            player->expToLevelUp = nextLevelExp;
            return;
        }
    }
}

void NormalState::onEnter(playerData *player)
{
    std::cout << "Player entered Normal State." << std::endl;
}
