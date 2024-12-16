#include "snzx.h"
//ȫ��̹��
snzx::snzx()
{
    name = "��֮��", skillname = "�Ű���", advice = "����";
    skillType = PHYSICS;
    blood = 800;//��ǰѪ��
    maxBlood = 800;//����ֵ
    level = 1; //�ȼ�
    attack = 50; //������
    protect = 30;//����
    magicPro = 20;//ħ��
    state = ATTACK;//����״̬
    attackDistance = 2;//��������
    price = 4;//����
    speed = 0.7;//����
}

void snzx::upLevel(Hero* snzx1)
{
    snzx1->blood = 1440;//��ǰѪ��
    snzx1->maxBlood = 1440;//����ֵ
    snzx1->level = 2; //�ȼ�
    snzx1->attack = 90; //������
    setScale(0.35f);
}

void snzx::Play()
{
    static Hero* enemy;
    static int attackNum = 0;
    {
        auto lambda = [=](float dt) {
            enemy = getEnemyByDistance(this, false, this->ofPlayer);//����
            if (enemy != nullptr)
                this->update(this, enemy, dt);
            this->healthBar->setPercentage(((double)blood / (double)maxBlood) * 100);
            isDead();
        };
        this->schedule(lambda, 1 / 60.f, "snzxMove");
        attackNum = 0;//��������
        if (enemy != nullptr) {
            static int hurt = (int)(attack * enemy->attackRate);//�˺�ֵ
            static int add = (level == 1 ? 50 : 100);
            {
                if (state == ATTACK) {
                    attackNum++;//�Ըõ��˵Ĺ�������+1
                    auto lambda = [=](float dt) {
                        if (enemy != nullptr)
                            snzx::snzxAttack(enemy, attackNum, hurt, add);
                    };
                    this->schedule(lambda, 1 / speed, "snzxAttack");
                }

            }
        }
    }
    //this->removeFromParent();
}


Hero* snzx::initsnzx()
{
    Hero* snzx = static_cast<Hero*>(snzx::create());
    snzx->picturename = "./hero/snzx.png";
    snzx->picturenum = 1;
    snzx->heroAnimation(snzx->picturename, snzx->picturenum, snzx, speed, -1);
    return snzx;
}


void snzx::snzxAttack(Hero* enemy, const int attackNum,const int hurt, const int add)
{
    blue += 30;
    int extra = (level == 1) ? 200 : 300;
    if (blue == blueMax)//���������ͬһĿ�깥��5
    {
        this->blood += ((level == 1) ? 250 : 450);
        Hero* enemynow = getEnemyByDistance(this,  true,this->ofPlayer);//������Զ
        if (enemynow == nullptr)
            return;
        moveToFar(enemynow);
        Dizzy(enemynow);
        enemynow->blood -= (hurt + extra + add - enemynow->protect);
        blue = 0;
    }
    else
    {
        enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;//���׵��������˺�
    }
    if (enemy->blood < 0)
        enemy->blood = 0;//�з�����
}

//��ʱû��ʵ�֣����Բο��Ѿ�ʵ���˵�����
void snzx::moveToFar( Hero* enemy)
{
    // ��ȡ���˵�λ����Ϣ
    cocos2d::Vec2 enemyPosition = enemy->getPosition();

    // ��ȡ�����λ����Ϣ
    cocos2d::Vec2 selfPosition = getPosition();

    // ������˺�����֮��ľ���
    float distance = enemyPosition.distance(selfPosition);

    // ȷ�����������
    if (distance > 0)
    {
        // ����Ŀ��λ���ڵ�������λ��
        cocos2d::Vec2 targetPosition = enemyPosition - (enemyPosition - selfPosition);

        // ʹ��Cocosϵͳ��������ɫ�ƶ���Ŀ��λ��
        runAction(cocos2d::MoveTo::create(0.f, targetPosition));
    }
}