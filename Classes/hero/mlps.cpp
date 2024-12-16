#include "mlps.h"

mlps::mlps()
{
    name = "��������", skillname = "��ը��", advice = "����";
    skillType = MAGIC;
    blood = 500;//��ǰѪ��
    maxBlood = 500;//����ֵ
    protect = 20;//����
    magicPro = 20;//ħ��
    state = ATTACK;//����״̬
    magicAmount = 50;//����ֵ
    attackDistance = 4;//��������
    price = 1;//����
    speed = 0.65;//����
}

Hero* mlps::initmlps()
{
    Hero* mlps = static_cast<Hero*>(mlps::create());
    mlps->picturename = "./hero/mlps.png";
    mlps->picturenum = 1;
    mlps->heroAnimation(mlps->picturename, mlps->picturenum, mlps, speed, -1);
    return mlps;
}

void mlps::upLevel(Hero* mlps1)
{
    mlps1->blood = 900;//��ǰѪ��
    mlps1->maxBlood = 900;//����ֵ
    mlps1->level = 2; //�ȼ�
    mlps1->attack = 90; //������
    setScale(0.35f);
}

void mlps::Play()
{
    static Hero* enemy;
    static int attackNum = 0;
    auto lambda = [=](float dt) {
        enemy = getEnemyByDistance(this, false, this->ofPlayer);//����
        if (enemy != nullptr)
            this->update(this, enemy, dt);
        this->healthBar->setPercentage(((double)blood / (double)maxBlood) * 100);
        isDead();
    };
    this->schedule(lambda, 1 / 60.f, "mlpsMove");
    attackNum = 0;//��������
    auto lambdb = [=](float dt) {
        if (enemy != nullptr) {
            if (state == ATTACK) 
            {
                attackNum++;//��������+1
                bomb(enemy, attack);//��ը��Ч
                mlps::mlpsAttack(enemy, attackNum);
            }
        }
    };
    this->schedule(lambdb, 1 / speed, "mlpsAttack");    
}

void mlps::mlpsAttack(Hero* enemy, const int attackNum)
{
    int hurt = (int)(attack * enemy->attackRate);//�˺�ֵ
    blue += 30;
    if (blue == blueMax)//��������������
    {
        enemy->blood -= level == 1 ? 95 : 135;//�����ʵ�˺�
        blue = 0;
    }
    else
    {
        enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;//�����˺�
        enemy->magicPro > magicAmount ? enemy->blood -= 0 : enemy->blood -= magicAmount - enemy->magicPro;//ħ������
    }
    if (enemy->blood < 0)
        enemy->blood = 0;//�з�����
    //attack += attack / 2;//ÿ�ι���������50%���˺�
    
    //�ӳ�����
    auto lambda = [=](float dt) {
        enemy->blood -= level == 1 ? 95 : 135;//�����ʵ�˺�
    };
    enemy->scheduleOnce(lambda, 4, "mlpsTimeAttack");
}