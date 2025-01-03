// Refactored with Observer pattern
#ifndef GAME_OBSERVER_H
#define GAME_OBSERVER_H

class GameObserver
{
public:
    virtual ~GameObserver() {}
    virtual void onGameTurnChanged(int newTurn) = 0; // 回合变化事件
};

#endif // GAME_OBSERVER_H
