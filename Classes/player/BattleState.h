// Refactored with State Pattern
#ifndef _BATTLE_STATE_H_
#define _BATTLE_STATE_H_

#include "PlayerState.h"

// 战斗状态类
class BattleState : public PlayerState {
public:
    void updateMoneyAndExp(playerData* player) override;
    void calExp(playerData* player) override;
    void onEnter(playerData* player) override;
};

#endif // !_BATTLE_STATE_H_
