#include "layerShop.h"

layerShop::layerShop() {
	shop();
}
layerShop* layerShop::createLayerShop() {
	auto tmp = layerShop::create();
	tmp->retain();
	return tmp;
}
bool layerShop::init() {
	if (!Layer::init()) {
		return false;
	}
	srand(time(NULL));
	return true;
}
bool layerShop::canBuy(int x, playerData& playerData) {
	int sum = 0;
	if (playerData.heroForBuy[x].cost > myPlayerData.playerMoney) {
		auto tmp = Label::createWithTTF("Not enough money!", "fonts/arial.ttf", 36);
		this->addChild(tmp);
		tmp->setTextColor(Color4B::WHITE);
		tmp->setPosition(800, 400);
		auto fade = FadeOut::create(2.0f);
		tmp->runAction(fade);
		return false;
	}
	for (int i = 0; i < CHESS_IN_A_ROW; i++) {
		sum += haveChess[0][i];
	}
	if (sum == 8) {
		auto tmp = Label::createWithTTF("You have too many heroes!", "fonts/arial.ttf", 36);
		this->addChild(tmp);
		tmp->setTextColor(Color4B::WHITE);
		tmp->setPosition(800, 400);
		auto fade = FadeOut::create(2.0f);
		tmp->runAction(fade);
		return false;
	}
	return true;
}
void layerShop::openShop() {
	openShopButton = MenuItemImage::create("./shop/openShop.png", "./shop/openShop.png",
		CC_CALLBACK_1(layerShop::openLayer, this));
	auto Open = Menu::create(openShopButton, nullptr);
	Open->setPosition(-250, 150);
	Open->setScale(0.1f);
	this->addChild(Open, 1);
}

void layerShop::closeShop() {
	closeShopButton = MenuItemImage::create("./shop/closeShop.png", "./shop/closeShop.png",
		CC_CALLBACK_1(layerShop::closeLayer, this));
	auto Close = Menu::create(closeShopButton, nullptr);
	Close->setPosition(-250, 200);
	Close->setScale(0.1f); 
	this->addChild(Close, 1);
}

void layerShop::openLayer(cocos2d::Ref* pSender) {
	subLayer->setPosition(650, 350);
	if (openShopButton != nullptr) {
		openShopButton->setVisible(false);
	}
	if (closeShopButton != nullptr) {
		closeShopButton->setVisible(true);
	}
}

void layerShop::closeLayer(cocos2d::Ref* pSender) 
{
	subLayer->setPosition(20000, 20000);
	openShop();
	if (openShopButton != nullptr) {
		openShopButton->setVisible(true);
	}
	if (closeShopButton != nullptr) {
		// 隐藏按钮
		closeShopButton->setVisible(false);
	}
}

void layerShop::heroShop(int i) 
{
	auto label1 = Label::createWithTTF(heroValue[myPlayerData.heroForBuy[i].cost], "fonts/arial.ttf", 28);
	subLayer->addChild(label1);
	label1->setPosition(790 - 350 * (4 - i), 420);
}

void layerShop::cover(float x, float y) {
	auto cover = Sprite::create("./shop/cover.png");
	subLayer->addChild(cover, 3);
	cover->setPosition(x, y);
}

void layerShop::buyHero(int index) {
	if (myPlayerData.heroForBuy[index].buy == false) {
		HeroCreator* creator = getHeroCreator(myPlayerData.heroForBuy[index].id);
		if (creator) {
			if (creator->canPurchaseHero(myPlayerData.heroForBuy[index].cost, myPlayerData)) {
				Hero* hero = creator->createHero();
				creator->addHeroToWaitingList(hero, myPlayerData);

				myPlayerData.heroForBuy[index].buy = true;
				myPlayerData.playerMoney -= myPlayerData.heroForBuy[index].cost;
				cover(790 - 350 * (4 - index), 250); // 使用 index 计算遮罩位置

				delete creator;
			}
		}
	}
}

void layerShop::shop() {
	static int x, y;
	x = 650;
	y = 350;
	subLayer = Layer::create();
	subLayer->setPosition(x,y);
	subLayer->setScale(0.6f);
	this->addChild(subLayer, 2);

	/*-------------------set background----------------------*/
	auto sprite = Sprite::create("./shop/backgroundofshop.png");
	sprite->setPosition(80, 250);
	subLayer->addChild(sprite);

	/*-------------------set label-------------------------*/
	auto label = Label::createWithTTF("SHOP", "fonts/Marker Felt.ttf", 24);
	label->setPosition(80, 490);
	subLayer->addChild(label);
	/*------------------refresh----------------------------*/
	auto Refresh = MenuItemImage::create("./shop/refresh.png", "./shop/refresh.png",
		CC_CALLBACK_1(layerShop::refresh1, this));
	auto reFresh = Menu::create(Refresh, nullptr);
	reFresh->setPosition(110, 570);
	subLayer->addChild(reFresh, 1);
	refresh(myPlayerData);

	/*------------------buy----------------------------*/
	for (int i = 0; i < 5; i++) {
		heroShop(i);

		// 创建购买按钮，使用lambda表达式绑定购买函数和索引
		auto buyButton = MenuItemImage::create(
			myPlayerData.heroForBuy[i].picName,
			myPlayerData.heroForBuy[i].picName,
			[this, i](cocos2d::Ref* pSender) {
				buyHero(i);
			}
		);

		auto buyMenu = Menu::create(buyButton, nullptr);
		subLayer->addChild(buyMenu, 1);
		buyMenu->setPosition(790 - 350 * (4 - i), 250);
		buyButton->setScale(0.5f);
	}

	/*----------------------close store-----------------*/
	closeShop();

	/*-----------------------reset buy status-----------*/
	for (int i = 0; i < 5; i++)
	{
		myPlayerData.heroForBuy[i].buy = false;
	}
}

void layerShop::refresh1(cocos2d::Ref* pSender) {
	srand(time(NULL));
	if (myPlayerData.playerMoney >= 2)
	{
		myPlayerData.playerMoney -= 2;
		subLayer->removeAllChildren();
		shop();
	}
	else
	{
		auto label = Label::createWithTTF("Not enough money!", "fonts/arial.ttf", 36);
		this->addChild(label);
		label->setTextColor(Color4B::WHITE);
		label->setPosition(800, 400);
		auto fade = FadeOut::create(2.0f);
		label->runAction(fade);
		return;
	}
}

void layerShop::refresh(playerData& playerdata) {
	srand(time(NULL));
	for (int i = 0; i < 5; i++)
	{
		int tmp = rand() % 8 + 1;
		myPlayerData.heroForBuy[i].buy = false;
		myPlayerData.heroForBuy[i].id = heroList[tmp - 1].id;
		myPlayerData.heroForBuy[i].picName = heroList[tmp - 1].picName;
		myPlayerData.heroForBuy[i].cost = heroList[tmp - 1].cost;
	}
}