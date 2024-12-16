#include "wlshz.h"

wlshz::wlshz()
{
    name = "δ���ػ���", skillname = "��������", advice = "ǰ��";
    skillType = TANK;
    blood = 700;//��ǰѪ��
    maxBlood = 700;//����ֵ
    level = 1; //�ȼ�
    attack = 60; //������
    protect = 35;//����
    magicPro = 20;//ħ��
    state = ATTACK;//����״̬
    magicAmount = 50;//����ֵ
    attackDistance = 100;//��������
    price = 2;//����
    speed = 0.65;//����
}

void wlshz::upLevel(Hero* wlshz1)
{
    wlshz1->blood = 1260;//��ǰѪ��
    wlshz1->maxBlood = 1260;//����ֵ
    wlshz1->level = 2; //�ȼ�
    wlshz1->attack = 108; //������
    setScale(0.35f);
}

void wlshz::Play()
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
    this->schedule(lambda, 1 / 60.f, "wlshzMove");
    auto lambdb = [=](float dt) {
        if (enemy != nullptr && state == ATTACK)
            wlshz::wlshzAttack(enemy);
    };
    this->schedule(lambdb, 1 / speed, "wlshzAttack");
}

Hero* wlshz::initwlshz()
{
    Hero* tfns = wlshz::create();
    tfns->picturename = "./hero/wlshz.png";
    tfns->picturenum = 1;
    tfns->heroAnimation(tfns->picturename, tfns->picturenum, tfns, speed, -1);
    return tfns;
}


void wlshz::wlshzAttack(Hero* enemy)
{
    int hurt = (int)((level == 1 ? 2.00 : 3.50) * attack * enemy->attackRate);//�˺�ֵ
    blue += 30;
    if (blue == blueMax)//��������������
    {
        enemy->blood -= hurt;//�����ʵ�˺�
        Dizzy(enemy);
        blue = 0;
    }
    else
    {
        enemy->magicPro > magicAmount ? enemy->blood -= 0 : enemy->blood -= magicAmount - enemy->magicPro;//ħ������
    }
    if (enemy->blood < 0)
        enemy->blood = 0;//�з�����
}