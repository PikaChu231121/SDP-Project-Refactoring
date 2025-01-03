// Refactored with Observer pattern
#ifndef _DATA_GAME_H_
#define _DATA_GAME_H_

#include "cocos2d.h"
#include <vector>
#include "GameObserver.h" // 包含观察者接口头文件

USING_NS_CC;

class gameData : public Scene
{
private:
    std::vector<GameObserver*> observers; // 观察者列表

public:
    int gameTurn;

    static gameData* createGameData();
    virtual bool init();
    void initGameStart();

    // 回合管理
    int getGameTurn() { return gameTurn; }
    void changeGameTurn();

    // 观察者管理
    void addObserver(GameObserver* observer);
    void removeObserver(GameObserver* observer);
    void notifyObservers();
};

#endif // !_DATA_GAME_H_
