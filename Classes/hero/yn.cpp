﻿// Refactored with Delegation Pattern and Lazy Loading Pattern
#include "yn.h"
#include "ResourceManager.h"

ynyn::ynyn()
{
    name = "隐娘", skillname = "影遁忍术", advice = "中排";
    skillType = PHYSICS;
    blood = 550;
    maxBlood = 550;
    level = 1; 
    attack = 70; 
    protect = 20;
    magicPro = 20;
    state = ATTACK;
    attackDistance = 1;
    price = 3;
    speed = 0.6;
}

void ynyn::upLevel(Hero* yn1)
{
    yn1->blood = 990;
    yn1->maxBlood = 990;
    yn1->level = 2;
    yn1->attack = 126;
    setScale(0.35f);
}

Hero* ynyn::initynyn()
{
    Hero* yn = static_cast<Hero*>(ynyn::create());
    //my = yn;
    yn->picturename = "./hero/yn.png";
    yn->picturenum = 1;
    yn->heroAnimation(yn->picturename, yn->picturenum, yn, speed, -1);

    return yn;
}



void ynyn::Play()
{
    static Hero* enemy;
    static int attackNum = 0;
    auto lambdd = [=](float dt) {
        enemy = getEnemyByDistance(this, false, this->ofPlayer);
        if (enemy != nullptr)
            this->update(this, enemy, dt);
        this->healthBar->setPercentage(((double)blood / (double)maxBlood) * 100);
        isDead();
        };
    this->schedule(lambdd, 1 / 60.f, "ynynMove");
    attackNum = 0;
    static double add = (level == 1) ? 300 : 400;
    static double exp = (level == 1) ? 3 : 4;
    if (enemy != nullptr)
    {
        static int hurt = (int)(enemy->attackRate * attack);
        auto lambda = [=](float dt) {
            if (enemy != nullptr && state == ATTACK)
            {
                ynyn::ynynNormalAttack(enemy, attackNum, add, hurt);
                attackNum++;
            }
            };
        this->schedule(lambda, 1 / speed, "ynAttack");
      
        if (blue == blueMax) {
            auto lambdc = [=](float dt) {
                ynyn::swordwaive(this);
                if (enemy != nullptr)
                {
                    if (enemy->blood > (int)(0.5 * enemy->maxBlood)) {
                        enemy->blood -= (int)(hurt - (enemy->protect) + add);
                    }
                    else {
                        enemy->blood -= (int)(hurt - (enemy->protect) + add * exp);
                    }
                }
                };
            this->schedule(lambdc, 1 / speed, "ynNormalAttack");
            blue = 0;
        }
    }
}

void ynyn::ynynNormalAttack(Hero* enemy, const int attackNum, const double add, const int hurt)
{
    blue += 30;
    enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;
    if (enemy->blood < 0)
        enemy->blood = 0;
    goaway(enemy->getPosition(), this);
}

void ynyn::swordwaive(Hero* my)
{
    Sprite* sword = ResourceManager::CreateNewSprite("./hero/sword.png");
    my->addChild(sword, 3);
    sword->setScale(2.0f);
    sword->setPosition(Vec2(600, 300));
    
    auto waive = Sequence::create(
        RotateTo::create(1.0f, 90), 
        RotateTo::create(1.0f, 0),  
        CallFunc::create([sword]() {
            sword->removeFromParent();
            }),
        nullptr
    );
    
    sword->runAction(waive);
}

void ynyn::goaway(Point Pos, Hero* my) {
   
    double distance = 50; 
    auto run = Sequence::create(
        MoveTo::create(1.0f, Vec2(Pos.x + distance, Pos.y)),
        nullptr
    );
    my->runAction(run);
}
