// Refactored with Observer pattern
#ifndef _DATA_GAME_H_
#define _DATA_GAME_H_

#include "cocos2d.h"
#include <vector>
#include "game/GameObserver.h" // Update the path if needed
#include "aiPlayer/Observer/IObserver.h"

USING_NS_CC;

class gameData : public cocos2d::Scene
{
private:
    std::vector<GameObserver *> observers; // ۲б

public:
    int gameTurn;

    CREATE_FUNC(gameData);
    static gameData *createGameData();
    virtual bool init();
    void initGameStart();

    // غϹ
    int getGameTurn() { return gameTurn; }
    void changeGameTurn();

    // ۲߹
    void addObserver(IObserver *observer);
    void removeObserver(IObserver *observer);
    void notifyObservers();
};

#endif // !_DATA_GAME_H_
