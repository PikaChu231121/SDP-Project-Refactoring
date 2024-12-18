#pragma once
#include "player/playerData.h"

class Hero;

class HeroCreator {
public:
	virtual Hero* createHero() = 0;
	virtual ~HeroCreator() {}
	// ºËÐÄÒµÎñÂß¼­
	bool canPurchaseHero(int cost, const playerData& playerData);

	bool hasSpaceForHero(const playerData& playerData);

	void addHeroToWaitingList(Hero* hero, playerData& playerData);

	static HeroCreator* getCreatorById(int heroId);

protected:
	Hero* initializeHero(Hero* hero);
};

class TFNSCreator : public HeroCreator {
public:
	Hero* createHero() override;
};

class BQZSCreator : public HeroCreator {
public:
	Hero* createHero() override;
}; 

class MLPSCreator : public HeroCreator {
public:
	Hero* createHero() override;
};

class QXSQCreator : public HeroCreator {
public:
	Hero* createHero() override;
};

class WLSHZCreator : public HeroCreator {
public:
	Hero* createHero() override;
};

class YNCreator : public HeroCreator {
public:
	Hero* createHero() override;
};

class LTZZCreator : public HeroCreator {
public:
	Hero* createHero() override;
};

class SNZXCreator : public HeroCreator {
public:
	Hero* createHero() override;
};