#include "GameMenu.h"

Scene* GameMenu::createScene()
{
	auto scene = Scene::create();

	auto layer = GameMenu::create();

	scene->addChild(layer);

	return scene;

}

bool GameMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	addMenu();

	return true;
}

void GameMenu::addMenu()
{
	Point originPoint = Director::getInstance()->getVisibleOrigin();
	Size  visibleSize = Director::getInstance()->getVisibleSize();
	auto menu = TMXTiledMap::create("menu.tmx");
	menu->setAnchorPoint(Point(0.5, 0.5));
	menu->setPosition(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 2);
	this->addChild(menu);
}

GameMenu::~GameMenu()
{
	this->removeAllChildrenWithCleanup(true);
}
