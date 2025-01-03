// Refactored with State Pattern
#ifndef _DATA_PLAYER_H_
#define _DATA_PLAYER_H_

#include "cocos2d.h"
#include "game/gameData.h"
#include "PlayerState.h"

#define maxHeroNum 20 // 最大玩家英雄数量
USING_NS_CC;

class playerData : public Ref
{
private:
	int playerMaxHealth = 100;
	int playerHealth = playerMaxHealth;
	int playerLevel = 1;
	int playerExp = 0;
	int playerMoney = 10;
	int expToLevelUp = 2;

	PlayerState *currentState; // 当前状态

public:
	playerData() : currentState(nullptr) {}
	~playerData()
	{
		if (currentState)
			delete currentState;
	}

	int getPlayerMoney() const { return playerMoney; }
	void setPlayerMoney(int money) { playerMoney = money; }
	void deductMoney(int amount) { playerMoney -= amount; }
	int getPlayerExp() const { return playerExp; }
	void setPlayerExp(int exp) { playerExp = exp; }
	void addExp(int amount) { playerExp += amount; }
	int getPlayerLevel() const { return playerLevel; }

	void playerHurt(int damageBlood) { this->playerHealth -= damageBlood; }

	void updateMoneyAndExp()
	{
		if (currentState)
			currentState->updateMoneyAndExp(this);
	}
	void calExp()
	{
		if (currentState)
			currentState->calExp(this);
	}

	void playerInit();

	void changeState(PlayerState *newState)
	{
		if (currentState)
			delete currentState;
		currentState = newState;
		currentState->onEnter(this);
	}
};

#endif // !_DATA_PLAYER_H_
