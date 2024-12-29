// Refactored with Factory Method Pattern
// Refactored with Composite Pattern

#pragma once
#include "cocos2d.h"
#include "hero/hero.h"
#include "hero/HeroCreator.h"
#include "AIComposite.h"
#include "CheckIfBuyExp.h"
#include "CheckUpgrade.h"
#include "CheckIfBuyHero.h"
#include "GoldManagement.h"
#include "ShopRefresh.h"

class aiPlayer
{
private:
	static const int MAX_SHOP_SLOTS = 5;

	AIComposite *rootBehavior; // 组合行为的根节点

public:
	aiPlayer();
	~aiPlayer();

	// 执行所有组合的行为
	void executeAIComposite();

	void creatBattleArray();
	Hero *soldHero();

	friend class sceneGame;
};
extern aiPlayer AIPlayer;