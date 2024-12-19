#include "game/layerHero.h"

layerHero* layerHero::createLayerHero()
{
	auto temp = layerHero::create();
	temp->retain();
	return temp;
}
void layerHero::playerArrayInit(ccArray* Array, int playerInfo)
{
	for (int i = 0; i < Array->num; i++)
	{
		auto currentHero = static_cast<Hero*>(Array->arr[i]);
		currentHero->setPosition(currentHero->getTempPosition());
		currentHero->set(currentHero->getTempPosition());

		HeroCreator* creator = getHeroCreator(currentHero->getType());
		if (creator) {
			Hero* newHero = creator->createHero();
			if (currentHero->level == 2)
				newHero->setScale(0.35f);

			creator->initializeHeroPosition(newHero, currentHero->getTempPosition(), playerInfo == 0);
			newHero->setPlayer(newHero->ofPlayer);

			if (ccArrayContainsObject(Array, currentHero))
				ccArrayRemoveObject(Array, currentHero);
			ccArrayInsertObjectAtIndex(Array, newHero, i);
			this->addChild(newHero);
			haveChess[pairReturn(currentHero->getTempPosition()).x][pairReturn(currentHero->getTempPosition()).y] = 1;

			delete creator;
		}
	}
}

bool layerHero::init()
{
	playerArrayInit(myPlayerData.waitingArray, 0);
	playerArrayInit(opPlayerData.battleArray, 1);
	playerArrayInit(myPlayerData.battleArray, 0);
	playerArrayInit(opPlayerData.battleArray, 1);

	return true;
}

void layerHero::update(float dt)
{
	for (int i = 0; i < myPlayerData.battleArray->num; i++) 
	{
		(static_cast<Hero*>(myPlayerData.battleArray->arr[i]))->isDead();
	}
	for (int i = 0; i < opPlayerData.battleArray->num; i++)
	{
		(static_cast<Hero*>(opPlayerData.battleArray->arr[i]))->isDead();
	}
}

void layerHero::heroUpgrade(playerData& pData)
{
	for (int i = 0; i < 18; i++)
	{
		if (pData.heroNum[i] >= 3)
		{
			Hero* heroesToUpgrade[3] = { nullptr };
			ccArray* sourceArrays[3] = {};
			int upgradeCount = 0;

			// 收集待升级的英雄  
			collectUpgradeableHeroes(pData, i, heroesToUpgrade, sourceArrays, upgradeCount);

			if (canUpgradeHeroes(heroesToUpgrade, upgradeCount, i))
			{
				HeroCreator* creator = getHeroCreator(i);
				if (creator) {
					Hero* upgrade_chess = creator->upgradeHero(heroesToUpgrade[0]);

					handleUpgradeProcess(pData, heroesToUpgrade, sourceArrays, upgrade_chess);
					delete creator;
					return;
				}
			}
		}
	}
}

/*PC_Player相关*/
void layerHero::aiShowWaitingArray()
{
	for (int i = 0; i < opPlayerData.waitingArray->num; i++)
	{
		static_cast<Hero*>(opPlayerData.waitingArray->arr[i])->setPosition(chessMap[7][i].x, chessMap[7][i].y);
		static_cast<Hero*>(opPlayerData.waitingArray->arr[i])->set(chessMap[7][i].x, chessMap[7][i].y);
	}
}
void layerHero::aiShowBattleArray()
{
	/*位置初始化*/
	for (int i = 0; i < opPlayerData.battleArray->num; i++)
	{
		if (i >= 0 && i <= 7) // 每行八个
		{
			static_cast<Hero*>(opPlayerData.battleArray->arr[i])->setPosition(chessMap[6][i].x, chessMap[6][i].y);
			static_cast<Hero*>(opPlayerData.battleArray->arr[i])->set(chessMap[6][i].x, chessMap[6][i].y);
			haveChess[6][i] = 1;
			if (globalGameData->getGameTurn() == 1) {
				this->addChild(static_cast<Hero*>(opPlayerData.battleArray->arr[i]));
			}
			else {
				//static_cast<Hero*>(opPlayerData.battleArray->arr[1])->removeFromParent();
			}
			
		}
		else if (i >= 8 && i <= 15)
		{
			static_cast<Hero*>(opPlayerData.battleArray->arr[i])->setPosition(chessMap[5][i - 8].x, chessMap[5][i - 8].y);
			static_cast<Hero*>(opPlayerData.battleArray->arr[i])->set(chessMap[5][i - 8].x, chessMap[5][i - 8].y);
			haveChess[5][i - 8] = 1;
			if (globalGameData->getGameTurn() == 1) {
				this->addChild(static_cast<Hero*>(opPlayerData.battleArray->arr[i - 8]));
			}
		}
		else if (i >= 16 && i <= 23)
		{
			static_cast<Hero*>(opPlayerData.battleArray->arr[i])->setPosition(chessMap[4][i - 16].x, chessMap[4][i - 16].y);
			static_cast<Hero*>(opPlayerData.battleArray->arr[i])->setPosition(chessMap[4][i - 16].x, chessMap[4][i - 16].y);
			haveChess[4][i - 16] = 1;
			if (globalGameData->getGameTurn() == 1) {
				this->addChild(static_cast<Hero*>(opPlayerData.battleArray->arr[i - 16]));
			}
		}
		// 只有最多三行
	}

}

float layerHero::calDistance(Hero* h1, Hero* h2)
{
	return sqrt(pow((h1->getPosition().x - h2->getPosition().x), 2)
		+ pow((h1->getPosition().y - h2->getPosition().y), 2));
}
float layerHero::calDistance(Point p1, Point p2)
{
	return sqrt(pow((p1.x - p2.x), 2)
		+ pow((p1.y - p2.y), 2));
}

void layerHero::collectUpgradeableHeroes(playerData& pData, int heroType, Hero* temp[3], ccArray* tempArray[3], int& count)
{
	// 从等待区域收集  
	collectFromArray(pData.waitingArray, heroType, temp, tempArray, count);

	// 如果还需要,从战斗区域收集  
	if (count < 3) {
		collectFromArray(pData.battleArray, heroType, temp, tempArray, count);
	}
}

void layerHero::collectFromArray(ccArray* array, int heroType, Hero* temp[3], ccArray* tempArray[3], int& count)
{
	for (int j = 0; j < array->num && count < 3; j++) {
		Hero* hero = static_cast<Hero*>(array->arr[j]);
		if (hero->getType() == heroType) {
			temp[count] = hero;
			tempArray[count] = array;
			count++;
		}
	}
}

bool layerHero::canUpgradeHeroes(Hero* temp[3], int count, int heroType)
{
	return temp[0] != nullptr && temp[1] != nullptr && temp[2] != nullptr
		&& count == 3
		&& temp[0]->getType() == heroType
		&& temp[1]->getType() == heroType
		&& temp[2]->getType() == heroType;
}

void layerHero::handleUpgradeProcess(playerData& pData, Hero* temp[3], ccArray* tempArray[3], Hero* upgrade_chess)
{
	pData.heroNum[temp[0]->getType()] -= 3;

	for (int k = 0; k < 3; k++) {
		haveChess[pairReturn(temp[k]->getTempPosition()).x]
			[pairReturn(temp[k]->getTempPosition()).y] = 0;
		temp[k]->retain();
		temp[k]->removeFromParent();
		if (ccArrayContainsObject(tempArray[k], temp[k])) {
			ccArrayRemoveObject(tempArray[k], temp[k]);
		}
	}

	ccArrayAppendObject(pData.waitingArray, upgrade_chess);
	pData.playerHaveNewHero = 1;
}


