#pragma once
#include "player/playerData.h"

class IObserver
{
public:
    virtual ~IObserver() = default;
    virtual void onNotify(const std::string &event, const PlayerData &data) = 0;
};