// Refactored with Observer pattern
#include "GameObserver.h"
#include "cocos2d.h"

USING_NS_CC;

class GameUI : public GameObserver
{
private:
    Label* turnLabel; // 显示回合数的标签

public:
    GameUI(Label* label) : turnLabel(label) {}

    // 接收通知，更新 UI
    void onGameTurnChanged(int newTurn) override
    {
        // 更新回合数显示
        std::string text = "Turn: " + std::to_string(newTurn);
        turnLabel->setString(text);

        // 显示提示信息
        if (newTurn % 2 == 1)
        {
            CCLOG("Player's turn");
        }
        else
        {
            CCLOG("AI's turn");
        }

    }
};

#endif // GAME_UI_H
