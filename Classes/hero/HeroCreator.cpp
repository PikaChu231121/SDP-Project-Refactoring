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
	return playerData.playerMoney >= cost;
}

bool HeroCreator::hasSpaceForHero(const playerData& playerData) {
	int sum = 0;
	for (int i = 0; i < CHESS_IN_A_ROW; i++) {
		sum += haveChess[0][i];
	}
	return sum < designedHeroNum;
}

void HeroCreator::addHeroToWaitingList(Hero* hero, playerData& playerData) {
	if (hero) {
		ccArrayAppendObject(playerData.waitingArray, hero);
		playerData.playerHaveNewHero = true;
	}
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