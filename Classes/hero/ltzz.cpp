#include "ltzz.h"

ltzz::ltzz()
{
    name = "����֮��", skillname = "����ŭצ", advice = "����";
    skillType = MAGIC;
    blood = 550;//��ǰѪ��
    maxBlood = 550;//����ֵ
    attack = 50; //������
    protect = 30;//����
    magicPro = 20;//ħ��
    state = ATTACK;//����״̬
    attackDistance = 1;//��������
    magicAmount = 75;//����ֵ
    price = 3;//����
    speed = 0.65;//����
}

Hero* ltzz::initltzz()
{
    Hero* ltzz = static_cast<Hero*>(ltzz::create());
    ltzz->picturename = "./hero/ltzz.png";
    ltzz->picturenum = 1;
    ltzz->heroAnimation(ltzz->picturename, ltzz->picturenum, ltzz, speed, -1);
    return ltzz;
}

void ltzz::upLevel(Hero* ltzz1)
{
    ltzz1->blood = 1350;//��ǰѪ��
    ltzz1->maxBlood = 1350;//����ֵ
    ltzz1->level = 2; //�ȼ�
    ltzz1->attack = 126; //������
    setScale(0.35f);
}

void ltzz::Play()
{
    static Hero* enemy, *tmpEnemy;
    auto lambda = [=](float dt) {
        enemy = getEnemyByDistance(this, false, this->ofPlayer);//����
        if (enemy != nullptr)
            this->update(this, enemy, dt);
        this->healthBar->setPercentage(((double)blood / (double)maxBlood) * 100);
        isDead();
    };
    this->schedule(lambda, 1 / 60.f, "ltzzMove");
    auto lambdc = [=](float dt) {
        if (enemy != nullptr && state == ATTACK)
            ltzz::ltzzAttack(enemy);
    };
    this->schedule(lambdc, 1 / speed, "ltzzAttack");
            //??????????//�Ƿ����ͬʱ���У�
    auto lambdb = [=](float dt) {
        for (int i = 0; i < 4; i++)//��฽�ӹ���4������
        {
            tmpEnemy = getEnemyByDistance(this, true, this->ofPlayer);//û�о�������
            if (tmpEnemy != nullptr)
                ltzz::ltzzAttack(tmpEnemy);
        }
    };
    this->schedule(lambdb, 20, "ltzzlightAttack");
}

void ltzz::ltzzAttack(Hero* enemy)
{
    int hurt = (int)((level == 1 ? 1.9 : 2) * attack * enemy->attackRate); // �˺�ֵ
    // ���ȶ��������ĵ��˽��й�����ħ���˺�
    lightning(enemy, hurt); // ������Ч
    enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect; // ������
    enemy->magicPro > magicAmount ? enemy->blood -= 0 : enemy->blood -= magicAmount - enemy->magicPro; // ħ���˺�
    if (enemy->blood < 0)
        enemy->blood = 0;
}