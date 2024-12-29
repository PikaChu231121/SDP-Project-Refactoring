#pragma once
// Refactored with Facade Pattern

#ifndef PLAYER_FACADE_H
#define PLAYER_FACADE_H

#include "player/playerData.h"
#include "hero/hero.h"
class PlayerFacade {
private:
    playerData* player;

public:
    explicit PlayerFacade(playerData* p) : player(p) {}

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

    playerData* getPlayerData() const {
        return player;
    }
};

#endif // PLAYER_FACADE_H

