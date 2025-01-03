// Refactored with Observer pattern
#include "game/gameData.h"

gameData* globalGameData = gameData::createGameData();

gameData* gameData::createGameData()
{
    auto game = gameData::create();
    game->retain();
    return game;
}

bool gameData::init()
{
    if (!Scene::init())
    {
        return false;
    }

    gameTurn = 0; // 初始化回合数
    return true;
}

void gameData::initGameStart()
{
    gameTurn = 0;
}

void gameData::changeGameTurn()
{
    gameTurn++;
    notifyObservers(); // 通知所有观察者
}

void gameData::addObserver(GameObserver* observer)
{
    observers.push_back(observer);
}

void gameData::removeObserver(GameObserver* observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void gameData::notifyObservers()
{
    for (auto observer : observers)
    {
        observer->onGameTurnChanged(gameTurn); // 通知每个观察者
    }
}

heroInfo heroList[designedHeroNum] = {
	{ 1, "./hero/tfns.png", 1, false },
	{ 2, "./hero/bqzs.png", 1, false },
	{ 3, "./hero/mlps.png", 1, false },
	{ 4, "./hero/qxsq.png", 2, false },
	{ 5, "./hero/wlshz.png", 2, false },
	{ 6, "./hero/yn.png", 3, false },
	{ 7, "./hero/ltzz.png", 3, false },
	{ 8, "./hero/snzx.png", 4, false }
};