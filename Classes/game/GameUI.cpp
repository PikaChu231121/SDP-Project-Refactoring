// Refactored with Observer pattern
#include "GameUI.h"

void GameUI::onGameTurnChanged(int newTurn)
{
    std::string text = "Turn: " + std::to_string(newTurn);
    turnLabel->setString(text); // 更新显示回合数
}
