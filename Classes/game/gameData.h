// Refactored with Observer pattern
#ifndef _DATA_GAME_H_
#define _DATA_GAME_H_

#include "cocos2d.h"
#include <vector>
#include "GameObserver.h" // �����۲��߽ӿ�ͷ�ļ�

USING_NS_CC;

class gameData : public Scene
{
private:
    std::vector<GameObserver*> observers; // �۲����б�

public:
    int gameTurn;

    static gameData* createGameData();
    virtual bool init();
    void initGameStart();

    // �غϹ���
    int getGameTurn() { return gameTurn; }
    void changeGameTurn();

    // �۲��߹���
    void addObserver(GameObserver* observer);
    void removeObserver(GameObserver* observer);
    void notifyObservers();
};

#endif // !_DATA_GAME_H_
