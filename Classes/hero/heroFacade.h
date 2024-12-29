#pragma once
// Refactored with Facade Pattern

#ifndef HERO_FACADE_H
#define HERO_FACADE_H

#include "hero/heroCreator.h"
#include "player/playerData.h"

class HeroFacade {
private:
    HeroCreator* creator;

public:
    explicit HeroFacade(HeroCreator* c) : creator(c) {}

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

#endif // HERO_FACADE_H
