// Refactored with State Pattern
#include "playerData.h"
#include "NormalState.h"

void playerData::playerInit() {
    this->playerMaxHealth = 100;
    this->playerHealth = this->playerMaxHealth;
    this->playerLevel = 1;
    this->playerExp = 0;
    this->playerMoney = 10;
    this->expToLevelUp = 2;

    // 初始化状态为普通状态
    this->changeState(new NormalState());
}
