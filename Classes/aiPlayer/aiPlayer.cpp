// Refactored with Factory Method Pattern
#include "./aiPlayer/aiPlayer.h"

Hero* aiPlayer::soldHero()
{
	Hero* sold = nullptr;
	for (int i = 0; i < opPlayerData.waitingArray->num; i++)
	{
		sold = static_cast<Hero*> (opPlayerData.waitingArray->arr[i]);
		if (sold->level == 1)
			return sold;
	}
	return sold;
}

void aiPlayer::judgeGold()
{
	refresh();	// 刷新商店
	opPlayerData.playerMoney += 2;
	checkUpgrade();
	judgeExp();	// 买经验
	if (checkLimit() && checkHighGoldHero() && opPlayerData.playerMoney >= 2) // 不超过人数限制且购买了高费英雄
		refresh(); // 刷新商店
}

bool aiPlayer::checkUpgrade()
{
	// 使用 HeroCreator 的 canPurchaseHero 函数检查是否可以购买英雄
	if (!HeroCreator::canPurchaseHero(0, opPlayerData)) {
		return false;
	}

	for (int i = 1; i < maxHeroNum; i++) {
		if (opPlayerData.heroNum[i] % 3 == 2 && aiBuy(i)) {
			return true;
		}
	}
	return false;
}

bool aiPlayer::checkLimit()
{
	int totalHero = opPlayerData.waitingArray->num + opPlayerData.battleArray->num;
	if (totalHero <= opPlayerData.playerLevel && opPlayerData.playerMoney > 5)
	{
		int tmpMoney = 0, tmpId = -1;
		for (int i = 0; i < 5; i++)
		{
			if (opPlayerData.heroForBuy[i].cost >= tmpMoney && opPlayerData.heroForBuy[i].buy == false)
			{
				tmpMoney = opPlayerData.heroForBuy[i].cost;
				tmpId = i;
			}
		}
		if (tmpId != -1)
			if (aiBuy(tmpId))
				return true;
			else
				return false;
	}
	return false;
}

void aiPlayer::judgeExp()
{
	int expGap = myPlayerData.playerExp - opPlayerData.playerExp;
	//while (expGap > 5 && opPlayerData.playerMoney >= 4)
	//{
	if (expGap > 5 && opPlayerData.playerMoney >= 4) {
		opPlayerData.playerMoney -= 4;
		opPlayerData.playerExp += 4;
		opPlayerData.calExp();
		expGap = myPlayerData.playerExp - opPlayerData.playerExp;
		if (opPlayerData.playerMoney < 0)
			opPlayerData.playerMoney = 0;
	}
	//}
}

bool aiPlayer::checkHighGoldHero()
{
	int tmpMoney = 0, tmpId = -1;
	for (int i = 0; i < 5; i++)
	{
		if (opPlayerData.heroForBuy[i].cost >= tmpMoney && !opPlayerData.heroForBuy[i].buy)
		{
			tmpMoney = opPlayerData.heroForBuy[i].cost;
			tmpId = i;
		}
	}
	if (aiBuy(tmpId))
		return true;
	return false;
}

bool aiPlayer::aiBuy(int id)
{
	if (HeroCreator::canPurchaseHero(opPlayerData.heroForBuy[id].cost, opPlayerData)) {
		return HeroCreator::processHeroPurchase(opPlayerData, opPlayerData.heroForBuy[id].id, opPlayerData.heroForBuy[id].cost);
	}
	return false;
}

void aiPlayer::refresh()
{
	int hero = 0;
	srand((unsigned int)time(0));
	for (int i = 0; i < 5; i++)
	{
		hero = rand() % 7 + 1;
		opPlayerData.heroForBuy[i].buy = false;
		opPlayerData.heroForBuy[i].id = heroList[hero - 1].id;
		opPlayerData.heroForBuy[i].picName = heroList[hero - 1].picName;
		opPlayerData.heroForBuy[i].cost = heroList[hero - 1].cost;
	}
	opPlayerData.playerMoney -= 2;
	if (opPlayerData.playerMoney < 0)
		opPlayerData.playerMoney = 0;
}

void aiPlayer::creatBattleArray()
{
	HeroCreator::transferToBattleArray(opPlayerData);
}

aiPlayer AIPlayer;