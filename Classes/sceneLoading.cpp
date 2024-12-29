// Refactored with Delegation Pattern and Lazy Loading Pattern
#include "sceneLoading.h"
#include "mainMenu/mainMenu.h"
#include "globalResSetting.h"
#include "ResourceManager.h"

sceneLoading* sceneLoading::createScene()
{
	return sceneLoading::create();
}

bool sceneLoading::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	totalResources = 16;
	loadedResources = 0;

	/**************MenuBackground**************/
	Sprite* bg = ResourceManager::CreateNewSprite("sceneLoading.png");
	if (bg == nullptr)
	{
		problemLoading("sceneLoading.png");
	}
	else
	{
		bg->setPosition(CENTER_WIN);
		bg->setScale(BG_SCALE);
		this->addChild(bg, 0);
	}

	loadingBar = ProgressTimer::create(ResourceManager::CreateNewSprite("loadingBar.png"));
	loadingBar->setScaleX(2.0);
	loadingBar->setType(ProgressTimer::Type::BAR);
	loadingBar->setMidpoint(Vec2(0, 0));
	loadingBar->setBarChangeRate(Vec2(1, 0));
	loadingBar->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 150));
	loadingBar->setPercentage(0);
	this->addChild(loadingBar, 1);

	loadResources();

	return true;

}

void sceneLoading::loadResources()
{
	auto callback = CC_CALLBACK_1(sceneLoading::loadingCallBack, this);

	ResourceManager::getTexture("./mainMenu/mainMenuBackground.png");
	ResourceManager::getTexture("./mainMenu/aboutBG.jpg");
	ResourceManager::getTexture("./gameScene/gameBackground.png");
	ResourceManager::getTexture("./player/avatar1.png");
	ResourceManager::getTexture("./player/avatar2.png");

	ResourceManager::getTexture("./hero/bqzs.png");
	ResourceManager::getTexture("./hero/ltzz.png");
	ResourceManager::getTexture("./hero/mlps.png");
	ResourceManager::getTexture("./hero/qxsq.png");
	ResourceManager::getTexture("./hero/snzx.png");
	ResourceManager::getTexture("./hero/tfns.png");
	ResourceManager::getTexture("./hero/wlshz.png");
	ResourceManager::getTexture("./hero/yn.png");

	ResourceManager::getTexture("./hero/bomb.png");
	ResourceManager::getTexture("./hero/lightning.png");
	ResourceManager::getTexture("./hero/dizzy.png");

	Director::getInstance()->getScheduler()->schedule([this](float) {
		loadingCallBack(nullptr);
		}, this, 0, totalResources, 0, false, "loading_scheduler");
}


void sceneLoading::loadingCallBack(Texture2D* texture)
{
	loadedResources++;
	loadingBar->setPercentage((float)loadedResources * 100 / totalResources);
	if (loadedResources == totalResources)
	{
		_director->pushScene(TransitionFade::create(2.0f, mainMenu::createScene()));
	}
}