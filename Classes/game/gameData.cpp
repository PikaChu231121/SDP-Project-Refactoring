// Refactored with Observer pattern
#include "game/gameData.h"
#include "hero.h"

const int designedHeroNum = 8;

gameData *globalGameData = gameData::createGameData();

gameData *gameData::createGameData()
{
    auto game = gameData::create();
    game->autorelease();
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

void gameData::addObserver(IObserver *observer)
{
    observers.push_back(observer);
}

void gameData::removeObserver(IObserver *observer)
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

struct hero
{
    int id;
    std::string picName;
    int cost;
    bool buy;
};

hero heroList[designedHeroNum] = {
    {1, "./hero/tfns.png", 1, false},
    {2, "./hero/bqzs.png", 1, false},
    {3, "./hero/mlps.png", 1, false},
    {4, "./hero/qxsq.png", 2, false},
    {5, "./hero/wlshz.png", 2, false},
    {6, "./hero/yn.png", 3, false},
    {7, "./hero/ltzz.png", 3, false},
    {8, "./hero/snzx.png", 4, false}};