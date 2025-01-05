// Refactored with Observer pattern
#ifndef _GAME_OBSERVER_H_
#define _GAME_OBSERVER_H_

class GameObserver
{
public:
    virtual void onGameTurnChanged(int turn) = 0;
    virtual ~GameObserver() = default;
};

#endif
