#include "tfns.h"


tfns::tfns()
{
    name = "�췣����", skillname = "ʥ�����",advice="����";
    skillType = PHYSICS;
    blood = 550;//��ǰѪ��
    maxBlood = 550;//����ֵ
    level = 1; //�ȼ�
    attack = 40; //������
    protect = 25;//����
    magicPro = 20;//ħ��
    state = ATTACK;//����״̬
    attackDistance = 50;//��������
    price = 1;//����
    speed = 0.7;//����
}

void tfns::upLevel(Hero* tfns1)
{
    tfns1->blood = 990;//��ǰѪ��
    tfns1->maxBlood = 990;//����ֵ
    tfns1->level = 2; //�ȼ�
    tfns1->attack = 72; //������
    setScale(0.35f);
}

void tfns::Play()
{
    static Hero* enemy;
    static int attackNum = 0;
        auto lambda = [=](float dt) {
            enemy = getEnemyByDistance(this, false, this->ofPlayer);
            if (enemy != nullptr)
                this->update(this, enemy, dt);
            this->healthBar->setPercentage(((double)blood / (double)maxBlood) * 100);
            isDead();
        };
        this->schedule(lambda, 1 / 60.f, "tfnsMove");
        auto lambdb = [=](float dt) {
            if (enemy != nullptr && state == ATTACK) {
                tfns::tfnsAttack(enemy, attackNum);
                attackNum++;//�Ըõ��˵Ĺ�������+1
            }
        };
        this->schedule(lambdb, 1 / speed, "tfnsAttack");
        auto lambdc = [=](float dt) {
            if (enemy != nullptr)
                enemy->setColor(Color3B::WHITE);
        };
        this->schedule(lambdc, speed, "tmp");
}

Hero* tfns::inittfns()
{
    Hero* tfns = tfns::create();
    tfns->picturename = "./hero/tfns.png";
    tfns->picturenum = 1;
    tfns->heroAnimation(tfns->picturename, tfns->picturenum, tfns, speed, -1);
    return tfns;
}


void tfns::tfnsAttack(Hero* enemy, const int attackNum)
{
    int hurt = (int)((level == 1 ? 1.08 : 1.12) * attack * enemy->attackRate);//�˺�ֵ
    enemy->setColor(Color3B::BLUE);
    blue += 30;
    if (blue == blueMax)//��������������
    {
        enemy->blood -= hurt;//�����ʵ�˺�
        blue = 0;
    }
    else
    {
        enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;//���׵��������˺�
    }
    if (enemy->blood < 0)
        enemy->blood = 0;//�з�����
}
