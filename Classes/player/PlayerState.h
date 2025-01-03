#ifndef _PLAYER_STATE_H_
#define _PLAYER_STATE_H_

class playerData; // 前向声明

// 状态接口类
class PlayerState {
public:
    virtual ~PlayerState() {}
    virtual void updateMoneyAndExp(playerData* player) = 0; // 更新金钱和经验值
    virtual void calExp(playerData* player) = 0;           // 计算经验值
    virtual void onEnter(playerData* player) = 0;          // 状态切换时的进入逻辑
};

#endif // !_PLAYER_STATE_H_
