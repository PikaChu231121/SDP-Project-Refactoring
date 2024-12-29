#pragma once
// Refactored with Adapter Pattern

#ifndef PLAYER_ADAPTER_H
#define PLAYER_ADAPTER_H

#include "player/playerData.h"
#include "hero/hero.h"
class PlayerAdapter {
private:
    playerData* player;

public:
    explicit PlayerAdapter(playerData* p) : player(p) {}

    int getPlayerMoney() const {
        return player->getPlayerMoney();
    }

    void deductMoney(int amount) {
        player->deductMoney(amount);
    }

    bool canAfford(int cost) const {
        return player->getPlayerMoney() >= cost;
    }

    heroInfo* getHeroForBuy(int index) {
        return &player->heroForBuy[index];
    }

    void addHeroToWaitingList(Hero* hero) {
        ccArrayAppendObject(player->waitingArray, hero);
    }
};

#endif // PLAYER_ADAPTER_H

