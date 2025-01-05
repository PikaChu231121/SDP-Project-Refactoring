#pragma once
#include "ICommand.h"
#include "../mainMenu.h"
#include "../sceneAbout.h"
#include "../sceneName.h"
#include "../sceneSetting.h"

class SceneTransitionCommand : public ICommand
{
protected:
	cocos2d::Scene *targetScene;
	float transitionTime;

public:
	SceneTransitionCommand(cocos2d::Scene *scene, float time = 1.0f)
		: targetScene(scene), transitionTime(time) {}

	void execute() override
	{
		auto transition = cocos2d::TransitionFade::create(transitionTime, targetScene);
		cocos2d::Director::getInstance()->replaceScene(transition);
	}
};

class NewGameCommand : public ICommand
{
public:
	void execute() override
	{
		auto scene = sceneName::createScene();
		auto transition = cocos2d::TransitionFade::create(1.0f, scene);
		cocos2d::Director::getInstance()->replaceScene(transition);
	}
};

class SettingsCommand : public ICommand
{
public:
	void execute() override
	{
		auto scene = sceneSettings::createScene();
		auto transition = cocos2d::TransitionFade::create(1.0f, scene);
		cocos2d::Director::getInstance()->replaceScene(transition);
	}
};

class AboutCommand : public ICommand
{
public:
	void execute() override
	{
		auto scene = sceneAbout::createScene();
		auto transition = cocos2d::TransitionFade::create(1.0f, scene);
		cocos2d::Director::getInstance()->replaceScene(transition);
	}
};

class ExitCommand : public ICommand
{
public:
	void execute() override
	{
		cocos2d::Director::getInstance()->end();
	}
};