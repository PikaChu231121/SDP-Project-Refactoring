// Refactored with State Pattern
#include "BattleState.h"
#include "playerData.h"
#include "NormalState.h"
#include <iostream>

void BattleState::updateMoneyAndExp(playerData *player)
{
    player->addExp(5); // 战斗状态经验增长更快
    player->calExp();
}

void BattleState::calExp(playerData *player)
{
    // 调用普通状态的经验计算逻辑
    NormalState normalState;
    normalState.calExp(player);
}

void BattleState::onEnter(playerData *player)
{
    std::cout << "Player entered Battle State." << std::endl;
    player->playerHealth -= 10;
}
