// Refactored with Composite Pattern

#pragma once
#include "Observer/IObserver.h"
#include "player/playerData.h"

class AIComponent : public IObserver
{
protected:
    playerData &opPlayerData;
    playerData &myPlayerData;

public:
    AIComponent(playerData &op, playerData &my)
        : opPlayerData(op), myPlayerData(my) {}
    virtual ~AIComponent() = default;

    // 执行 AI 行为
    virtual void execute() = 0;

    // 实现观察者接口
    virtual void onNotify(const std::string &event, const playerData &data) {}
};