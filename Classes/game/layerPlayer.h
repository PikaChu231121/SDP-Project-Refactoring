// Refactored with Delegation Pattern and Lazy Loading Pattern
#ifndef _LAYERS_PLAYER_H_
#define _LAYERS_PLAYER_H_

#include "cocos2d.h"
#include <string>
#include "player/playerData.h"
#include "ResourceManager.h"
USING_NS_CC;
using namespace std;

class layerPlayer : public Layer
{
private:

public:
	static layerPlayer* createPlayer(string& name);
	virtual bool init();
	void update(float dt);
	void buyExp(cocos2d::Ref* pSender);

	/*************Player UIs***************/
	Label* Coins = Label::createWithTTF("Coins: "+to_string(myPlayerData.playerMoney), "fonts/betterFont.ttf", 22);
	Label* Levels = Label::createWithTTF("Lv: " + to_string(myPlayerData.playerLevel), "fonts/betterFont.ttf", 22);
	Label* playerHP = Label::createWithTTF(to_string(myPlayerData.playerHealth), "fonts/betterFont.ttf", 24);
	ProgressTimer* playerHPBar = ProgressTimer::create(ResourceManager::CreateNewSprite("./player/blood.png"));
	Sprite* playerHPBarBg = ResourceManager::CreateNewSprite("./player/bloodBg.png");
	ProgressTimer* playerExpBar = ProgressTimer::create(ResourceManager::CreateNewSprite("./player/greenBlood.png"));
	Sprite* playerExpBarBg = ResourceManager::CreateNewSprite("./player/bloodBg.png");

	/*************Player2/AI UIs***************/
	Label* opCoins = Label::createWithTTF("Coins: " + to_string(opPlayerData.playerMoney), "fonts/betterFont.ttf", 22);
	Label* opLevels = Label::createWithTTF("Lv: " + to_string(opPlayerData.playerLevel), "fonts/betterFont.ttf", 22);
	Label* opplayerHP = Label::createWithTTF(to_string(opPlayerData.playerHealth), "fonts/betterFont.ttf", 24);
	ProgressTimer* opplayerHPBar = ProgressTimer::create(ResourceManager::CreateNewSprite("./player/blood.png"));
	Sprite* opplayerHPBarBg = ResourceManager::CreateNewSprite("./player/bloodBg.png");
	ProgressTimer* opplayerExpBar = ProgressTimer::create(ResourceManager::CreateNewSprite("./player/greenBlood.png"));
	Sprite* opplayerExpBarBg = ResourceManager::CreateNewSprite("./player/bloodBg.png");


	CREATE_FUNC(layerPlayer);

};



#endif // !_LAYERS_PLAYER_H_