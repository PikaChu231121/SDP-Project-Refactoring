// Refactored with Factory Method Pattern
// Refactored with Composite Pattern
// Refactored with ObserverPattern

#include "./aiPlayer/aiPlayer.h"

// 构造函数,初始化组合行为
aiPlayer::aiPlayer()
{

	CCLOG("aiPlayer constructor: Entered.\n");
	rootBehavior = new AIComposite();

	// 添加子行为到组合模式
	auto shopRefresh = new ShopRefresh();
	auto goldManagement = new GoldManagement();
	auto checkUpgrade = new CheckUpgrade();
	auto checkIfBuyExp = new CheckIfBuyExp();
	auto checkIfBuyHero = new CheckIfBuyHero();

	rootBehavior->add(shopRefresh);
	rootBehavior->add(goldManagement);
	rootBehavior->add(checkUpgrade);
	rootBehavior->add(checkIfBuyExp);
	rootBehavior->add(checkIfBuyHero);

	// 注册观察者
	opPlayerData.attach(shopRefresh);
	opPlayerData.attach(checkIfBuyExp);
	opPlayerData.attach(checkIfBuyHero);

	CCLOG("AIPlayer constructor executed.\n");
}

aiPlayer::~aiPlayer()
{
	if (rootBehavior)
	{
		delete rootBehavior;
		rootBehavior = nullptr;
	}
}

// 执行组合模式中的所有行为
void aiPlayer::executeAIComposite()
{
	if (rootBehavior)
	{
		CCLOG("Executing AI Composite...");
		rootBehavior->execute();
	}
	else
	{
		CCLOG("Error: rootBehavior is null.");
	}
}

// 转移英雄数据到战斗数组
void aiPlayer::creatBattleArray()
{
	HeroCreator::transferToBattleArray(opPlayerData);
}

// 出售英雄
Hero *aiPlayer::soldHero()
{
	Hero *sold = nullptr;
	for (int i = 0; i < opPlayerData.waitingArray->num; i++)
	{
		sold = static_cast<Hero *>(opPlayerData.waitingArray->arr[i]);
		if (sold->level == 1)
			return sold;
	}
	return sold;
}

aiPlayer AIPlayer;