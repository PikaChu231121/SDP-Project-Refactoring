// Refactored with State Pattern
#ifndef _NORMAL_STATE_H_
#define _NORMAL_STATE_H_

#include "PlayerState.h"

// 普通状态类
class NormalState : public PlayerState {
public:
    void updateMoneyAndExp(playerData* player) override;
    void calExp(playerData* player) override;
    void onEnter(playerData* player) override;
};

#endif // !_NORMAL_STATE_H_
