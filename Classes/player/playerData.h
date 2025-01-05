// Refactored with State Pattern
#ifndef _DATA_PLAYER_H_
#define _DATA_PLAYER_H_

#include "cocos2d.h"
#include "game/gameData.h"
#include "PlayerState.h"
#include "../aiPlayer/Observer/ISubject.h"
#include <vector>
#include "hero/heroInfo.h"

#define maxHeroNum 20 // 最大玩家英雄数量
USING_NS_CC;

// 定义事件类型
enum class PlayerEvent
{
	MONEY_CHANGED,
	EXP_CHANGED,
	LEVEL_CHANGED,
	HEALTH_CHANGED,
	STATE_CHANGED
};

class playerData : public cocos2d::Node, public ISubject
{
public:
	int playerHealth;
	int playerMaxHealth = 100;
	int playerLevel = 1;
	int playerExp = 0;
	int playerMoney = 10;
	int expToLevelUp = 2;

	PlayerState *currentState; // 当前状态
	std::vector<IObserver *> observers;

	struct HeroForBuy
	{
		int id;
		std::string picName;
		int cost;
		bool buy;
	};

	HeroForBuy heroForBuy[5]; // 添加这个成员变量

	playerData() : currentState(nullptr) {}
	~playerData()
	{
		if (currentState)
			delete currentState;
	}

	// 观察者模式方法实现
	void attach(IObserver *observer) override
	{
		observers.push_back(observer);
	}

	void detach(IObserver *observer) override
	{
		observers.erase(
			std::remove(observers.begin(), observers.end(), observer),
			observers.end());
	}

	void notify(const std::string &event) override
	{
		for (auto observer : observers)
		{
			observer->onNotify(event, *this);
		}
	}

	// Getter和Setter方法，增加通知功能
	int getPlayerMoney() const { return playerMoney; }
	void setPlayerMoney(int money)
	{
		if (playerMoney != money)
		{
			playerMoney = money;
			notify("MONEY_CHANGED");
		}
	}
	void deductMoney(int amount)
	{
		setPlayerMoney(playerMoney - amount);
	}
	int getPlayerExp() const { return playerExp; }
	void setPlayerExp(int exp)
	{
		if (playerExp != exp)
		{
			playerExp = exp;
			notify("EXP_CHANGED");
		}
	}
	void addExp(int amount)
	{
		setPlayerExp(playerExp + amount);
	}
	int getPlayerLevel() const { return playerLevel; }
	void setPlayerLevel(int level)
	{
		if (playerLevel != level)
		{
			playerLevel = level;
			notify("LEVEL_CHANGED");
		}
	}

	void playerHurt(int damageBlood)
	{
		playerHealth -= damageBlood;
		notify("HEALTH_CHANGED");
	}

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

	// 状态改变时通知观察者
	void changeState(PlayerState *newState)
	{
		if (currentState)
			delete currentState;
		currentState = newState;
		currentState->onEnter(this);
		notify("STATE_CHANGED");
	}

	// 获取当前状态（用于观察者）
	PlayerState *getCurrentState() const
	{
		return currentState;
	}

	// 获取其他属性（用于观察者）
	int getPlayerHealth() const { return playerHealth; }
	int getPlayerMaxHealth() const { return playerMaxHealth; }
	int getExpToLevelUp() const { return expToLevelUp; }

	void decreaseHealth(int amount) { playerHealth -= amount; }
};

#endif // !_DATA_PLAYER_H_
