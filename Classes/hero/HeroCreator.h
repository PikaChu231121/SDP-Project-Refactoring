#pragma once
#include "hero.h"
#include "tfns.h"
#include "bqzs.h"
#include "mlps.h"
#include "qxsq.h"
#include "wlshz.h"
#include "yn.h"
#include "ltzz.h"
#include "snzx.h"

class HeroCreator {
public:
	virtual Hero* createHero() = 0;
	virtual ~HeroCreator() {}
protected:
	Hero* initializeHero(Hero* hero) {
		hero->setScale(0.25f);
		hero->addChild(hero->createHealthBar(100));
		return hero;
	}
};

class TFNSCreator : public HeroCreator {
public:
	Hero* createHero() override {
		tfns* tfnsHero = new tfns();
		Hero* hero = tfnsHero->inittfns();
		hero->type = TFNS;
		return initializeHero(hero);
	}
};

class BQZSCreator : public HeroCreator {
public:
	Hero* createHero() override {
		bqzs* bqzsHero = new bqzs();
		Hero* hero = bqzsHero->initbqzs();
		hero->type = BQZS;
		return initializeHero(hero);
	}
};

class MLPSCreator : public HeroCreator {
public:
	Hero* createHero() override {
		mlps* mlpsHero = new mlps();
		Hero* hero = mlpsHero->initmlps();
		hero->type = MLPS;
		return initializeHero(hero);
	}
};

class QXSQCreator : public HeroCreator {
public:
	Hero* createHero() override {
		qxsq* qxsqHero = new qxsq();
		Hero* hero = qxsqHero->initqxsq();
		hero->type = QXSQ;
		return initializeHero(hero);
	}
};

class WLSHZCreator : public HeroCreator {
public:
	Hero* createHero() override {
		wlshz* wlshzHero = new wlshz();
		Hero* hero = wlshzHero->initwlshz();
		hero->type = WLSHZ;
		return initializeHero(hero);
	}
};

class YNCreator : public HeroCreator {
public:
	Hero* createHero() override {
		ynyn* ynHero = new ynyn();
		Hero* hero = ynHero->initynyn();
		hero->type = YN;
		return initializeHero(hero);
	}
};

class LTZZCreator : public HeroCreator {
public:
	Hero* createHero() override {
		ltzz* ltzzHero = new ltzz();
		Hero* hero = ltzzHero->initltzz();
		hero->type = LTZZ;
		return initializeHero(hero);
	}
};

class SNZXCreator : public HeroCreator {
public:
	Hero* createHero() override {
		snzx* snzxHero = new snzx();
		Hero* hero = snzxHero->initsnzx();
		hero->type = SNZX;
		return initializeHero(hero);
	}
};