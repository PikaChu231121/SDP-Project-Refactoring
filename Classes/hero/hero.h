#ifndef _HERO_H_
#define _HERO_H_
#include"cocos2d.h"
#include"player/playerData.h"
#include "globalResSetting.h"
#include<string>
USING_NS_CC;

using std::string;

#define FREEZETIME 2
#define COLDDOWNTIME 1
#define ATTACK 1
#define FREEZE 0
#define PHYSICS 0
#define MAGIC 1
#define TANK 2

class Hero :public Sprite
{
public:
	//friend Battle<T>;
	string name, skillname;
	ProgressTimer* healthBar;
	int type = 0;
	string advice;//ǰ�����ź��Ž���
	int skillType = -1;
	int blood = 500;
	int maxBlood = 500;//Ѫ��
	int level = 1; //�ȼ�(Ŀǰֻ���������ȼ�)
	int attack = 50; //������
	int protect = 0;//����
	int magicPro = 10;//ħ��
	int state;//����״̬

	double speed = 0.6;//����
	double attackRate = 1;

	int blue = 0;//��ǰ����
	const int blueMax = 150;//�������ֵ
	double movespeed = 1;
	//////////////////////
	double attackDistance = 100;  //��������
	//������
	int ofPlayer = 0;     //�������
	int price = 1;    //������
	int soldMoney = price; //����������


public:
	string picturename;   //ͼƬ����
	int picturenum;       //ͼƬ����
	virtual void Play() {}//���ڸ�������Ľ���
	Hero() = default;
	bool isDead();//�ж��Ƿ�����
	void update(Hero* my, Hero* enemy, float dt);
	Hero* getEnemyByDistance(Hero* myHero, bool mode, bool isMyHero);
	bool isInAttackRange(Hero* myHero, Hero* enemyHero);
	bool isWin(playerData* myPlayer, playerData* opPlayer);
	int getBlood() { return blood; }
	int getMaxBlood() { return maxBlood; }
	void recover();
	bool connection(const playerData& myPlayerData);

	/*******************************12.30���(�������Ѿ���ӹ��ģ���type)*************************/

	float x = 0.f;
	float y = 0.f;


	float xTemp = x;
	float yTemp = y;
	//���ڼ�¼Ӣ�۽����ƶ�����ǰ�����꣬��ʼ����Ϊ��ԭʼ����һ��

	void set(float x1, float y1) { x = x1, y = y1; }
	void set(Point point) { x = point.x; y = point.y; }
	// ��Ӧ����������ʽ
	void setTempPosition() { xTemp = x; yTemp = y; }
	Point getTempPosition() { return Point(xTemp, yTemp); }   //��ý���ս��ʱ��λ��

	int getPrice() { return price; }
	void setPlayer(int player) {
		ofPlayer = player;
	}

	int getType() { return type; }//���ص���ÿ��Ӣ�۵����ͣ�playerData�е�enum��Ĭ��ÿ��Ӣ���Ѿ����˸��Ե�type

	/*******************************12.30���*************************/
	virtual void upLevel(Hero* hero) {};

	/*����װ���޸�����*/
	void changeAttackDistance(int value) { attackDistance += value; }
	void changePro(int value) { protect += value; }
	void changeSpeed(double value) { speed += value; }
	void changeAttack(int value) { attack += value; }
	//void equimentchange();
	void heroAnimation(string picturename, const int picturenum, Sprite* sprite, const double speed, const int loop);
	Node* Hero::createHealthBar(double percentage);

};

Hero* createHero(int name);
void bomb(Hero* enemy, int attack);
void lightning(Hero* enemy, const int hurt);
void Dizzy(Hero* enemy);
void proProtect(Hero* my);
void sevInjure(Hero* enemy);
void relProtect(Hero* enemy);
void immune(Hero* enemy);





#endif
