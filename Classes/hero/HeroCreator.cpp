// Refactored with Factory Method Pattern
#include "HeroCreator.h"  
#include "hero.h"  
#include "tfns.h"  
#include "bqzs.h"  
#include "mlps.h"  
#include "qxsq.h"  
#include "wlshz.h"  
#include "yn.h"  
#include "ltzz.h"  
#include "snzx.h"  

bool HeroCreator::canPurchaseHero(int cost, const playerData& playerData) {
	return playerData.playerMoney >= cost
		&& playerData.waitingArray->num + playerData.battleArray->num < playerData.playerLevel + designedHeroNum;
}

bool HeroCreator::processHeroPurchase(playerData& playerData, int heroId, int cost)
{
	Hero* newHero = createHeroById(heroId);
	if (newHero) {
		ccArrayAppendObject(playerData.waitingArray, newHero);
		playerData.playerHaveNewHero = true;
		playerData.playerMoney -= cost;
		if (playerData.playerMoney < 0) {
			playerData.playerMoney = 0;
		}
		playerData.heroNum[heroId]++;
		return true;
	}
	return false;
}

void HeroCreator::addHeroToWaitingList(Hero* hero, playerData& playerData) {
	if (hero) {
		ccArrayAppendObject(playerData.waitingArray, hero);
		playerData.playerHaveNewHero = true;
	}
}

Hero* HeroCreator::upgradeHero(Hero* hero)
{
	if (hero) {
		hero->upLevel(hero);
		hero->setScale(0.35f);
	}
	return hero;
}

HeroCreator* HeroCreator::getCreatorById(int heroId) {
	switch (heroId) {
	case TFNS:
		return new TFNSCreator();
	case BQZS:
		return new BQZSCreator();
	case MLPS:
		return new MLPSCreator();
	case QXSQ:
		return new QXSQCreator();
	case WLSHZ:
		return new WLSHZCreator();
	case YN:
		return new YNCreator();
	case LTZZ:
		return new LTZZCreator();
	case SNZX:
		return new SNZXCreator();
	default:
		return nullptr;
	}
}

Hero* HeroCreator::createHeroById(int heroId)
{
	HeroCreator* creator = getCreatorById(heroId);
	if (creator) {
		Hero* hero = creator->createHero();
		delete creator;
		return hero;
	}
	return nullptr;
}

void HeroCreator::initializeHeroPosition(Hero* hero, const Point& position, bool isVisible) {
	if (hero) {
		hero->setPosition(position);
		hero->set(position);
		hero->setTempPosition();
		if (!isVisible) {
			hero->setPosition(10000, 10000);
			hero->set(10000, 10000);
		}
	}
}

float HeroCreator::calculateDistance(Hero* h1, Hero* h2)
{
	if (!h1 || !h2) return 0.0f;
	return sqrt(pow((h1->getPosition().x - h2->getPosition().x), 2)
		+ pow((h1->getPosition().y - h2->getPosition().y), 2));
}

float HeroCreator::calculateDistance(const Point& p1, const Point& p2)
{
	return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

void HeroCreator::transferToBattleArray(playerData& playerData)
{
	int availableSlots = playerData.playerLevel - playerData.battleArray->num;
	for (int i = 0; i < availableSlots && i < playerData.waitingArray->num; i++) {
		ccArrayAppendObject(playerData.battleArray, playerData.waitingArray->arr[i]);
		ccArrayRemoveObject(playerData.waitingArray, playerData.waitingArray->arr[i]);
	}
}

Hero* HeroCreator::initializeHero(Hero* hero) {
	hero->setScale(0.25f);
	hero->addChild(hero->createHealthBar(100));
	return hero;
}

Hero* TFNSCreator::createHero() {
	tfns* tfnsHero = new tfns();
	Hero* hero = tfnsHero->inittfns();
	hero->type = TFNS;
	return initializeHero(hero);
}

Hero* BQZSCreator::createHero() {
	bqzs* bqzsHero = new bqzs();
	Hero* hero = bqzsHero->initbqzs();
	hero->type = BQZS;
	return initializeHero(hero);
}

Hero* MLPSCreator::createHero() {
	mlps* mlpsHero = new mlps();
	Hero* hero = mlpsHero->initmlps();
	hero->type = MLPS;
	return initializeHero(hero);
}

Hero* QXSQCreator::createHero() {
	qxsq* qxsqHero = new qxsq();
	Hero* hero = qxsqHero->initqxsq();
	hero->type = QXSQ;
	return initializeHero(hero);
}

Hero* WLSHZCreator::createHero() {
	wlshz* wlshzHero = new wlshz();
	Hero* hero = wlshzHero->initwlshz();
	hero->type = WLSHZ;
	return initializeHero(hero);
}

Hero* YNCreator::createHero() {
	ynyn* ynHero = new ynyn();
	Hero* hero = ynHero->initynyn();
	hero->type = YN;
	return initializeHero(hero);
}

Hero* LTZZCreator::createHero() {
	ltzz* ltzzHero = new ltzz();
	Hero* hero = ltzzHero->initltzz();
	hero->type = LTZZ;
	return initializeHero(hero);
}

Hero* SNZXCreator::createHero() {
	snzx* snzxHero = new snzx();
	Hero* hero = snzxHero->initsnzx();
	hero->type = SNZX;
	return initializeHero(hero);
}