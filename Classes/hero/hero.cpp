﻿// Refactored with Factory Method Pattern
// Refactored with Delegation Pattern and Lazy Loading Pattern
#include "hero.h"
#include "tfns.h"
#include "mlps.h"
#include "wlshz.h"
#include "ltzz.h"
#include "bqzs.h"
#include "yn.h"
#include "qxsq.h"
#include "snzx.h"
#include "ResourceManager.h"

bool Hero::connection(const playerData& myPlayerData) 
{
    for (size_t i = 0; i < myPlayerData.battleArray->num; i++)
    {
        Hero* tmp = static_cast<Hero*>(myPlayerData.battleArray->arr[i]);
        if (tmp->name == "天罚弩神") 
        {
            for (size_t j = 0; j < myPlayerData.battleArray->num; j++) 
            {
                Hero* tmp2 = static_cast<Hero*>(myPlayerData.battleArray->arr[j]);
                if (tmp2->name == "未来守护者") 
                {
                    Sprite* connect1 = ResourceManager::CreateNewSprite("./hero/connect.png");
                    Sprite* connect2 = ResourceManager::CreateNewSprite("./hero/connect.png");
                    connect1->setScale(2.5f);
                    connect2->setScale(2.5f);
                    tmp->addChild(connect1);
                    tmp2->addChild(connect2);
                    connect1->setPosition(Vec2(600, 400));
                    connect2->setPosition(Vec2(600, 400));
                    auto lambda = [=](float dt) {
                        tmp2->attack += 10;
                    };
                    this->schedule(lambda, 1 / 60.f, "connection");
                    return true;
                }
            }
        }

    }
    return false;
}

Node* Hero::createHealthBar(double percentage)
{
    string backgroundTexture = "./hero/backgroundTexture.png";
    string foregroundTexture = "./hero/foregroundTexture.png";
    CCLOG("blood=%f", ((double)blood / (double)maxBlood) * 100);
    // 创建血条底部背景精灵
    Sprite* backgroundSprite = ResourceManager::CreateNewSprite(backgroundTexture);
    backgroundSprite->setScale(0.25f);

    // 创建血条前景精灵
    /*Sprite* foregroundSprite = ResourceManager::CreateNewSprite(foregroundTexture);
    foregroundSprite->setScale(0.25f);*/

    // 创建血条的 ProgressTimer
    healthBar = ProgressTimer::create(ResourceManager::CreateNewSprite(foregroundTexture));
    healthBar->setScale(0.25f);
    healthBar->setType(ProgressTimer::Type::BAR);
    healthBar->setMidpoint(Point(0, 1));
    healthBar->setBarChangeRate(Point(1, 0));
    healthBar->setPercentage(percentage);

    // 设置血条底部背景精灵和 ProgressTimer 的位置
    backgroundSprite->setPosition(Point(400, 500));
    healthBar->setPosition(Point(400,500));

    // 创建容器节点，将血条底部背景精灵和 ProgressTimer 添加到容器中
    Node* containerNode = Node::create();
    containerNode->addChild(backgroundSprite);
    containerNode->addChild(healthBar);

    return containerNode;
}

bool Hero::isDead()
{
    if (this->blood <= 0) {
        this->removeFromParentAndCleanup(true);
        return true;
    }
    return false;
}

void Hero::heroAnimation(string picturename, const int picturenum, Sprite* sprite, const double speed, const int loop)
{
    Animation* animation = Animation::create();
    const char* picname = picturename.c_str();

    for (int i = 0; i < picturenum; i++) {
        char key[32];
        sprintf(key, picname, i);
        animation->addSpriteFrameWithFile(key);
    }
    animation->setDelayPerUnit(speed); //设定速度
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(loop); //loop=-1,循环
    auto action = Animate::create(animation);
    //action->setTag(-2);
    //sp->runAction(animate);
    sprite->runAction(action);
}

Hero* Hero::getEnemyByDistance(Hero* myHero, bool mode, bool isMyHero)
{
    playerData opPlayer;
    if (isMyHero) {
        opPlayer = opPlayerData;
    }
    else {
        opPlayer = myPlayerData;
    }
    Point enemyPosition(0, 0);
    Point myPosition = myHero->getPosition();
    float opDistance = mode ? -999999 : 999999;
    Hero* enemy = NULL;
    for (int i = 0; i < opPlayer.battleArray->num; i++)
    {
        auto tempEnemy = opPlayer.battleArray->arr[i];
        Point tempEnemyPosition = (static_cast<Hero*>(tempEnemy))->getPosition();
        float tempDistance = sqrt((tempEnemyPosition.x - myPosition.x) * (tempEnemyPosition.x - myPosition.x) +
            (tempEnemyPosition.y - myPosition.y) * (tempEnemyPosition.y - myPosition.y));
        if (mode)
        {
            // 最远的敌人
            if (tempDistance > opDistance && tempDistance > 0 && !((static_cast<Hero*>(tempEnemy))->isDead()))
            {
                opDistance = tempDistance;
                enemyPosition = tempEnemyPosition;
                enemy = static_cast<Hero*>(tempEnemy);
            }
        }
        else
        {
            // 最近的敌人
            if (tempDistance < opDistance && tempDistance > 0 && !((static_cast<Hero*>(tempEnemy))->isDead()))
            {
                opDistance = tempDistance;
                enemyPosition = tempEnemyPosition;
                enemy = static_cast<Hero*>(tempEnemy);
            }
        }
    }

    return enemy;
}

