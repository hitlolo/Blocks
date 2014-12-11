#include "CommandCenter.h"

CommandCenter* CommandCenter::_commandCenter = nullptr;

CommandCenter::CommandCenter()
{
	curSpeed = 0;
}

CommandCenter::~CommandCenter()
{
	CC_SAFE_DELETE(_commandCenter);
}

CommandCenter* CommandCenter::getInstance()
{
	if (_commandCenter == nullptr)
	{
		_commandCenter = new CommandCenter();
		return _commandCenter;
	}
	else
		return _commandCenter;
}

void CommandCenter::goState(GAME_STATE state)
{
	this->setCurState(state);
	switch (state)
	{
	case GAME_STATE::LOGO:
		toLogo();
		break;
	case GAME_STATE::MENU:
		toMenu();
		break;
	case GAME_STATE::GAME:
		toGame();
		break;
	case GAME_STATE::OVER:
		toOver();
		break;
	}
}

void   CommandCenter::toNextScene(Scene* scene)
{
	this->setCurScene(scene);
	TransitionScene *transition = TransitionFade::create(1.3f, scene);
	Director::getInstance()->replaceScene(transition);
}

void CommandCenter::toLogo()
{
	auto scene = GameLogo::createScene();
	this->toNextScene(scene);
}

void   CommandCenter::toMenu()
{
	auto scene = GameMenu::createScene();
	this->toNextScene(scene);
}

void   CommandCenter::toGame()
{
	auto scene = GameScene::createScene();
	this->toNextScene(scene);
}

void   CommandCenter::toOver()
{
	
	auto overLayer = OverLayer::create();
	this->getCurScene()->addChild(overLayer);
}