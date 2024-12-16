#ifndef _DATA_PLAYER_H_
#define _DATA_PLAYER_H_

#include "cocos2d.h"
#include "game/gameData.h"

#define maxHeroNum 20		// ������Ӣ������
USING_NS_CC;



class playerData : public Ref
{
private:
	/*********��һ�����Ϣ**********/
	int playerMaxHealth = 100;					//�������ֵ
	int playerHealth = playerMaxHealth;			//��ҵ�ǰ����ֵ
	int playerLevel = 1;						//��ҵȼ�
	int playerExp = 0;							//��Ҿ���ֵ
	int playerMoney = 10;						//��ҽ�Ǯ
	int expToLevelUp = 2;						//�������辭��ֵ
	void calExp();								//���㾭��ֵ
	bool playerHaveNewHero = false;				//����Ƿ�ӵ����Ӣ��

	friend class sceneGame;
	friend class layerPlayer;
	friend class layerHero;
	friend class aiPlayer;
	friend class layerSettings;
	friend class layerShop;

public:
	void playerHurt(int damageBlood) { this->playerHealth -= damageBlood; }		//�������
	void updateMoneyAndExp();													//���½�Ǯ�;���ֵ
	void playerInit();															//��ҳ�ʼ��

	/*********���Ӣ����Ϣ**********/
	ccArray* waitingArray = ccArrayNew(100);	//��ұ�ս����
	ccArray* battleArray = ccArrayNew(100);		//���ս������
	int heroNum[maxHeroNum] = { 0 };			//���ӵ��Ӣ������
	heroInfo heroForBuy[5];				//��ҿɹ���Ӣ��



	/*********���װ����Ϣ**********/
	//ccArray* equippedArray = ccArrayNew(100);		//���װ�����ݣ���װ����
	//ccArray* unequippedArray = ccArrayNew(100);		//���װ��������δװ����
	//int equippedNum = 0;							//�����װ��װ������

};

extern playerData myPlayerData;
extern playerData opPlayerData;


#endif // !_DATA_PLAYER_H_

