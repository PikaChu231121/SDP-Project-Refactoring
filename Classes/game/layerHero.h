#ifndef _LAYERS_HERO_H_
#define _LAYERS_HERO_H_

#include "cocos2d.h"
#include "player/playerData.h"
#include "hero/allheros.h"
#include "hero/HeroCreator.h"
USING_NS_CC;
using namespace std;

class layerHero : public cocos2d::Layer
{
public:
	static layerHero* createLayerHero();
	CREATE_FUNC(layerHero);

	void playerArrayInit(ccArray* Array, int playerInfo);
	virtual bool init();
	void update(float dt);

	/****aiœ‡πÿ****/
	void aiShowWaitingArray();
	void aiShowBattleArray();

private:
	void heroUpgrade(playerData& pData);

	friend class sceneGame;
	float calDistance(Hero* h1, Hero* h2);
	float calDistance(Point p1, Point p2);
	void layerHero::collectUpgradeableHeroes(playerData& pData, int heroType,
		Hero* temp[3], ccArray* tempArray[3], int& count);
	void layerHero::collectFromArray(ccArray* array, int heroType,
		Hero* temp[3], ccArray* tempArray[3], int& count);
	bool layerHero::canUpgradeHeroes(Hero* temp[3], int count, int heroType);
	void layerHero::handleUpgradeProcess(playerData& pData, Hero* temp[3],
		ccArray* tempArray[3], Hero* upgrade_chess);
	HeroCreator* getHeroCreator(int heroId) {
		return HeroCreator::getCreatorById(heroId);
	}
};


#endif // !_LAYERS_HERO_H_
