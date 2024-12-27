// Refactored with Factory Method Pattern
#pragma once
#include "cocos2d.h"
#include "./hero/hero.h"
#include "./hero/HeroCreator.h"
#include "./player/playerData.h"

class aiPlayer
{
private:
	static const int MAX_SHOP_SLOTS = 5;
public:
	Hero* soldHero();
	HeroCreator* getHeroCreator(int heroId) {
		return HeroCreator::getCreatorById(heroId);
	}
protected:
	void judgeGold();
	bool checkUpgrade();
	bool checkLimit();
	void judgeExp();
	bool checkHighGoldHero();
	bool aiBuy(int id);
	void refresh();
	void creatBattleArray();

	friend class sceneGame;

};
extern aiPlayer AIPlayer;