void Hero::update(Hero* my, Hero* enemy, float dt)
{
    Vec2 currentPosition = my->getPosition();
    Vec2 targetPosition = enemy->getPosition(); // 获取目标位置
    // 设置最小的分离距离
    float separationDistance = 100.0f;
    // 设置移动速度
     // 计算移动方向向量
    Vec2 direction = targetPosition - currentPosition;
    direction.normalize();
    float movespeed = 100.0f;
    // 计算两个角色之间的距离
    float distance = currentPosition.distance(targetPosition);
    if (distance < separationDistance)
    {
        // 计算分离向量
        Vec2 separationVector = currentPosition - targetPosition;
        separationVector.normalize();

        // 根据分离向量调整移动方向
        direction += separationVector;
        direction.normalize();
    }
    // 根据方向向量移动英雄
    Vec2 newPosition = currentPosition + direction * movespeed * dt;
    my->setPosition(newPosition);
}

bool Hero::isWin(playerData* myPlayer, playerData* opPlayer)
{
    if (myPlayer->battleArray->num == 0 || opPlayer->battleArray->num == 0)
        return true;
    else
        return false;
    return false;
}

bool Hero::isInAttackRange(Hero* myHero, Hero* enemyHero)
{
    Point myPosition = myHero->getPosition();
    Point enemyPosition = enemyHero->getPosition();
    float distance = sqrt((myPosition.x - enemyPosition.x) * (myPosition.x - enemyPosition.x) +
        (myPosition.y - enemyPosition.y) * (myPosition.y - enemyPosition.y));
    if (distance <= myHero->attackDistance)
        return true;
    return false;
}


void Dizzy(Hero* enemy)
{
    //英雄变成灰色
    enemy->setColor(Color3B::GRAY);
    // 创建精灵
    Sprite* dizzy = ResourceManager::CreateNewSprite("./hero/dizzy.png");
    enemy->addChild(dizzy);
    dizzy->setPosition(Vec2(500, 400));

    // 设置消失动作
    auto removeSprite = CallFunc::create([dizzy]() {
        dizzy->removeFromParentAndCleanup(true);
        });
    Sequence* sequence = Sequence::create(DelayTime::create(3.f), removeSprite, nullptr);
    dizzy->runAction(sequence);
    //禁用英雄的动作
    enemy->stopAllActions();
    auto lambda = [=](float dt) {
        // 在这里添加恢复正常状态的操作，将英雄的颜色恢复为原始颜色
        enemy->setColor(Color3B::WHITE);
        // 重新启用英雄的动作
        enemy->heroAnimation(enemy->picturename, enemy->picturenum, enemy, enemy->speed, -1);
    };
    enemy->scheduleOnce(lambda, 3, "dizzyKey");
}

void sevInjure(Hero* enemy)
{
    //英雄变成红色
    enemy->setColor(Color3B::RED);
    // 禁用英雄
    enemy->movespeed = enemy->movespeed * 0.5;
    enemy->speed = enemy->speed * 0.5;
    auto lambda = [=](float dt) {
        // 在这里添加恢复正常状态的操作，将英雄的颜色恢复为原始颜色
        enemy->setColor(Color3B::WHITE);
        // 重新启用英雄
        enemy->movespeed = enemy->movespeed * 2;
        enemy->speed = enemy->speed * 2;
    };
    enemy->scheduleOnce(lambda, 2, "sevInjureKey");
}

void proProtect(Hero* my)
{
    my->protect = (int)(my->protect * 1.2);
}


void relProtect(Hero* enemy)
{
    enemy->setColor(Color3B::GREEN);
    enemy->protect = (int)(enemy->protect * 0.8);
    auto lambda = [=](float dt) {
        // 在这里添加恢复正常状态的操作，将英雄的颜色恢复为原始颜色
        enemy->setColor(Color3B::WHITE);
        enemy->protect = (int)(enemy->protect * 1.25);
    };
    enemy->scheduleOnce(lambda, 2, "relProtect");
}


void immune(Hero* enemy)
{
    double Rate = enemy->attackRate;
    enemy->attackRate = 0;
    auto lambda = [=](float dt) {
        enemy->attackRate = Rate;
    };
    enemy->scheduleOnce(lambda, 2, "immuneKey");
}

void bomb(Hero* enemy, int attack)
{
    // 创建精灵
    Sprite* bomb = ResourceManager::CreateNewSprite("./hero/bomb.png");
    enemy->addChild(bomb);
    bomb->setPosition(Vec2(500, 400));

    // 设置消失动作
    auto removeSprite = CallFunc::create([bomb]() {
        bomb->removeFromParentAndCleanup(true);
        });
    Sequence* sequence = Sequence::create(DelayTime::create(1.f), removeSprite, nullptr);
    bomb->runAction(sequence);
    auto lambda = [=](float dt) {
        enemy->blood -= (int)(attack * enemy->attackRate * 1.5);
    };
    enemy->scheduleOnce(lambda, 2, "bombKey");
}

void lightning(Hero* enemy, const int hurt)
{
    // 创建精灵
    Sprite* light = ResourceManager::CreateNewSprite("./hero/lightning.png");
    enemy->addChild(light);
    light->setPosition(Vec2(500, 400));

    // 设置消失动作
    auto removeSprite = CallFunc::create([light]() {
        light->removeFromParentAndCleanup(true);
        });
    Sequence* sequence = Sequence::create(DelayTime::create(1.f), removeSprite, nullptr);
    light->runAction(sequence);
    enemy->setColor(Color3B::GRAY);
    enemy->blood -= hurt * 0.9;//造成额外90%的伤害
}
void Hero::recover()
{
    blood = maxBlood;
    blue = 0;
    healthBar->setPercentage(100.f);
    if (this->level > 1) {
        setScale(0.35f);
    }
}