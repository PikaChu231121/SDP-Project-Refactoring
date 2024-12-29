#pragma once
// Refactored with Adapter Pattern

#ifndef HERO_ADAPTER_H
#define HERO_ADAPTER_H

#include "hero/heroCreator.h"
#include "player/playerData.h"

class HeroAdapter {
private:
    HeroCreator* creator;

public:
    explicit HeroAdapter(HeroCreator* c) : creator(c) {}

    bool canPurchaseHero(int cost, const playerData& player) {
        return HeroCreator::canPurchaseHero(cost, player);
    }

    Hero* createHero() {
        return creator->createHero();
    }

    void addHeroToWaitingList(Hero* hero, playerData& player) {
        creator->addHeroToWaitingList(hero, player);
    }

    static HeroCreator* getCreatorById(int heroId) {
        return HeroCreator::getCreatorById(heroId);
    }
};

#endif // HERO_ADAPTER_H
