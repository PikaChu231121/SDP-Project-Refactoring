// Refactored with Delegation Pattern and Lazy Loading Pattern
#include "qxsq.h"


qxsq::qxsq()
{
    name = "��аʥǹ", skillname = "���׷��", advice = "����";
    skillType = PHYSICS;
    blood = 600;//��ǰѪ��
    maxBlood = 600;//����ֵ
    level = 1; //�ȼ�
    attack = 65; //������
    protect = 25;//����
    magicPro = 20;//ħ��
    state = ATTACK;//����״̬
    attackDistance = 100;//��������
    price = 2;//����
    speed = 0.65;//����
}

void qxsq::upLevel(Hero* qxsq1)
{
    qxsq1->blood = 1080;//��ǰѪ��
    qxsq1->maxBlood = 1080;//����ֵ
    qxsq1->level = 2; //�ȼ�
    qxsq1->attack = 117; //������
    setScale(0.35f);
}

void qxsq::Play()
{
    static Hero* enemy;
    static int attackNum = 0;
    auto lambdb = [=](float dt) {
        enemy = getEnemyByDistance(this, true, this->ofPlayer);//����
        if (enemy != nullptr)
            this->update(this, enemy, dt);
        this->healthBar->setPercentage(((double)blood / (double)maxBlood) * 100);
        isDead();
    };
    this->schedule(lambdb, 1 / 60.f, "qxsqMove");
    {
        attackNum = 0;//��������
        if(enemy!=nullptr)
        {
            static int hurt = (int)(attack * enemy->attackRate);//�˺�ֵ
            static int add = (level == 1 ? 125 : 250);
            {
                attackNum++;//�Ըõ��˵Ĺ�������+1
                auto lambda = [=](float dt) {
                    if (state == ATTACK) {
                        enemy->setColor(Color3B::GRAY);
                        qxsq::qxsqAttack(enemy, attackNum, hurt, add);
                        attackNum++;
                    }
                };
                this->schedule(lambda, 1 / speed, "qxsqAttack");
            }
        }
        }
}


Hero* qxsq::initqxsq()
{
    Hero* qxsq = static_cast<Hero*>(qxsq::create());
    qxsq->picturename = "./hero/qxsq.png";
    qxsq->picturenum = 1;
    qxsq->heroAnimation(qxsq->picturename, qxsq->picturenum, qxsq, speed, -1);
    return qxsq;
}




void qxsq::qxsqAttack(Hero* enemy, const int attackNum,const int hurt,const int add)
{
    blue += 50;
    if (blue == blueMax)//���������ͬһĿ�깥������
    {
        enemy->blood -= (hurt + add);//�����ʵ�˺�
        blue = 0;
    }
    else
    {
        enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;//���׵��������˺�
    }
    if (enemy->blood < 0)
        enemy->blood = 0;//�з�����
}


//void qxsq::shootbullet(string picturename, Point Pos, Hero* my)
//{
//    Sprite* bullet = ResourceManager::CreateNewSprite(picturename);
//    this->addChild(bullet);
//    bullet->setPosition(400,230);//??????????//���ľ��룿
//
//    auto move = MoveBy::create(1.f, Pos);
//    auto back = MoveTo::create(0.f, Vec2(40, 30));//??????????//���ľ��룿
//    auto appear = FadeIn::create(0.f);
//    auto disappear = FadeOut::create(0.f);
//
//    auto actionTo = Sequence::createWithTwoActions(appear, move);
//    auto actionBack = Sequence::createWithTwoActions(disappear, back);
//    auto all = Sequence::createWithTwoActions(actionTo, actionBack);
//    bullet->runAction(Repeat::create(all, 1));
//}